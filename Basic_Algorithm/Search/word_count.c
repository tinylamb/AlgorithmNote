/*
 * =========================================================
 *       Filename:  word_count.c
 *    Description:  source http://uva.onlinejudge.org/external/4/494.html
 *                  在C programming language 中的单词记数问题
 *
 * =========================================================
 */
#include <stdio.h>
#include <stdbool.h>
#define IsLetter(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'z'))
int main(){
    int c;
    int count = 0;
    bool InWord = false;
    while((c = getchar()) != EOF){
        if(c == '\n'){
            printf("%d\n",count);
            count = 0; //reset count 
        }
        else{
            if(!IsLetter(c))
                InWord = false;
            else if (!InWord){ //same with if(IsLetter(c) && !InWord)
                ++count;
                InWord = true;
            }
        }
    }
    return 0;
}

