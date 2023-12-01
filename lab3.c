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

// validate function
void* validate(void* param){
    param_struct* p = (param_struct*) param;

    int usedNumbers [] = {0,0,0,0,0,0,0,0,0};
    int row = p->starting_row;
    int rowEnd = p->ending_row;
    int col = p->starting_col;
    int colEnd = p->ending_col;
    int id = p->id;

    
    
    for (int i = row; i <= rowEnd; i++ ){
        for (int j = col; j <= colEnd; j++){

            int element = sudoku_board[i][j]-1;
            usedNumbers[element] = 1;

        }
    }

    int sum = 0;
    for (int num = 0; num < 9; num++){
        sum+=usedNumbers[num];
    }

    if (sum =! 9){
        worker_validation[id] = 0;
    }

    worker_validation[id] = 1;

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
    
    // grids
    for (int row = 0; row < ROW_SIZE; row += 3){
        for (int col = 0; col < COL_SIZE; col += 3){
            parameter[num].id = num;
            parameter[num].starting_row = row;
            parameter[num].starting_col = col;
            parameter[num].ending_row = row+2;
            parameter[num].ending_col = col+2;

            pthread_create(&(tid[num]),&attr, validate, &(parameter[num]));
            validate(&(parameter[num]));
            num++;
        }
    }

    // cols
    for (int col = 0; col < COL_SIZE; col += 3){
    
        parameter[num].id = num;
        parameter[num].starting_row = 0;
        parameter[num].starting_col = col;
        parameter[num].ending_row = ROW_SIZE-1;
        parameter[num].ending_col = col;

        pthread_create(&(tid[num]),&attr,validate, &(parameter[num]));
        validate(&(parameter[num]));
        num++;
    }

    // rows
    for (int row = 0; row < ROW_SIZE; row+=3){
    
        parameter[num].id = num;
        parameter[num].starting_row = row;
        parameter[num].starting_col = 0;
        parameter[num].ending_row = row;
        parameter[num].ending_col = COL_SIZE-1;

        pthread_create(&(tid[num]),&attr,validate, &(parameter[num]));
        validate(&(parameter[num]));
        num++;
            
    }

    for(int index = 0; index< NUM_OF_THREADS; index++) 
        pthread_join(tid[index], NULL);
    
    for (int thread = 0; thread< NUM_OF_THREADS; thread++)
        if(worker_validation[thread] != 1)return 0;

    free(worker_validation);
    free(tid);
    return 1;


    
}


