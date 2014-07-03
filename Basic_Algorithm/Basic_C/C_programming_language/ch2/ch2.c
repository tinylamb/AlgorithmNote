/*
 * =========================================================
 *       Filename:  ch2.c
 *    Description:  
 *
 * =========================================================
 */
/*reference http://users.powernet.co.uk/eton/kandr2/index.html*/
/*
Exercise 2-1. Write a program to determine the ranges of 
char, short, int, and long variables, both signed and unsigned, 
by printing appropriate values from standard headers and by direct
computation. Harder if you compute them: determine the ranges of the various floating-point types.
*/
/*********too slow***************
#include <stdio.h>
#define ElemType signed short
int main(){
  ElemType c,max,min;
  c=max=1;
  while(c==max){
    c++;
    if (c-max==1)
      max++;
  }
  c=min=1;
  while(c==min){
    c--;
    if(c-min==-1)
      c--;
  }
  printf("max:%d  min:%d.\n",max,min);
  return 0;
}
**************************************/


/*---------------------------------------------------
 *  v1 hint:利用越界的概念
 *---------------------------------------------------*/
#include <stdio.h>
#define ElemType signed short
int main(){
  ElemType c,max,min;
  c=max=1;
  while(c==max){
    c*=2;
    if (c/max==2)
      max*=2;
    else
      max=max-1+max;

  }
  c=min=1;
  while(c==min){
    c*=-2;
    if (c/min==-2)
      min*=-2;
  }
  printf("max:%d  min:%d.\n",max,min);
  return 0;
}

/*---------------------------------------------------
 *  v2 利用bit表示的原理
 *---------------------------------------------------*/
#include <stdio.h>
// Prints min and max value for a signed type
void printUnsignedRange(size_t bytes)
{
    int bits = 8*bytes;
 
    // Note that the value of ‘to’ is "(1 << bits) – 1"
    // Writing it in following way doesn’t cause overflow
    unsigned int to = ((1 << (bits-1)) – 1) + (1 << (bits-1)) ;
 
    printf(" range is from %u to %u \n", 0, to);
}
 
// Prints min and max value for an unsigned type
void printSignedRange(size_t bytes)
{
   int bits = 8*bytes;
   int from = -(1 << (bits-1));
   int to =  (1 << (bits-1)) – 1;
   printf(" range is from %d to %d\n", from, to);
}
 
int main()
{
    printf("signed char: ");
    printSignedRange(sizeof(char));
 
    printf("unsigned char: ");
    printUnsignedRange(sizeof(unsigned char));
 
    printf("signed int: ");
    printSignedRange(sizeof(int));
 
    printf("unsigned int: ");
    printUnsignedRange(sizeof(unsigned int));
 
    printf("signed short int: ");
    printSignedRange(sizeof(short int));
 
    printf("unsigned short int: ");
    printUnsignedRange(sizeof(unsigned short int));
 
    return 0;
}

/*
Exercise 2-2.Write a loop equivalent to the for loop above without using && or || . 
*/
#include <stdio.h>
#define MAX_STRING_LENGTH 100
int main(void)
{
  /*
	for (i = 0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
		s[i] = c;
	*/
	int i = 0,lim = MAX_STRING_LENGTH,c;
	char s[MAX_STRING_LENGTH];
	while (i < (lim - 1))
	{
		c = getchar();
		if (c == EOF)
			break;
		else if (c == '\n')
			break;
		s[i++] = c;
	}
	s[i] = '\0';   /* terminate the string */
	return 0;
}


/*Exercise 2-3. Write a function htoi(s), which converts 
 * a string of hexadecimal digits (including an optional 0x or 0X) 
 * into its equivalent integer value. The allowable digits
 *  are 0 through 9, a through f, and A through F.
 */
