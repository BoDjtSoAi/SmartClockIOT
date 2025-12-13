//Arduino-TFT_eSPI board-template main routine. There's a TFT_eSPI create+flush driver already in LVGL-9.1 but we create our own here for more control (like e.g. 16-bit color swap).

#include <lvgl.h>
#include <LGFX_Setup.h>
#include <UI/ui.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;
// Cấu hình chân I2C ESP32-S3 WeAct
#define I2C_SDA 42
#define I2C_SCL 41
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char monthsOfTheYear[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

/*Don't forget to set Sketchbook location in File/Preferences to the path of your UI project (the parent foder of this INO file)*/

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;

enum { SCREENBUFFER_SIZE_PIXELS = screenWidth * screenHeight / 10 };
static lv_color_t buf [SCREENBUFFER_SIZE_PIXELS];

LGFX tft; /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush (lv_display_t *disp, const lv_area_t *area, uint8_t *pixelmap)
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    if (LV_COLOR_16_SWAP) {
        size_t len = lv_area_get_size( area );
        lv_draw_sw_rgb565_swap( pixelmap, len );
    }

    tft.pushImage( area->x1, area->y1, w, h, (uint16_t*) pixelmap );

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
void my_touchpad_read (lv_indev_t * indev_driver, lv_indev_data_t * data)
{
    uint16_t touchX = 0, touchY = 0;

    bool touched = tft.getTouch( &touchX, &touchY );

    if (!touched)
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;

        Serial.print( "Data x " );
        Serial.println( touchX );

        Serial.print( "Data y " );
        Serial.println( touchY );
    }
}

/*Set tick routine needed for LVGL internal timings*/
static uint32_t my_tick_get_cb (void) { return millis(); }


void setup ()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */

    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    Wire.begin(I2C_SDA, I2C_SCL);
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
    }
    if (rtc.lostPower()) {
        Serial.println("RTC lost power, let's set the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    tft.init();          /* TFT init */
    tft.setRotation( 1 ); /* Landscape orientation, flipped */
    tft.setBrightness(255);
    tft.setSwapBytes(true);
    
    static lv_disp_t* disp;
    disp = lv_display_create( screenWidth, screenHeight );
    lv_display_set_buffers( disp, buf, NULL, SCREENBUFFER_SIZE_PIXELS * sizeof(lv_color_t), LV_DISPLAY_RENDER_MODE_PARTIAL );
    lv_display_set_flush_cb( disp, my_disp_flush );

    static lv_indev_t* indev;
    indev = lv_indev_create();
    lv_indev_set_type( indev, LV_INDEV_TYPE_POINTER );
    lv_indev_set_read_cb( indev, my_touchpad_read );

    lv_tick_set_cb( my_tick_get_cb );

    ui_init();

    Serial.println( "Setup done" );
}

void loop ()
{
    lv_timer_handler(); /* let the GUI do its work */

    static uint32_t last_update = 0;
    if (millis() - last_update >= 1000) {
        last_update = millis();
        DateTime now = rtc.now();
        
        // Update UI labels
        if(uic_dateMonth) lv_label_set_text_fmt(uic_dateMonth, "%02d %s", now.day(), monthsOfTheYear[now.month() - 1]);
        if(uic_dayOfWeek) lv_label_set_text(uic_dayOfWeek, daysOfTheWeek[now.dayOfTheWeek()]);
        if(uic_hours) lv_label_set_text_fmt(uic_hours, "%02d:%02d", now.hour(), now.minute());
        if(uic_seconds) lv_label_set_text_fmt(uic_seconds, ":%02d", now.second());
        if(uic_rtcTemp) {
             String temp = String(rtc.getTemperature(), 1) + " 'C";
             lv_label_set_text(uic_rtcTemp, temp.c_str());
        }
    }

    delay(5);
}
