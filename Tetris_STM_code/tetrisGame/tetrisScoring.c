/**
  ******************************************************************************
  * @file           : tetrisScoring.c
  * @brief          : Program for Tetris Scoring system
  ******************************************************************************
  * @date 08 février 2024
  ******************************************************************************
  */

#include "tetrisScoring.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include <stdio.h>
#include "tetrisLeveling.h"

uint32_t tetrisScore = 100000;
uint8_t piecePosee = 100;

/** @brief Getter of score
  * @retval Return the value of score
  */
uint32_t getScore(){
	return tetrisScore;
}

/** @brief Calculate the Score
 * @param  numberOfLineCompleted
  */
void calculateScore(int _numberOfLineCompleted){
	addScorePiece();
	addScoreLine(_numberOfLineCompleted);
	newLevelCalculate(_numberOfLineCompleted);
	return;
}

/** @brief  Add points to the score when a Piece fall to its place
*/
void addScorePiece()
{
	tetrisScore += piecePosee;
}

/**
  * @brief  Add points to the score,
  * 		using numberOfLineCompleted and levelNumber as factors
  * @param  numberOfLineCompleted: numberOfLineCompleted in one fall by a piece
  */
void addScoreLine(uint8_t _numberOfLineCompleted)
{
	//ajouter des points si on clique sur fallButton ? == augmenter la difficulté
	int levelNumber = getLevelNumber();
	switch(_numberOfLineCompleted){
	case 0:
		//pas de nouveau point
		break;
	case 1:
		tetrisScore += 100*levelNumber;
		break;
	case 2:
		tetrisScore += 300*levelNumber;
		break;
	case 3:
		tetrisScore += 500*levelNumber;
		break;
	case 4:
		tetrisScore += 800*levelNumber;
		break;
	case 5:
		//erreur CAS IMPOSSIBLE, il n'y a pas de
		break;
	}
}

/**
  * @brief  Print the score on the screen
  */
void printScore(){
	char strScore[12];
	sprintf(strScore, "%ld points", tetrisScore);
	ssd1306_SetCursor(10, 10);
	ssd1306_WriteString(strScore, Font_6x8, White);
	ssd1306_UpdateScreen();
}
