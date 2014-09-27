/*
 * =========================================================
 *       Filename:  ch6.c
 *    Description:  
 *
 * =========================================================
 */

/*Exercise 6-1. Our version of getword does not
 *  properly handle underscores, string constants,
 *   comments, or preprocessor control lines. Write a better version.
 */
#include <stdio.h>
#include <ctype.h>
#define LIMIT 20
#define STRCONSTANT 0
#define COMMENT 1
#define WORD 2
#define NORMAL 3
#define NKEYS (int)(sizeof(keytab)/sizeof(keytab[0]))

/*char get and unget*/
#define STACKSIZE 10
int top=0;
int buffer[STACKSIZE];
int getch(void){
    return (top==0)?getchar():buffer[--top];
}
void ungetch(int c){
    if(top==STACKSIZE-1)
        printf("buffer full.\n");
    else
        buffer[top++]=c;
}

/*struct key table*/
typedef struct key{
    char *key;
    int count;
}Key;
Key keytab[]={{"auto",0},{"break",0},{"case",0}};

/*deal word in inputstream*/
int GetWord(char *word,const int lim);
int Classify(char c);
void HandleStr(char c);//skip string constants
void HandleCom(char c);//skop comments
void HandleWord(char c, char *word,const int lim);
int IsWord(char c);

int main(){
    char word[LIMIT];
    int class;
    int n;
    while((class=GetWord(word,LIMIT))!=EOF){
        if(class==WORD){
            if((n=binsearch(word,keytab,NKEYS))>=0)
                keytab[n].count++;
        }
    }
    return 0;
}
int GetWord(char *word,const int lim){
    int getch(void);//getchar from input
    void ungetch(int);//putchar back to buffer
    //skip space
    while(isspace(c=getch()))
        ;
    switch(Classify(c)){
        case EOF:
            return EOF;
            break;
        case STRCONSTANT://skip string constants
            HandleStr(c);
            return STRCONSTANT;
            break;
        case COMMENT://skip comments
            HandleCom(c);
            return COMMENT;
            break;
        case WORD:
            HandleWord(c,word,lim);
            return WORD;
            break;
        default:
            return NORMAL;
    }
}
int Classify(char c){
    if(c==EOF)
        return EOF;
    else if(c=='"')
        return STRCONSTANT;
    else if(c=='/')
        return COMMENT;
    else if(c=='_' || isalpha(c))
        return WORD;
    else
        return NORMAL;
}
void HandleStr(char c){
    int ch;
    while((ch=getch())!='"')
        ;
}
void HandleCom(char c){
    int ch;
    if((ch=getch())=='*')
        while((ch=getch())!='/')
            ;
    else
        while((ch=getch())!='\n')
            ;
}
void HandleWord(char c, char *word,const int lim){
    *word++=c;
    int ch;
    for(;--(lim-1)>0;word++)
        if(!IsWord(*word=getch())){
            ungetch(*word);
            break;
        }
    *word='\0';

}
int IsWord(char c){
    return (isalnum(c) || c=='_')?1:0;
}

/*Exercise 6-2. Write a program that reads a C program 
 * and prints in alphabetical order each group of variable
 *  names that are identical in the first 6 characters, 
 *  but different somewhere thereafter. Don't count words
 *   within strings and comments. Make 6 a parameter that
 *    can be set from the command line.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define INITIALSIZE 2
#define INCREMENT 10
#define LIMIT 20
#define STRCONSTANT 0
#define COMMENT 1
#define WORD 2
#define PREPRO 3
#define BRACKET 4
#define NORMAL 5

/*char get and unget*/
#define STACKSIZE 10
int top=0;
int buffer[STACKSIZE];
int getch(void){
    return (top==0)?getchar():buffer[--top];
}
void ungetch(int c){
    if(top==STACKSIZE-1)
        printf("buffer full.\n");
    else
        buffer[top++]=c;
}

/*struct key node*/
typedef struct node{
    char **key;
    int count;
    int size;
    struct node *left;
    struct node *right;
}Node;

/*deal word in inputstream*/
int GetWord(char *word, int lim);
int Classify(char c);
void HandleStr(char c);//skip string constants
void HandleCom(char c);//skip comments
void HandlePre(char c);//skip pre processor
void HandleBra(char c);//skip () and []
void HandleWord(char c, char *word,int lim);
int IsWord(char c);

/*add a word into key tree*/
Node *addtree(Node *,char*,int);
void treeprint(Node*);
char *Strdup(char *);//important
void Initialize(char ***sp,char *w,int *count,int *size);
void InsertWord(char ***sp,char *w,int *count,int *size);

/*strcmpN  preN same*/
int strcmpN(char *s,char *t,int n);

