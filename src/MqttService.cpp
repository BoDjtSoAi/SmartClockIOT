#include "MqttService.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <RTClib.h>
#include <Preferences.h>
#include "UI/ui.h"

// WiFi credentials
String global_ssid = "";
String global_password = "";

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
  int year = 0;
  int month = 0;
  int day = 0;
  int hour = 0;
  int minute = 0;
  bool enabled = false;
};

AlarmConfig alarm1;

static lv_calendar_date_t highlighted_days[1];

void updateCalendarHighlights() {
    if (uic_CalendarMain == NULL) return;
    if (!lv_obj_is_valid(uic_CalendarMain)) return; // Extra safety check

    if (alarm1.enabled) {
        highlighted_days[0].year = alarm1.year;
        highlighted_days[0].month = alarm1.month;
        highlighted_days[0].day = alarm1.day;
        lv_calendar_set_highlighted_dates(uic_CalendarMain, highlighted_days, 1);
    } else {
        lv_calendar_set_highlighted_dates(uic_CalendarMain, highlighted_days, 0);
    }
}

// MQTT Broker
const char *mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// MQTT Topics
const char *topic_sub_out_weather = "out/weather";
const char *topic_sub_out_air_quality = "out/air-quality";
const char *topic_sub_set_clock = "set/clock";
const char *topic_arlarm_set = "set/alarm";
const char *topic_delete_alarm = "delete/alarm";

// Shared data (Core 0 -> Core 1)
String weatherMessage;
String airQualityMessage;
String clockMessage;
String alarmMessage;
String deleteAlarmMessage;

// Shared weather data for UI
char currentWeatherDesc[50] = "N/A";
float currentTemp = 0.0;

bool newWeather = false;
bool newAir = false;
bool newClock = false;
bool newAlarm = false;
bool newDeleteAlarm = false;

// MQTT & System
WiFiClient espClient;
PubSubClient client(espClient);
// rtc is define in main.cpp --> use extern
extern RTC_DS3231 rtc;
Preferences preferences;
Preferences wifiPreferences;

void saveWifiConfig(const char* ssid, const char* pwd) {
    wifiPreferences.begin("wifi", false);
    wifiPreferences.putString("ssid", ssid);
    wifiPreferences.putString("password", pwd);
    wifiPreferences.end();
    
    global_ssid = String(ssid);
    global_password = String(pwd);
    Serial.println("[WiFi] Config saved");
}

void loadWifiConfig() {
    wifiPreferences.begin("wifi", true);
    global_ssid = wifiPreferences.getString("ssid", "");
    global_password = wifiPreferences.getString("password", "");
    wifiPreferences.end();
    
    if (global_ssid == "") {
        Serial.println("[WiFi] No saved config, using defaults");
        // Optional: Set default fallback if needed
    } else {
        Serial.println("[WiFi] Config loaded: " + global_ssid);
    }
}

#ifdef __cplusplus
extern "C" {
#endif

void loadWifiSettingsUI() {
    // Ensure we have the latest config
    if (global_ssid == "") {
        loadWifiConfig();
    }
    
    if (ui_ssid) {
        lv_textarea_set_text(ui_ssid, global_ssid.c_str());
    }
    if (ui_ssidPwd) {
        lv_textarea_set_text(ui_ssidPwd, global_password.c_str());
    }
}

void saveWifiSettingsC() {
    if (ui_ssid && ui_ssidPwd) {
        const char* ssid = lv_textarea_get_text(ui_ssid);
        const char* pwd = lv_textarea_get_text(ui_ssidPwd);
        saveWifiConfig(ssid, pwd);
        
        // Optional: Trigger reconnect
        WiFi.disconnect();
        WiFi.begin(global_ssid.c_str(), global_password.c_str());
    }
}

#ifdef __cplusplus
}
#endif

void saveAlarmConfig() {
  // Use a small delay to ensure stability before flash operations
  delay(10);
  if (!preferences.begin("alarm", false)) {
      Serial.println("[System] Failed to open preferences for saving");
      return;
  }
  preferences.putInt("year", alarm1.year);
  preferences.putInt("month", alarm1.month);
  preferences.putInt("day", alarm1.day);
  preferences.putInt("hour", alarm1.hour);
  preferences.putInt("minute", alarm1.minute);
  // Use putInt instead of putBool for better compatibility
  preferences.putInt("enabled", alarm1.enabled ? 1 : 0);
  preferences.end();
  delay(10); // Allow flash write to settle
  Serial.println("[System] Alarm config saved");
}

