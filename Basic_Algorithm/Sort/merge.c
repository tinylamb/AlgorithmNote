/*
 * =========================================================
 *       Filename:  merge.c
 *    Description:  喜欢的算法之一
 *
 * =========================================================
 */
#include <stdio.h>
void mergeSort(int arr[],int start,int end);
void merge(int arr[],int start,int mid ,int end);
void printArray(int arr[],int size);
/* Driver program to test above functions */
int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
 
    printf("Given array is \n");
    printArray(arr, arr_size);
 
    mergeSort(arr, 0, arr_size - 1);
 
    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}

void mergeSort(int arr[],int start,int end){
    if(start < end){
        int mid = start + (end - start)/2;
        mergeSort(arr,start,mid);
        mergeSort(arr,mid + 1,end);
        merge(arr,start,mid,end);
    }
}
void merge(int arr[],int start,int mid ,int end){
    int i,j,k;// 需要合并的数组的index
    int n1 = mid - start + 1;
    int n2 = end - mid;
    int L1[n1] , L2[n2];//temp 数组保存arr中的切片
    for(i = 0;i < n1;i++)
        L1[i] = arr[start + i];
    for(j = 0;j < n2;j++)
        L2[j] = arr[mid + 1 + j];
    //合并temp到arr位置,更新arr
    i = j = 0;
    k = start;
    while(k <= end){ //这里nice
        if(j > n2-1 || (i < n1 && L1[i] < L2[j])){
            arr[k] = L1[i];
            i++;
        }
        else{
            arr[k] = L2[j];
            j++;
        }
        k++;
    }
}
void printArray(int arr[],int size){
    int i = 0;
    while(i < size){
        printf("%d%s",arr[i],(i == size-1)?"\n":" ");
        i++;
    }
}
