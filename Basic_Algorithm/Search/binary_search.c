/*
 * =========================================================
 *       Filename:  binary_search.c
 *    Description:  Given a sorted array arr[] of n elements, write a
 *                  function to search a given element x in arr[].
 *
 *
 * =========================================================
 */
#include <stdio.h>
int search(int arr[],int n ,int x); // O(N) 
int bin_search(int arr[],int n,int x);// Iterative O(log(N))
int bin_search_r(int arr[],int left , int right ,int x);// Recursive 
int main(){
    int arr[] = {2,3,4,10,20,43};//sorted array
    int n = sizeof(arr)/sizeof(arr[0]);
    int x = 10;
    int index = bin_search(arr,n,x);
    (index == -1)?printf("elem not in array\n"):printf("elem index is %d\n",index);
}

int search(int arr[],int n ,int x){
    int i;
    for(i = 0; i < n; i++)
        if (arr[i] == x)
            return i;
    return -1;
}
int bin_search(int arr[],int n,int x){
    int left = 0;
    int right = n - 1;
    int mid;
    while(left <= right){
        mid = left + (right - left)/2;
        if(arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
int bin_search_r(int arr[],int left , int right ,int x){
    if(left > right)
        return -1;
    int mid = left + (right - left)/2;
    if(arr[mid] == x)
        return mid;
    else if(arr[mid] < x)
        return bin_search_r(arr,mid + 1,right ,x);
    else
        return bin_search_r(arr,left,mid - 1,x);
}