/*main function*/
int main(int argc,char *argv[]){
    int n=atoi(argv[1]+1);
    Node *root=NULL;
    char word[LIMIT];
    int class;
    while((class=GetWord(word,LIMIT))!=EOF){
        if(class==WORD){
            root=addtree(root,word,n);
        }
    }
    treeprint(root);
    return 0;
}
int GetWord(char *word,const int lim){
    int getch(void);//getchar from input
    void ungetch(int);//putchar back to buffer
    int c;
    //skip space
    while(isspace(c=getch()))
        ;
    switch(Classify(c)){
        case EOF:
            return EOF;
            break;
        case STRCONSTANT://skip string constants
            HandleStr(c);
            return STRCONSTANT;
            break;
        case COMMENT://skip comments
            HandleCom(c);
            return COMMENT;
            break;
        case WORD:
            HandleWord(c,word,lim);
            return WORD;
            break;
        case PREPRO:
            HandlePre(c);
            return PREPRO;
            break;
        case BRACKET:
            HandleBra(c);
            return BRACKET;
            break;
        default:
            return NORMAL;
    }
}
int Classify(char c){
    if(c==EOF)
        return EOF;
    else if(c=='"')
        return STRCONSTANT;
    else if(c=='/')
        return COMMENT;
    else if(c=='_' || isalpha(c))
        return WORD;
    else if(c=='#')
        return PREPRO;
    else if(c=='[' || c=='(')
        return BRACKET;
    else
        return NORMAL;
}
void HandleStr(char c){
    int ch;
    while((ch=getch())!='"')
        ;
}
void HandleCom(char c){
    int ch;
    if((ch=getch())=='*')
        while((ch=getch())!='/')
            ;
    else
        while((ch=getch())!='\n')
            ;
}
void HandlePre(char c){
    int ch;
    while((ch=getch())!='\n')
        ;
}
void HandleBra(char c){
    int ch;
    int bra=1;
    while((ch=getch())){
        if(ch=='('||ch=='[')
            bra++;
        else if(ch==')'||ch==']')
            bra--;
        if(bra==0)
            break;
    }
}
void HandleWord(char c, char *word,int lim){
    *word++=c;
    int ch;
    for(;--lim>0;word++)
        if(!IsWord(*word=getch())){
            ungetch(*word);
            break;
        }
    *word='\0';

}
int IsWord(char c){
    return (isalnum(c) || c=='_')?1:0;
}
Node *addtree(Node *r,char *w,int n){
    int cmp;
    if(r==NULL){
        r=(Node *)malloc(sizeof(Node));
        r->left=r->right=NULL;
        Initialize(&(r->key),w,&(r->count),&(r->size));
    }
    else if((cmp=strcmpN((r->key)[0],w,n))==0){
        InsertWord(&(r->key),w,&(r->count),&(r->size));
    }
    else if(cmp<0)
        r->right=addtree(r->right,w,n);
    else
        r->left=addtree(r->left,w,n);
    return r;
}
void treeprint(Node *r){
    if(r!=NULL){
        treeprint(r->left);
        int start=0;
        for(;start<r->count;start++)
            printf("%s ",(r->key)[start]);
        /*
        while(--(r->count)>0){
            printf("%s ",*(r->key));
            (r->key)++;
        }*/
        printf("\n");
        treeprint(r->right);
    }
}
char *Strdup(char *s){
    char *p;
    p=(char *)malloc(strlen(s)+1);
    if(p!=NULL)
        strcpy(p,s);
    return p;
}
void Initialize(char ***sp,char *w,int *count,int *size){
    *count=0;
    *size=INITIALSIZE;
    char **s=*sp;
    s=(char **)malloc((*size)*sizeof(char*));
    s[(*count)++]=Strdup(w);
    *sp=s;
}
void InsertWord(char ***sp,char *w,int *count,int *size){
    char **s=*sp;
    s[(*count)++]=Strdup(w);
    if(*count==*size){
        *size+=INCREMENT;
        s=(char **)realloc(s,(*size)*sizeof(char *));
    }
    *sp=s;
}
int strcmpN(char *s,char *t,int n){
    int i=0;
    while(*s!='\0' && *s==*t){
        i++;
        s++;
        t++;
        if(i==n)
            return 0;
    }
    return (*s-*t>0)?1:-1;
}

/*
Exercise 6-5. Write a function undef that will remove a name and
definition from the table maintained by lookup and install.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 20
#define HASHSIZE 101
/*hash table*/
typedef struct hlist{
    struct hlist *next;
    char *key;
    char *defn;
}Hlist;
Hlist *hashtab[HASHSIZE];

/*hash function f(key)=hashval */
unsigned hash(char *key){
    unsigned hashval=0;
    while(*key!='\0'){
        hashval=31*hashval+*key;
        key++;
    }
    hashval%=HASHSIZE;
    return hashval;
}

/*look up for a key*/
Hlist *Lookup(char *key){
    Hlist *hp;
    hp=hashtab[hash(key)];
    while(hp && strcmp(key,hp->key)!=0)
        hp=hp->next;
    return hp;
}
/*update a key*/
Hlist *Install(char *key,char *defn){
    Hlist *hp;
    hp=Lookup(key);
    if(hp==NULL){
        hp=(Hlist *)malloc(sizeof(Hlist));
        if(hp==NULL || (hp->key=strdup(key))==NULL || (hp->defn=strdup(defn))==NULL)
            return NULL;
        hp->next=hashtab[hash(key)];//insert new at the head
        hashtab[hash(key)]=hp;
    }
    else
        free(hp->defn);
    if((hp->defn=strdup(defn))==NULL)
        return NULL;
    printf("success\n");
    return hp;
}
/*delete a key*/
int Undef(char *key){
    Hlist *hp=hashtab[hash(key)];
    if(hp==NULL)
      return hp;
    if(strcmp(hp->key,key)==0){//if hp points to key
        hashtab[hash(key)]=hp->next;
        free(hp);
        return 1;
    }
    else{
        while(hp->next && strcmp(hp->next->key,key)!=0)//find pre
            hp=hp->next;
        if(hp->next){//if pre exits
            hp->next=hp->next->next;
            free(hp->next);
            return 1;
        }
    }
    return 0;
}

int main(){
    char key[SIZE],defn[SIZE],query[SIZE];
    printf("input your query key: ");
    scanf("%s",query);
    while(scanf("%s %s",key,defn)!=EOF){
        Install(key,defn);
    }
    Hlist *hp;
    if((hp=Lookup(query)))
        printf("key:%s  defn:%s\n",hp->key,hp->defn);
    else
        printf("%s not in hashtable\n",query);
    return 0;
}

