/**
  ******************************************************************************
  * @file           : tetrisGame.c
  * @brief          : Main program of the Tetris Game
  ******************************************************************************
  * @date 08 février 2024
  * @mainpage Tetris Game
  * @section Introduction
  *
  * Ce jeu de Tetris a entièrement été réalisé par Adrien Kerfriden, Lou Vacher et Pierre Pontet.
  *
  * Il a été conçu pour fonctionner sur une carte STM32 L031K6.
  *
  * Il suffit de brancher 5 boutons, sur les broches PA1, PA3, PA4, PA6 et PA7.
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h> // memcpy
#include <stdlib.h> // random
#include <tim.h>

#include "tetrisScoring.h"
#include "userOled.h"

#define PIECE_TOUCHED 2
#define PIECE_FALLED 1
#define FALL_COOLDOWN 0


/** @brief Game States
  */
enum game_state { PLAY_STATE = 0, SCORE_STATE = 1, SPAWN_STATE = 2, GAMEOVER_STATE = 3, START_STATE = 4};

/** @brief Zigzag piece in 4 by 4 grid
  */
int pieceZigzag[4][4]= {{0,0,0,0},
                        {1,1,0,0},
                        {0,1,1,0},
                        {0,0,0,0}};
/** @brief S piece in 4 by 4 grid
  */
int pieceS[4][4]= 	{{0,0,0,0},
                    {0,0,1,1},
                    {0,1,1,0},
                    {0,0,0,0}};
/** @brief Bar piece in 4 by 4 grid
  */
int pieceBar[4][4]= {   {0,1,0,0},
                        {0,1,0,0},
                        {0,1,0,0},
                        {0,1,0,0}};
/** @brief Square piece in 4 by 4 grid
  */
int pieceSquare[4][4]= {{0,0,0,0},
                        {0,1,1,0},
                        {0,1,1,0},
                        {0,0,0,0}};         
/** @brief L piece in 4 by 4 grid
  */
int pieceL[4][4]= { {0,0,0,0},
                    {0,1,0,0},
                    {0,1,0,0},
                    {0,1,1,0}};
/** @brief J piece in 4 by 4 grid
  */
int pieceJ[4][4]= { {0,0,0,0},
                    {0,0,1,0},
                    {0,0,1,0},
                    {0,1,1,0}};
/** @brief T piece in 4 by 4 grid
  */
int pieceT[4][4]= { {0,0,0,0},
                    {1,1,1,0},
                    {0,1,0,0},
                    {0,0,0,0}};   


/** @brief PlayZone
  */
int playZone[23][16] =
    {{1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
    

/** @brief Structure to locate the current tetrimino in the game
  */
typedef struct{
    int coordY;
    int coordX;
    int piece[4][4];
}TETRIMINO;


uint32_t nextFallTime = 0;

int fallDelay = 1000;
int rotateFallDelay = 500;
int moveFallDelay = 500;
int userInput = 0;	//stocke les entrées de l'utilisateur

/** @brief Inputs du jeu, permet de simplifier le code
  */
enum inputs { gauche = -1, droite = 1, fall = 2, rotate = 3, menu = 4};

//declaration fonctions
void addPieceIntoPlayZone(TETRIMINO*);  // int[][16]
void removePieceFromPlayZone(TETRIMINO*);
int isClippingInPlayZone(TETRIMINO*);
int falling(TETRIMINO*);
void printPlayZone(void);
int movePiece(TETRIMINO*, int);
int rotatePiece(TETRIMINO*);
int getLinesCompleted();
void removeLine(int);
void resetPlayZone();
void moveDownPlayZone(int);
void randomPiece(TETRIMINO*);
void tetrisInit();

/** @brief Permet d'initialiser le jeu
  */
void tetrisInit(){
  ssd1306_Init();
  drawBorder();
  drawTetrisStartGame();
  ssd1306_UpdateScreen();
}

/** @brief Permet de lancer le jeu
 *  @retval 0 si erreur
  */
int tetrisGame()
{
	HAL_Delay(1000);	//Temps d'attente car il faut attendre que les condensateurs de l'écran soient chargés avant de commencer
	//TODO REFLECHIR SI ON VEUT VRAIMENT DE LA RNG OU PAS
    // Structure avec la pièce
    TETRIMINO tetrimino;

    char pieceMoved = 0;
    int fallState;
    int gameState = START_STATE;
    while(1)
    {
        switch(gameState)
        {
            case PLAY_STATE:
            	switch(userInput)
            		{
            		case gauche:
            			if(movePiece(&tetrimino, gauche)){
                            pieceMoved = 1;
                        }
            			break;
            		case droite:
						if(movePiece(&tetrimino, droite)){
                            pieceMoved = 1;
                        }
						break;
            		case fall:
                    	nextFallTime = HAL_GetTick() + 0; // trigger fall immediatly when falling() is called (below)
                    	break;
            		case rotate:
						if(rotatePiece(&tetrimino)){
                            pieceMoved = 1;
                        }
						break;
            		default:
            			break;
            		}
            		userInput = 0;


                fallState = falling(&tetrimino);

                if(fallState == PIECE_FALLED){
                    pieceMoved = 1;
                }

                if(pieceMoved == 1) //piece moved, so update the display
                {
                    pieceMoved = 0;
                    addPieceIntoPlayZone(&tetrimino);
                    drawPlayZone(playZone);
                    removePieceFromPlayZone(&tetrimino);
                }

                if(fallState == PIECE_TOUCHED)
                {
                    gameState = SCORE_STATE;
                }

            break;


        case SCORE_STATE:
            addPieceIntoPlayZone(&tetrimino);  //piece wont move anymore, add it to play zone before score calculation
            calculateScore(getLinesCompleted());
            drawPlayZone(playZone);
            printf("score : %ld\n", getScore());
            gameState = SPAWN_STATE;
            
            break;


        case SPAWN_STATE:
            tetrimino.coordY = 0;
            tetrimino.coordX = 7;
            randomPiece(&tetrimino);

            if(isClippingInPlayZone(&tetrimino)){
                gameState = GAMEOVER_STATE;
            } else {
                addPieceIntoPlayZone(&tetrimino);
                drawPlayZone(playZone);
                removePieceFromPlayZone(&tetrimino);
                gameState = PLAY_STATE;
            }

            break;

        case GAMEOVER_STATE:
        	drawGameOver();
        	while(HAL_GPIO_ReadPin(menuButton_GPIO_Port, menuButton_Pin)){
        		Clignotement_Click();
		    }
        	resetPlayZone();
        	gameState = START_STATE;
            break;

        case START_STATE:
		  tetrisInit();
		  HAL_Delay(1000);
		  while(HAL_GPIO_ReadPin(menuButton_GPIO_Port, menuButton_Pin)){
			  Clignotement_Click();
		  }
		  clearPlayZone();
		  gameState = SPAWN_STATE;
        	break;

        default:
        	return 0;

        }
    }
    return 0;
}

/** @brief Permet de placer la pièce dans le jeu
 *  @param *currentTetrimino: Current tetrimino used
  */
void addPieceIntoPlayZone(TETRIMINO* currentTetrimino){
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(currentTetrimino->piece[i][j] == 1){
                playZone[currentTetrimino->coordY+i][currentTetrimino->coordX+j] = 1;
            }
        }
    }
}

