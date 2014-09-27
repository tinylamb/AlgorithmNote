/*
 * =========================================================
 *       Filename:  ch3.c
 *    Description:  solutions to TCPL ch3
 *
 * =========================================================
 */

/*reference http://users.powernet.co.uk/eton/kandr2/index.html*/
/*
Exercise 3-1. Our binary search makes two tests inside the loop, when one would suffice (at the price of
more tests outside.) Write a version with only one test inside the loop and measure the difference in runtime.
*/
#include <stdio.h>
int binarysearch(int a[],int x,int n){
  int low=0,high=n-1;
  int mid=(low+high)/2;
  while(low<=high && a[mid]!=x){
    if (a[mid]<x)
      low=mid+1;
    else
      high=mid-1;
    mid=(low+high)/2;
  }
  if(low<=high)
    return mid;
  else
    return -1;

}
int main(){
  int a[]={1,3,4,6,8,10,34,45,67,34};
  int p=binarysearch(a,10,10);
  printf("%d\n",p);
  return 0;
}
/****
  while(low<=high && a[mid]!=x){
    if (a[mid]<x){
      low=mid+1;
      mid=(low+high)/2;
    }
    else{
      high=mid-1;
      mid=(low+high)/2;
    }
  }
****/

/*
Exercise 3-2. Write a function escape(s,t) that converts characters like newline and tab into visible
escape sequences like \n and \t as it copies the string t to s. Use a switch. Write a function for the
other direction as well, converting escape sequences into the real characters.
*/
#include <stdio.h>
#define MAXSIZE 100
void getstring(char s[]){
  int c,i=0;
  printf("enter string:\n");
  while((c=getchar())!=EOF)
    s[i++]=c;
  s[i]='\0';
}
void escape(char s[],char t[]){
  int i=0,j=0;
  while(t[j]!='\0'){
    switch(t[j]){
      case '\n':
        s[i++]='\\';
        s[i++]='n';
        break;
      case '\t':
        s[i++]='\\';
        s[i++]='t';
        break;
      default:
        s[i++]=t[j];
    }
    j++;
  }
  s[i]='\0';
}
int main(){
  char s[MAXSIZE],t[MAXSIZE];
  getstring(t);
  escape(s,t);
  printf("t:\n%s\ns:\n%s\n",t,s);
  return 0;
}

/*Exercise 3-3. Write a function expand(s1,s2) that
 *expands shorthand notations like a-z in the
 *string s1 into the equivalent complete list 
 *abc...xyz in s2. Allow for letters of either
 *case and digits, and be prepared to handle cases
 *like a-b-c and a-z0-9 and -a-z. Arrange that a leading
 *or trailing - is taken literally.
 */
#include <stdio.h>
#include <ctype.h>
#define MAXSIZE 100
int IsShortHand(char *c);//return short case
int main(){
    char s1[MAXSIZE]="-m-z3-9-";
    char s2[MAXSIZE];
    int i=0,j=0;//i for s1,j for s2 X(j position)
    while(s1[i]!='\0' &&s1[i+2]!='\0'){//pattern x-y
        if(IsShortHand(s1+i)){ 
            s2[j++]=s1[i];// char(j position)
            i+=2;//upper bound
            while(s2[j-1]!=s1[i]){
                s2[j]=s2[j-1]+1;
                j++;
            }
            i++;//next undo char
        }
        else
            s2[j++]=s1[i++];
    }
    while(s2[j++]=s1[i++])//a-zpq deal pq 
        ;
    printf("%s\n%s\n",s1,s2);
    return 0;
}
int IsShortHand(char *c){
    int bound=((isdigit(*c) && isdigit(*(c+2)))||(isalpha(*c) && isalpha(*(c+2))))?1:0;//bound alpha-alpha or digit-digit
    int mid=(*(c+1)=='-')?1:0;
    return (bound && mid);
}
/*Exercise 3-4. In a two's complement number
 *  representation, our version of itoa does no
 *  t handle the largest negative number, that is, 
 *  the value of n equal to -(2wordsize-1). Explain
 *   why not. Modify it to print that value correctly, 
 *   regardless of the machine on which it runs.
 */
