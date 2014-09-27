/*
 * =========================================================
 *       Filename:  ch1.c
 *    Description:  solutions to TCPL ch1
 *
 * =========================================================
 */

/*reference http://users.powernet.co.uk/eton/kandr2/index.html*/
/*
Exercise 1-1. Run the ``hello, world'' program on your system. Experiment with 
leaving out parts of the program, to see what error messages you get.
*/
#include <stdio.h>
int main(){
  printf("hello world.\n");
  return 0;
}

/*
Exercise 1-2. Experiment to find out what happens when prints's argument string
contains \c, where c is some character not listed above.
*/
key word:escape sequences
\c isn't a escape sequence

/*
Exercise 1-3. Modify the temperature conversion program to print a heading above the table.
*/
#include <stdio.h>

int main(void)
{
  float fahr, celsius;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  printf("%6s %6s","fahr","celsius");
  fahr = lower;
  while(fahr <= upper)
  {
    celsius = (5.0 / 9.0) * (fahr - 32.0);
    printf("%6.0f %6.1f\n", fahr, celsius);
    fahr = fahr + step;
  }
  return 0;
}

/*
Exercise 1-4. Write a program to print the corresponding Celsius to Fahrenheit table.
*/
#include <stdio.h>
#include <string.h>
#define CONVERTF(F) 5*(F-32)/9.0 /* 函数宏 编译阶段完成 */
#define CONVERTC(C) 9.0*C/5+32
#define STEP 20 /* 常量宏 */
#define LOWER 0
#define UPPER 300
int main(int argc,char *argv[]){
    if(argc!=2)
        printf("-usage: func [-f|c]\n");
    else{
        float f,c;
        if(strcmp(argv[1],"-f")==0)
            for(f=LOWER;f<=UPPER;f+=STEP)
                printf("%10.2f%10.2f\n",f,CONVERTF(f));
        else
            for(c=LOWER;c<=UPPER;c+=STEP)
                printf("%10.2f%10.2f\n",c,CONVERTC(c));
    }
    return 0;

}

/*
Exercise 1-5. Modify the temperature conversion program to print the table in reverse 
order, that is, from 300 degrees to 0.
*/
#include <stdio.h>

int main(void)
{
  float fahr, celsius;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  printf("%6s %6s","fahr","celsius");
  fahr = upper;
  while(fahr >= lower)
  {
    celsius = (5.0 / 9.0) * (fahr - 32.0);
    printf("%6.0f %6.1f\n", fahr, celsius);
    fahr = fahr -step;
  }
  return 0;
}

/*
Exercsise 1-6. Verify that the expression getchar() != EOF is 0 or 1.
 *This program prompts for input, and then captures a character
 * from the keyboard. If EOF is signalled (typically through a
 * control-D or control-Z character, though not necessarily),
 * the program prints 0. Otherwise, it prints 1.
 *
 * If your input stream is buffered (and it probably is), then
 * you will need to press the ENTER key before the program will
 * respond.
*/
#include <stdio.h>

int main()
{
  printf("Press a key. ENTER would be nice :-)\n\n");
  printf("The expression getchar() != EOF evaluates to %d\n", getchar() != EOF);
  return 0;
}

/*
Exercise 1-7. Write a program to print the value of EOF.
EOF=-1.
return of getchar():
*On success, the character read is returned (promoted to an int value).ASCII
*The return type is int to accommodate for the special value EOF, which indicates failure:
*If the standard input was at the end-of-file, the function returns EOF and sets the eof 
*indicator (feof) of stdin.
*If some other reading error happens, the function also returns EOF, but sets its error 
*indicator (ferror) instead.
*/
#include <stdio.h>

int main()
{
  printf("The value of EOF is %d\n\n", EOF);
  
  return 0;
}

/*
Exercise 1-8. Write a program to count blanks, tabs, and newlines.
*/
#include <stdio.h>
int main(){
  int blank=tab=nl=0;
  int c;
  while((c=getchar())!=EOF){
    if (c==' ')
      blank++;
    else if (c=='\t')
      tab++;
    else if (c=='\n')
      nl++;
  }
  printf("blank:%2d tab:%2d newline:%2d \n",blank,tab,nl);
  return 0;
}

/*
Exercise 1-9. Write a program to copy its input to its output, replacing each string 
of one or more blanks by a
single blank.
*/
#include <stdio.h>
int main(){
    int c,blank=0;//blank==0表示output的末尾不是空符(tab/nl/' ') blank==1则相反
    while((c=getchar())!=EOF){
        if (c!=" "){
            putchar(c);
            blank=0;
        }
        else{
            if (blank==0){
                putchar(c);
                blank=1;
            }
        }
    }
    return 0;
}

