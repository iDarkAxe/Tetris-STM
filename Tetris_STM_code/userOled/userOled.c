/*
 * userOled.c
 *
 *  Created on: Feb 7, 2024
 *      Author: VACHER
 */

#include "userOled.h"

void createBorder(){
	ssd1306_Fill(Black);
	ssd1306_DrawRectangle(0, 0, 127, 63, White);
	ssd1306_DrawRectangle(1, 1, 126, 62, White);
	ssd1306_UpdateScreen();
}

void drawTile(uint8_t x, uint8_t y){
	ssd1306_FillRectangle(x, y, x+5, y+5, White);
}

void drawStack(int stack[23][16]){
	uint8_t i, j;
	for (i = 0; i < 20; ++i) {
		for (j = 3; j < 13; ++j) {
			if (stack[i][j]) {
				drawTile((i*6)+6, (12-j)*6+2);
			}
		}
	}
	ssd1306_UpdateScreen();
}

void gameOverAnimation(){
	for (int i = 0; i < 3; ++i) {
		ssd1306_WriteCommand(0xA6);
		ssd1306_UpdateScreen();
		HAL_Delay(200);
		ssd1306_WriteCommand(0xA7);
		ssd1306_UpdateScreen();
		HAL_Delay(200);
	}
	ssd1306_WriteCommand(0xA6);
	ssd1306_UpdateScreen();
}
