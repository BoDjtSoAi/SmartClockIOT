#include "TimerService.h"
#include "MqttService.h" // For buzzerBeepCount if needed

// State variables
bool timerActive = false;  // Timer mode is active (counting or paused)
bool timerRunning = false; // Timer is currently counting down
long timerDuration = 0;    // Total duration in seconds
long timerRemaining = 0;   // Remaining time in seconds
unsigned long lastTimerTick = 0;

// Externs from MqttService.cpp
extern int buzzerBeepCount;
extern bool buzzerState;

// Externs from UI (if not already available via ui.h, but ui.h declares them)
// ui.h includes ui_pomodoro.h which declares ui_rollHour etc.
// But we need the pointers to the objects.
// In ui_pomodoro.c, uic_* are assigned to ui_*.
// We should use ui_* variables as they are the global ones declared in headers.
// ui_pomodoro.h declares `extern lv_obj_t * ui_rollHour;`
// So we can use `ui_rollHour`.

void Timer_Init()
{
    // Initialize anything if needed
}

void Timer_Start()
{
    if (timerActive && !timerRunning)
    {
        // Resume
        timerRunning = true;
        lastTimerTick = millis();
        // Update button icon to pause
        if (ui_btnControl1)
        {
            lv_obj_set_style_bg_img_src(ui_btnControl1, &ui_img_timer_24dp_789de5_fill0_wght400_grad0_opsz24_png, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        return;
    }

    // New Start
    if (!ui_rollHour || !ui_rollMinutes || !ui_rollSeconds)
        return;

    int h = lv_roller_get_selected(ui_rollHour);
    int m = lv_roller_get_selected(ui_rollMinutes);
    int s = lv_roller_get_selected(ui_rollSeconds);

    timerDuration = h * 3600 + m * 60 + s;
    if (timerDuration <= 0)
    {
        if (ui_SetupTime)
            _ui_flag_modify(ui_SetupTime, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        if (ui_contBtn)
            _ui_flag_modify(ui_contBtn, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        if (ui_contTimer)
            _ui_flag_modify(ui_contTimer, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        if (ui_contBtnRUN)
            _ui_flag_modify(ui_contBtnRUN, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        if (ui_countDown)
            _ui_flag_modify(ui_countDown, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    } // khỏi chạy linh tinh

    timerRemaining = timerDuration;
    timerActive = true;
    timerRunning = true;
    lastTimerTick = millis();

    // Update button icon to pause
    if (ui_btnControl1)
    {
        lv_obj_set_style_bg_img_src(ui_btnControl1, &ui_img_timer_24dp_789de5_fill0_wght400_grad0_opsz24_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    // Update UI immediately
    h = timerRemaining / 3600;
    m = (timerRemaining % 3600) / 60;
    s = timerRemaining % 60;

    char buf[16];
    snprintf(buf, sizeof(buf), "%02d:%02d:%02d", h, m, s);
    if (ui_countdownTimeBig2)
    {
        lv_label_set_text(ui_countdownTimeBig2, buf);
    }
}

void Timer_Pause()
{
    if (timerRunning)
    {
        timerRunning = false;
        // Update button icon to play
        if (ui_btnControl1)
        {
            lv_obj_set_style_bg_img_src(ui_btnControl1, &ui_img_timer_play_24dp_0eb456_fill0_wght400_grad0_opsz24_png, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    else if (timerActive)
    {
        // Resume
        Timer_Start();
    }
}

void Timer_Dismiss()
{
    timerActive = false;
    timerRunning = false;

    // Reset UI
    if (ui_dayOfWeek)
        lv_label_set_text(ui_dayOfWeek, "Sunday"); // Will be updated by main loop

    // Switch UI back to setup
    // Note: SquareLine events might also be doing this, but we do it here to be sure or if called programmatically
    if (ui_SetupTime)
        _ui_flag_modify(ui_SetupTime, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    if (ui_contBtn)
        _ui_flag_modify(ui_contBtn, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    if (ui_contTimer)
        _ui_flag_modify(ui_contTimer, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    if (ui_contBtnRUN)
        _ui_flag_modify(ui_contBtnRUN, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    if (ui_countDown)
        _ui_flag_modify(ui_countDown, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

    // Reset rollers?
    if (ui_rollMinutes)
        lv_roller_set_selected(ui_rollMinutes, 0, LV_ANIM_ON);
    if (ui_rollSeconds)
        lv_roller_set_selected(ui_rollSeconds, 0, LV_ANIM_ON);
    if (ui_rollHour)
        lv_roller_set_selected(ui_rollHour, 0, LV_ANIM_ON);
}

bool Timer_IsActive()
{
    return timerActive;
}

void Timer_Loop()
{
    if (!timerActive)
        return;

    bool timeChanged = false;

    if (timerRunning)
    {
        unsigned long currentMillis = millis();
        if (currentMillis - lastTimerTick >= 1000)
        {
            timerRemaining--;
            lastTimerTick = currentMillis;
            timeChanged = true;

            if (timerRemaining <= 0)
            {
                timerRemaining = 0;
                timerRunning = false;
                timerActive = false;

                // Ring buzzer
                buzzerBeepCount = 50; // Beep for 5 seconds (approx, depends on loop speed)

                // Clear itself
                Timer_Dismiss();
                return;
            }
        }
    }

    if (timeChanged)
    {
        // Update UI
        int h = timerRemaining / 3600;
        int m = (timerRemaining % 3600) / 60;
        int s = timerRemaining % 60;

        char buf[16];
        snprintf(buf, sizeof(buf), "%02d:%02d:%02d", h, m, s);

        if (ui_countdownTimeBig2)
            lv_label_set_text(ui_countdownTimeBig2, buf);

        // Update Main Screen
        if (ui_dayOfWeek)
            lv_label_set_text(ui_dayOfWeek, "TIMER");

        char buf2[16];
        snprintf(buf2, sizeof(buf2), "-%02d:%02d:%02d", h, m, s);
        if (ui_dateMonth)
            lv_label_set_text(ui_dateMonth, buf2);
    }
}
