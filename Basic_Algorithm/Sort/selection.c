/*
 * =========================================================
 *       Filename:  selection.c
 *    Description:  选择排序
 *    Hints:
The algorithm maintains two subarrays in a given array.
1) The subarray which is already sorted.
2) Remaining subarray which is unsorted.
In every iteration of selection sort, the minimum element (considering ascending order) from the unsorted subarray is picked and moved to the sorted subarray.
 *    
 *
 * =========================================================
 */
#include <stdio.h>
#define SWAP(x,y) do{int temp;temp = x;x = y; y = temp;}while(0)//排序函数少不了swap
void selectionSort(int arr[],int n);
void printArray(int arr[],int n);
int main()
{
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr)/sizeof(arr[0]);
    selectionSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}

void selectionSort(int arr[],int n){
    int i,j;
    for(i = 0;i < n;i++){
        int min_index = i;
        for(j = i;j < n;j++)
            if(arr[j] < arr[min_index])
                min_index = j;
        SWAP(arr[i],arr[min_index]);
    }
}
void printArray(int arr[],int n){
    int i = 0;
    while(i < n){//别乱用 i++ < n
        printf("%d%s",arr[i],(i == n-1)?"\n":" ");
        ++i;
    }
}