void loadAlarmConfig() {
  preferences.begin("alarm", true);
  alarm1.year = preferences.getInt("year", 0);
  alarm1.month = preferences.getInt("month", 0);
  alarm1.day = preferences.getInt("day", 0);
  alarm1.hour = preferences.getInt("hour", 0);
  alarm1.minute = preferences.getInt("minute", 0);
  // Read as int
  alarm1.enabled = (preferences.getInt("enabled", 0) == 1);
  preferences.end();

  // Restore RTC alarm if enabled
  if (alarm1.enabled) {
      DateTime now = rtc.now();
      // Basic validation
      if (alarm1.year < 2000 || alarm1.month < 1 || alarm1.month > 12 || alarm1.day < 1 || alarm1.day > 31) {
          alarm1.enabled = false;
      } else {
          DateTime dtAlarm(alarm1.year, alarm1.month, alarm1.day, alarm1.hour, alarm1.minute, 0);
          if (dtAlarm.unixtime() <= now.unixtime()) {
              Serial.println("[System] Loaded alarm is in the past. Disabling.");
              alarm1.enabled = false;
          }
      }
  }

  if (alarm1.enabled) {
      rtc.disableAlarm(1);
      rtc.clearAlarm(1);
      // Set hardware alarm for Day, Hour, Minute
      rtc.setAlarm1(DateTime(alarm1.year, alarm1.month, alarm1.day, alarm1.hour, alarm1.minute, 0), DS3231_A1_Date);
      updateCalendarHighlights();
  }
}

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
    else if (strcmp(topic, topic_delete_alarm) == 0)
    {
      deleteAlarmMessage = buffer;
      newDeleteAlarm = true;
    }

    xSemaphoreGive(mqttMutex);
  }
}

