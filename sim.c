/**
 * Assignment: life
 * Name: Rahul Jones
 * PID: A17330596
 * Class: UCSD CSE30-SP21
 *
 */
#include "sim.h"

#define CIMP
extern void asm_doRow(belem *, belem *, size_t, size_t, size_t);

/**
 * gets x mod N (works for negative numbers as well! Use this instead of %)
 */
size_t getModVal(int x, size_t N){
     size_t adj = x/N;

     return((x+adj*N)%N);
}

/**
 * process one row of the board
 */
static void doRow(belem *dest, belem *src, size_t row, size_t rows, size_t cols){
  // TODO: 
  
  size_t colLeftCompare;
  size_t colRightCompare;
  size_t rowTopCompare;
  size_t rowBottomCompare;
  
  for(int i = 0; i<cols; i++){
    int counter = 0;
    colLeftCompare = getModVal(i-1+cols,cols);
    colRightCompare=getModVal(i+1+cols, cols);
    rowTopCompare=getModVal(row-1+rows, rows);
    rowBottomCompare=getModVal(row+1+rows, rows);

      counter+=(int)src[getIndex(cols, rowTopCompare, colLeftCompare)];
      counter+=(int)src[getIndex(cols, rowTopCompare, i)];
      counter+=(int)src[getIndex(cols, rowTopCompare, colRightCompare)];
      counter+=(int)src[getIndex(cols, row, colRightCompare)];
      counter+=(int)src[getIndex(cols, row, colLeftCompare)];
      counter+=(int)src[getIndex(cols, rowBottomCompare, colLeftCompare)];
      counter+=(int)src[getIndex(cols, rowBottomCompare, i)];
      counter+=(int)src[getIndex(cols, rowBottomCompare, colRightCompare)];

    if(src[row*cols+i]!= 0){
      if(counter ==0 || counter == 1){
        dest[row*cols+i] = 0;
      }
      else if(counter ==2 || counter == 3){
        dest[row*cols+i] = 1;
      }
      else{
        dest[row*cols+i] = 0;
      }
    }
    else if(src[row*cols+i]== 0){
      if(counter==3){
        dest[row*cols+i] = 1;
      }
      else{
        dest[row*cols+i] = 0;
      }
    }
  }
}


/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 */
void simLoop(boards_t *self, unsigned int steps){
  // TODO:
  for(int i = 0; i<steps; i++){
    for(int j = 0; j<self->numRows; j++){
      doRow(self->nextBuffer, self->currentBuffer, j, self->numRows, self->numCols);
    }
    swapBuffers(self);
    self->gen+=1;
  }
}