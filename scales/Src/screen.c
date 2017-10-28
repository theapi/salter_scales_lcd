/*
 * screen.c
 *
 * The LCD screen as used by the Salter bathroom scales.
 *

Digits:  12.34
8 = A B C D E F G
1 = B C
 Multiplexing:
 1 = B C
     Digit 1 = COM1:SEG7, COM3:SEG7
     Digit 2 = COM1:SEG5, COM3:SEG5
     Digit 3 = COM1:SEG3, COM3:SEG3
     Digit 4 = COM1:SEG1, COM3:SEG1
 2 = A B D E G
     Digit 1 = COM1:SEG8, COM1:SEG7, COM4:SEG7, COM3:SEG8, COM2:SEG7
 ...
 *
 */


#include "screen.h"

/**
  LCD GPIO Configuration
    PA1     ------> LCD_SEG0  ------> PIN_4
    PA2     ------> LCD_SEG1  ------> PIN_5
    PA3     ------> LCD_SEG2  ------> PIN_6
    PA6     ------> LCD_SEG3  ------> PIN_7
    PA7     ------> LCD_SEG4  ------> PIN_8
    PB0     ------> LCD_SEG5  ------> PIN_9
    PB1     ------> LCD_SEG6  ------> PIN_10
    PA8     ------> LCD_COM0  ------> PIN_16
    PA9     ------> LCD_COM1  ------> PIN_15
    PA10    ------> LCD_COM2  ------> PIN_14
    PB3     ------> LCD_SEG7  ------> PIN_11
    PB4     ------> LCD_SEG8  ------> PIN_12
    PB9     ------> LCD_COM3  ------> PIN_13


pin : digit segment,

COM0 PA8:
  1:denominator A, 2:numerator A, 3:  ,
  4:kg, 5:0A, 6:0F, 7:1A, 8:1F, 9:2A, 10:2F, 11:3A, 12:3F

COM1 PA9:
  1:denominator C, 2:numerator B, 3:  ,
  4:lb, 5:0B, 6:0G, 7:1B, 8:1G, 9:2B, 10:2G, 11:3B, 12:3G

COM2 PA10:
  1:denominator F, 2:numerator C, 3:  ,
  4:denominator E&D
        5:0C, 6:0E, 7:1C, 8:1E, 9:2C, 10:2E, 11:3C, 12:3E

COM3 PB9:
  1:  , 2:  , 3:  ,
  4: top of denominator & bar
        5:St, 6:0D, 7:. , 8:1D, 9:: , 10:2D, 11:  , 12:3D

*/


