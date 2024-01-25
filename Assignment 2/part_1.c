#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "t1.h"


//Fills the array with ascending, consecutive numbers, starting from 0.
void fill_ascending(int *array, int size) //0,1,2,3,4,5
{

    for (int i=0; i<size; i++){
        array[i] = i;
    }
    
}
//Fills the array with descending numbers, starting from size-1
void fill_descending(int *array, int size) //5,4,3,2,1
{
    for (int i=0; i<size ; i++){
        array[i] = size-i-1;
    }
    
}

//Fills the array with uniform numbers.
void fill_uniform(int *array, int size) //4,4,4,4,4
{
    int num = rand()%size; //get random num, max is size

    for(int i= 0; i<size; i++){
        array[i] = num;
    }
    
}

//Fills the array with random numbers within 0 and size-1. Duplicates are allowed.
void fill_with_duplicates(int *array, int size)
{
    for(int i = 0; i<size; i++){
        int random = rand() % size;
        array[i] = random;
    }
}

//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int *array, int size)
{
   
    fill_ascending(array, size);

    for(int i=0; i<size; i++){
        int rindex = rand()%(size-1); //random index between 0 and size-1
        // swaps
        int temp = array[i];
        array[i] = array[rindex];
        array[rindex] = temp;
    }
}

void printArray(int* arr, int size){
  int i;
  for(i=0; i<size;i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main()
{
    int size = 55;
    int array [size];
    

    fill_with_duplicates(array, size);
    printArray(array, size);
    quickSort(array, size);
    printArray(array, size);

    return 0;

}
