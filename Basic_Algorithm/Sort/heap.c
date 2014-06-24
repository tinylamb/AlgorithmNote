/*
 * =========================================================
 *       Filename:  heap.c
 *    Description:  堆排序
 *
 * =========================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define SIZE 100 /* heap size */
#define LEFT(i) (2*i + 1)
#define RIGHT(i) (2*i + 2)

typedef struct heapq{ /* step 1.优先队列结构体声明 */
//    int arr[SIZE];
    int *arr;
    int len;
}HeapQ;


/*---------------------------------------------------
 * step 2.  HeapQ 方法的声明
 *---------------------------------------------------*/
void initialize(HeapQ* h);
HeapQ* heapify(int arr[] , int n);
void adjust(HeapQ* h , int p);
void swap(int *a,int *b);
void heapSort(int arr[], int n);//step 3.堆排序
void printArray(int arr[], int n);
int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(arr)/sizeof(arr[0]);
 
    printf("Given array is \n");
    printArray(arr, size);
 
    heapSort(arr, size);
 
    printf("\nSorted array is \n");
    printArray(arr, size);
    return 0;
}

void initialize(HeapQ* h){
    h->len = 0;
}

HeapQ* heapify(int arr[] , int n){
    HeapQ* h;
    h = malloc(sizeof(HeapQ));
    h->len = n;
    h->arr = arr;
    int i;
//    for(i = 0;i < n;i++)// 初始化
//        h->arr = arr[i];
    for(i = (h->len)/2 - 1;i >= 0;i--)
        adjust(h , i);// LEFT(i) RIGHT(i) 已经是堆
    return h;
    
}

void adjust(HeapQ* h , int p){
    int min;//小根堆调整策略,较小的上调
    while(p <= (h->len)/2 - 1){
        min = p;
        if(LEFT(p) < h->len && h->arr[LEFT(p)] < h->arr[min])
            min = LEFT(p);
        if(RIGHT(p) < h->len && h->arr[RIGHT(p)] < h->arr[min])
            min = RIGHT(p);
        if(min == p)
            break;
        else{
            swap(h->arr + p,h->arr + min);
            p = min;
        }
    }
}

void heapSort(int arr[], int n){//step 3.堆排 小根堆做降序,大根堆做升序.这点我没想到
    HeapQ* h = heapify(arr,n);
    while(h->len > 1){
        swap(h->arr , h->arr + (h->len - 1));
        --(h->len);
        adjust(h , 0);
    }
}

inline void swap(int *a,int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

void printArray(int arr[], int n){
    int i = 0;
    while(i < n){
        printf("%d%s",arr[i],(i == n-1)?"\n":" ");
        i++;
    }
}
