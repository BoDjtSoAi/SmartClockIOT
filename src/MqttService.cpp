#include "MqttService.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <RTClib.h>
#include <Preferences.h>
#include "UI/ui.h"

#define BUZZER_PIN 4
#define SQW_PIN 5

unsigned long buzzerLastTime = 0;
int buzzerBeepCount = 0;
bool buzzerState = false;

// WiFi reconnect
unsigned long lastTimeConnectWifi = 0;
const unsigned long wifiReconnectInterval = 5000; // 5 seconds

volatile bool alarmFlag = false;

// Hàm xử lý ngắt (ISR)
void IRAM_ATTR onAlarmISR()
{
  alarmFlag = true;
}

struct AlarmConfig
{
  int hour = -1;
  int minute = -1;
  bool activeDays[7]; // 0=CN, 1=T2, ..., 6=T7
  bool enabled = false;
};

AlarmConfig alarm1;

// MQTT Broker
const char *mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// MQTT Topics
const char *topic_sub_out_weather = "out/weather";
const char *topic_sub_out_air_quality = "out/air-quality";
const char *topic_sub_set_clock = "set/clock";
const char *topic_arlarm_set = "set/alarm";

// Shared data (Core 0 -> Core 1)
String weatherMessage;
String airQualityMessage;
String clockMessage;
String alarmMessage;

// Shared weather data for UI
char currentWeatherDesc[50] = "N/A";
float currentTemp = 0.0;

bool newWeather = false;
bool newAir = false;
bool newClock = false;
bool newAlarm = false;

// MQTT & System
WiFiClient espClient;
PubSubClient client(espClient);
// rtc is define in main.cpp --> use extern
extern RTC_DS3231 rtc;
Preferences preferences;

// FreeRTOS mutex for MQTT data
SemaphoreHandle_t mqttMutex;

/*
 *  MQTT CALLBACK (CORE 0)
 *  - Chỉ copy dữ liệu
 *  - KHÔNG xử lý JSON
 *  - KHÔNG LVGL
 */
void callback(char *topic, byte *payload, unsigned int length)
{

  static char buffer[512];
  if (length >= sizeof(buffer))
    return;

  memcpy(buffer, payload, length);
  buffer[length] = '\0';

  if (xSemaphoreTake(mqttMutex, 0) == pdTRUE)
  {

    if (strcmp(topic, topic_sub_out_weather) == 0)
    {
      weatherMessage = buffer;
      newWeather = true;
    }
    else if (strcmp(topic, topic_sub_out_air_quality) == 0)
    {
      airQualityMessage = buffer;
      newAir = true;
    }
    else if (strcmp(topic, topic_sub_set_clock) == 0)
    {
      clockMessage = buffer;
      newClock = true;
    }
    else if (strcmp(topic, topic_arlarm_set) == 0)
    {
      alarmMessage = buffer;
      newAlarm = true;
    }

    xSemaphoreGive(mqttMutex);
  }
}

