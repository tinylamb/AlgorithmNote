/*
 * =========================================================
 *       Filename:  bubble.c
 *    Description:  
 *
 * =========================================================
 */
#include <stdio.h>
#include <stdbool.h>
#define SWAP(x,y) do{int temp;temp = x; x = y;y = temp;}while(0)
void bubbleSort(int arr[],int n);
void printArray(int arr[],int n);
int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);
    bubbleSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
void bubbleSort(int arr[],int n){
    int i,j;
    bool swaped;
    for(i = n-1 ; i > 0 ; i--){
        bool swaped = false;
        for(j = 0 ; j < i ;j++)
            if(arr[j] > arr[j+1]){
                SWAP(arr[j] , arr[j + 1]);
                swaped = true;
            }
        if(!swaped)
            break;
    }
}
void printArray(int arr[],int n){
    int i = 0;
    while(i < n){
        printf("%d%s",arr[i],(i == n-1)?"\n":" ");
        ++i;
    }

}
