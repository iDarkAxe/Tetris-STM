#include <stdio.h>
#include <string.h> // memcpy
#include <conio.h>  // get la touche
#include <time.h>   // délai avec clock()
#include <stdlib.h> // random

#define MOVE_LEFT -1
#define MOVE_RIGHT 1

#define PIECE_TOUCHED 2
#define PIECE_FALLED 1
#define FALL_COOLDOWN 0

#define PLAY_STATE 0
#define SCORE_STATE 1
#define SPAWN_STATE 2
#define GAMEOVER_STATE 3


int pieceZigzag[4][4]= {{0,0,0,0},
                        {1,1,0,0},
                        {0,1,1,0},
                        {0,0,0,0}};


int pieceBar[4][4]= {   {0,1,0,0},
                        {0,1,0,0},
                        {0,1,0,0},
                        {0,1,0,0}};

int pieceSquare[4][4]= {{0,0,0,0},
                        {0,1,1,0},
                        {0,1,1,0},
                        {0,0,0,0}};         

int pieceL[4][4]= { {0,0,0,0},
                    {0,1,0,0},
                    {0,1,0,0},
                    {0,1,1,0}};

int pieceT[4][4]= { {0,0,0,0},
                    {1,1,1,0},
                    {0,1,0,0},
                    {0,0,0,0}};   


//play window
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
    
//structure to locate the current tetramino in the game
typedef struct{
    int coordY;
    int coordX;
    int piece[4][4];
}TETRAMINO_ATM;


long int nextFallTime = 0;

int fallDelay = 1000;   // les diminuer au fil du temps/score ?
int rotateFallDelay = 500;
int moveFallDelay = 500;


//declaration fonctions
void addPieceIntoStack(TETRAMINO_ATM*);  // int[][16]
void removePieceFromStack(TETRAMINO_ATM*);
int isClippingInStack(TETRAMINO_ATM*);
int falling(TETRAMINO_ATM*);
void printStack(void);
int movePiece(TETRAMINO_ATM*, int);
int rotatePiece(TETRAMINO_ATM*);
int scoreCalculation(void);
void removeLine(int);
void moveDownStack(int);
void randomPiece(TETRAMINO_ATM*);


int main()
{
    // Init the RNG
    srand(time(NULL));

    // Structure avec la pièce
    TETRAMINO_ATM tetramino;

    char pieceMoved = 0;
    char userInput;   
    int fallState;
    int gameState = SPAWN_STATE;
    int scoreTotal = 0;
    
    while(1)
    {
        switch(gameState)
        {
            case PLAY_STATE:
                if(kbhit())
                {
                    userInput = getch();

                    if(userInput == 'q')
                    {
                        if(movePiece(&tetramino, MOVE_LEFT)){
                            pieceMoved = 1;
                        }
                    } 
                    else if(userInput == 'd')
                    {
                        if(movePiece(&tetramino, MOVE_RIGHT)){
                            pieceMoved = 1;
                        }
                    }
                    else if(userInput == 's')
                    {
                        nextFallTime = clock() + 0; // trigger fall immediatly when falling() is called (below)
                    }
                    else if(userInput == 'r')
                    {
                        if(rotatePiece(&tetramino)){
                            pieceMoved = 1;
                        }
                    }
                    else if(userInput == ' ')
                    {
                        gameState = GAMEOVER_STATE;
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
                    printStack();
                    removePieceFromStack(&tetramino);
                }

                if(fallState == PIECE_TOUCHED)
                {
                    gameState = SCORE_STATE;
                }

            break;


        case SCORE_STATE:
            addPieceIntoStack(&tetramino);  //piece wont move anymore, add it to stack before score calculation
            scoreTotal += scoreCalculation();
            printStack();
            printf("score : %d\n", scoreTotal);
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
                printStack();
                removePieceFromStack(&tetramino);
                gameState = PLAY_STATE;
            }

            break;


        case GAMEOVER_STATE:
            printf("\nGame over !\n");
            printf("Score total : %d\n", scoreTotal);
            printf("\nAppuyez sur entree pour quitter...\n");
            getchar();
            return 0;
        }
    }
    return 0;
}


void addPieceIntoStack(TETRAMINO_ATM* tetraminoAtm){
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(tetraminoAtm->piece[i][j] == 1){
                playStack[tetraminoAtm->coordY+i][tetraminoAtm->coordX+j] = 1;                
            }
        }
    }
}


void removePieceFromStack(TETRAMINO_ATM* tetraminoAtm){
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(tetraminoAtm->piece[i][j] == 1){
                playStack[tetraminoAtm->coordY+i][tetraminoAtm->coordX+j] = 0;                
            }
        }
    }
}


// returns 1 if the current piece would clip into the stack
// else returns 0
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


int falling(TETRAMINO_ATM* tetraminoAtm)
{
    if(clock() < nextFallTime){
        return FALL_COOLDOWN;
    }
    nextFallTime = clock() + fallDelay;

    tetraminoAtm->coordY += 1;
    if(isClippingInStack(tetraminoAtm)){
        tetraminoAtm->coordY -= 1;  // cancel the fall
        return PIECE_TOUCHED;       // piece touched something below
    } else {
        return PIECE_FALLED;
    }
}


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


int movePiece(TETRAMINO_ATM* tetraminoAtm, int direction)
{
    int movement = 0;

    if(direction == MOVE_LEFT) {
        movement = -1;
    } 
    else if(direction == MOVE_RIGHT) {
        movement = 1;
    }

    tetraminoAtm->coordX += movement;

    if(isClippingInStack(tetraminoAtm)) {
        tetraminoAtm->coordX -= movement;
        return 0;
    } else {
        nextFallTime = clock() + moveFallDelay; // piece moved, so add delay before next fall
        return 1;
    }
}


// returns 1 if rotation was applied, or 0 if it didnt rotate because of clipping
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
        nextFallTime = clock() + rotateFallDelay; // piece rotated, so add delay before next fall
        return 1;
    }
}


int scoreCalculation(void)
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


void removeLine(int line)
{
    for(int i = (0+3); i < (16-3); i++){
        playStack[line][i] = 0;
    }
    return;
}


void moveDownStack(int startLine)
{
    //all lines above "startLine" will shift 1 tile down
    for(int i = startLine; i > 0; i--){  // start from bottom, to the top
        memcpy(playStack+i, playStack+(i-1), sizeof(playStack[i]));
    }
    
    removeLine(0);  // and empty the 1st line
    return;
}


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
