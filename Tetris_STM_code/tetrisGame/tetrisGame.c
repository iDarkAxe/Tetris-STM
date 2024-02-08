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
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h> // memcpy
#include <stdlib.h> // random
#include "tetrisScoring.h"
#include "userOled.h"

#define PIECE_TOUCHED 2
#define PIECE_FALLED 1
#define FALL_COOLDOWN 0

#define PLAY_STATE 0
#define SCORE_STATE 1
#define SPAWN_STATE 2
#define GAMEOVER_STATE 3

/** @brief Zigzag piece in 4 by 4 grid
  */
int pieceZigzag[4][4]= {{0,0,0,0},
                        {1,1,0,0},
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
/** @brief T piece in 4 by 4 grid
  */
int pieceT[4][4]= { {0,0,0,0},
                    {1,1,1,0},
                    {0,1,0,0},
                    {0,0,0,0}};   


/** @brief PlayWindow
  */
int playStack[23][16] = 
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
    

/** @brief Structure to locate the current tetramino in the game
  */
typedef struct{
    int coordY;
    int coordX;
    int piece[4][4];
}TETRAMINO_ATM;


uint32_t nextFallTime = 0;

int fallDelay = 1000;   // les diminuer au fil du temps/level ?
int rotateFallDelay = 500;
int moveFallDelay = 500;

/** @brief Inputs du jeu, permet de simplifier le code
  */
enum inputs { gauche = 0, droite = 1, bas = 2, rotate = 3, menu = 4};   

//declaration fonctions
void addPieceIntoStack(TETRAMINO_ATM*);  // int[][16]
void removePieceFromStack(TETRAMINO_ATM*);
int isClippingInStack(TETRAMINO_ATM*);
int falling(TETRAMINO_ATM*);
void printStack(void);
int movePiece(TETRAMINO_ATM*, int);
int rotatePiece(TETRAMINO_ATM*);
int getLineCompleted();
void removeLine(int);
void moveDownStack(int);
void randomPiece(TETRAMINO_ATM*);


int tetrisGame()
{
	//TODO REFLECHIR SI ON VEUT VRAIMENT DE LA RNG OU PAS
    // Structure avec la pièce
    TETRAMINO_ATM tetramino;

    char pieceMoved = 0;
    int userInput = 5;
    int fallState;
    int gameState = SPAWN_STATE;
    
    while(1)
    {
        switch(gameState)
        {
            case PLAY_STATE:
            	if(1)	//si exti n'importe quelle touche
                {
//                	userInput = 's';  //TODO changer pour détecter les inputs
					//old : userInput = getch();
            		switch(userInput)
            		{
            		case gauche:
            			if(movePiece(&tetramino, gauche)){
                            pieceMoved = 1;
                        }
            			break;
            		case droite:
						if(movePiece(&tetramino, droite)){
                            pieceMoved = 1;
                        }
						break;
            		case bas:
						//TODO TESTER la clock
                    	nextFallTime = HAL_GetTick() + 0; // trigger fall immediatly when falling() is called (below)
//                        nextFallTime = clock() + 0;
                    	break;
            		case rotate:
						if(rotatePiece(&tetramino)){
                            pieceMoved = 1;
                        }
						break;
            		case 19:	//TODO on implémente ou pas ?
            			gameState = GAMEOVER_STATE;
            			break;
            		default:
            			break;	//TODO gerer les erreurs
            		}
                }

                fallState = falling(&tetramino);

                if(fallState == PIECE_FALLED){
                    pieceMoved = 1;
                }

                if(pieceMoved == 1) //piece moved, so update the display
                {
                    pieceMoved = 0;
                    addPieceIntoStack(&tetramino);
                    drawStack(playStack);
                    removePieceFromStack(&tetramino);
                }

                if(fallState == PIECE_TOUCHED)
                {
                    gameState = SCORE_STATE;
                }

            break;


        case SCORE_STATE:
            addPieceIntoStack(&tetramino);  //piece wont move anymore, add it to stack before score calculation
            calculateScore(getLineCompleted());
            drawStack(playStack);
            printf("score : %ld\n", getScore());
            gameState = SPAWN_STATE;
            
            break;


        case SPAWN_STATE:
            tetramino.coordY = 0;
            tetramino.coordX = 7;
            randomPiece(&tetramino);

            if(isClippingInStack(&tetramino)){
                gameState = GAMEOVER_STATE;
            } else {
                addPieceIntoStack(&tetramino);
                drawStack(playStack);
                removePieceFromStack(&tetramino);
                gameState = PLAY_STATE;
            }

            break;


        case GAMEOVER_STATE:
            printf("\nGame over !\n");
            printf("Score total : %ld\n", getScore());
            printf("\nAppuyez sur entree pour quitter...\n");
            getchar();
            return 0;
        }
    }
    return 0;
}

/** @brief Permet de placer une pièce dans le jeu
 *  @param *tetraminoAtm: Current tetramino used
  */
void addPieceIntoStack(TETRAMINO_ATM* tetraminoAtm){
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(tetraminoAtm->piece[i][j] == 1){
                playStack[tetraminoAtm->coordY+i][tetraminoAtm->coordX+j] = 1;                
            }
        }
    }
}

/** @brief Permet de supprimer une pièce du jeu
 *  @param *tetraminoAtm: Current tetramino used
  */
void removePieceFromStack(TETRAMINO_ATM* tetraminoAtm){
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(tetraminoAtm->piece[i][j] == 1){
                playStack[tetraminoAtm->coordY+i][tetraminoAtm->coordX+j] = 0;                
            }
        }
    }
}

/** @brief Permet prédire si la pièce va rentrer en colision avec les blocs déjà présents
 *  @param *tetraminoAtm: Current tetramino used
 * 
 *  @retval state: 1 if would clip, 0 if not
  */
