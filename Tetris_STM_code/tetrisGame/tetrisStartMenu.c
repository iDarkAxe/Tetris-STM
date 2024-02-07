#include "tetrisStartMenu.h"

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
  ssd1306_DrawPixel(2, 59, color);
  ssd1306_DrawPixel(4, 60, color);
  ssd1306_DrawPixel(5, 58, color);

  ssd1306_DrawPixel(2, 56, color);
  ssd1306_DrawPixel(2, 57, color);
  ssd1306_DrawPixel(2, 58, color);

  ssd1306_DrawPixel(5, 61, color);
  ssd1306_DrawPixel(6, 61, color);
  ssd1306_DrawPixel(7, 61, color);

  //BORD DROIT BAS
  ssd1306_DrawPixel(124, 3, color);
  ssd1306_DrawPixel(126, 3, color);
  ssd1306_DrawPixel(125, 3, color);
  ssd1306_DrawPixel(125, 4, color);
  ssd1306_DrawPixel(123, 5, color);

  ssd1306_DrawPixel(121, 2, color);
  ssd1306_DrawPixel(122, 2, color);
  ssd1306_DrawPixel(123, 2, color);

  ssd1306_DrawPixel(126, 5, color);
  ssd1306_DrawPixel(126, 6, color);
  ssd1306_DrawPixel(126, 7, color);

  //BORD GAUCHE BAS		//A REFAIRE RIEN n'est BON
  ssd1306_DrawPixel(126, 62, color);
  ssd1306_DrawPixel(125, 61, color);
  ssd1306_DrawPixel(124, 61, color);
  ssd1306_DrawPixel(123, 60, color);
  ssd1306_DrawPixel(122, 59, color);

  ssd1306_DrawPixel(121, 57, color);
  ssd1306_DrawPixel(122, 58, color);
  ssd1306_DrawPixel(123, 59, color);

  ssd1306_DrawPixel(126, 62, color);
  ssd1306_DrawPixel(126, 62, color);
  ssd1306_DrawPixel(126, 62, color);
  HAL_Delay(100);
}

void tetrisStartMenu(SSD1306_COLOR color){
  tetrisBordureDecor(color);
  ssd1306_UpdateScreen();
  //afficher "Tetris The GAME"
  //afficher flèche click
  //afficher "Click to Start"
  //afficher les tetriminos
}
