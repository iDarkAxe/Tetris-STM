/*
Calcul dimensionnement anti rebond

220nF * 45KΩ  =  8.8 ms
*/

/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <string.h>


//play window
int stack[20][10] = 
   {{0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,1,0,1,0},
    {0,0,0,1,1,1,1,1,1,1}};


//structure to locate the current tetramino in the game
typedef struct{
    int coordY;
    int coordX;
    int piece[4][4];
}TETRAMINO_ATM;

//prototype declaration
void addPieceIntoStack(TETRAMINO_ATM* tetraminoAtm);

int main()
{
    int piece[4][4] = {{0,1,1,0},{0,1,1,0},{0,1,1,0},{0,1,1,0}};
    int piece90[4][4] = {{0,1,1,1},{0,1,1,1},{0,1,1,0},{0,1,1,0}};
    TETRAMINO_ATM tetraminoAtm = {0,2};
    memcpy(tetraminoAtm.piece, piece, sizeof(piece));
    addPieceIntoStack(&tetraminoAtm);
    for(int i = 0; i<20;i++){
        for(int j = 0; j<10;j++){
            printf("%d", stack[i][j]);
        }
        printf("\n");
    }
    return 0;
}

void addPieceIntoStack(TETRAMINO_ATM* tetraminoAtm){
    for (int i = 0; i < 4; i++) {
        memcpy(&stack[tetraminoAtm->coordY+i][tetraminoAtm->coordX], tetraminoAtm->piece[i], sizeof(tetraminoAtm->piece[i]));
    }
}
