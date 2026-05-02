#include "lcd.h"

static inline void lcdDelayUsSoft(uint32_t us) {
	for (volatile uint32_t i = 0; i < us * 5; i++) { __NOP();}
}

static void lcdPulseEnable(void) {
	HAL_GPIO_WritePin(EN_PORT, EN_PIN, GPIO_PIN_SET);
	lcdDelayUsSoft(50);
	HAL_GPIO_WritePin(EN_PORT, EN_PIN, GPIO_PIN_RESET);
	lcdDelayUsSoft(50);
}

static void lcdWrite4(uint8_t nibble) {
	HAL_GPIO_WritePin(D4_PORT, D4_PIN, (nibble & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D5_PORT, D5_PIN, (nibble & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D6_PORT, D6_PIN, (nibble & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D7_PORT, D7_PIN, (nibble & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	lcdPulseEnable();
}

static void lcdWrite(uint8_t value, uint8_t rs) {
	HAL_GPIO_WritePin(RS_PORT, RS_PIN, rs ? GPIO_PIN_SET : GPIO_PIN_RESET);
	lcdWrite4((value >> 4) & 0x0F);
	lcdWrite4(value & 0x0F);
}

void lcdCommand(uint8_t cmd) {
	lcdWrite(cmd, 0);
	if (cmd == 0x01 || cmd == 0x02) HAL_Delay(2);
}

static void lcdData(uint8_t data) {
	lcdWrite(data, 1);
}

void lcdInit(void) {
	HAL_GPIO_WritePin(BL_PORT, BL_PIN, GPIO_PIN_SET);

	HAL_Delay(50);

	HAL_GPIO_WritePin(RS_PORT, RS_PIN, GPIO_PIN_RESET);

	lcdWrite4(0x03); HAL_Delay(5);
	lcdWrite4(0x03); HAL_Delay(5);
	lcdWrite4(0x03); HAL_Delay(5);
	lcdWrite4(0x02); HAL_Delay(5);

	lcdCommand(0x28);
	lcdCommand(0x0C);
	lcdCommand(0x01);
	lcdCommand(0x06);
}

void lcdClear(void) {
	lcdCommand(0x01);
}

void lcdSetCursor(uint8_t row, uint8_t col) {
	if (row >= LCD_ROWS) row = LCD_ROWS - 1;
	if (col >= LCD_COLS) col = LCD_COLS - 1;

	uint8_t base = (row == 0) ? 0x00 : 0x40;
	lcdCommand(0x80 | (base + col));
}

void lcdPrint(char* str) {
	while (*str) {
		lcdData((uint8_t)*str++);
	}
}