/*
Exercise 1-10. Write a program to copy its input to its output, replacing each tab by \t, 
each backspace by \b,
and each backslash by \\. This makes tabs and backspaces visible in an unambiguous way.
*/
#include <stdio.h>
int main(){
  int c;
  while((c=getchar())!=EOF){
    if (c=='\t')
      printf("\\t");
    else if(c=='\b')
      printf("\\b");
    else if (c=='\\')
      printf("\\\\");
    else 
      putchar(c);
  }
}

/*
Exercise 1-12. Write a program that prints its input one word per line.
*/
#include <stdio.h>
int main(){
  int c,blank=1;
  while((c=getchar())!=EOF){
    if (c=='\n'||c=='\t'||c==' '){
      if (blank==0){
        printf("\n");
        blank=1;
      }
    }
    else{
      putchar(c);
      blank=0;
    }
  }
  return 0;
}

/*rewite from WordCount */
#include <stdio.h>
main(){
  int c,blank=1;//blank=1 means there is a blank at the end of buffer
  int word=0;
  while((c=getchar())!=EOF){
    if (c=="\n" || c=='\t' || c==' ')
      blank=1;
    else{
      if(blank==1){
        word++;
        blank=0;
      }
    }
  }
  printf("word:%d\n",word);
}

/*another version*/
#include <stdio.h>
int main(){
    int c;//char in in stream
    int word=0;//counting of words
    int space=1;//1 means there is space at the end of out stream
    int newline=0;//newline controal many newlines to 1
    while((c=getchar())!=EOF){
        if(c==' '|| c=='\t' || c=='\n'){
            space=1;
            if(newline==0){
                printf("\n");
                newline=1;
            }
        }
        else{
            if(space==1)
                word++;
            putchar(c);
            space=0;
            newline=0;
        }
    }
    printf("%d\n",word);
    return 0;
}


/*
Exercise 1-13. Write a program to print a histogram of the lengths of words in its input.
It is easy to draw the
histogram with the bars horizontal; a vertical orientation is more challenging.
*rewrite from WordCount
*/
#include<stdio.h>
void print_stars(int n){
  for(int i=1;i<=n;i++)
    printf("* ");
}
main(){
  int c,blank=1;
  int word[100],w=-1;//word[i] = len of word(i),i from 0,1,2...
  while((c=getchar())!=EOF){
    if(c=='\n'||c==' '||c=='\t')
      blank=1;
    else{
      if (blank==1){
        w++;
        word[w]=1;
        blank=0;
      }
      else if(blank==0)
        word[w]++;
    }
  }
  word[w+1]=0;//end to the word sequence
  for(int i=0;word[i]!=0;i++){
    printf("word %d:",i+1);
    print_stars(word[i]);
    printf("\n");
  }
}
/*rewrite from wordcount*/
#include <stdio.h>
#include <ctype.h>
#define MAX 30
void printstars(int);
int main(){
    int c;
    int len=0;// length of word
    int newline=1;
    while((c=getchar())!=EOF){
        if(isspace(c)){
            if(newline==0){
                printstars(len);
                newline=1;
                len=0;
            }

        }
        else{
            putchar(c);
            len++;
            newline=0;
        }
    }
    return 0;
}
void printstars(int n){
    int i=1;
    printf(":");
    while(i++<=n){
        printf("* ");
    }
    printf("\n");
}

/*Exercise 1-14. Write a program to print a histogram of
 * the frequencies of different characters in its input.
 */
#include <stdio.h>
#define ASCII 256
int main(){
    int ch[ASCII];//like a hash table
    int i;
    for(i=0;i<ASCII;i++)//initialize ch[ASCII]
        ch[i]=0;
    int c;
    while((c=getchar())!=EOF)
        ch[c]++;
    for(i=0;i<ASCII;i++)
        if(ch[i]!=0)
            printf("%c:%d\n",i,ch[i]);
    return 0;
}

