#include "main.h"
#include <string.h>
#include <stdint.h>

//LCD Pin Definitions
#define RS_PIN GPIO_PIN_9
#define RS_PORT GPIOA
#define EN_PIN GPIO_PIN_7
#define EN_PORT GPIOC
#define D4_PIN GPIO_PIN_5
#define D4_PORT GPIOB
#define D5_PIN GPIO_PIN_4
#define D5_PORT GPIOB
#define D6_PIN GPIO_PIN_10
#define D6_PORT GPIOB
#define D7_PIN GPIO_PIN_8
#define D7_PORT GPIOA
#define BL_PIN GPIO_PIN_6
#define BL_PORT GPIOB

#define LCD_COLS 16
#define LCD_ROWS 2

void lcdInit(void);
void lcdClear(void);
void lcdSetCursor(uint8_t row, uint8_t col);
void lcdPrint(char* str);