#include <stdio.h>
#include <ctype.h>
int htoi(char *);
int main(int argc,char *argv[]){
    if(argc!=2)
        printf("format error:./func hex\n");
    else{
        printf("%d\n",htoi(argv[1]));
    }
}
int htoi(char *s){
    int iter=0;//iterator
    int i=0;//h to i
    if(s[iter+1]=='x' || s[iter+1]=='X')//pass 0x/0X option
        iter+=2;
    while(isdigit(s[iter]) || (s[iter]>='a'&&s[iter]<='f') || (s[iter]>='A'&&s[iter]<='F')){//allowable 0-9 a-f A-F
        if(isdigit(s[iter]))
            i=16*i+s[iter]-'0';
        else if(s[iter]>='a' && s[iter]<='f')
            i=16*i+s[iter]-87;//'a'=97  in hex a=10
        else
            i=16*i+s[iter]-45;//'A'=65 in hex A=10
        iter++;
    }
    if(s[iter]!='\0'){
        printf("allowable 0-9 a-f A-F\n");
        return -1;
    }
    else
        return i;

}

/*
Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes each character in s1 that
matches any character in the string s2.
*/
#include <stdio.h>
void set(char s[]){// delete duplicated items in s
  int i,j,end;
  end=0;
  for(i=1;s[i]!='\0';i++){//iter in [0,\0)
    j=0;//iter in [0,end]
    while(j<=end && s[j]!=s[i])//[0,end] already set
      j++;
    if (j>end){//s[i] not in [0,end]
      end=j;//expand end position
      s[end]=s[i];
    }
  }
  s[end+1]='\0';
}

void delete_char(char s[],char c){
  int i,j;
  for(i=j=0;s[i]!='\0';i++)
    if (s[i]!=c)
      s[j++]=s[i];
  s[j]='\0';
  //return s;
}

void squeeze(char s1[],char s2[]){
  set(s2);//key operation
  for(int i=0;s2[i]!='\0';i++)
    delete_char(s1,s2[i]);
}

int main(){
  char s[]="my name is gao yang x";
  char s1[]="my name is gao yang";
  squeeze(s,s1);
  printf("%s\n",s);
  return 0;
}

/*Exercise 2-5. Write the function any(s1,s2), which returns the
 *  first location in a string s1 where any character from the 
 *  string s2 occurs, or -1 if s1 contains no characters from s2. 
 *  (The standard library function strpbrk does the same job but 
 *  returns a pointer to the location.)
 */
#include <stdio.h>
void any(char *,char *);
int position(char *,char);
int main(int argc,char *argv[]){
    if(argc!=3)
        printf("format error:./func s1 s2\n");
    else
        any(argv[1],argv[2]);
    return 0;
}
void any(char *s1,char *s2){//find s2 in s1
    while(*s2 !='\0'){//error:*s2++
        printf("%d ",position(s1,*s2));
        s2++;
    }
    printf("\n");

}
int position(char *s1,char c){
    int i=0;
    while(s1[i]!='\0' && s1[i]!=c)
        i++;
    if(s1[i]=='\0')
        return -1;
    else
        return i;
}

/*Exercise 2-6. Write a function setbits(x,p,n,y)
 *  that returns x with the n bits that begin
 *   at position p set to the rightmost n bits of y,
 *   leaving the other bits unchanged.
 */
#include <stdio.h>
#include <stdlib.h>
int setbits(int,int,int,int);
void binary(int);
int main(int argc,char *argv[]){
    
    if(argc!=5)
        printf("format error:./func x p n y\n");
    else{
        int x=atoi(argv[1]);
        int convert_i;
        int y=atoi(argv[4]);
        convert_i=setbits(x,atoi(argv[2]),atoi(argv[3]),y);
        binary(x);
        binary(y);
        binary(convert_i);
    }
    return 0;
}
int setbits(int x,int p,int n,int y){
    int key,new_key;
    key=(1<<n)-1;//001
    new_key=key<<(p+1-n);//010
    y=y&key;//00y;
    y=y<<(p+1-n);//get the last n bits of y  0y0
    y=(~new_key)^y;//101 ^ 0y0 =1y1
    x=x|new_key;//abc to a1c
    x=x&y;//a1c & 1y1 =ayc
    return x;
}
void binary(int i){
    int size=(int)sizeof(int);
    int len=size*8;
    char b[len+1];
    b[len]='\0';
    int iter,mod;
    for(iter=len-1;iter>=0;iter--){
        if(i!=0){
            mod=i%2;
            if(mod==1)
                b[iter]='1';
            else
                b[iter]='0';
            i/=2;
        }
        else
            b[iter]='0';
    }
    printf("%s\n",b);
}

