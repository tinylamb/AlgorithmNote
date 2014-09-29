/*
 * =========================================================
 *       Filename:  findmink.c
 *    Description:  基于快排的两种寻找pivot元素位置的方法
 *    来实现寻找数列中最小的k个数字
 *
 * =========================================================
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SWAP(a,b) do{int temp;temp=a;a=b;b=temp;}while(0)
typedef struct interval{
    int left;
    int right;
}Interval;
int findp_v1(int a[] , int left , int right);
Interval *findp_v2(int a[] , int left , int right);
int findmink(int a[],int left,int right,int k);
void print(int a[],int start,int end);
int main(){
    long seed;
    seed=time(NULL);
    srand(seed);

    int *a , n , k ,kth;
    while(scanf("%d%d",&n ,&k) == 2){
        a = malloc(sizeof(int) * n);
        for(int i = 0; i < n ; ++i)
            scanf("%d",a + i);
        findmink(a , 0 , n-1 , k);
        print(a , 0 ,k- 1);
        free(a);
    }
}

int findmink(int a[],int left,int right,int k){
//    int p=k-1;
//    Interval *inter;
//    inter = findp_v2(a , left ,right);
//    if(p >= inter->left && p <= inter->right)
//        return k;
//    else if(p < inter->left)
//        return findmink(a , left ,inter->left -1 ,k);
//    else
//        return findmink(a , inter->right +1 ,right,k);
    int p = findp_v1(a , left ,right);
    if( p < k-1)
        return findmink(a , p+1 , right , k);
    else if(p > k-1)
        return findmink(a , left , p-1 ,k);
    else
        return k;
}


int findp_v1(int a[] , int left , int right){ // left <= pivot <= right
    //从[left , right]随机选出pivot元素 
    int random=rand()%(right-left+1)+left;
    SWAP(a[left],a[random]);
    int pivot=a[left];
    int l = left + 1;
    int r = right;
    while(l < r){// l == r 时跳出循环
        while(a[l] <= pivot && l < r)
            ++l;
        while(a[r] >= pivot && l < r)
            --r;
        if(l < r)
            SWAP(a[l] , a[r]);
    }
    if(a[l] >= pivot){
        SWAP(a[l-1] , a[left]);
        return l-1;
    }
    else{
        SWAP(a[l] , a[left]);
        return l;
    }
}

/*
以[0,n-1]为例解释各个参数的含义
[1,l]<p  l指向最后一个小于p的数
(r,n]>p  r+1指向第一个大于p的数
(l,i)=p
[i,r] 未处理的数
*/
Interval *findp_v2(int a[] , int left , int right){
    int random = rand() % (right - left + 1) + left;
    SWAP(a[left] , a[random]);
    int pivot = a[left];
    int l=left,r=right;
    int i;
    for(i=left+1;i<=r;i++){
        if(a[i]<pivot){
            l++;
            SWAP(a[l],a[i]);
        }
        else if(a[i]>pivot){
            while(a[r]>pivot && r>=i)// important!!!
                r--;
            if(r>=i){
                SWAP(a[r],a[i]);
                r--;
                if(a[i]<pivot){
                    l++;
                    SWAP(a[l],a[i]);
                }
            }
        }
    }
    SWAP(a[left],a[l]);
    Interval *inter = malloc(sizeof(Interval));
    inter->left = l;
    inter->right = r;
    return inter;
}
void print(int a[],int start,int end){
    int i;
    for(i=start;i<=end;i++)
        printf("%d%s",a[i],(i==end)?"\n":" ");
}



