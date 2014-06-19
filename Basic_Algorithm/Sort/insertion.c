/*
 * =========================================================
 *       Filename:  insertion.c
 *    Description:  Insertion sort is a simple sorting algorithm 
 *                   that works the way we sort playing cards in our hands
 *
 * =========================================================
 */
#include <stdio.h>

void insertionSort(int arr[],int n);
void printArray(int arr[],int n);
int main()
{
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);

    insertionSort(arr, n);
    printArray(arr, n);

    return 0;
}

void insertionSort(int arr[],int n){
    int i,j,unsort;
    for(i = 0 ;i < n;i++){
        unsort = arr[i];
        j = i - 1;
        while(j >= 0 && unsort < arr[j]){//两个操作可以在一起的,我sb的放到两个循环中
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = unsort;
/*         int position = j + 1;
 *         if(position != i)
 *             for(j = i-1 ;j >= position;j--)
 *                 arr[j + 1] = arr[j];//take arr[j] to arr[j + 1]
 *         arr[position] = unsort;
 */
    }
}
void printArray(int arr[],int n){
    int i = 0;
    while(i < n){
        printf("%d%s",arr[i],(i == n-1)?"\n":" ");
        i++;
    }
}
