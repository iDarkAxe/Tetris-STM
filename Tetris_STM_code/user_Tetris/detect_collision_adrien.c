#include <stdio.h>

int main()
{
    
    char stack[20][10] = {0};   // 20 lignes, 10 colonnes
    char piece[4][4] = {{0,1,0,0},
                        {0,1,0,0},
                        {0,1,0,0},
                        {0,1,0,0}};   
    char x_piece = 4;
    char y_piece = 3;
    for(int i = 0;i<10;i++){
        stack[5][i] = 1;    // créer une ligne pleine 
    }
    
    
    
    //-- DEBUT FONCTION DETECTION COLLISION AVEC STACK --//
    
    char piece_tab[20][10] = {0};   // tableau avec piece a emplacement reel
    
    for(int i = 0 ; i < 4 ; i++) {
        for(int j = 0; j < 4; j++) {
            piece_tab[y_piece + i-1][x_piece + j-1] = piece[i][j];
        }
    }

    for(int i = 0; i < 20; i++){
        for(int j = 0;j<10;j++){
            if((stack[i][j] == piece_tab[i][j]) && piece_tab[i][j] == 1) {
                printf("collision\n");
            }
        }
    }
    
    
    //-- FIN FONCTION --//    
    
    
    
    for(int i = 0; i < 20; i++){
        for(int j = 0;j<10;j++){
            printf("%d",piece_tab[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    
    
    
    for(int i = 0; i < 20; i++){
        for(int j = 0;j<10;j++){
            printf("%d",stack[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    
    
    return 0;
}
