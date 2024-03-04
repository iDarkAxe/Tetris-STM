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

#include "tetrisLeveling.h"
#include "tetrisGame.h"

uint8_t levelNumber = 1;
uint32_t totalLinesCompleted = 0;

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
	totalLinesCompleted += _numberOfLineCompleted;
	if(totalLinesCompleted >= 10*levelNumber){
		levelNumber+= 1;
		reduceFallDelay();
	}

}

#endif /* TETRISLEVELING_C_ */
