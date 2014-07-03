/*
 * =========================================================
 *       Filename:  bitmap.c
 *    Description:  数组限制 {i|0<= i <= MAX,i 是整数} 元素不重复
 *
 * =========================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 9999 // 需要MAX个bits
int map[MAX/32 + 1]; //计算bitmap的大小
void set_one(int map[],int i); //在bitmap中给i置1
bool test(int i,int k);//检查i的k位是否为1
int main(){
    memset(map,0,sizeof(map));
    int i;
    while(scanf("%d",&i) == 1)
        set_one(map,i);
    for(i = 0;i < (MAX/32 + 1);i++){
        int temp = map[i];//temp test if there is 1 in map[i]
        int j;
        for(j = 0;j < 31;j++){
            if(temp == 0)
                break;
            else if(test(map[i] ,j)){
                temp &= (temp - 1);//原用于统计bit位上1出现的次数
                int num = 32*i + j;
                printf("%d ",num);
            }
        }
    }
}




void set_one(int map[],int i){
    int key = i/32;
    int shift = i%32;
    map[key] |= (1<<shift);
}

bool test(int i,int k){
    if(i & (1 << k))
        return true;
    else
        return false;
}