void mqttTask(void *parameter)
{
  // Non-blocking loop: ensure WiFi is actively retried here and MQTT connects when possible.
  static unsigned long lastWiFiAttempt = 0;
  for (;;)
  {
    // If WiFi is disconnected, try to (re)start the connection periodically.
    if (WiFi.status() != WL_CONNECTED)
    {
      unsigned long now = millis();
      if (now - lastWiFiAttempt >= wifiReconnectInterval)
      {
        lastWiFiAttempt = now;
        Serial.println("[WIFI] Not connected, attempting WiFi.begin()...");
        WiFi.disconnect();
        if (global_ssid != "") {
            WiFi.begin(global_ssid.c_str(), global_password.c_str());
        }
      }
      // Wait a bit and continue; MQTT cannot connect without WiFi.
      vTaskDelay(pdMS_TO_TICKS(200));
      continue;
    }

    if (!client.connected())
    {
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);

      if (client.connect(clientId.c_str()))
      {
        client.subscribe(topic_sub_out_weather);
        client.subscribe(topic_sub_out_air_quality);
        client.subscribe(topic_sub_set_clock);
        client.subscribe(topic_arlarm_set);
        client.subscribe(topic_delete_alarm);
        Serial.println("[MQTT] Connected & Subscribed");
      }
      else
      {
        // Back off a bit before retrying MQTT connect
        vTaskDelay(pdMS_TO_TICKS(500));
        continue;
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
  if (uic_percent1)
  {
    String humStr = String(humidity, 1) + "%";
    lv_label_set_text(uic_percent1, humStr.c_str());
  }

  if (uic_cityName)
  {
    lv_label_set_text(uic_cityName, city);
  }

  if (uic_cityNameSetting)
  {
    lv_label_set_text(uic_cityNameSetting, city);
  }

if (uic_cityNameTemp)
{
    String upperCity = String(city);
    upperCity.toUpperCase();    
    lv_label_set_text(uic_cityNameTemp, upperCity.c_str());
}
  
  if (uic_weatherTemp)
  {
    String tempStr = String(temp, 0) + "'C";
    lv_label_set_text(uic_weatherTemp, tempStr.c_str());
  }

  if (uic_tempOutdoor1)
  {
    String tempStr = String(temp, 0) + "'C";
    lv_label_set_text(uic_tempOutdoor1, tempStr.c_str());
  }

  if (uic_weatherStatus)
  {
    lv_label_set_text(uic_weatherStatus, desc);
  }

  if (uic_description1)
  {
    lv_label_set_text(uic_description1, desc);
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
  if (uic_AQInumber1)
  {
    String aqiStr = String(aqi);
    lv_label_set_text(uic_AQInumber1, aqiStr.c_str());
  }

  if (uic_pm25Number1)
  {
    String pm25Str = String(pm2_5, 1) + " ug/m3";
    lv_label_set_text(uic_pm25Number1, pm25Str.c_str());
  }


  if (uic_pm10Number1)
  {
    String pm10Str = String(pm10, 1) + " ug/m3";
    lv_label_set_text(uic_pm10Number1, pm10Str.c_str());
  }

  if (uic_NONumber1)
  {
    String noStr = String(no, 1) + " ug/m3";
    lv_label_set_text(uic_NONumber1, noStr.c_str());
  }

  if (uic_CONumber1)
  {
    String coStr = String(co, 1) + " ug/m3";
    lv_label_set_text(uic_CONumber1, coStr.c_str());
  }
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

#ifdef __cplusplus
extern "C" {
#endif
void dismissAlarm()
{
  // Turn off alarm logic
  alarm1.enabled = false; 
  saveAlarmConfig();
  buzzerBeepCount = 0;
  digitalWrite(BUZZER_PIN, LOW);
  rtc.clearAlarm(1);
  
  // Switch back to main screen
  /*if (!ui_mainTime) {
      ui_mainTime_screen_init();
  }
  lv_disp_load_scr(ui_mainTime);
  */
  
  if (uic_CalendarMain)
  updateCalendarHighlights();
}
#ifdef __cplusplus
}
#endif

//-----------------------------------kiểm tra và xử lý khi có báo thức---------------------------------//
void checkAlarmTrigger()
{
  // Khi có ngắt từ DS3231- SQW pin
  if (alarmFlag)
  {
    alarmFlag = false;
    rtc.clearAlarm(1); // Clear hardware flag immediately

    if (!alarm1.enabled) return;

    DateTime now = rtc.now();
    // Safety check for invalid RTC data
    if (now.month() < 1 || now.month() > 12) return;

    // Check full date match (Year, Month, Day, Hour, Minute)
    // Note: Hardware alarm matches Day, Hour, Minute. We verify Month and Year here.
    if (now.year() == alarm1.year && now.month() == alarm1.month && now.day() == alarm1.day && 
        now.hour() == alarm1.hour && now.minute() == alarm1.minute)
    {
      // Switch to alarm screen instead of buzzer
      if (!ui_alarmRang) {
          ui_alarmRang_screen_init();
      }
      lv_disp_load_scr(ui_alarmRang);
      buzzerBeepCount = 50; // Beep for 5 seconds

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
  
  loadAlarmConfig(); // Load alarm from flash
  loadWifiConfig();  // Load WiFi config from flash

  // Reserve heap to avoid fragmentation
  weatherMessage.reserve(512);
  airQualityMessage.reserve(256);
  clockMessage.reserve(256);

  // Mutex
  mqttMutex = xSemaphoreCreateMutex();

  // WiFi
  WiFi.setSleep(false);
  loadWifiConfig(); // Load WiFi credentials
  if (global_ssid != "") {
      WiFi.begin(global_ssid.c_str(), global_password.c_str());
  }
  // Start WiFi connection in non-blocking mode and continue boot.
  // The mqttTask() will handle reconnects and final subscription when WiFi is available.
  Serial.println("[System] WiFi begin (non-blocking)");

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

void updateAlarmUI() {
    if (!uic_alarmTime || !uic_alarmStatus) return;

    if (!alarm1.enabled) {
        lv_label_set_text(uic_alarmTime, "--:--");
        lv_label_set_text(uic_alarmStatus, "OFF");
        rtc.clearAlarm(1);
        rtc.disableAlarm(1);
        return;
    }

    lv_label_set_text_fmt(uic_alarmTime, "%02d:%02d", alarm1.hour, alarm1.minute);

    DateTime now = rtc.now();
    // Check if alarm is today
    if (now.year() == alarm1.year && now.month() == alarm1.month && now.day() == alarm1.day) {
         lv_label_set_text(uic_alarmStatus, "Today");
    } 
    // Check if alarm is tomorrow
    else {
        DateTime tomorrow = now + TimeSpan(1, 0, 0, 0);
        if (tomorrow.year() == alarm1.year && tomorrow.month() == alarm1.month && tomorrow.day() == alarm1.day) {
             lv_label_set_text(uic_alarmStatus, "Tmrw");
        } else {
             // Show date e.g. 16/12
             lv_label_set_text_fmt(uic_alarmStatus, "%02d/%02d", alarm1.day, alarm1.month);
        }
    }
}

void setAlarmFromMQTT(const String &message)
{
  Serial.println("[MQTT] Received set alarm request");
  StaticJsonDocument<256> doc;
  if (deserializeJson(doc, message))
  {
    Serial.println("[MQTT] JSON deserialize failed");
    return;
  }

  int year = doc["year"];
  int month = doc["month"];
  int day = doc["day"];
  int hour = doc["hour"];
  int minute = doc["minute"];

  // Check if alarm is in the past (e.g. retained message)
  DateTime now = rtc.now();
  // Basic validation
  if (year < 2000 || month < 1 || month > 12 || day < 1 || day > 31) {
      Serial.println("[MQTT] Invalid alarm date received");
      return;
  }
  
  DateTime dtAlarm(year, month, day, hour, minute, 0);

  if (dtAlarm.unixtime() <= now.unixtime()) {
      Serial.println("[MQTT] Ignored old alarm message");
      return;
  }

  alarm1.year = year;
  alarm1.month = month;
  alarm1.day = day;
  alarm1.hour = hour;
  alarm1.minute = minute;
  alarm1.enabled = true;

  Serial.println("[MQTT] Saving to flash...");
  saveAlarmConfig(); // Save to flash
  Serial.println("[MQTT] Saved. Setting RTC...");
  delay(10);

  rtc.clearAlarm(1);
  // Set hardware alarm for Day, Hour, Minute
  rtc.setAlarm1(dtAlarm, DS3231_A1_Date);
  Serial.println("[MQTT] Alarm set successfully");
  updateCalendarHighlights();
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

  String delAlarmMsg;
  bool delAlarmFlag = false;
  if (xSemaphoreTake(mqttMutex, 0) == pdTRUE)
  {
    if (newDeleteAlarm)
    {
      delAlarmMsg = deleteAlarmMessage;
      newDeleteAlarm = false;
      delAlarmFlag = true;
    }
    xSemaphoreGive(mqttMutex);
  }
  if (delAlarmFlag) {
    // Dismiss alarm
    alarm1.enabled = false;
    saveAlarmConfig();
    rtc.clearAlarm(1);
    updateAlarmUI();
    updateCalendarHighlights();
  }

  // Update Alarm UI
  static unsigned long lastAlarmUIUpdate = 0;
  if (millis() - lastAlarmUIUpdate >= 1000) {
      lastAlarmUIUpdate = millis();
      updateAlarmUI();
  }

  // Throttle WiFi check to avoid overhead every frame
  static unsigned long lastWifiCheck = 0;
  if (millis() - lastWifiCheck >= 3000) 
  {
    lastWifiCheck = millis();
    if (WiFi.status() != WL_CONNECTED)
    {
      unsigned long currentMillis = millis();
      if (currentMillis - lastTimeConnectWifi >= wifiReconnectInterval)
      {
        lastTimeConnectWifi = currentMillis;
        WiFi.disconnect();
        if (global_ssid != "") {
            WiFi.begin(global_ssid.c_str(), global_password.c_str());
        }
      }
    }
  }
}

#ifdef __cplusplus
extern "C" {
#endif
void snoozeAlarm()
{
  // 1. Turn off buzzer
  buzzerBeepCount = 0;
  digitalWrite(BUZZER_PIN, LOW);
  
  // 2. Calculate new time (now + 5 mins)
  DateTime now = rtc.now();
  DateTime snoozeTime = now + TimeSpan(0, 0, 5, 0); // +5 minutes

  // Update alarm1 config to match snooze time so checkAlarmTrigger passes
  alarm1.year = snoozeTime.year();
  alarm1.month = snoozeTime.month();
  alarm1.day = snoozeTime.day();
  alarm1.hour = snoozeTime.hour();
  alarm1.minute = snoozeTime.minute();
  alarm1.enabled = true;

  saveAlarmConfig();

  // 3. Set RTC Alarm 1 to snooze time
  rtc.clearAlarm(1);
  rtc.setAlarm1(snoozeTime, DS3231_A1_Date); // Match Date, Hours, Minutes

  // 4. Switch back to main screen
  /*if (!ui_mainTime) {
      ui_mainTime_screen_init();
  }
  lv_disp_load_scr(ui_mainTime);
  */
  
  updateAlarmUI();
  updateCalendarHighlights();
}
#ifdef __cplusplus
}
#endif


