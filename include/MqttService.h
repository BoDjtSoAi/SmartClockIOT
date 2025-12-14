#ifndef MQTT_SERVICE_H
#define MQTT_SERVICE_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

void System_Init();        // Khởi tạo WiFi, MQTT, RTC
void System_Handle_Loop(); // Xử lý dữ liệu trong vòng lặp

#ifdef __cplusplus
}
#endif

#endif