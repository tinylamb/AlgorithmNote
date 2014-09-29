/*
 * =========================================================
 *       Filename:  sortedArray_to_bt.c
 *    Description:  有序数组转化为平衡二叉树
 *
 * =========================================================
 */
#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int elem;
    struct node* left;
    struct node* right;
}Node;

Node* change(int a[],int s, int e);
Node* newNode(int e);
void inOrder(Node* root);
int main(){
    int a[] = {0,1,2,3,4,5,6,7,8,9};
    Node* t;
    t = change(a, 0, 9);
    inOrder(t);
    return 0;
}


Node* change(int a[],int s, int e){// 数学归纳法 利用n = 1 来写代码形式;利用 n=k -> n=k+1来检验正确性
    if(s > e)
        return NULL;
    int mid = (s + e)/2;
    printf("mid is %d\n",a[mid]);
    Node *root = newNode(a[mid]);
    root->left = change(a, s, mid-1);
    root->right = change(a, mid+1, e);
    return root;
}

Node* newNode(int e){
    Node* n = (Node*)malloc(sizeof(Node));
    n->elem = e;
    return n;
}

void inOrder(Node* root){
    if(root){
        inOrder(root->left);
        printf(" %d ",root->elem);
        inOrder(root->right);
    }
}
