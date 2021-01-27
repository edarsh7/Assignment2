#include "merge.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 

int curr_td = 0;

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

void * thread_ms_qt(void * strct)
{
  a_struct * td_strct = (a_struct *) strct;

  int mid_qt = (td_strct->left + td_strct->right)/2;

  singleThreadedMergeSort(td_strct->values, td_strct->left, td_strct->right);
}



void * thread_ms_hf(void * strct)
{
  a_struct * td_strct = (a_struct *) strct;

  int mid_2 = (td_strct->left + td_strct->right)/2 ;

  a_struct a_left_2;
  a_left_2.values = td_strct->values;
  a_left_2.left = td_strct->left;
  a_left_2.right = mid_2;

  a_struct a_right_2;
  a_right_2.values = td_strct->values;
  a_right_2.left = mid_2 + 1;
  a_right_2.right = td_strct->right;

  pthread_t left_td_2;
  pthread_t right_td_2;

  pthread_create(&left_td_2, NULL, thread_ms_qt, (void *)&a_left_2);
  pthread_create(&right_td_2, NULL, thread_ms_qt, (void*)&a_right_2);

  pthread_join(left_td_2, NULL);
  pthread_join(right_td_2, NULL);

  merge(td_strct->values, td_strct->left, mid_2, td_strct->right);
}

/* 
 * This function stub needs to be completed
 */
void multiThreadedMergeSort(int arr[], int left, int right) 
{
  int middle = (left+right)/2;

  a_struct a_left;
  a_left.values = arr;
  a_left.left = left;
  a_left.right = middle;

  a_struct a_right;
  a_right.values = arr;
  a_right.left = middle + 1;
  a_right.right = right;

  pthread_t left_td;
  pthread_t right_td;

  pthread_create(&left_td, NULL, thread_ms_hf, (void *)&a_left);
  pthread_create(&right_td, NULL, thread_ms_hf, (void*)&a_right);

  pthread_join(left_td, NULL);
  pthread_join(right_td, NULL);
  
  merge(arr, left, middle, right);

}
