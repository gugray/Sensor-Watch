/*
 * MIT License
 *
 * Copyright (c) 2023 Gabor L Ugray
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdlib.h>
#include <string.h>
#include "chirpy_demo_face.h"
#include "chirpy_tx_face.h"

// Data sequence has 4 + 16 + 2 + 16 + 2 = 40 items
#define INFO_SEQ_LEN 54
const uint8_t info_seq[] = {
    17, 16, 17, 16,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    1, 8, 4, 15, 13, 12, 2, 6, 5, 11, 7, 0, 3, 14, 10, 9,
    7, 12, 6, 8, 10, 4, 15, 3, 14, 5, 11, 0, 13, 1, 2, 9,
    16, 17
};

void chirpy_demo_face_setup(movement_settings_t *settings, uint8_t watch_face_index, void ** context_ptr) {
    (void) settings;
    (void) watch_face_index;
    if (*context_ptr == NULL) {
        *context_ptr = malloc(sizeof(chirpy_demo_state_t));
        memset(*context_ptr, 0, sizeof(chirpy_demo_state_t));
        // Do any one-time tasks in here; the inside of this conditional happens only at boot.
    }
    // Do any pin or peripheral setup here; this will be called whenever the watch wakes from deep sleep.
}

void chirpy_demo_face_activate(movement_settings_t *settings, void *context) {
    (void) settings;
    chirpy_demo_state_t *state = (chirpy_demo_state_t *)context;

    state->mode = CDM_INFO_4R;
}


static void _chirpy_demo_face_update_lcd(chirpy_demo_state_t *state) {
    // Show beep rate
    uint8_t rate = 4;
    if (state->mode == CDM_INFO_20R) rate = 20;
    // Assemble & write to LCD
    char buf[11];
    sprintf(buf, "CH%2d PLAY ", rate);
    watch_display_string(buf, 0);
}

static void _chirpy_demo_face_play(chirpy_demo_state_t *state) {
    
    uint16_t signal_duration = state->mode == CDM_INFO_4R ? 250 : 50;
    watch_set_indicator(WATCH_INDICATOR_BELL);
    uint16_t i;

    // Countdown
    uint16_t buzzer_period = chirpy_tone_periods[16];
    watch_set_buzzer_period(buzzer_period);
    for (i = 0; i < 3; ++i) {
        watch_set_buzzer_on();
        delay_ms(125);
        watch_set_buzzer_off();
        delay_ms(875);
    }

    // Data
    for (i = 0; i < INFO_SEQ_LEN; ++i) {
        uint8_t sym_ix = info_seq[i];
        buzzer_period = chirpy_tone_periods[sym_ix];
        watch_set_buzzer_period(buzzer_period);
        #ifdef __EMSCRIPTEN__
        watch_set_buzzer_on();
        #else
        if (i == 0) watch_set_buzzer_on();
        #endif
        delay_ms(signal_duration);
    }

    watch_set_buzzer_off();
    watch_clear_indicator(WATCH_INDICATOR_BELL);
}


bool chirpy_demo_face_loop(movement_event_t event, movement_settings_t *settings, void *context) {
    (void) settings;
    chirpy_demo_state_t *state = (chirpy_demo_state_t *)context;

    switch (event.event_type) {
        case EVENT_ACTIVATE:
            _chirpy_demo_face_update_lcd(state);
            movement_request_tick_frequency(32);
            break;
        case EVENT_MODE_BUTTON_UP:
            movement_move_to_next_face();
            break;
        case EVENT_LIGHT_BUTTON_UP:
            state->mode = (state->mode + 1) % 2;
            _chirpy_demo_face_update_lcd(state);
            break;
        case EVENT_ALARM_BUTTON_UP:
            _chirpy_demo_face_play(state);
            break;
        case EVENT_TIMEOUT:
            movement_move_to_face(0);
        default:
            break;
    }

    // return true if the watch can enter standby mode. If you are PWM'ing an LED or buzzing the buzzer here,
    // you should return false since the PWM driver does not operate in standby mode.
    return true;
}

void chirpy_demo_face_resign(movement_settings_t *settings, void *context) {
    (void) settings;
    (void) context;

    // handle any cleanup before your watch face goes off-screen.
}