const uint32_t lcd_digits[4][11][4] = {

    /* Digit 3 - Hundreds */
    {
        /* 0 */
        {
            LCD_PIN_11 | LCD_PIN_12, /* COM0 */
            LCD_PIN_11 , /* COM1 */
            LCD_PIN_11 | LCD_PIN_12, /* COM2 */
            LCD_PIN_12  /* COM3 */
        },
        /* 1 */
        {0, LCD_PIN_11, LCD_PIN_11, 0},
        /* 2 */
        {LCD_PIN_11, LCD_PIN_11 | LCD_PIN_12, LCD_PIN_12, LCD_PIN_12},
        /* 3 */
        {LCD_PIN_11, LCD_PIN_11 | LCD_PIN_12, LCD_PIN_11, LCD_PIN_12},
        /* 4 */
        {LCD_PIN_12, LCD_PIN_11 | LCD_PIN_12, LCD_PIN_11, 0},
        /* 5 */
        {LCD_PIN_11 | LCD_PIN_12, LCD_PIN_12, LCD_PIN_11, LCD_PIN_12},
        /* 6 */
        {LCD_PIN_11 | LCD_PIN_12, LCD_PIN_12, LCD_PIN_11 | LCD_PIN_12, LCD_PIN_12},
        /* 7 */
        {LCD_PIN_11, LCD_PIN_11, LCD_PIN_11, 0},
        /* 8 */
        {LCD_PIN_11 | LCD_PIN_12, LCD_PIN_11 | LCD_PIN_12, LCD_PIN_11 | LCD_PIN_12, LCD_PIN_12},
        /* 9 */
        {LCD_PIN_11 | LCD_PIN_12, LCD_PIN_11 | LCD_PIN_12, LCD_PIN_11, LCD_PIN_12},
        /* blank */
        {0, 0, 0, 0},
    },

    /* Digit 2 - Tens */
    {
        /* 0 */
        {
            LCD_PIN_9 | LCD_PIN_10, /* COM0 */
            LCD_PIN_9 , /* COM1 */
            LCD_PIN_9 | LCD_PIN_10, /* COM2 */
            LCD_PIN_10  /* COM3 */
        },
        /* 1 */
        {0, LCD_PIN_9, LCD_PIN_9, 0},
        /* 2 */
        {LCD_PIN_9, LCD_PIN_9 | LCD_PIN_10, LCD_PIN_10, LCD_PIN_10},
        /* 3 */
        {LCD_PIN_9, LCD_PIN_9 | LCD_PIN_10, LCD_PIN_9, LCD_PIN_10},
        /* 4 */
        {LCD_PIN_10, LCD_PIN_9 | LCD_PIN_10, LCD_PIN_9, 0},
        /* 5 */
        {LCD_PIN_9 | LCD_PIN_10, LCD_PIN_10, LCD_PIN_9, LCD_PIN_10},
        /* 6 */
        {LCD_PIN_9 | LCD_PIN_10, LCD_PIN_10, LCD_PIN_9 | LCD_PIN_10, LCD_PIN_10},
        /* 7 */
        {LCD_PIN_9, LCD_PIN_9, LCD_PIN_9, 0},
        /* 8 */
        {LCD_PIN_9 | LCD_PIN_10, LCD_PIN_9 | LCD_PIN_10, LCD_PIN_9 | LCD_PIN_10, LCD_PIN_10},
        /* 9 */
        {LCD_PIN_9 | LCD_PIN_10, LCD_PIN_9 | LCD_PIN_10, LCD_PIN_9, LCD_PIN_10},
        /* blank */
        {0, 0, 0, 0},
    },

    /* Digit 1 - Ones */
    {
        /* 0 */
        {
            LCD_PIN_7 | LCD_PIN_8, /* COM0 */
            LCD_PIN_7 , /* COM1 */
            LCD_PIN_7 | LCD_PIN_8, /* COM2 */
            LCD_PIN_8  /* COM3 */
        },
        /* 1 */
        {0, LCD_PIN_7, LCD_PIN_7, 0},
        /* 2 */
        {LCD_PIN_7, LCD_PIN_7 | LCD_PIN_8, LCD_PIN_8, LCD_PIN_8},
        /* 3 */
        {LCD_PIN_7, LCD_PIN_7 | LCD_PIN_8, LCD_PIN_7, LCD_PIN_8},
        /* 4 */
        {LCD_PIN_8, LCD_PIN_7 | LCD_PIN_8, LCD_PIN_7, 0},
        /* 5 */
        {LCD_PIN_7 | LCD_PIN_8, LCD_PIN_8, LCD_PIN_7, LCD_PIN_8},
        /* 6 */
        {LCD_PIN_7 | LCD_PIN_8, LCD_PIN_8, LCD_PIN_7 | LCD_PIN_8, LCD_PIN_8},
        /* 7 */
        {LCD_PIN_7, LCD_PIN_7, LCD_PIN_7, 0},
        /* 8 */
        {LCD_PIN_7 | LCD_PIN_8, LCD_PIN_7 | LCD_PIN_8, LCD_PIN_7 | LCD_PIN_8, LCD_PIN_8},
        /* 9 */
        {LCD_PIN_7 | LCD_PIN_8, LCD_PIN_7 | LCD_PIN_8, LCD_PIN_7, LCD_PIN_8},
        /* blank */
        {0, 0, 0, 0},
    },

    /* Digit 0 - Decimal */
    {
        /* 0 */
        {
            LCD_PIN_5 | LCD_PIN_6, /* COM0 */
            LCD_PIN_5 , /* COM1 */
            LCD_PIN_5 | LCD_PIN_6, /* COM2 */
            LCD_PIN_6  /* COM3 */
        },
        /* 1 */
        {0, LCD_PIN_5, LCD_PIN_5, 0},
        /* 2 */
        {LCD_PIN_5, LCD_PIN_5 | LCD_PIN_6, LCD_PIN_6, LCD_PIN_6},
        /* 3 */
        {LCD_PIN_5, LCD_PIN_5 | LCD_PIN_6, LCD_PIN_5, LCD_PIN_6},
        /* 4 */
        {LCD_PIN_6, LCD_PIN_5 | LCD_PIN_6, LCD_PIN_5, 0},
        /* 5 */
        {LCD_PIN_5 | LCD_PIN_6, LCD_PIN_6, LCD_PIN_5, LCD_PIN_6},
        /* 6 */
        {LCD_PIN_5 | LCD_PIN_6, LCD_PIN_6, LCD_PIN_5 | LCD_PIN_6, LCD_PIN_6},
        /* 7 */
        {LCD_PIN_5, LCD_PIN_5, LCD_PIN_5, 0},
        /* 8 */
        {LCD_PIN_5 | LCD_PIN_6, LCD_PIN_5 | LCD_PIN_6, LCD_PIN_5 | LCD_PIN_6, LCD_PIN_6},
        /* 9 */
        {LCD_PIN_5 | LCD_PIN_6, LCD_PIN_5 | LCD_PIN_6, LCD_PIN_5, LCD_PIN_6},
        /* blank */
        {0, 0, 0, 0},
    },

};


