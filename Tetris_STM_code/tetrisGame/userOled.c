/**
  ******************************************************************************
  * @file           : userOled.c
  * @brief          : Others functions for Oled drawing
  ******************************************************************************
  * @date 08 février 2024
  ******************************************************************************
  */

#include "userOled.h"

/** @brief Draw the border of the game
  */
void drawBorder(){
	ssd1306_Fill(Black);
	ssd1306_DrawRectangle(0, 0, 127, 63, White);
	ssd1306_DrawRectangle(1, 1, 126, 62, White);
	ssd1306_UpdateScreen();
}

/** @brief Draw a normal tile
  */
void drawTile(uint8_t x, uint8_t y, SSD1306_COLOR color){
	ssd1306_FillRectangle(x, y, x+5, y+5, color);
}

/** @brief Draw the entire stack
 * @param stack[][]: the stack of the game
  */
void drawStack(int stack[23][16]){
	uint8_t i, j;
	for (i = 0; i < 20; ++i) {
		for (j = 3; j < 13; ++j) {
			if (stack[i][j]) {
				drawTile((i*6)+6, (12-j)*6+2, White);
			}
			else{
				drawTile((i*6)+6, (12-j)*6+2, Black);
			}
		}
	}
	ssd1306_UpdateScreen();
}

/** @brief Plays the gameOver Animation
  */
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

void drawTetrisStartGame()
{

}
