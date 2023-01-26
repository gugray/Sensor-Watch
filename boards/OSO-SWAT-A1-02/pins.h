#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

// Detects if we are on USB power.
#define VBUS_DET GPIO(GPIO_PORTA, 2)

// Buttons
#define BTN_ALARM GPIO(GPIO_PORTB, 5)
#define WATCH_BTN_ALARM_EIC_CHANNEL 5
#define BTN_LIGHT GPIO(GPIO_PORTA, 22)
#define WATCH_BTN_LIGHT_EIC_CHANNEL 6
#define BTN_MODE GPIO(GPIO_PORTA, 23)
#define WATCH_BTN_MODE_EIC_CHANNEL 7

// Buzzer
#define BUZZER GPIO(GPIO_PORTA, 27)
#define WATCH_BUZZER_TCC_PINMUX PINMUX_PA27F_TCC0_WO5
#define WATCH_BUZZER_TCC_CHANNEL 1

// LEDs
#ifdef WATCH_IS_BLUE_BOARD
    #define RED GPIO(GPIO_PORTA, 21)
    #define WATCH_RED_TCC_PINMUX PINMUX_PA21F_TCC0_WO7
    #define WATCH_RED_TCC_CHANNEL 3
    #define GREEN GPIO(GPIO_PORTA, 20)
    #define WATCH_GREEN_TCC_CHANNEL 2
    #define WATCH_GREEN_TCC_PINMUX PINMUX_PA20F_TCC0_WO6
#else
    #define RED GPIO(GPIO_PORTA, 20)
    #define WATCH_RED_TCC_PINMUX PINMUX_PA20F_TCC0_WO6
    #define WATCH_RED_TCC_CHANNEL 2
    #define GREEN GPIO(GPIO_PORTA, 21)
    #define WATCH_GREEN_TCC_CHANNEL 3
    #define WATCH_GREEN_TCC_PINMUX PINMUX_PA21F_TCC0_WO7
#endif

// Segment LCD
#define SLCD0 GPIO(GPIO_PORTB, 6)
#define SLCD1 GPIO(GPIO_PORTB, 7)
#define SLCD2 GPIO(GPIO_PORTB, 8)
#define SLCD3 GPIO(GPIO_PORTB, 9)
#define SLCD4 GPIO(GPIO_PORTA, 4)
#define SLCD5 GPIO(GPIO_PORTA, 5)
#define SLCD6 GPIO(GPIO_PORTA, 6)
#define SLCD7 GPIO(GPIO_PORTA, 7)
#define SLCD8 GPIO(GPIO_PORTA, 8)
#define SLCD9 GPIO(GPIO_PORTA, 9)
#define SLCD10 GPIO(GPIO_PORTA, 10)
#define SLCD11 GPIO(GPIO_PORTA, 11)
#define SLCD12 GPIO(GPIO_PORTB, 11)
#define SLCD13 GPIO(GPIO_PORTB, 12)
#define SLCD14 GPIO(GPIO_PORTB, 13)
#define SLCD15 GPIO(GPIO_PORTB, 14)
#define SLCD16 GPIO(GPIO_PORTB, 15)
#define SLCD17 GPIO(GPIO_PORTA, 12)
#define SLCD18 GPIO(GPIO_PORTA, 13)
#define SLCD19 GPIO(GPIO_PORTA, 14)
#define SLCD20 GPIO(GPIO_PORTA, 15)
#define SLCD21 GPIO(GPIO_PORTA, 16)
#define SLCD22 GPIO(GPIO_PORTA, 17)
#define SLCD23 GPIO(GPIO_PORTA, 18)
#define SLCD24 GPIO(GPIO_PORTA, 19)
#define SLCD25 GPIO(GPIO_PORTB, 16)
#define SLCD26 GPIO(GPIO_PORTB, 17)

// 9-pin connector
#define A0 GPIO(GPIO_PORTB, 4)
#define WATCH_A0_EIC_CHANNEL 4
#define A1 GPIO(GPIO_PORTB, 1)
#define WATCH_A1_EIC_CHANNEL 1
#define A2 GPIO(GPIO_PORTB, 2)
#define WATCH_A2_EIC_CHANNEL 2
#define A3 GPIO(GPIO_PORTB, 3)
#define WATCH_A3_EIC_CHANNEL 3
#define A4 GPIO(GPIO_PORTB, 0)
#define WATCH_A4_EIC_CHANNEL 0
#define SDA GPIO(GPIO_PORTB, 30)
#define SCL GPIO(GPIO_PORTB, 31)

// aliases for as A3/A4; these were mentioned as D0/D1 in early documentation.
#define D0 GPIO(GPIO_PORTB, 3)
#define D1 GPIO(GPIO_PORTB, 0)

#endif // PINS_H_INCLUDED
