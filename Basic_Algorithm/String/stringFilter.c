/*
 * =========================================================
 *       Filename:  stringFilter.c
 *    Description:  字符集{a ~ z} 字符串去重
 *    hint       :  bitmap
 *
 * =========================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
void stringFilter(char s[]);
bool Map(char c, int *m);
int main(){
    char s[] = "ababcccdef";
    printf("before : %s\n",s);
    stringFilter(s);
    printf("fliter : %s\n",s);
    return 0;
}


void stringFilter(char s[]){
    int map = 0;//{a ~ z} 映射到一个整型 初始化为0
    int index; // a-> 0 ... z-> 25
    char *p, *q;
    p = q = s;//p 遍历 s ,q 指向当前去重后的尾字符
    while(*p){ // 不是while(p) 啊 操
        index = *p - 'a';
        if((1 << index) & map)
            ++p;
        else{
            map |= (1 << index);
            *q++ = *p++;
        }
    }
    *q = '\0';
}

