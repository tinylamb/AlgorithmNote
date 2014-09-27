/*
 * =========================================================
 *       Filename:  ch4.c
 *    Description:  solutions to TCPL ch4
 *
 * =========================================================
 */
/*reference http://users.powernet.co.uk/eton/kandr2/index.html*/

/*
Exercise 4-1. Write the function strindex(s,t) which returns the position of 
the first occurrence of t in s, or -1 if there is none.
*/
#include <stdio.h>
#define SIZE 100

int strindex(char s[] , char p[]);//return (p in s)?index:-1
int main(){
   char s[SIZE] = "aaaaaaaaaaaaaaaaaaaaaaaaaab";
   char p[SIZE] = "aaaaaaaab";
   int index = strindex(s , p);
   printf("%d\n",index);
}

int strindex(char s[] , char p[]){
    int i = 0,j = 0;// i ,j 分别遍历 s[i] ,p[j]
    while( s[i] && p[j]){
        printf("%d %d\n",i,j);
        if (s[i] == p[j]){
            ++i;
            ++j;
        }
        else{//如果匹配失败，j的位置将影响i的移动;update 下面两者等价
/*            if (j == 0)
*                 ++i;
*             else
*/                i = i-j+1;
            j = 0;
        }
    }
    return (p[j] == '\0')?i-j:-1;
}

/*
Exercise 4-2. Extend atof to handle scientific notation of the form
123.45e-6
where a floating-point number may be followed by e or E and an optionally signed exponent.

*/
#include <stdio.h>
#include <ctype.h>
#include <math.h> //gcc -lm
double atof(char *);
int main(){
    
    char * number[]={"  1.0e43","-1.2e-3","-13.41E03",""};
    int i;
    for(i=0;*number[i];i++)
        printf("atof(%s)=%g\n",number[i],atof(number[i]));
    /* v1
    char num[]="  13.41";
    double number=atof(num);
    printf("%s\n%.3f\n",num,number);
        
       v2 
    char * number[]={"  13.41","-13.41","+13.41"};
    double num[3];
    int i;
    for(i=0;i<3;i++)
        num[i]=atof(number[i]);
    for(i=0;i<3;i++)
        printf("%s\n\t%.3f\n",number[i],num[i]);
    */

}
double atof(char s[]){
    double val,power,epart;
    int i=0,sign,esign;
    while(isspace(s[i]))//skip space
        i++;
    sign=(s[i]=='-')?-1:1;//get sign
    if(s[i]=='+'||s[i]=='-')
        i++;
    for(val=0.0;isdigit(s[i]);i++)//get integer part
        val=(s[i]-'0')+10*val;
    if(s[i]=='.')//get frac part
        i++;
    for(power=1;isdigit(s[i]);i++){
        val=(s[i]-'0')+10*val;
        power*=10;
    }
    if(s[i]=='e'||s[i]=='E')//get e part
        i++;
    esign=(s[i]=='-')?-1:1;
    if(s[i]=='+'||s[i]=='-')
        i++;
    for(epart=0.0;isdigit(s[i]);i++)
        epart=(s[i]-'0')+10*epart;

    return sign*val/power*pow(10,esign*epart);
}
/*
Exercise 4-3. Given the basic framework, it's straightforward to extend the calculator. 
Add the modulus (%) operator and provisions for negative numbers.
*/
int getop(char s[]){
    int i=0,c;//i for the last char in s
    while((s[i]=getch())==' '||s[i]=='\t')
        ;
    if(!isdigit(s[i]) && s[i]!='.' &&s[i]!='-')//important change
        return s[i];
    if(s[i]=='-')
        if ((s[++i]=getch())!='.' && !isdigit(s[i])){
            if(s[i]!=EOF)
                ungetch(s[i]);
            return s[i-1];
        }
    if(isdigit(s[i])) //current i=0
        while(isdigit(s[++i]=getch()))
            ;
    if(s[i]=='.')
        while(isdigit(s[++i]=getch()))
            ;
    if(s[i]!=EOF)
        ungetch(s[i]);
    s[i]='\0';
    return NUMBER;

}

case '%':
                if((op2=pop())!=0){
                    op1=pop();
                    i=(int)op1/op2;
                    push(op1-op2*i);
                }
                else
                    printf("error:zero\n");
                break;

/*
calculator
*/
#include <stdio.h>
#include <stdlib.h>
#define MAXOP 100  //max len of operator
#define NUMBER '0' //signal that a number is found

#define MAXVAL 100 //max depth of stack
int sp=0; //top pointer of stack
double val[MAXVAL]; //val stack
void push(double f){
    if (sp<MAXVAL)
        val[sp++]=f;
    else
        printf("error:stack full,can't push.\n");
}
double pop(){
    if (sp>0)
        return val[--sp];
    else{
        printf("error:stack empty.\n");
        return 0.0;
    }
}

#include <ctype.h>
int getch();
void ungetch(int);
int getop(char s[]){
    int i=0,c;//i for the last char in s
    while((s[i]=getch())==' '||s[i]=='\t')
        ;
    if(!isdigit(s[i]) && s[i]!='.')
        return s[i];
    if(isdigit(s[i])) //current i=0
        while(isdigit(s[++i]=getch()))
            ;
    if(s[i]=='.')
        while(isdigit(s[++i]=getch()))
            ;
    if(s[i]!=EOF)
        ungetch(s[i]);
    s[i]='\0';
    return NUMBER;

}
/* another version getop
int getop(char s[]){//get next character
    int i,c;
    while((s[0]=c=getch())==' '|| c=='\t')
        ;
    s[1]='\0';
    if(!isdigit(c) && c!='.')
        return c; //not a number
    i=0;
    if(isdigit(c))
        while(isdigit(s[++i]=c=getch()))
            ;
    if(c=='.')
        while(isdigit(s[++i]=c=getch()))
            ;
    s[i]='\0';
    if(c!=EOF)
        ungetch(c);
    return NUMBER;
}*/

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp=0;
int getch(){
    return (bufp>0)?buf[--bufp]:getchar();
}
void ungetch(int c){
    if(bufp>BUFSIZE)
        printf("error:buffer full.\n");
    else
        buf[bufp++]=c;
}

int  GetLine(char  s[]){
    int  l=0,c;
    while((c=getchar())!=EOF  &&  c!='\n')
        s[l++]=c;
    s[l++]='\n'