int isClippingInStack(TETRAMINO_ATM* tetraminoAtm)
{
    for(int i = 0; i < 4; i++){
        for(int j = 0 ; j < 4; j++){
            if((playStack[i+tetraminoAtm->coordY][j+tetraminoAtm->coordX] == 1) && tetraminoAtm->piece[i][j] == 1) {
                //printf("collision\n");
                return 1;
            }
        }
    }
    return 0;
}

/** @brief Permet de faire descendre naturellement une pièce du jeu
 *  @param *tetraminoAtm: Current tetramino used
 * 
 *  @retval state: PIECE_TOUCHED, or PIECE_FALLED
  */
int falling(TETRAMINO_ATM* tetraminoAtm)
{
    if(HAL_GetTick() < nextFallTime){
        return FALL_COOLDOWN;
    }
    nextFallTime = HAL_GetTick() + fallDelay;

    tetraminoAtm->coordY += 1;
    if(isClippingInStack(tetraminoAtm)){
        tetraminoAtm->coordY -= 1;  // cancel the fall
        return PIECE_TOUCHED;       // piece touched something below
    } else {
        return PIECE_FALLED;
    }
}

/** @brief Affiche la stack sur le terminal
  */
void printStack(void)
{
    printf("\n\n\n");
    for(int i = 0; i < 23; i++){
        for(int j = 0; j < 16; j++){
            printf("%d", playStack[i][j]);
        }
        printf("\n");
    }
    return;
}

/** @brief Permet de déplacer une pièce en fonction de sa direction
 *  @param *tetraminoAtm: Current tetramino used
 *  @param direction: 
 *  @retval state: //TODO ????? JE MET quoi là ?
  */
int movePiece(TETRAMINO_ATM* tetraminoAtm, int direction)
{
    int movement = 0;   //TODO OPTIMISER POUR SUPPRIMER movement

    if(direction == gauche) {
        movement = -1;
    } 
    else if(direction == droite) {
        movement = 1;
    }

    tetraminoAtm->coordX += movement;

    if(isClippingInStack(tetraminoAtm)) {
        tetraminoAtm->coordX -= movement;
        return 0;
    } else {
        nextFallTime = HAL_GetTick() + moveFallDelay; // piece moved, so add delay before next fall
        return 1;
    }
}

/** @brief Permet tourner une pièce, seulement si elle ne va pas clip
 *  @param *tetraminoAtm: Current tetramino used
 *  @retval state: 1 if rotated and 0 if clipping
  */
int rotatePiece(TETRAMINO_ATM* tetraminoAtm)
{
    int tempCopy[4][4];
    memcpy(tempCopy, tetraminoAtm->piece, sizeof(tetraminoAtm->piece));

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
        tetraminoAtm->piece[i][j] = tempCopy[3 - j][i];
        }
    }

    if(isClippingInStack(tetraminoAtm)){
        //clips, so dont rotate, copy back original rotation
        memcpy(tetraminoAtm->piece, tempCopy, sizeof(tempCopy));
        return 0;
    } else {
        //managed to rotate, tetramino has been modified, all good
        nextFallTime = HAL_GetTick() + rotateFallDelay; // piece rotated, so add delay before next fall
        return 1;
    }
}

/**
  * @brief  calculate LineCompleted and moveDownStack if lineFull
  * @retval linesCount: number of Lines completed
  */
int getLineCompleted()
{
    int linesCount = 0;
    int isLineFull = 0;

    for(int i = (0+3) ; i < (23-3); i++){
        isLineFull = 0;
        for(int j = (0+3) ; j < (16-3) ; j++){
            if(playStack[i][j] == 0){
                isLineFull = 1;
            }
        }
        if(isLineFull == 0){  // line was full of 1's
            moveDownStack(i);
            linesCount++;
        }
    }
    return linesCount;
}

/** @brief Remove the selected line
 * @param  line: line selected
  */
void removeLine(int line)
{
    for(int i = (0+3); i < (16-3); i++){
        playStack[line][i] = 0;
    }
    return;
}

/** @brief Move all the stack  above "startLine" down by one line
 *  @param startLine: line which got cleared
  */
void moveDownStack(int startLine)
{
    for(int i = startLine; i > 0; i--){  // start from bottom, to the top
        memcpy(playStack+i, playStack+(i-1), sizeof(playStack[i]));
    }
    removeLine(0);  // and empty the 1st line
    return;
}

/** @brief Select a random piece among the tetraminos
 * @param  tetraminoAtm: list of tetraminos
  */
void randomPiece(TETRAMINO_ATM* tetraminoAtm)
{
    int randomPiece = rand() % 5; // [0 ; 4] car 5 pièces
    switch(randomPiece)
    {
        case 0:
            memcpy(tetraminoAtm->piece, pieceZigzag, sizeof(pieceZigzag));
            break;

        case 1:
            memcpy(tetraminoAtm->piece, pieceBar, sizeof(pieceBar));
            break;

        case 2:
            memcpy(tetraminoAtm->piece, pieceSquare, sizeof(pieceSquare));
            break;

        case 3:
            memcpy(tetraminoAtm->piece, pieceL, sizeof(pieceL));
            break;

        case 4:
            memcpy(tetraminoAtm->piece, pieceT, sizeof(pieceT));
            break;
    }

    int rotationCount = rand() % 4;  // [0 ; 3] entre 0 et 3 rotations
    for(int i = 0; i < rotationCount; i++){
        if(!rotatePiece(tetraminoAtm))   // try to apply random rotation
        {
            break;  // if couldn't rotate, stop trying
        }
    }
    return;
}
