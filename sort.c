#include "merge.h"
#include <iostream> 
#include <pthread.h> 

/* LEFT index and RIGHT index of the sub-array of ARR[] to be sorted */
void singleThreadedMergeSort(int arr[], int left, int right) 
{
  if (left < right) {
    int middle = (left+right)/2;
    singleThreadedMergeSort(arr, left, middle); 
    singleThreadedMergeSort(arr, middle+1, right); 
    merge(arr, left, middle, right); 
  } 
}

void * thread_ms(void * arg)
{
  printf("sum is now: %d \n", sum);
  sum++;
}

/* 
 * This function stub needs to be completed
 */
void multiThreadedMergeSort(int arr[], int left, int right) 
{
  pthread_t threads[4];
  int sum = 0;
  
  for(int i=0; i< 4; i++)
  {
    pthread_create(&threads[i], NULL, thread_ms,(void*)NULL)
  }

  for(int j=0; j<4; j++)
  {
    pthread_join(threads[i], NULL);
  }

}