/** @brief Permet de supprimer la pièce du jeu
 *  @param *currentTetrimino: Current tetrimino used
  */
void removePieceFromPlayZone(TETRIMINO* currentTetrimino){
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(currentTetrimino->piece[i][j] == 1){
                playZone[currentTetrimino->coordY+i][currentTetrimino->coordX+j] = 0;
            }
        }
    }
}

/** @brief Permet de détecter si la pièce rentrerait en collision avec les blocs déjà présents
 *  @param *currentTetrimino: Current tetrimino used
 * 
 *  @retval state: 1 if would clip, 0 if not
  */
int isClippingInPlayZone(TETRIMINO* currentTetrimino)
{
    for(int i = 0; i < 4; i++){
        for(int j = 0 ; j < 4; j++){
            if((playZone[i+currentTetrimino->coordY][j+currentTetrimino->coordX] == 1) && currentTetrimino->piece[i][j] == 1) {
                //printf("collision\n");
                return 1;
            }
        }
    }
    return 0;
}

/** @brief Permet de gérer la chute de la pièce
 *  @param *currentTetrimino: Current tetrimino used
 * 
 *  @retval state: PIECE_TOUCHED, or PIECE_FALLED
  */
int falling(TETRIMINO* currentTetrimino)
{
    if(HAL_GetTick() < nextFallTime){
        return FALL_COOLDOWN;
    }
    nextFallTime = HAL_GetTick() + fallDelay;

    currentTetrimino->coordY += 1;
    if(isClippingInPlayZone(currentTetrimino)){
        currentTetrimino->coordY -= 1;  // cancel the fall
        return PIECE_TOUCHED;       	// piece touched something below
    } else {
        return PIECE_FALLED;
    }
}

/** @brief Affiche la play zone sur le terminal
  */
void printPlayZone(void)
{
    printf("\n\n\n");
    for(int i = 0; i < 23; i++){
        for(int j = 0; j < 16; j++){
            printf("%d", playZone[i][j]);
        }
        printf("\n");
    }
    return;
}

/** @brief Permet de déplacer une pièce vers la gauche ou la droite
 *  @param *currentTetrimino: Current tetrimino used
 *  @param direction: userInputs
 *  @retval state: 1 si déplacement OK, 0 si non
  */
int movePiece(TETRIMINO* currentTetrimino, int direction)
{
    currentTetrimino->coordX += direction;

    if(isClippingInPlayZone(currentTetrimino)) {
        currentTetrimino->coordX -= direction;
        return 0;
    } else {
        nextFallTime = HAL_GetTick() + moveFallDelay; // piece moved, so add delay before next fall
        return 1;
    }
}

/** @brief Permet de pivoter de 90° une pièce, seulement si elle ne va pas clip
 *  @param *currentTetrimino: Current tetrimino used
 *  @retval state: 1 if rotated and 0 if clipping
  */
