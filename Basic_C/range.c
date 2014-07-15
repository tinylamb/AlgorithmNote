/*
 * =========================================================
 *       Filename:  range.c
 *    Description:  How to write C code to print range of basic data types like
 *                  int, char, short int, unsigned int, unsigned char etc?
 *                  It may be assumed that signed numbers are stored in 2′s complement form.
 *           hint:  得到正确的二进制形式
 *
 * =========================================================
 */
#include <stdio.h>
#include <assert.h>
#define ElemType int
int main(){
    ElemType start = 1;
    ElemType from , to;
    ElemType bits = sizeof(start) * 8;
    if((start - 2) > 0){// 无符号数
        from = 0;
        to = (start << (bits - 1)) + ((start << (bits - 1)) - 1);
        printf("this type is from %u to %u\n",from ,to);

    }
    else{//signed type
        from = -(start << (bits - 1));
        to = (start << (bits - 1)) - 1;
        printf("this type is from %d to %d\n",from ,to);
    }
    return 0;
}