/**
 * Show the digits on the display.
 * NB: only kg
 */
void Screen_Update(LCD_HandleTypeDef *hlcd, uint8_t hundreds, uint8_t tens, uint8_t ones, uint8_t decimal) {

    /* COM0 */
    LCD->RAM[LCD_RAM_REGISTER0] = lcd_digits[0][hundreds][0]
            | lcd_digits[1][tens][0] | lcd_digits[2][ones][0]
            | lcd_digits[3][decimal][0];

    /* COM1 */
    LCD->RAM[LCD_RAM_REGISTER2] = lcd_digits[0][hundreds][1]
            | lcd_digits[1][tens][1] | lcd_digits[2][ones][1]
            | lcd_digits[3][decimal][1];

    /* COM2 */
    LCD->RAM[LCD_RAM_REGISTER4] = lcd_digits[0][hundreds][2]
            | lcd_digits[1][tens][2] | lcd_digits[2][ones][2]
            | lcd_digits[3][decimal][2];

    /* COM3 */
    LCD->RAM[LCD_RAM_REGISTER6] = lcd_digits[0][hundreds][3]
            | lcd_digits[1][tens][3] | lcd_digits[2][ones][3]
            | lcd_digits[3][decimal][3];

    // Decimal point (always on)
    LCD->RAM[LCD_RAM_REGISTER6] |= LCD_PIN_7;

    // Kg  (always on)
    LCD->RAM[LCD_RAM_REGISTER0] |= LCD_PIN_4;

    HAL_LCD_UpdateDisplayRequest(hlcd);
}

/**
 * Start blinking the display.
 */
void Screen_BlinkStart(LCD_HandleTypeDef *hlcd) {
    LCD->FCR |= LCD_BLINKMODE_ALLSEG_ALLCOM | LCD_BLINKFREQUENCY_DIV512;
}

/**
 * Stop blinking the display.
 */
void Screen_BlinkStop(LCD_HandleTypeDef *hlcd) {
    LCD->FCR &= ~(LCD_BLINKMODE_ALLSEG_ALLCOM);
}

/**
 * Clear the display.
 */
void Screen_Clear(LCD_HandleTypeDef *hlcd) {
    LCD->RAM[LCD_RAM_REGISTER0] = 0;
    LCD->RAM[LCD_RAM_REGISTER2] = 0;
    LCD->RAM[LCD_RAM_REGISTER4] = 0;
    LCD->RAM[LCD_RAM_REGISTER6] = 0;
    HAL_LCD_UpdateDisplayRequest(hlcd);
}
