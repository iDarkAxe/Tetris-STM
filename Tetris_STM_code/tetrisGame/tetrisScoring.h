/*
 * tetrisScoring.h
 *
 *  Created on: Feb 1, 2024
 *      Author: PONTET
 */

#ifndef TETRISSCORING_H_
#define TETRISSCORING_H_

#include "main.h"


uint16_t getScore();
void addScore(uint8_t numberOfLineCompleted);

void printScore();

#endif /* TETRISSCORING_H_ */
