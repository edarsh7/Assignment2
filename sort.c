#include "merge.h" 
#include <stdio.h>
#include <pthread.h> 

int curr_td = 0;

typedef struct arr_props{
  int* values;
  int size;
}arr_props;                                                                                                                                                                                                                                                                       

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
  
}

/* 
 * This function stub needs to be completed
 */
void multiThreadedMergeSort(int arr[], int left, int right) 
{
  arr_props new_arr;
  new_arr.size = sizeof(arr)/sizeof(arr[0]);
  new_arr.values = (int*)malloc(sizeof(int)*new_arr.size);

  memcpy(new_arr.values, arr, new_arr.size);
  printf("arx= %d\n", new_arr.values[0]);


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
