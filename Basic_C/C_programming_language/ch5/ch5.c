/*
 * =========================================================
 *       Filename:  ch5.c
 *    Description:  
 *
 * =========================================================
 */

/*
Exercise 5-1. As written, getint treats a + or - not followed 
by a digit as a valid representation of zero. 
Fix it to push such a character back on the input.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXSIZE 100
int getch();
void ungetch(int);
int getint(int *);

main(){
    int *i;
    while(1){
        if(getint(i))
            printf("%d\n",*i);
    }
}

/*getch & ungetch */
int top=0;
int buffer[MAXSIZE];
int getch(){
    return (top>0)?buffer[--top]:getchar();
}
void ungetch(int ch){
    if(top==MAXSIZE-1)
        printf("error:buffer full\n");
    else
        buffer[top++]=ch;
}

/*getint (fail)?0:1*/
int getint(int *i){
    int signal=0;//test this condition +/-undigit
    //i=NULL;segmentation fault
    int c,sign=0;
    while(isspace(c=getch()))//skip space
        ;
    if(c!=EOF && !isdigit(c) && c!='+' && c!='-'){// && isn't a number
        ungetch(c);
        return 0;
    }
    sign=(c=='-')?-1:1;
    if(c=='+' ||  c=='-')
        c=getch();
    if(isdigit(c)){ // test this condition +/-undigit
        signal=1;
        *i=c-'0';
        while(isdigit(c=getch()))
            *i=*i*10+(c-'0');
    }
    /*
    for(*i=0;isdigit(c);c=getch())
        *i=*i*10+(c-'0');
    */
    if(signal)//i!=NULL
        *i=sign*(*i);
    if(c!=EOF){
        if (signal==0){//i==NULL
            ungetch(c);
            sign=(-1)?'-':'+';
            ungetch(sign);
            return 0;
        }
        ungetch(c);
    }
    //*i=*i*sign;
    //if(c!=EOF)
    //    ungetch(c);
    return 1;
}

/*
Exercise 5-2. Write getfloat, the floating-point analog of getint.
What type does getfloat return as its function value?
*/
//reference e5_1 e4_2

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define SIZE 10
/*input buffer*/
int top=0;
char buffer[SIZE];
char getch(void){
    return (top==0)?getchar():buffer[--top];
}
void ungetch(char c){
    if(top==SIZE-1)
        printf("buffer full\n");
    else
        buffer[top++]=c;
}
//Isnumber
int IsNumber(char c){
    return isdigit(c)||c=='+'||c=='-'||c=='.';
}
int main(){
    int getfloat(float *f);
    float f;
    int t;
    while((t=getfloat(&f)))
        if(t==1)
            printf("%f\n",f);
    return 0;
}
int getfloat(float *f){
    int c;//char in input stream
    //float like this -5.13E-34
    int sign,esign;
    int power,epower;
    while(!IsNumber(c=getch()) && c!=EOF)//input 12  name  3.23  output: 12  3.23
        ;
    if(c==EOF)
        return 0;
    sign=(c=='-')?-1:1;//deal with sign
    if(c=='+'||c=='-' ||c=='.')
        c=getch();
    if(!IsNumber(c)){// +/-/. fllowed nothing
        ungetch(c);
        return 2;
    }
    //deal with integer part
    for(*f=0;isdigit(c);c=getch())
        *f=*f*10+(c-'0');
    if(c=='.')//deal with frac part
        c=getch();
    for(power=1;isdigit(c);c=getch()){
        power*=10;
        *f=*f*10+(c-'0');
    }
    if(c=='e'||c=='E')//deal with E part
        c=getch();
    esign=(c=='-')?-1:1;
    if(c=='-'||c=='+')
        c=getch();
    for(epower=0;isdigit(c);c=getch())
        epower=10*epower+c-'0';
    *f=sign*(*f)/power*pow(10,esign*epower);
    if(c!=EOF)
        ungetch(c);
    return 1;

}

/*Exercise 5-3. Write a pointer version of the function str_cat 
 * that we showed in Chapter 2:
 *  str_cat(s,t) copies the string t to the end of s.
 *  reference:http://stackoverflow.com/questions
 *  /3948488/is-kr-teaching-bad-readability
 */
#include <stdio.h>
#include <stdlib.h>
char* str_cat(char *,char *);
void str_copy(char*,char *);
int str_len(char *);
int main(){
    char s[]="gao ";
    char *t="yang";
    printf("%s\n",str_cat(s,t));
}
int str_len(char *s){
    char *iter=s;
    while(*iter)
        iter++;
    return iter-s;

}
void str_copy(char *s,char *t ){
    while(*s++=*t++)
        ;
}
char* str_cat (char *s,char *t ){
    char *result;
    result=(char *)malloc((str_len(s)+str_len(t)+1)*sizeof(char));
    str_copy(result,s);
    char *iter=result;
    while(*iter)
        iter++;
    str_copy(iter,t);
    return result;
}

