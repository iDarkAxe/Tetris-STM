/**
  ******************************************************************************
  * @file           : userOled.c
  * @brief          : Others functions for Oled drawing
  ******************************************************************************
  * @date 08 février 2024
  ******************************************************************************
  */

#include "userOled.h"
#include "tetrisScoring.h"

// Screen object
static SSD1306_t SSD1306;

/** @brief Draw the border of the game
  */
void drawBorder(){
	ssd1306_Fill(Black);
	ssd1306_DrawRectangle(0, 0, 127, 63, White);
	ssd1306_DrawRectangle(1, 1, 126, 62, White);
	ssd1306_UpdateScreen();
}

/** @brief Draw a normal tile
 *  @param x,y: position de la Tile à changer
 *  @param color: couleur de la Tile
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
void drawGameOver(){
	Clignotement_Ecran();
	ssd1306_WriteCommand(0xA6);
	ssd1306_UpdateScreen();
	clearPlayZone();
	ssd1306_SetCursorVertical(30, 46);
	ssd1306_WriteStringVertical("Game", Font_7x10_new, White);
	ssd1306_SetCursorVertical(40, 46);
	ssd1306_WriteStringVertical("Over", Font_7x10_new, White);
	printScore();
	drawTetriminos();
	ssd1306_UpdateScreen();
}

/** @brief Plays the StartMenu Animation
  */
void drawTetrisStartGame(){
	ssd1306_SetCursorVertical(20, 52);
	ssd1306_WriteStringVertical("Tetris", Font_7x10_new, White);
	ssd1306_SetCursorVertical(32, 41);
	ssd1306_WriteStringVertical("the", Font_7x10_new, White);
	ssd1306_SetCursorVertical(44, 45);
	ssd1306_WriteStringVertical("GAMe", Font_7x10_new, White);
	ssd1306_SetCursorVertical(90, 46);
	ssd1306_WriteStringVertical("Click", Font_6x8_new, White);
	tetrisBordureDecor(White);
	drawTetriminos();
}

/** @brief Clear the PlayZone
  */
void clearPlayZone(){
	ssd1306_FillRectangle(2, 2, 125, 61, Black);
}

/** @brief Ecrit un caractère verticalement
 *  @param ch: caractère à afficher
 *  @param Font: police sélectionnée
 *  @param color: couleur sélectionnée
  */
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

/** @brief Ecrit une chaîne de caractères verticalement
 *  @param str: chaîne de caractères à afficher
 *  @param Font: police sélectionnée
 *  @param color: couleur sélectionnée
  */
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

/** @brief Déplace le curseur à sa position Verticale
 *  @param x,y : position du curseur à changer
  */
void ssd1306_SetCursorVertical(uint8_t x, uint8_t y) {
    SSD1306.CurrentX = x;
    SSD1306.CurrentY = y;
}

/** @brief Draw the decor
 *  @param color: couleur sélectionnée
  */
void tetrisBordureDecor(SSD1306_COLOR color)
{
  //BORD DROIT HAUT
  ssd1306_DrawPixel(2, 3, color);
  ssd1306_DrawPixel(3, 2, color);
  ssd1306_DrawPixel(4, 3, color);
  ssd1306_DrawPixel(3, 4, color);
  ssd1306_DrawPixel(5, 5, color);

  ssd1306_DrawPixel(5, 2, color);
  ssd1306_DrawPixel(6, 2, color);
  ssd1306_DrawPixel(7, 2, color);

  ssd1306_DrawPixel(2, 5, color);
  ssd1306_DrawPixel(2, 6, color);
  ssd1306_DrawPixel(2, 7, color);

  //BORD GAUCHE HAUT
  ssd1306_DrawPixel(2, 60, color);
  ssd1306_DrawPixel(3, 61, color);
  ssd1306_DrawPixel(3, 59, color);
  ssd1306_DrawPixel(4, 60, color);
  ssd1306_DrawPixel(5, 58, color);

  ssd1306_DrawPixel(2, 56, color);
  ssd1306_DrawPixel(2, 57, color);
  ssd1306_DrawPixel(2, 58, color);

  ssd1306_DrawPixel(5, 61, color);
  ssd1306_DrawPixel(6, 61, color);
  ssd1306_DrawPixel(7, 61, color);

  //BORD DROIT BAS
  ssd1306_DrawPixel(124, 2, color);
  ssd1306_DrawPixel(125, 3, color);
  ssd1306_DrawPixel(123, 3, color);
  ssd1306_DrawPixel(124, 4, color);
  ssd1306_DrawPixel(122, 5, color);

  ssd1306_DrawPixel(120, 2, color);
  ssd1306_DrawPixel(121, 2, color);
  ssd1306_DrawPixel(122, 2, color);

  ssd1306_DrawPixel(125, 5, color);
  ssd1306_DrawPixel(125, 6, color);
  ssd1306_DrawPixel(125, 7, color);

  //BORD GAUCHE BAS
  ssd1306_DrawPixel(124, 61, color);
  ssd1306_DrawPixel(124, 59, color);
  ssd1306_DrawPixel(125, 60, color);
  ssd1306_DrawPixel(123, 60, color);
  ssd1306_DrawPixel(122, 58, color);

  ssd1306_DrawPixel(125, 56, color);
  ssd1306_DrawPixel(125, 57, color);
  ssd1306_DrawPixel(125, 58, color);

  ssd1306_DrawPixel(120, 61, color);
  ssd1306_DrawPixel(121, 61, color);
  ssd1306_DrawPixel(122, 61, color);
}

/** @brief Affiche les tetriminos en bas du StartMenu
  */
void drawTetriminos(){
	ssd1306_FillRectangle(110, 50, 118, 52, White);//L
	ssd1306_FillRectangle(116, 47, 118, 49, White);
	ssd1306_FillRectangle(113, 39, 118, 44, White);//carre
	ssd1306_FillRectangle(113, 31, 115, 36, White);//Zigzag
	ssd1306_FillRectangle(116, 28, 118, 33, White);
	ssd1306_FillRectangle(107, 23, 118, 25, White);//barre
	ssd1306_FillRectangle(113, 12, 115, 20, White);//T
	ssd1306_FillRectangle(116, 15, 118, 17, White);
}

void Clignotement_Ecran()
{
	for (int i = 0; i < 3; ++i) {
		ssd1306_WriteCommand(0xA6);
		ssd1306_UpdateScreen();
		HAL_Delay(200);
		ssd1306_WriteCommand(0xA7);
		ssd1306_UpdateScreen();
		HAL_Delay(200);
	}
}

void Clignotement_Click()
{
	static uint32_t tick = 0, lastTick = 0;
	tick = HAL_GetTick();
	if(tick - lastTick >= 800)
	{
		lastTick = tick;
		ssd1306_SetCursorVertical(90, 46);
		ssd1306_WriteStringVertical("Click", Font_6x8_new, Black);
	}
	else
	{
		ssd1306_SetCursorVertical(90, 46);
		ssd1306_WriteStringVertical("Click", Font_6x8_new, White);
	}
	ssd1306_UpdateScreen();
}
