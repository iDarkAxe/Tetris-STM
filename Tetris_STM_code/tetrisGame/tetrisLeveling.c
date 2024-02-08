/**
  ******************************************************************************
  * @file           : tetrisLeveling.c
  * @brief          : Program for Tetris Leveling system
  ******************************************************************************

  ******************************************************************************
  */

#ifndef TETRISLEVELING_C_
#define TETRISLEVELING_C_

#include "../tetrisGame/tetrisLeveling.h"

int levelNumber = 0;

/**
  * @brief  Return levelNumber
  * @retval levelNumber
  */
int getLevelNumber()
{
	return levelNumber;
}

/**
  * @brief  Verify and change levelNumber
  * @param _numberOfLineCompleted: each level requires a numberOfLine completed to be incremented
  */
void newLevelCalculate(int _numberOfLineCompleted)
{
	if(_numberOfLineCompleted >= (10*levelNumber)){
		levelNumber+= 1;
	}
	//TODO GERER LA VITESSE DU JEU
}

#endif /* TETRISLEVELING_C_ */
