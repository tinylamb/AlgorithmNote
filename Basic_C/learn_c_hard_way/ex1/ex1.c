/*
 * =========================================================
 *       Filename:  hello.c
 *    Description:  
 *
 * =========================================================
 */
#include <stdio.h> //如果缺失 warning: implicit declaration of function 'puts' is invalid in C99
int main(int argc, char *argv[]){
    if (puts("fuck you") != EOF)
        puts("sb world.");
    return 0;
}