int rotatePiece(TETRIMINO* currentTetrimino)
{
    int tempCopy[4][4];
    memcpy(tempCopy, currentTetrimino->piece, sizeof(currentTetrimino->piece));

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
        currentTetrimino->piece[i][j] = tempCopy[3 - j][i];
        }
    }

    if(isClippingInPlayZone(currentTetrimino)){
        //clips, so dont rotate, copy back original rotation
        memcpy(currentTetrimino->piece, tempCopy, sizeof(tempCopy));
        return 0;
    } else {
        //managed to rotate, tetrimino has been modified, all good
        nextFallTime = HAL_GetTick() + rotateFallDelay; // piece rotated, so add delay before next fall
        return 1;
    }
}

/**
  * @brief  Calculate amount of lines completed, and shifts down the playZone accordingly
  * @retval linesCount: number of Lines completed
  */
int getLinesCompleted()
{
    int linesCount = 0;
    int isLineFull = 0;

    for(int i = (0+3) ; i < (23-3); i++){
        isLineFull = 0;
        for(int j = (0+3) ; j < (16-3) ; j++){
            if(playZone[i][j] == 0){
                isLineFull = 1;
            }
        }
        if(isLineFull == 0){  // line was full of 1's
            moveDownPlayZone(i);
            linesCount++;
        }
    }
    return linesCount;
}

/** @brief Remove the selected line (fill it with 0)
 * @param  line: line selected
  */
void removeLine(int line)
{
    for(int i = (0+3); i < (16-3); i++){
        playZone[line][i] = 0;
    }
    return;
}

/** @brief Reset the PlayZone
  */
void resetPlayZone()
{
	for(int line = 0; line < 20; line ++){
		removeLine(line);
	}
}

/** @brief Move all the play zone  above "startLine" down by one line
 *  @param startLine: line which got cleared
  */
void moveDownPlayZone(int startLine)
{
    for(int i = startLine; i > 0; i--){  // start from bottom, to the top
        memcpy(playZone+i, playZone+(i-1), sizeof(playZone[i]));
    }
    removeLine(0);  // and empty the 1st line
    return;
}

/** @brief Select a random piece among the tetriminos
 * @param  currentTetrimino: list of tetriminos
  */
void randomPiece(TETRIMINO* currentTetrimino)
{
    int randomPiece = rand() % 7; // [0 ; 6] car 7 pièces
    switch(randomPiece)
    {
        case 0:
            memcpy(currentTetrimino->piece, pieceZigzag, sizeof(pieceZigzag));
            break;

        case 1:
            memcpy(currentTetrimino->piece, pieceBar, sizeof(pieceBar));
            break;

        case 2:
            memcpy(currentTetrimino->piece, pieceSquare, sizeof(pieceSquare));
            break;

        case 3:
            memcpy(currentTetrimino->piece, pieceL, sizeof(pieceL));
            break;

        case 4:
            memcpy(currentTetrimino->piece, pieceT, sizeof(pieceT));
            break;
        case 5:
		   memcpy(currentTetrimino->piece, pieceS, sizeof(pieceS));
		   break;
        case 6:
		   memcpy(currentTetrimino->piece, pieceJ, sizeof(pieceJ));
		   break;
    }

    int rotationCount = rand() % 4;  // [0 ; 3] entre 0 et 3 sens de rotations
    for(int i = 0; i < rotationCount; i++){
        if(!rotatePiece(currentTetrimino))   // try to apply random rotation
        {
            break;  // if couldn't rotate, stop trying
        }
    }
    return;
}

/** @brief Reduce the delay of fallTime
  */
void reduceFallDelay()
{
	if(fallDelay <= 200){
		if(fallDelay > 50){
			fallDelay -= 50;
		}
		return;
	}

	fallDelay -= 100;
}

/** @brief Gestion des interruptions
 * @param  GPIO_Pin: Pin sur lequel a lieu l'interruption
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	switch(GPIO_Pin){
		case rightButton_Pin:
		case leftButton_Pin:
		case rotateButton_Pin:
		case fallButton_Pin:
			HAL_TIM_Base_Start_IT(&htim22);
			break;
		default:
			break;
	}
}

/** @brief Fin du timer pour lire les boutons
 * @param  *htim: timer
  */
// Callback: timer has rolled over
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	  if (htim == &htim22 )
	  {
		if(!HAL_GPIO_ReadPin(leftButton_GPIO_Port, leftButton_Pin)){
			userInput = gauche;
		}
		if(!HAL_GPIO_ReadPin(rightButton_GPIO_Port, rightButton_Pin)){
			userInput = droite;
		}
		if(!HAL_GPIO_ReadPin(rotateButton_GPIO_Port, rotateButton_Pin)){
			userInput = rotate;
		}
		if(!HAL_GPIO_ReadPin(fallButton_GPIO_Port, fallButton_Pin)){
			userInput = fall;
		}
		if(!HAL_GPIO_ReadPin(menuButton_GPIO_Port, menuButton_Pin)){
			userInput = menu;
		}
		HAL_TIM_Base_Stop_IT(&htim22);
		__HAL_TIM_SET_COUNTER(&htim22, 0);
	  }
}