#include <stdio.h>
#include <string.h>
#define MAXSIZE 100
#define BITS 8*(int)sizeof(int)
void itoa(int,char *);
void reverse(char *);
void swap(char*,char *);
int main(){
    int n=1<<(BITS-1);
    char s[MAXSIZE];
    itoa(n,s);
    printf("%d\n%s\n",n,s);
    return 0;
}
void itoa(int n,char s[]){
    int i,sign,overflow=0;
    if(n==(1<<(BITS-1))){//important
        n+=1;
        overflow=1;
    }
    if((sign=n)<0)
        n=-n;
    i=0;
    do{
        s[i++]=n%10+'0';
    }while((n/=10)>0);
    if(sign<0)
        s[i++]='-';
    if(overflow)
        s[0]+=1;
    s[i]='\0';
    reverse(s);
}
void reverse(char s[]){
    int len=strlen(s);//different from sizeof(s)/sizeof(char)
    int i=0;
    int j=len-1;
    while(i<=j){//important
        swap(s+i,s+j);
        i++;
        j--;
    }
}
void swap(char *a,char *b){
    char c;
    c=*a;
    *a=*b;
    *b=c;
}

/*Exercise 3-5. Write the function itob(n,s,b)
 *  that converts the integer n into a base b character
 *   representation in the string s. In particular, 
 *   itob(n,s,16) formats s as a hexadecimal integer in s.
 */
#include <stdio.h>
#include <string.h>
#define MAXSIZE 100
#define BITS 8*(int)sizeof(int)
#define STEP 87 // if dim=11 use a=(10+87) represent 11
void itob(int,char *,int);
void reverse(char *);
void swap(char*,char *);
int main(){
    //int n=1<<(BITS-1);
    int n=-19;
    char s[MAXSIZE];
    int base=20;
    itob(n,s,base);
    printf("%d\n%s\n",n,s);
    return 0;
}
void itob(int n,char s[],int base){
    int i=0,bit;// s[i],bit=n%base
    int sign=(n>=0)?1:-1;
    int overflow=0;// only base 10 would happen
    if(n==(1<<(BITS-1)) && base==10){
        n+=1;
        overflow=1;
    }
    do{
        bit=n%base;
        bit=(bit>0)?bit:-bit;
        s[i++]=bit+((bit<10)?'0':STEP);//base=16 10->a
    }while((n/=base)!=0);
    if(sign==-1)
        s[i++]='-';
    if(overflow)
        s[0]+=1;
    s[i]='\0';
    reverse(s);
}
void reverse(char s[]){
    int len=strlen(s);
    int i=0;
    int j=len-1;
    while(i<=j){//important
        swap(s+i,s+j);
        i++;
        j--;
    }
}
void swap(char *a,char *b){
    char c;
    c=*a;
    *a=*b;
    *b=c;
}

/*Exercise 3-6. Write a version of itoa that
 *  accepts three arguments instead of two. 
 *  The third argument is a minimum field width; 
 *  the converted number must be padded with blanks
 *   on the left if necessary to make it wide enough.
 */
#include <stdio.h>
#include <string.h>
#define MAXSIZE 100
#define BITS 8*(int)sizeof(int)
void itoa(int,char*,int width);
void reverse(char *);
void swap(char *,char *);
int main(){
    int n=-19;
    char s[MAXSIZE];
    int width=20;
    itoa(n,s,width);
    printf("%d\n%s\n",n,s);
}
void itoa(int n,char s[],int width){
    int i=0,bit;//s[i],bit=n%10
    int sign=(n>=0)?1:-1;
    int overflow=0;
    if(n==1<<(BITS-1)){
        n+=1;
        overflow=1;
    }
    do{
        bit=n%10;
        bit=(bit>0)?bit:(-bit);
        s[i++]=bit+'0';
    }while((n/=10)!=0);
    if(sign==-1)
        s[i++]='-';
    if(overflow)
        s[0]+=1;
    while(i<width)
        s[i++]=' ';
    s[i]='\0';
    reverse(s);
}
void reverse(char s[]){
    int len=strlen(s);
    int i=0;
    int j=len-1;
    while(i<=j){//important
        swap(s+i,s+j);
        i++;
        j--;
    }
}
void swap(char *a,char *b){
    char c;
    c=*a;
    *a=*b;
    *b=c;
}

