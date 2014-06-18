/*
 * =========================================================
 *       Filename:  sum_of_cubes.c
 *    Description:  求1到n的立方和
 *
 * =========================================================
 */
#include <stdio.h>
int main(){
    unsigned int n;
    unsigned int sum = 0;
    printf("input an integer: \n");
    scanf("%u",&n);
    unsigned int i;
    for(i = 1; i <= n; i++)
        sum += i*i*i;
    printf("sum of cubes is : %u\n",sum);
    return 0;

}