/*Exercise 5-4. Write the function strend(s,t), which returns 1 
 * if the string t occurs at the end of the string s, and zero otherwise.
 */
#include <stdio.h>
int strcomp(char *,char *);
int str_len(char *);
int strend(char *,char *);
int main(){
    char *s="gao yang";
    char *t="yag";
    if(strend(s,t))
        printf("%s at end of %s\n",t,s);
    else
        printf("%s not at end of %s\n",t,s);
}

int strcomp(char *s,char *t){
    while(*s && *s==*t){
        s++;
        t++;
    }
    return (*t=='\0')?1:0;
}

int str_len(char *s){
    char *iter=s;
    while(*iter)
        iter++;
    return iter-s;
}

int strend(char *s,char *t){
    int p=str_len(s)-str_len(t);//p is the start of comparision
    int i=0;
    while(i!=p){
        s++;
        i++;
    }
    return strcomp(s,t);
}

/*Exercise 5-5. Write versions of the library functions
 *  Strncpy, strncat, and strncmp, which operate on at 
 *  most the first n characters of their argument strings.
 *   For example, Strncpy(s,t,n) copies at most n characters of t to s.
 */
#include <stdio.h>
#define SIZE 100
void Strncpy(char *s,char *t,int n);
void Strncat(char *s,char *t,int n);
int Strncmp(char *s,char *t,int n);
int main(){
    char s[SIZE]="gao";
    char t[SIZE]="gamy";
    printf("%d\n",Strncmp(s,t,3));
    Strncat(s,t,3);
    printf("%s\n",s);
    return 0;
}
void Strncpy(char *s,char *t,int n){
    while(n-->0 && *t)
        *s++=*t++;
    
}
void Strncat(char *s,char *t,int n){
    while(*s!='\0')
        s++;
    Strncpy(s,t,n);
}
int Strncmp(char *s,char *t,int n){
    while(n-->0 && *s==*t){
        if(*s=='\0'||n==0)//important
            return 0;
        s++;
        t++;
    }
    return (*s-*t>0)?1:-1;
}


/*Exercise 5-8. There is no error checking in
 *  day_of_year or month_day. Remedy this defect.
 */
#include <stdio.h>
static char daytab[2][13]={
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};
int day_of_year(int year,int month,int day){
    int i,leap;
    leap=(year%4==0 && year%100!=0) || year%400==0;
    if(month<1 || month>12)
        printf("invalid month.\n");
    if(!(day>0 && day<=daytab[leap][month]))
        printf("invalid day.\n");
    for(i=1;i<month;i++)
        day+=daytab[leap][i];
    return day;
}
void month_day(int year,int yearday,int *month,int *day){
    int i,leap;
    leap=(year%4==0 && year%100!=0 )|| year%400==0;
    if(!(yearday>0 && yearday <=365+leap))
        printf("invalid yearday.\n");
    for(i=0;yearday>daytab[leap][i];i++)
        yearday-=daytab[leap][i];
    *month=i;
    *day=yearday;
}
int main(){
}


/*Exercise 5-10. Write the program expr, which evaluates a
 *  reverse Polish expression from the command line, 
 *  where each operator or operand is a separate argument.
 *  For example,expr 2 3 4 + *evaluates 2 * (3+4).
 */
#include <stdio.h>
#include <stdlib.h>
#define MAXOP 100  //max len of operator

/*value stack*/
#define MAXVAL 100 //max depth of stack
int top=0; //top pointer of stack
double val[MAXVAL]; //val stack
void push(double f){
    if (top<MAXVAL)
        val[top++]=f;
    else
        printf("error:stack full,can't push.\n");
}
double pop(){
    if (top>0)
        return val[--top];
    else{
        printf("error:stack empty.\n");
        return 0.0;
    }
}

double  Atof(char  s[]){
    double  val,power;
    int  i=0,sign;
    while(isspace(s[i]))
        i++;
    sign=(s[i]=='-')?-1:1;
    if(s[i]=='+'||s[i]=='-')
        i++;
    for(val=0.0;isdigit(s[i]);i++)
        val=10.0*val+(s[i]-'0');
    if(s[i]=='.')
        i++;
    for(power=1.0;isdigit(s[i]);i++){
        val=10.0*val+(s[i]-'0');
        power*=10;
    }
    return  sign*val/power;
}
int main(int argc,char *argv[]){
   char *op;
   double op1,op2;
   //print operators
   int i=argc;
   char **p=argv; //p=++argv!!! segmentation fault
   while(i-->0)
       printf("%s ",*++p);
   printf("\n");
   
   while(--argc>0){// argc represen
