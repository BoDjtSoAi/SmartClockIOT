# SmartClockIOT - AI Coding Instructions

## Project Overview
This is a **PlatformIO** project for **ESP32-S3** using the **Arduino framework**. The project implements a smart clock with MQTT connectivity, weather display, and alarm functionality.

## Architecture & Key Components

### 1. Core System (`src/main.cpp`)
-   **Entry Point**: Handles hardware initialization (`setup()`) and the main execution loop (`loop()`).
-   **Display Driver**: Uses **LovyanGFX** (`LGFX`) for high-performance display driving with DMA.
-   **UI Engine**: Uses **LVGL 8.3** for the graphical user interface.
-   **Sensors**:
    -   **Ultrasonic (HC-SR05)**: Detects presence to control screen brightness/power (Pins: Trig 18, Echo 17).
    -   **RTC (DS3231)**: Keeps time and handles alarms (I2C: SDA 42, SCL 41).
    -   **RGB LED**: Status indicator (Pin 48).

### 2. Connectivity & Logic (`src/MqttService.cpp`)
-   **System Management**: Contains `System_Init()` and `System_Handle_Loop()` which manage WiFi and MQTT.
-   **MQTT**: Uses `PubSubClient` to connect to `broker.hivemq.com`.
    -   **Topics**: `out/weather`, `out/air-quality`, `set/clock`, `set/alarm`, `delete/alarm`.
-   **Data Handling**: Uses `ArduinoJson` for parsing payloads.
-   **Alarm Logic**: Manages alarm state and RTC interrupts.

### 3. User Interface (`src/UI/`)
-   **Generated Code**: The UI code in `src/UI/` appears to be generated (likely SquareLine Studio).
-   **Integration**: UI widgets are accessed via global pointers (e.g., `uic_hours`, `uic_CalendarMain`).
-   **Updates**:
    -   **Time**: Updated every second in `main.cpp`.
    -   **Weather/Alarm**: Updated in `MqttService.cpp` upon receiving MQTT messages.

## Development Workflows

### Build & Run
-   **Build**: `pio run`
-   **Upload**: `pio run -t upload`
-   **Monitor**: `pio device monitor` (Baud: 115200)

### Coding Conventions
-   **UI Updates**: Always check if UI objects exist before updating (e.g., `if (uic_hours) ...`).
-   **Concurrency**:
    -   `lv_timer_handler()` must be called frequently in `loop()` for UI rendering.
    -   Avoid blocking code (long `delay()`) in the main loop.
-   **Hardware Access**: Use defined constants for pins (e.g., `TRIG_PIN`, `RGB_PIN`).
-   **Memory**: The project uses PSRAM (`-DBOARD_HAS_PSRAM`). Large buffers are allocated in PSRAM.

## Key Files
-   `platformio.ini`: Project configuration and dependencies.
-   `src/main.cpp`: Main loop, sensor logic, display flush callback.
-   `src/MqttService.cpp`: WiFi/MQTT logic, alarm handling.
-   `include/LGFX_Setup.h`: Display driver configuration.
