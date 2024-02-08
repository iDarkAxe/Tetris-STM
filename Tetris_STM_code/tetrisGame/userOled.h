/*
 * userOled.h
 *
 *  Created on: Feb 7, 2024
 *      Author: VACHER
 */

#ifndef USEROLED_H_
#define USEROLED_H_

#include "main.h"
#include "ssd1306.h"

void drawBorder();
void drawTile(uint8_t x, uint8_t y, SSD1306_COLOR color);
void drawStack(int stack[23][16]);
void gameOverAnimation();
void ssd1306_SetCursorVertical(uint8_t x, uint8_t y);
char ssd1306_WriteStringVertical(char* str, FontDef Font, SSD1306_COLOR color);
void drawTetrisStartGame();
void clearPlayZone();

#endif /* USEROLED_H_ */
