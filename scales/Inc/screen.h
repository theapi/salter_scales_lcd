/**
 * LCD screen found in Salter bathroom scales.
 *
 *
 * 3V, 1/4 Duty, 1/3 bias
 *
 *
           A
      ----------
      |         |
     F|         |B
      |         |
      -----G-----
      |         |
     E|         |C
      |         |    _   _
      -----------   |_| |_|COLON
           D
 *
 */

    /**LCD GPIO Configuration
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
    */

#ifndef __screen_H
#define __screen_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32l0xx_hal.h"
#include "main.h"


#define LCD_PIN_4  0x01
#define LCD_PIN_5  0x02
#define LCD_PIN_6  0x04
#define LCD_PIN_7  0x08
#define LCD_PIN_8  0x10
#define LCD_PIN_9  0x20
#define LCD_PIN_10 0x40
#define LCD_PIN_11 0x80
#define LCD_PIN_12 0x100


void Screen_Update(LCD_HandleTypeDef *hlcd, uint8_t hundreds, uint8_t tens, uint8_t ones, uint8_t decimal);
void Screen_BlinkStart(LCD_HandleTypeDef *hlcd);
void Screen_BlinkStop(LCD_HandleTypeDef *hlcd);
void Screen_Clear(LCD_HandleTypeDef *hlcd);

#ifdef __cplusplus
}
#endif
#endif /*__screen_H */

