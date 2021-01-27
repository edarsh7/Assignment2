#include "merge.h" 

#include <stdio.h>
#include <pthread.h> 

typedef struct arr_props{
  int* values;
  int left;
  int right;
}a_struct;                                                                                                                                                                                                                                                                       

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

/* This function will sort a quarter of the array based on the thread passed in*/
void * thread_ms_qt(void * strct)
{
  a_struct * qt_strct = (a_struct *) strct;

  singleThreadedMergeSort((*qt_strct).values, (*qt_strct).left, (*qt_strct).right);

  return NULL;
}


/* This function is called by the original pthread_create. It will create two more halves from its half and merge them after sorting from pthread_create function merge sort*/
void * thread_ms_hf(void * half)
{
  a_struct * hf_struct = (a_struct *) half;

  pthread_t left_td_hf;
  pthread_t right_td_hf;

  int mid_hf = ((*hf_struct).left + (*hf_struct).right)/2 ;

  a_struct a_left_hf;
  a_left_hf.values = (*hf_struct).values;
  a_left_hf.left = (*hf_struct).left;
  a_left_hf.right = mid_hf;

  a_struct a_right_hf;
  a_right_hf.values = (*hf_struct).values;
  a_right_hf.left = mid_hf + 1;
  a_right_hf.right = (*hf_struct).right;


  pthread_create(&left_td_hf, NULL, thread_ms_qt, (void *)&a_left_hf);
  pthread_create(&right_td_hf, NULL, thread_ms_qt, (void*)&a_right_hf);

  pthread_join(left_td_hf, NULL);
  pthread_join(right_td_hf, NULL);

  merge((*hf_struct).values, (*hf_struct).left, mid_hf, (*hf_struct).right);

  return NULL;
}

/* 
 * This function will create two threads to sort their respective halves of the same array using structures as arguments passed to pthread_create
 */
void multiThreadedMergeSort(int arr[], int left, int right) 
{
  pthread_t left_td;
  pthread_t right_td;

  int middle = (left+right)/2;

  a_struct a_left;
  a_left.values = arr;
  a_left.left = left;
  a_left.right = middle;

  a_struct a_right;
  a_right.values = arr;
  a_right.left = middle + 1;
  a_right.right = right;


  pthread_create(&left_td, NULL, thread_ms_hf, (void *)&a_left);
  pthread_create(&right_td, NULL, thread_ms_hf, (void*)&a_right);

  pthread_join(left_td, NULL);
  pthread_join(right_td, NULL);
  
  merge(arr, left, middle, right);

}
