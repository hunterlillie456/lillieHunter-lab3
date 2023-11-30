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

// validates grid
int validate_grid(){
    // Test #1 Variable
        int sum = 0;
    
        // Test #2 Variables
  	    int one = 0;
  	    int two = 0;
  	    int three = 0;
        int four = 0;
        int five = 0;
        int six = 0;
        int seven = 0;
        int eight = 0;
        int nine = 0;

    for (int row = 0; row < ROW_SIZE; row++){

       	for (int col = 0; col <COL_SIZE; col++ ){

            // Test #1: sum = 45
            sum+=sudoku_board[row][col];

            // Test #2: No duplicates
            if (sudoku_board[row][col] == 1) {
               one = 1;
            }
            if (sudoku_board[row][col] == 2) {
               two = 1;
            }
            if (sudoku_board[row][col] == 3) {
               three = 1;
            }
            if (sudoku_board[row][col] == 4) {
               four = 1;
            }
            if (sudoku_board[row][col] == 5) {
               five = 1;
            }

            if (sudoku_board[row][col] == 6 ) {
               six = 1;
            }

            if (sudoku_board[row][col] == 7) {
               seven = 1;
            }

            if (sudoku_board[row][col] == 8) {
               eight = 1;
            }
            if (sudoku_board[row][col] == 9) {
               nine = 1;
            }
       	}
    }

    if (sum != 45) {
       return 0;
    }

    if (one*two*three*four*five*six*seven*eight*nine == 0){
       return 0;
    } 

    return 1;
}

//validates columns
int validate_col(){

}

//validates rows
int validate_row(){

    
}


int is_board_valid(){
    pthread_t* tid;  /* the thread identifiers */
    pthread_attr_t attr;
    param_struct* parameter;

    worker_validation = (int*)malloc(sizeof(int)*NUM_OF_THREADS);
    tid = (pthread_t*)malloc(sizeof(int)*NUM_OF_THREADS);
    parameter =(param_struct*)malloc(sizeof(param_struct)*NUM_OF_THREADS); 

    int num = 0;

    pthread_attr_init(&attr);
    
        for (int i = 0; i < ROW_SIZE; i++){
        for (int j = 0; j < COL_SIZE; j++)
        {
            
            // Create thread for 3x3
            if (i%3 == 0 && j%3 == 0)
            {
                parameter->id = num++;
                parameter->starting_row = i;
                parameter->starting_col = j;
                parameter->ending_row = i+1;
                parameter->ending_col = j+1;

                pthread_create(&(tid[i]),&attr,validate_grid, &(parameter[num]));
            }

            // Create thread for cols
            if (j == 0)
            {
                parameter->id = num++;
                parameter->starting_row = i;
                parameter->starting_col = j;
                parameter->ending_row = i;
                parameter->ending_col = j+1;
                pthread_create(&(tid[i]),&attr,validate_col, &(parameter[num]));
            }

            // Create thread for rows 
            if (i == 0)
            {
                parameter->id = num++;
                parameter->starting_row = i;
                parameter->starting_col = j;
                parameter->ending_row = i+1;
                parameter->ending_col = j;
                pthread_create(&(tid[i]),&attr,validate_row, &(parameter[num]));
            }
        }
    }

    return 0;
}