void mqttTask(void *parameter)
{
  for (;;)
  {

    if (!client.connected())
    {

      if (WiFi.status() != WL_CONNECTED)
      {
        vTaskDelay(pdMS_TO_TICKS(10));
        continue;
      }

      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);

      if (client.connect(clientId.c_str()))
      {
        client.subscribe(topic_sub_out_weather);
        client.subscribe(topic_sub_out_air_quality);
        client.subscribe(topic_sub_set_clock);
        client.subscribe(topic_arlarm_set);
        Serial.println("[MQTT] Connected & Subscribed");
      }
    }

    client.loop();
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

// Weather data process
void processWeatherInformation(const String &message)
{

  StaticJsonDocument<512> doc;
  if (deserializeJson(doc, message))
  {
    return;
  }

  const char *city = doc["city"];
  float temp = doc["temp"];
  float humidity = doc["humidity"];
  const char *desc = doc["desc"];

  // Store for alarm screen
  currentTemp = temp;
  strncpy(currentWeatherDesc, desc, sizeof(currentWeatherDesc) - 1);
  currentWeatherDesc[sizeof(currentWeatherDesc) - 1] = '\0';

  // Change to print in lvgl
  // Serial.print("Khu vực: ");
  // Serial.println(city);
  // Serial.print("Nhiệt độ: ");
  // Serial.println(temp);
  // Serial.print("Độ ẩm: ");
  // Serial.println(humidity);
  // Serial.print("Mô tả: ");
  // Serial.println(desc);

  if (uic_cityName)
  {
    lv_label_set_text(uic_cityName, city);
  }
  
  if (uic_weatherTemp)
  {
    String tempStr = String(temp, 1) + " 'C";
    lv_label_set_text(uic_weatherTemp, tempStr.c_str());
  }

  if (uic_weatherStatus)
  {
    lv_label_set_text(uic_weatherStatus, desc);
  }
}

// Air quality data process
void processAirQualityInformation(const String &message)
{

  StaticJsonDocument<256> doc;
  if (deserializeJson(doc, message))
  {
    return;
  }

  const char *city = doc["city"];
  int aqi = doc["aqi"];
  float co = doc["co"];
  float no = doc["no"];
  float pm2_5 = doc["pm2_5"];
  float pm10 = doc["pm10"];

  // Change to print in lvgl
  Serial.print("Khu vực: ");
  Serial.println(city);
  Serial.print("AQI: ");
  Serial.println(aqi);
}

// Set RTC from MQTT message
void setClockFromMQTT(const String &message)
{

  StaticJsonDocument<512> doc;
  if (deserializeJson(doc, message))
  {
    return;
  }

  rtc.adjust(DateTime(
      doc["year"],
      doc["month"],
      doc["day"],
      doc["hour"],
      doc["minute"],
      doc["second"]));

  Serial.println("[RTC] Time updated from MQTT");
}

// Set Alarm from MQTT message
void setAlarmFromMQTT(const String &message)
{
  StaticJsonDocument<256> doc;
  if (deserializeJson(doc, message))
  {
    return;
  }

  alarm1.hour = doc["hour"];
  alarm1.minute = doc["minute"];
  alarm1.enabled = true;
  for (int i = 0; i < 7; i++)
    alarm1.activeDays[i] = false;

  // Set active days
  JsonArray days = doc["days"];
  for (int d : days)
  {
    if (d >= 0 && d <= 6)
    {
      alarm1.activeDays[d] = true;
    }
  }

  rtc.clearAlarm(1);
  rtc.setAlarm1(DateTime(2020, 1, 1, alarm1.hour, alarm1.minute, 0), DS3231_A1_Hour);
}

void dismissAlarm()
{
  // Turn off alarm logic
  alarm1.enabled = false; 
  buzzerBeepCount = 0;
  digitalWrite(BUZZER_PIN, LOW);
  rtc.clearAlarm(1);

  // Switch back to main screen
  lv_disp_load_scr(ui_mainTime);
}

//-----------------------------------kiểm tra và xử lý khi có báo thức---------------------------------//
void checkAlarmTrigger()
{
  // Khi có ngắt từ DS3231- SQW pin
  if (alarmFlag)
  {
    alarmFlag = false;
    DateTime now = rtc.now();
    if (alarm1.enabled && alarm1.activeDays[now.dayOfTheWeek()])
    {
      // Switch to alarm screen instead of buzzer
      lv_disp_load_scr(ui_alarmRang);

      // Feed data to the screen
      // Format date: "Monday, January 15"
      const char* daysOfWeek[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
      const char* months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
      char dateStr[50];
      snprintf(dateStr, sizeof(dateStr), "%s, %s %d", daysOfWeek[now.dayOfTheWeek()], months[now.month() - 1], now.day());
      if(uic_dowDate) lv_label_set_text(uic_dowDate, dateStr);

      // Format weather: "38'C Sunny"
      char tempStr[50];
      snprintf(tempStr, sizeof(tempStr), "%.0f'C %s", currentTemp, currentWeatherDesc);
      if(uic_temp) lv_label_set_text(uic_temp, tempStr);

      // Format time: "HH:MM"
      char timeStr[6];
      snprintf(timeStr, sizeof(timeStr), "%02d:%02d", now.hour(), now.minute());
      if(uic_alarmTimeBig) lv_label_set_text(uic_alarmTimeBig, timeStr);
    }
    rtc.clearAlarm(1);
  }
}

void System_Handle_Buzzer()
{
  if (buzzerBeepCount <= 0)
    return;
  unsigned long currentMillis = millis();

  if (currentMillis - buzzerLastTime >= 100)
  {
    buzzerLastTime = currentMillis;
    buzzerState = !buzzerState;
    digitalWrite(BUZZER_PIN, buzzerState ? HIGH : LOW);

    buzzerBeepCount--;
    if (buzzerBeepCount <= 0)
    {
      digitalWrite(BUZZER_PIN, LOW);
      buzzerState = false;
    }
  }
}

void System_Init()
{
  // Alarm Buzzer & SQW pin
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  pinMode(SQW_PIN, INPUT_PULLUP);

  rtc.writeSqwPinMode(DS3231_OFF);
  rtc.disable32K();
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);

  // Cài đặt ngắt cho chân SQW khi có tín hiệu từ DS3231 thì gọi hàm onAlarmISR
  attachInterrupt(digitalPinToInterrupt(SQW_PIN), onAlarmISR, FALLING);
  // Reserve heap to avoid fragmentation
  weatherMessage.reserve(512);
  airQualityMessage.reserve(256);
  clockMessage.reserve(256);

  // Mutex
  mqttMutex = xSemaphoreCreateMutex();

  // WiFi
  WiFi.setSleep(false);
  WiFi.begin("Mahihi", "09092004");

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 50) // 15 seconds timeout
  {
    delay(300);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("\n[System] WiFi Connected");
  }
  else
  {
    Serial.println("\n[System] WiFi Connection Failed");
  }

  // MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Create MQTT task on Core 0
  xTaskCreatePinnedToCore(
      mqttTask,
      "MQTT_Task",
      8192,
      NULL,
      1,
      NULL,
      0);

  Serial.println("[System] Init done");
}

