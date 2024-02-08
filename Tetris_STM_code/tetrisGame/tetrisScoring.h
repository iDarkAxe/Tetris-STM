/*
 * tetrisScoring.h
 *
 *  Created on: Feb 1, 2024
 *      Author: PONTET
 */

#ifndef TETRISSCORING_H_
#define TETRISSCORING_H_

#include "main.h"


uint32_t getScore();
void calculateScore(int);
void addScorePiece();
void addScoreLine(uint8_t);

void printScore();

#endif /* TETRISSCORING_H_ */
