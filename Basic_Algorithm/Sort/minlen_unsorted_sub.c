/*
 * =========================================================
 *       Filename:  minlen_unsorted_sub.c
 *    Description:  Given an unsorted array arr[0..n-1] of size n,
 *    find the minimum length subarray arr[s..e]
 *    such that sorting this subarray makes the whole array sorted.
 * =========================================================
 */
#include <stdio.h>
void printUnsorted(int arr[],int n);
int main()
{
  int arr[] = {10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60};
  int arr_size = sizeof(arr)/sizeof(arr[0]);
  printUnsorted(arr, arr_size);
  getchar();
  return 0;
}


void printUnsorted(int arr[],int n){
    int s = 0,e = n-1,i,max,min;
    //初始化 s,e
    for(;s < n-1;s++){
        if(arr[s] > arr[s + 1])
            break;
    }
    if(s == n-1){
        printf("already sorted.\n");
        return ;
    }
    for(;e > 0 ;e--)
        if(arr[e] < arr[e-1])
            break;
    //调整 s ,e
    //先找到[s,e]中min ,max
    max = min = arr[s];
    for(i = s+1;i <= e;i++){
        if(arr[i] < min)
            min = arr[i];
        if(arr[i] > max)
            max = arr[i];
    }
    //找到(0,s]中第一个大于min的数
    for(i = 0 ;i < s;i++)
        if(arr[i] > min){
            s = i;
            break;
        }
    //找到(e,n-1]中第一个小于max的数
    for(i = n-1;i > e;i--)
        if(arr[i] < max){
            e = i;
            break;
        }
    printf("sub array start from %d to %d.\n",s,e);
}
