#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "lab3.h"

extern int** sudoku_board;
int* worker_validation;

int** read_board_from_file(char* filename){
    FILE *fp = NULL;
    int** board = NULL;

    fp = fopen(filename, "r");
    board = (int**)malloc(sizeof(int*)*ROW_SIZE);
    
    for(int row = 0; row <ROW_SIZE; row++){
        board[row] = (int*)malloc(sizeof(int)*COL_SIZE);
    }

    for(int row = 0; row < ROW_SIZE; row++){
        for (int col = 0; col < COL_SIZE; col++){
            fscanf(fp,"%d,",&(board[row][col]));
        }
    }

    for(int row = 0; row < ROW_SIZE; row++){
        for (int col = 0; col < COL_SIZE-1; col++){
            printf("%d,",board[row][col]);
        }
        printf("%d\n",board[row][COL_SIZE-1]);
    }

    fclose(fp);
    return board;
}


int is_board_valid(){
    pthread_t* tid;  /* the thread identifiers */
    pthread_attr_t attr;
    param_struct* parameter;

    tid = (pthread_t*)malloc(sizeof(int)*NUM_OF_THREADS);
    parameter =(param_struct*)malloc(sizeof(param_struct)*NUM_OF_THREADS); 
    
        for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++)
        {
            
            // Create thread for 3x3
            if (i%3 == 0 && j%3 == 0)
            {
                
            }

            // Create thread for cols
            if (j == 0)
            {
                
            }

            // Create thread for rows 
            if (i == 0)
            {
                
            }
        }
    }

    return 0;
}


