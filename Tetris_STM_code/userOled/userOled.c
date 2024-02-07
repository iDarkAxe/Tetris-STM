/*
 * userOled.c
 *
 *  Created on: Feb 7, 2024
 *      Author: VACHER
 */

#include "userOled.h"
#include "usart.h"
#include "string.h"

// Screen object
static SSD1306_t SSD1306;

void drawBorder(){
	ssd1306_Fill(Black);
	ssd1306_DrawRectangle(0, 0, 127, 63, White);
	ssd1306_DrawRectangle(1, 1, 126, 62, White);
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

void drawTetrisStartGame(){
	char* stringTetris = "Tetris";
	ssd1306_SetCursorVertical(20, (SSD1306_HEIGHT-strlen(stringTetris)*Font_7x10.FontWidth)/2+strlen(stringTetris)*Font_7x10.FontWidth);
	ssd1306_WriteStringVertical(stringTetris, Font_7x10_new, White);
	ssd1306_SetCursorVertical(45, 46);
	ssd1306_WriteStringVertical("Click", Font_6x8, White);
	ssd1306_SetCursorVertical(55, 37);
	ssd1306_WriteStringVertical("to", Font_6x8, White);
	ssd1306_SetCursorVertical(65, 46);
	ssd1306_WriteStringVertical("Start", Font_6x8, White);
}

void clearPlayZone(){
	ssd1306_FillRectangle(2, 2, 125, 61, Black);
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


char ssd1306_WriteCharVertical(char ch, FontDef Font, SSD1306_COLOR color) {
    uint32_t i, b, j;

    // Check if character is valid
    if (ch < 32 || ch > 126)
        return 0;

    // Check remaining space on current line
    if (SSD1306_WIDTH < (SSD1306.CurrentX + Font.FontHeight) ||
        0 >= (SSD1306.CurrentY - Font.FontWidth))
    {
        // Not enough space on current line
        return 0;
    }
    // Use the font to write
    for(i = 0; i < Font.FontHeight; i++) {
        b = Font.data[(ch - 32) * Font.FontHeight + i];
        for(j = 0; j < Font.FontWidth; j++) {
            if((b << j) & 0x8000)  {
                ssd1306_DrawPixel(SSD1306.CurrentX + i, (SSD1306.CurrentY - j), (SSD1306_COLOR) color);
            } else {
                ssd1306_DrawPixel(SSD1306.CurrentX + i, (SSD1306.CurrentY - j), (SSD1306_COLOR)!color);
            }
        }
    }

    // The current space is now taken
    SSD1306.CurrentY -= Font.FontWidth;

    // Return written char for validation
    return ch;
}

/* Write full string to screenbuffer */
char ssd1306_WriteStringVertical(char* str, FontDef Font, SSD1306_COLOR color) {
    while (*str) {
        if (ssd1306_WriteCharVertical(*str, Font, color) != *str) {
            // Char could not be written
            return *str;
        }
        str++;
    }

    // Everything ok
    return *str;
}
void ssd1306_SetCursorVertical(uint8_t x, uint8_t y) {
    SSD1306.CurrentX = x;
    SSD1306.CurrentY = y;
}
