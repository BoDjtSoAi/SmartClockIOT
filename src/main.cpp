#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include <lvgl.h>
#include "LGFX_Setup.h" 
#include "ui/ui.h" 

// --- RTC Objects ---
RTC_DS3231 rtc;
#define I2C_SDA 42
#define I2C_SCL 41

// Mảng tên ngày/tháng
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char monthsOfTheYear[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

// --- Display & Buffer Config ---
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

// 1/10 Screen Buffer (Tối ưu cho SPI DMA)
#define BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10)
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[BUF_SIZE];

// --- LGFX Instance ---
LGFX tft;

/* --- DISPLAY FLUSHING (Dùng DMA để Max Speed) --- */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    if (tft.getStartCount() == 0) {
        tft.endWrite();
    }
    // Đẩy dữ liệu qua DMA
    tft.pushImageDMA(area->x1, area->y1, w, h, (uint16_t *)&color_p->full);
    
    lv_disp_flush_ready(disp);
}

/* --- TOUCHPAD READ --- */
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
    uint16_t touchX, touchY;
    bool touched = tft.getTouch(&touchX, &touchY);

    if (!touched) {
        data->state = LV_INDEV_STATE_REL;
    } else {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = touchX;
        data->point.y = touchY;
    }
}

void setup() {
    Serial.begin(115200);
    
    // --- 1. Init RTC ---
    Wire.begin(I2C_SDA, I2C_SCL);
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
    }
    if (rtc.lostPower()) {
        Serial.println("RTC lost power, setting time...");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    // --- 2. Init Hardware Display ---
    tft.init();
    tft.setRotation(1); 
    tft.setBrightness(255);
    
    // --- 3. Init LVGL ---
    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, BUF_SIZE);

    // --- 4. Register Display Driver (LVGL 8 Syntax) ---
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // --- 5. Register Input Driver (LVGL 8 Syntax) ---
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    // --- 6. Init UI ---
    ui_init(); 

    Serial.println("Setup done");
}

void loop() {
    lv_timer_handler(); // Để LVGL vẽ giao diện
    
    // --- Logic cập nhật đồng hồ (Mỗi 1 giây chạy 1 lần) ---
    static uint32_t last_update = 0;
    if (millis() - last_update >= 1000) {
        last_update = millis();
        
        DateTime now = rtc.now();
        
        // --- Cập nhật UI (Đã khôi phục code UIC của bạn) ---
        
        // 1. Cập nhật Ngày/Tháng
        if(uic_dateMonth) {
            lv_label_set_text_fmt(uic_dateMonth, "%02d %s", now.day(), monthsOfTheYear[now.month() - 1]);
        }

        // 2. Cập nhật Thứ
        if(uic_dayOfWeek) {
            lv_label_set_text(uic_dayOfWeek, daysOfTheWeek[now.dayOfTheWeek()]);
        }

        // 3. Cập nhật Giờ:Phút
        if(uic_hours) {
            lv_label_set_text_fmt(uic_hours, "%02d:%02d", now.hour(), now.minute());
        }

        // 4. Cập nhật Giây
        if(uic_seconds) {
            lv_label_set_text_fmt(uic_seconds, ":%02d", now.second());
        }
        
        // 5. Cập nhật Nhiệt độ RTC
        if(uic_rtcTemp) {
             String temp = String(rtc.getTemperature(), 1) + " 'C";
             lv_label_set_text(uic_rtcTemp, temp.c_str());
        }
    }

    delay(5); // Nhường CPU để không bị nóng
}