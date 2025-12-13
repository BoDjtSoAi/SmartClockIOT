#ifndef LGFX_SETUP_H
#define LGFX_SETUP_H
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ILI9488 _panel_instance;
  lgfx::Bus_SPI       _bus_instance;
  lgfx::Touch_XPT2046 _touch_instance;
  lgfx::Light_PWM     _light_instance;

public:
  LGFX(void) {
    { // 1. CẤU HÌNH BUS SPI (CHUNG CHO CẢ LCD VÀ TOUCH)
      auto cfg = _bus_instance.config(); 
      cfg.spi_host = SPI2_HOST;     // Dùng SPI2 trên S3
      cfg.spi_mode = 0;
      cfg.freq_write = 40000000;    // Tốc độ ghi hình ảnh (40MHz)
      cfg.freq_read  = 16000000;    // Tốc độ đọc
      cfg.spi_3wire  = false;       // Dùng 4 dây (quan trọng để có MISO cho Touch)
      cfg.use_lock   = true;        // Khóa bus khi đang truyền
      
      // Khai báo chân SPI theo sơ đồ S3
      cfg.pin_sclk = 12;  // Nối vào cả SCK và T_CLK
      cfg.pin_mosi = 11;  // Nối vào cả SDI và T_DIN
      cfg.pin_miso = 13;  // Nối vào T_DO (Quan trọng nhất cho Touch)
      cfg.pin_dc   = 9;   // Chân DC của màn hình

      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    { // 2. CẤU HÌNH ĐÈN NỀN
      auto cfg = _light_instance.config();    
      cfg.pin_bl = 3;
      cfg.invert = false;
      cfg.freq   = 12000;
      cfg.pwm_channel = 7;
      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance);
    }

    { // 3. CẤU HÌNH CẢM ỨNG (TOUCH)
      auto cfg = _touch_instance.config();
      
      // Giá trị thô ADC (để dải rộng tối đa, sau đó dùng Calibrate để chỉnh)
      cfg.x_min      = 4095;
      cfg.x_max      = 0;
      cfg.y_min      = 0;
      cfg.y_max      = 4095;
      
      cfg.pin_int    = -1; // Không dùng ngắt
      cfg.bus_shared = true; // BÁO RẰNG ĐANG DÙNG CHUNG BUS SPI
      cfg.offset_rotation = 2;

      // Cấu hình SPI cho Touch (Trùng với Bus ở trên)
      cfg.spi_host = SPI2_HOST;
      cfg.freq = 2500000; // 2.5MHz (XPT2046 chạy chậm thôi)
      
      // Các chân này thực tế đã được khai báo ở Bus, 
      // nhưng khai báo lại để Touch instance biết
      cfg.pin_sclk = 12; 
      cfg.pin_mosi = 11; 
      cfg.pin_miso = 13; // Chân T_DO
      cfg.pin_cs   = 8;  // Chân T_CS (Khác chân CS màn hình)

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }

    { // 4. CẤU HÌNH PANEL
      auto cfg = _panel_instance.config();
      cfg.pin_cs           = 10;  // Chân CS màn hình
      cfg.pin_rst          = 46;  
      cfg.pin_busy         = -1; 
      cfg.panel_width      = 320;
      cfg.panel_height     = 480;
      cfg.offset_rotation  = 0;
      cfg.readable         = true; // Cần true để chia sẻ bus
      cfg.bus_shared       = true; // Quan trọng

      _panel_instance.config(cfg);
    }

    setPanel(&_panel_instance);
  }
};
#endif