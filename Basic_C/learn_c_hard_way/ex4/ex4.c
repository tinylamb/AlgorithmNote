/*
 * =========================================================
 *       Filename:  ex4.c
 *    Description:   Introducing Valgrind
 *
 * =========================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    int a[10];
    memset(a, 0, sizeof(a));
    for (int i = 0; i < 100; i++)
        printf("%d ",a[i]);
    return 0;
}

