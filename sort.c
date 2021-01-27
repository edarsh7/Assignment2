#include "merge.h" 
#include <stdio.h>
#include <pthread.h> 

int curr_td = 0;                                                                                                                                                                                                                                                                          

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
  int x = curr_td++;
  int thread_part = part++; 
  
    // calculating low and high 
    int low = thread_part * (MAX / 4); 
    int high = (thread_part + 1) * (MAX / 4) - 1; 
  
    // evaluating mid point 
    int mid = low + (high - low) / 2; 
    if (low < high) { 
        singleThreadedMergeSort(arg, low, mid); 
        singleThreadedMergeSort(arg, mid + 1, high); 
        merge(low, mid, high); 
    } 
  
  
}

/* 
 * This function stub needs to be completed
 */
void multiThreadedMergeSort(int arr[], int left, int right) 
{
  pthread_t threads[4];
  
  
  for(int i=0; i< 4; i++)
  {
    pthread_create(&threads[i], NULL, thread_ms,(void *)arr);
  }

  for(int j=0; j<4; j++)
  {
    pthread_join(threads[j], NULL);
  }

}
