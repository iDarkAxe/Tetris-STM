/**
  ******************************************************************************
  * @file           : tetrisLeveling.c
  * @brief          : Program for Tetris Leveling system
  ******************************************************************************
  * @date 08 février 2024
  ******************************************************************************
  */

#ifndef TETRISLEVELING_C_
#define TETRISLEVELING_C_

#include "../tetrisGame/tetrisLeveling.h"

uint8_t levelNumber = 0;

/**
  * @brief  Return levelNumber
  * @retval levelNumber
  */
uint8_t getLevelNumber()
{
	return levelNumber;
}

/**
  * @brief  Verify and change levelNumber
  * @param _numberOfLineCompleted: each level requires a numberOfLine completed to be incremented
  */
void newLevelCalculate(uint8_t _numberOfLineCompleted)
{
	if(_numberOfLineCompleted >= (10*levelNumber)){
		levelNumber+= 1;
	}

	//TODO GERER LA VITESSE DU JEU
}

#endif /* TETRISLEVELING_C_ */