/*Exercise 2-7. Write a function invert(x,p,n)
 *  that returns x with the n bits that begin 
 *  at position p inverted (i.e., 1 changed into 0
 *   and vice versa), leaving the others unchanged.
 */
#include <stdio.h>
#include <stdlib.h>
void binary(int);
int invert(int ,int ,int);
int main(int argc,char *argv[]){
    
    if(argc!=4)
        printf("format error:./func x p n\n");
    else{
        int x=atoi(argv[1]);
        int invert_x;
        invert_x=invert(x,atoi(argv[2]),atoi(argv[3]));
        binary(x);
        binary(invert_x);
    }
    return 0;

}
int invert(int x,int p,int n){
    int key,new_key;
    key=(1<<n)-1;//001
    new_key=key<<(p+1-n);//010
    x=x^new_key;//abc ^ 010 =a(~b)c
    return x;
}
void binary(int i){
    int size=(int)sizeof(int);
    int len=size*8;
    char b[len+1];
    b[len]='\0';
    int iter,mod;
    for(iter=len-1;iter>=0;iter--){
        if(i!=0){
            mod=i%2;
            if(mod==1)
                b[iter]='1';
            else
                b[iter]='0';
            i/=2;//i=i>>2 error?
        }
        else
            b[iter]='0';
    }
    printf("%s\n",b);
}

/*Exercise 2-8. Write a function rightrot(x,n)
 *  that returns the value of the integer x
 *  rotated to the right by n positions.
 */
#include <stdio.h>
#include <stdlib.h>
#define BITS 8*(int)sizeof(int)
void binary(int);
int rightrot(int ,int);
int main(int argc,char *argv[]){
    if(argc!=3)
        printf("format error:./func x n\n");
    else{
        int x=atoi(argv[1]);
        int rightrot_x=rightrot(x,atoi(argv[2]));
        binary(x);
        binary(rightrot_x);

    }
    return 0;
}
int rightrot(int x,int n){
    //x=ab
    int key,y;
    key=(1<<n)-1;//01
    y=x&key;//0b
    y=y<<(32-n);//b0
    x=x>>n;//0a
    return x+y;//0a+b0=ba
}
void binary(int i){//signed number ex:-1 error
    int sign=1;//1 for positive number,-1 for negtive number
    char b[BITS+1];
    b[BITS]='\0';
    int iter,mod;
    if(i<0){//important
        i=((1<<(BITS-1))-1)&i;
        sign=-1;
    }
    for(iter=BITS-1;iter>=0;iter--){
        if(i!=0){
            mod=i%2;
            if(mod==1)
                b[iter]='1';
            else
                b[iter]='0';
            i/=2;//i=i>>2 error?
        }
        else
            b[iter]='0';
    }
    if(sign==-1)
        b[0]='1';
    printf("%s\n",b);
}
/*e2_9 In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x 
. Explain why. Use this observation to write a faster version of bitcount . 
*/

//bitcount is written on p.50 as this:
// bitcount:  count 1 bits in x 
int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}


/* Answer: If x is odd, then (x-1) has the same bit representation as x 
 * except that the rightmost 1-bit is now a 0. In this case, (x & (x-1)) == (x-1). 
 * If x is even, then the representation of (x-1) has the rightmost zeros of x 
 * becoming ones and the rightmost one becoming a zero. Anding the two 
 * clears the rightmost 1-bit in x and all the rightmost 1-bits from (x-1).
 * Here's the new version of bitcount: 
 */

 /* bitcount:  count 1 bits in x */
int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x &= (x-1))
        b++;
    return b;
}

/*Exercise 2-10. Rewrite the function lower, which
 * converts upper case letters to lower case, with a
 *conditional expression instead of if-else.
 */
#include <stdio.h>
#include <ctype.h>
int lower(int);
int main(){
    int c;
    while((c=getchar())!=EOF )
        if(isalpha(c)) 
            printf("%c\n",lower(c));
        else
            putchar(c);
    return 0;
}
int lower(int c){
    return (c>='A' && c<='Z')?c+'a'-'A':c;
}

