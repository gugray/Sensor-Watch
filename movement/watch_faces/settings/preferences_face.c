#include <stdlib.h>
#include "preferences_face.h"
#include "watch.h"

#define PREFERENCES_FACE_NUM_PREFEFENCES (7)
const char preferences_face_titles[PREFERENCES_FACE_NUM_PREFEFENCES][11] = {
    "CL        ",   // Clock: 12 or 24 hour
    "BT  Beep  ",   // Buttons: should they beep?
    "TO        ",   // Timeout: how long before we snap back to the clock face?
    "LE        ",   // Low Energy mode: how long before it engages?
    "LT        ",   // Light: duration
    "LT   grn  ",   // Light: green component
    "LT   red  ",   // Light: red component
};

void preferences_face_setup(movement_settings_t *settings, void ** context_ptr) {
    (void) settings;
    if (*context_ptr == NULL) *context_ptr = malloc(sizeof(uint8_t));
}

void preferences_face_activate(movement_settings_t *settings, void *context) {
    (void) settings;
    *((uint8_t *)context) = 0;
    movement_request_tick_frequency(4); // we need to manually blink some pixels
}

bool preferences_face_loop(movement_event_t event, movement_settings_t *settings, void *context) {
    uint8_t current_page = *((uint8_t *)context);
    switch (event.event_type) {
        case EVENT_MODE_BUTTON_UP:
            watch_set_led_off();
            movement_move_to_next_face();
            return false;
        case EVENT_LIGHT_BUTTON_UP:
            current_page = (current_page + 1) % PREFERENCES_FACE_NUM_PREFEFENCES;
            *((uint8_t *)context) = current_page;
            break;
        case EVENT_ALARM_BUTTON_UP:
            switch (current_page) {
                case 0:
                    settings->bit.clock_mode_24h = !(settings->bit.clock_mode_24h);
                    break;
                case 1:
                    settings->bit.button_should_sound = !(settings->bit.button_should_sound);
                    break;
                case 2:
                    settings->bit.to_interval = settings->bit.to_interval + 1;
                    break;
                case 3:
                    settings->bit.le_interval = settings->bit.le_interval + 1;
                    break;
                case 4:
                    settings->bit.led_duration = settings->bit.led_duration + 1;
                    break;
                case 5:
                    settings->bit.led_green_color = settings->bit.led_green_color + 1;
                    break;
                case 6:
                    settings->bit.led_red_color = settings->bit.led_red_color + 1;
                    break;
            }
            break;
        case EVENT_TIMEOUT:
            movement_move_to_face(0);
            break;
        default:
            break;
    }

    watch_display_string((char *)preferences_face_titles[current_page], 0);

    if (event.subsecond % 2) return current_page <= 2;
    char buf[8];
    switch (current_page) {
        case 0:
            if (settings->bit.clock_mode_24h) watch_display_string("24h", 4);
            else watch_display_string("12h", 4);
            break;
        case 1:
            if (settings->bit.button_should_sound) watch_display_string("y", 9);
            else watch_display_string("n", 9);
            break;
        case 2:
            switch (settings->bit.to_interval) {
                case 0:
                    watch_display_string("60 sec", 4);
                    break;
                case 1:
                    watch_display_string("2 n&in", 4);
                    break;
                case 2:
                    watch_display_string("5 n&in", 4);
                    break;
                case 3:
                    watch_display_string("30n&in", 4);
                    break;
            }
            break;
        case 3:
            switch (settings->bit.le_interval) {
                case 0:
                    watch_display_string(" never", 4);
                    break;
                case 1:
                    watch_display_string("1 hour", 4);
                    break;
                case 2:
                    watch_display_string("2 hour", 4);
                    break;
                case 3:
                    watch_display_string("6 hour", 4);
                    break;
                case 4:
                    watch_display_string("12 hr", 4);
                    break;
                case 5:
                    watch_display_string(" 1 day", 4);
                    break;
                case 6:
                    watch_display_string(" 2 day", 4);
                    break;
                case 7:
                    watch_display_string(" 7 day", 4);
                    break;
            }
            break;
        case 4:
            if (settings->bit.led_duration) {
                // FIXME: since we time the LED with the 1 Hz tick, the actual time lit can vary depending
                // on whether the user hit it just before or just after a tick. so the setting is "1-2 s",
                // "3-4 s", or "5-6 s". If we time this with the system tick we can do better.
                sprintf(buf, " %1d-%1d s", settings->bit.led_duration * 2 - 1, settings->bit.led_duration * 2);
                watch_display_string(buf, 4);
            } else {
                watch_display_string("no LEd", 4);
            }
            break;
        case 5:
            sprintf(buf, "%2d", settings->bit.led_green_color);
            watch_display_string(buf, 8);
            break;
        case 6:
            sprintf(buf, "%2d", settings->bit.led_red_color);
            watch_display_string(buf, 8);
            break;
    }

    if (current_page >= 5) {
        watch_set_led_color(settings->bit.led_red_color ? (0xF | settings->bit.led_red_color << 4) : 0,
                            settings->bit.led_green_color ? (0xF | settings->bit.led_green_color << 4) : 0);
        return false;
    }

    watch_set_led_off();
    return true;
}

void preferences_face_resign(movement_settings_t *settings, void *context) {
    (void) settings;
    (void) context;
    watch_set_led_off();
    movement_request_tick_frequency(1);
}
