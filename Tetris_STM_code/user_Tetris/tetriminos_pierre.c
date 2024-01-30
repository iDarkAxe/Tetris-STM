/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
typedef struct{
    int *piece1;
    int *piece2;
    
    int *piece3;
    
    int *piece4;
    int *piece5;

    int *piece6;
    int *piece7;
    int *piece8;
    int *piece9;
    
    int *pieceA;
    int *pieceB;
    int *pieceC;
    int *pieceD;
}LISTE_TETRIMINOS;

LISTE_TETRIMINOS liste_tetriminos;

//zigzag only 2 directions
int zigzag[4][4]= {{0,0,0,0}
                  ,{1,1,0,0}
                  ,{0,1,1,0}
                  ,{0,0,0,0}};
int zigzag_h[4][4] = {{0,0,1,0}
                     ,{0,1,1,0}
                     ,{0,1,0,0}
                     ,{0,0,0,0}};
//cube only 1 direction                  
int cube[4][4]= {{0,0,0,0}
                ,{0,1,1,0}
                ,{0,1,1,0}
                ,{0,0,0,0}};
//line only 2 directions                  
int line_hl[4][4]= {{0,1,0,0}
                   ,{0,1,0,0}
                   ,{0,1,0,0}
                   ,{0,1,0,0}};
int line_rg[4][4]= {{0,0,0,0}
                  ,{1,1,1,1}
                  ,{0,0,0,0}
                  ,{0,0,0,0}};                  
//T piece 4 directions
int T_l[4][4] = {{0,0,0,0}
                ,{1,1,1,0}
                ,{0,1,0,0}
                ,{0,0,0,0}};
int T_h[4][4] = {{0,0,0,0}
               ,{0,1,0,0}
               ,{1,1,1,0}
               ,{0,0,0,0}};
int T_r[4][4] = {{0,0,1,0}
                ,{0,1,1,0}
                ,{0,0,1,0}
                ,{0,0,0,0}};            
int T_g[4][4] = {{0,1,0,0}
                ,{0,1,1,0}
                ,{0,1,0,0}
                ,{0,0,0,0}}; 
//L piece 4 directions             
int L_h[4][4]= {{0,1,0,0}
               ,{0,1,0,0}
               ,{0,1,1,0}
               ,{0,0,0,0}};
int L_l[4][4]= {{0,1,1,0}
               ,{0,0,1,0}
               ,{0,0,1,0}
               ,{0,0,0,0}};
int L_r[4][4]= {{0,0,0,0}
               ,{0,1,1,1}
               ,{0,1,0,0}
               ,{0,0,0,0}};
int L_g[4][4]= {{0,0,0,0}
               ,{1,1,1,0}
               ,{0,0,1,0}
               ,{0,0,0,0}};

int main()
{
    for(int j=0; j<4; j++){
        for(int i=0; i<4; i++){
            printf("%d", L_r[i][j]);
        }
        printf("\n");
    }

    return 0;
}
