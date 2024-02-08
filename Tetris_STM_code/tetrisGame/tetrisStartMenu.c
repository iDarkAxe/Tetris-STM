/**
  ******************************************************************************
  * @file           : tetrisStartMenu.c
  * @brief          : Program to draw the Menu
  ******************************************************************************

  ******************************************************************************
  */

#include "../tetrisGame/tetrisStartMenu.h"


/** @brief Draw the start menu
  */
void tetrisStartMenu(SSD1306_COLOR color){
  tetrisBordureDecor(color);
  ssd1306_UpdateScreen();   //TODO METTRE LES FONCTIONS DE LOU ICI
  //afficher "Tetris The GAME"
  //afficher flèche click
  //afficher "Click to Start"
  //afficher les tetriminos
}