/*Exercise 1.15. Rewrite the temperature conversion program
 * of Section 1.2 to use a function for conversion.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
float FtoC(float);
float CtoF(float);
int main(int argc,char *argv[]){
    if(argc!=3)
        printf("format error: ./func [-f|-c] float\n");
    else{ 
        if(strcmp(argv[1],"-f")==0)
            printf("%5.3f\n",FtoC(atof(argv[2])));
        else
            printf("%5.3f\n",CtoF(atof(argv[2])));
    }
    return 0;
}
float FtoC(float f){
    return 5.0*(f-32)/9;
}
float CtoF(float c){
    return 9.0*c/5+32;
}

/*.........print maxlen line.............*/
//refer:http://denniskubes.com/2012/08/14/do-you-know-what-p-does-in-c/  *p++
#include <stdio.h>
#define MAXSIZE 100
void strcopy(char *,char *);
int main(){
    char line[MAXSIZE];
    char max[MAXSIZE];
    int len=0,maxlen=0;
    int c;
    while((c=getchar())!=EOF){
        if(c!='\n')
            line[len++]=c;
        else{
            if(len>maxlen){
                line[len]='\0';
                strcopy(max,line);
            }
            len=0;
        }
    }
    printf("maxline:%s\n",max);
    return 0;
}
void strcopy(char *s,char *t){//t to s
    while(*s++=*t++)
        ;
}
//make getline() universal
int getline(char *l,int lim){
    int c;
    int len=0;
    while(--lim>0 &&(c=getchar())!=EOF && c!='\n' )
        l[len++]=c;
    l[len]='\0';
    return len;
}
/*
Exercise 1-16. Revise the main routine of the longest-line program so it will 
correctly print the length of arbitrary long input lines, 
and as much as possible of the text.
*/
#include <stdio.h>
int main(){
    int c;
    int maxline=0,line=1,maxlen=0,len=0;//the first line is 1-th line
    int number=0;// 0 means there is no line number
    while((c=getchar())!=EOF){
        if(c!='\n'){
            if(number==0)
                printf("%d:",line);
            len++;
            number=1;
        }
        else{// newline update len,number=0
            if(len>maxlen){
                maxlen=len;
                maxline=line;
            }
            line++;//next line
            len=0;
            number=0;
        }
        putchar(c);

    }
    printf("max line is line %d.with len of %d\n",maxline,maxlen);
    return 0;
}
/*
Exercise 1-17. Write a program to print all input lines that are longer than 80 characters.
*/
while(GetLine(l,LIM)>80)
    printf("%s",l);
    
/*Exercise 1-18. Write a program to remove trailing
 *  blanks and tabs from each line of input, and to
 *  delete entirely blank lines.
 */
#include <stdio.h>
#define MAXLEN 100
int GetLine(char *,int);
int main(){
    char line[MAXLEN];
    int len;
    while((len=GetLine(line,MAXLEN))>0)
        if(len>1)
            printf("%s",line);
    return 0;
}
int GetLine(char *l,int lim){
    int c;
    int space=0;//the first space position at tail
    int p=0;//current position
    while((c=getchar())!=EOF && c!='\n'){
        l[p++]=c;
        if(c!=' '&& c!='\t')//key idea
            space=p;
    }
    if(c=='\n')//c==EOF || c=='\n' break while
        l[space++]='\n';
    l[space]='\0';
    return space;
}

/*
Exercise 1-19. Write a function reverse(s) that reverses the character string s. 
Use it to write a program that reverses its input a line at a time.
*/

/*
how to increse string  dynamically?
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INCREMENT 32
int GetString(char *s,char **t,unsigned int InitialSize);
int main(){
    unsigned int InitialSize=10;
    char *s=malloc(InitialSize);
    /*...v3  success in main
    int c;
    unsigned int current_size=InitialSize;
    unsigned int len=0;
    while((c=getchar())!=EOF && c!='\n'){
        s[len++]=c;
        if(len==current_size){
            current_size+=INCREMENT;
            s=realloc(s,current_size);
        }
    }
    s[len]='\0';
    printf("%s\n",s);
    */
    if(GetString(s,&s,InitialSize)>0) 
        printf("%s\n",s);
    free(s);
    s=NULL;
}
//....v4 success by calling function
int GetString(char *s,char **t,unsigned int InitialSize){
    int c;
    unsigned int current_size=InitialSize;
    unsigned int len=0;
    while((c=getchar())!=EOF && c!='\n'){
        s[len++]=c;
        if(len==current_size){
            current_size+=INCREMENT;
            s=realloc(s,current_size);
        }
    }
    s[len]='\0';
    *t=s;
    return len;
}

/*...v2 fail same reason with v1
int GetString(char *s,unsigned int InitialSize){
    int c;
    unsigned int current_size=InitialSize;
    unsigned int len=0;
    while((c=getchar())!=EOF && c!='\n'){
        s[len++]=c;
        if(len==current_size){
            current_size+=INCREMENT;
            s=realloc(s,current_size);
        }
    }
    s[len]='\0';
    return len;
}
*/

/*...v1 fail  know why!
int Getline(char *s,char *more);
int main(){
    char *s=(char *)malloc(1*sizeof(char));
    char *more=(char*