void System_Handle_Loop()
{

  // WEATHER
  String wMsg;
  bool wFlag = false;

  if (xSemaphoreTake(mqttMutex, 0) == pdTRUE)
  {
    if (newWeather)
    {
      wMsg = weatherMessage;
      newWeather = false;
      wFlag = true;
    }
    xSemaphoreGive(mqttMutex);
  }
  if (wFlag)
    processWeatherInformation(wMsg);

  // AIR
  String aMsg;
  bool aFlag = false;

  if (xSemaphoreTake(mqttMutex, 0) == pdTRUE)
  {
    if (newAir)
    {
      aMsg = airQualityMessage;
      newAir = false;
      aFlag = true;
    }
    xSemaphoreGive(mqttMutex);
  }
  if (aFlag)
    processAirQualityInformation(aMsg);

  // CLOCK
  String cMsg;
  bool cFlag = false;

  if (xSemaphoreTake(mqttMutex, 0) == pdTRUE)
  {
    if (newClock)
    {
      cMsg = clockMessage;
      newClock = false;
      cFlag = true;
    }
    xSemaphoreGive(mqttMutex);
  }
  if (cFlag)
    setClockFromMQTT(cMsg);

  // ALARM
  String alarmMsg;
  bool alarmFlag = false;
  if (xSemaphoreTake(mqttMutex, 0) == pdTRUE)
  {
    if (newAlarm)
    {
      alarmMsg = alarmMessage;
      newAlarm = false;
      alarmFlag = true;
    }
    xSemaphoreGive(mqttMutex);
  }
  if (alarmFlag)
    setAlarmFromMQTT(alarmMsg);

  checkAlarmTrigger();
  System_Handle_Buzzer();

  if (WiFi.status() != WL_CONNECTED)
  {
    unsigned long currentMillis = millis();
    if (currentMillis - lastTimeConnectWifi >= wifiReconnectInterval)
    {
      lastTimeConnectWifi = currentMillis;
      WiFi.disconnect();
      WiFi.begin("Mahihi", "09092004");
    }
  }
}
