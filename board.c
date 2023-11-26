/**
 * Assignment: life
 * Name :Rahul Jones
 * PID: A17330596
 * Class: UCSD CSE30-SP21
 *
 */
#include "cse30life.h"
#include "board.h"


/**
 * create a new board
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which is the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc bufferA and bufferB 
 * - Set currentBuffer and nextBuffer
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, set the cell in the current buffer
 * - close the file
 * - return the boards pointer if successfull or NULL ptr otherwise
 */
boards_t * createBoard(char *initFileName){
  
  FILE* fp;
  if((fp = fopen(initFileName, "r")) == NULL){
    return NULL;
  }
  boards_t* gameBoard = (boards_t*)malloc(sizeof(boards_t));
  fscanf(fp, "%d", &(gameBoard->numRows));
  fscanf(fp, "%d", &(gameBoard->numCols));
  gameBoard->gen = 0;

  gameBoard->bufferA = (belem*)malloc(gameBoard->numRows *gameBoard->numCols* sizeof(belem));
  gameBoard->bufferB=(belem*)malloc(gameBoard->numRows* gameBoard->numCols*sizeof(belem));
  gameBoard->currentBuffer = gameBoard->bufferA;
  gameBoard->nextBuffer = gameBoard->bufferB;
  clearBoards(gameBoard);

  int col = 0;
  int row = 0;
  while (fscanf(fp, "%d %d", &row, &col)>0) {
      gameBoard->currentBuffer[getIndex(gameBoard->numCols, row, col)] = 1;
  }
  fclose(fp);
  return gameBoard;
  
}



/**
 * delete a board
 */
void deleteBoard(boards_t **bptrPtr){
  // TODO:
  boards_t* board = *bptrPtr;

    free((*bptrPtr)->bufferA);
    free((*bptrPtr)->bufferB);

    (*bptrPtr)->bufferA = NULL;
    (*bptrPtr)->bufferB = NULL;
    (*bptrPtr)->currentBuffer = NULL;
    (*bptrPtr)->nextBuffer = NULL;
    (*bptrPtr)->numRows = 0;
    (*bptrPtr)->numCols = 0;
    (*bptrPtr)->gen = 0;

    free(board);
    *bptrPtr = NULL;
}
/**
 * set all the belems in both buffers to 0
 */
void clearBoards(boards_t *self){
  // TODO:
  //memset(self->bufferA, 0, self->numRows * self->numCols * sizeof(belem));
  //memset(self->bufferB, 0, self->numRows * self->numCols * sizeof(belem));
  for(int i = 0; i<self->numRows*self->numCols; i++){
    self->bufferA[i] = 0;
    self->bufferB[i] = 0;
  }
  
}

/**
 * swap the current and next buffers
 */
void swapBuffers(boards_t *self){
  belem *bufferHolder = self->currentBuffer;
  self->currentBuffer = self->nextBuffer;
  self->nextBuffer = bufferHolder;
  
}


/**
 * get a cell index
 */
size_t getIndex(size_t numCols, size_t row, size_t col){
  return row*numCols+col;
}
  
