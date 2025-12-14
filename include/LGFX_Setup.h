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
    { // 1. CẤU HÌNH BUS SPI (SHARED BUS CONFIG)
      auto cfg = _bus_instance.config(); 

      // --- Performance Settings ---
      cfg.spi_host = SPI2_HOST;     
      cfg.spi_mode = 0;
      
      // OPTION: Nếu hình ảnh tốt ở 40MHz, hãy thử bỏ comment dòng 80MHz để mượt hơn
      //cfg.freq_write = 80000000; // Max Performance (80MHz)
      cfg.freq_write = 40000000;    // Safe Mode (40MHz) - YOUR CURRENT SETTING
      
      cfg.freq_read  = 16000000;    
      cfg.spi_3wire  = false;       
      cfg.use_lock   = true;        
      
      // --- DMA IS CRITICAL FOR LVGL ---
      cfg.dma_channel = SPI_DMA_CH_AUTO; // NEW: Auto-assign DMA channel

      // --- PIN DEFINITIONS ---
      cfg.pin_sclk = 12;  
      cfg.pin_mosi = 11;  
      cfg.pin_miso = 13;  
      cfg.pin_dc   = 9;   

      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    { // 2. CẤU HÌNH ĐÈN NỀN (BACKLIGHT)
      auto cfg = _light_instance.config();    
      cfg.pin_bl      = 3;
      cfg.invert      = false;
      cfg.freq        = 12000;
      cfg.pwm_channel = 7;
      
      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance);
    }

    { // 3. CẤU HÌNH CẢM ỨNG (TOUCH XPT2046)
      auto cfg = _touch_instance.config();
      
      // Calibrate Values (Standard generic 3.5" values)
      cfg.x_min      = 0;    // Adjusted defaults 
      cfg.x_max      = 4095;
      cfg.y_min      = 0;
      cfg.y_max      = 4095;
      
      cfg.pin_int    = -1; 
      cfg.bus_shared = true; // IMPORTANT: Device shares SPI bus
      cfg.offset_rotation = 0; // Match Panel Rotation 

      // SPI Config for Touch (Must match Bus)
      cfg.spi_host = SPI2_HOST;
      cfg.freq     = 2500000; // Keep 2.5MHz for stability
      
      // Pins (Redundant but safe to declare)
      cfg.pin_sclk = 12; 
      cfg.pin_mosi = 11; 
      cfg.pin_miso = 13; 
      cfg.pin_cs   = 8;   // Touch CS

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }

    { // 4. CẤU HÌNH PANEL (DISPLAY)
      auto cfg = _panel_instance.config();
      
      cfg.pin_cs           = 10;  // Screen CS
      cfg.pin_rst          = 46;  
      cfg.pin_busy         = -1; 
      
      cfg.panel_width      = 320;
      cfg.panel_height     = 480;
      cfg.offset_rotation  = 0;
      cfg.invert           = false; 
      
      cfg.readable         = true; 
      cfg.bus_shared       = true; // Vital for shared SPI
      cfg.dlen_16bit       = false; // Ensure serial mode

      _panel_instance.config(cfg);
    }

    setPanel(&_panel_instance);
  }
};
#endif