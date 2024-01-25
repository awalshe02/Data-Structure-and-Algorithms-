#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include "t2.h"

int number_comparisons = 0;
int number_swaps = 0;

void swap(int* a, int* b){ // swapping function
    int temp = *a;
    *a = *b;
    *b = temp;
    number_swaps++;
}

void selectionSort(int arr[], int size) 
{ 
  for(int i=0; i<size-1 ; i++){
    int mindex = i; //set first index in array as min

    for(int j=i+1; j<size; j++){ // finding smallest num 

      number_comparisons++;

      if(arr[j] < arr[mindex]) //j num smaller than min
        mindex = j;  //set j as min
    }

    if(mindex != i){
      swap(&arr[mindex], &arr[i]); //swap min num with first num
    }  
  }
} 

void insertionSort(int arr[], int size) 
{ 
  for(int i=1; i<size; i++){
    int temp = arr[i]; //current 
    int j=i-1; // previous

    number_comparisons++;
    while(temp < arr[j] && j>=0){ //move nums that are bigger than temp one ahead of current position

      number_comparisons++;

      arr[j+1] = arr[j];
      j--;
      number_swaps++;
    }
    arr[j+1] = temp; //new temp aka. current
  }
}

int random_pivot_index(int start, int end){
  srand(time(NULL));
  return start + rand() % (end - start+ + 1); // generating random pivot index
}

int partition(int arr[], int start, int end){
  int pindex = random_pivot_index(start, end);
  int pvalue = arr[pindex];

  swap(&arr[pindex], &arr[end]);

  int i = start - 1;

  for(int j = start; j < end; j++){
    number_comparisons++;

    if(arr[j] < pvalue){ // less then pivot value
      i++;
      swap(&arr[i], &arr[j]); //moves smaller num to left of partition
    }
  }

  swap(&arr[i+1], &arr[end]); //pivot swapped int final position aka. middle of partition
  return i+1;
}

void newquickSort(int arr[], int start, int end){
  if(start < end){
    int part = partition(arr, start, end);

    newquickSort(arr, start, part-1); //left hand side
    newquickSort(arr, part+1, end); //right hand side
  }
}

void quickSort(int arr[], int size) 
{ 
 newquickSort(arr ,0, size-1);
 
}
