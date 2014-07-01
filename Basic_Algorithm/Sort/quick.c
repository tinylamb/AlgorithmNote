/*
 * =========================================================
 *       Filename:  quick.c
 *    Description:  The key process in quickSort is partition()
 *
 * =========================================================
 */
#include <stdio.h>
#define SWAP(a,b) do{int temp;temp=a;a=b;b=temp;}while(0)


int partition(int arr[],int l,int r);
void quickSort(int arr[],int l,int r);
void printArray(int arr[],int n);
// Driver program to test above functions
int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    quickSort(arr, 0, n-1);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}



/*---------------------------------------------------
   This function takes first element as pivot,
   places the pivot element at its
   correct position in sorted array,
   and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right of pivot
   [l , i-1] < pivot
   i -> pivot
   [i+1 , r] >= pivot
   link : https://gist.github.com/tinylamb/7624054
   以[0,n-1]为例解释各个参数的含义
   [1,l]<p  l指向最后一个小于p的数
   (r,n]>p  r+1指向第一个大于p的数
   (l,i)=p
   [i,r] 未处理的数
 *---------------------------------------------------*/
int partition(int arr[],int l,int r){
    int pivot = arr[l];
    int i = l;//be sure [start+1 , i] < pivot
    for(int j = l+1;j <= r;j++){
        if(arr[j] < pivot){
            i++;
            SWAP(arr[i],arr[j]);
        }
    }
    SWAP(arr[l],arr[i]);//make [start,i-1] < pivot
    return i; // i point to the right place of pivot
}

void quickSort(int arr[],int l,int r){
    if(l < r){
        int p = partition(arr,l,r);
        quickSort(arr,l,p-1);
        quickSort(arr,p+1,r);
    }
}

void printArray(int arr[],int n){
    int i = 0;
    while(i < n){
        printf("%d%s",arr[i],(i == n-1)?"\n":" ");
        i++;
    }

}
