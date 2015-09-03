/* 
链接 http://www.hawstein.com/posts/1.2.html
原文：

Write code to reverse a C-Style String. (C-String means that “abcd” is represented as five characters, including the null character.)

译文：

写代码翻转一个C风格的字符串。(C风格的意思是"abcd"需要用5个字符来表示，包含末尾的 结束字符)
  
*/

/* 
分析:
input  : C string
output : reverse string
tips   : 从简单情况开始考虑
1 从最短长度的string考虑,要本末导致就是交换两个char位置.那么更长的string呢?
2 为什么不用 ^ 方式的 swap 
http://www.cnblogs.com/ider/archive/2012/05/03/xor_swap_issues.html
 */

#include "string_alg.h"

void swap(char& cA, char& cB);
void swapV1(char* pA, char* pB);
int main(){
    cout << "input a string : ";
    string sInput;
    cin >> sInput;
    //convert sInput to a C_str
    char* pInput = new char[sInput.size() + 1];
    std::strcpy(pInput, sInput.c_str());
    char* pHead = pInput;
    char* pTail = pInput + sInput.size() - 1;
    while (pHead < pTail){
        swap(*pHead, *pTail);
        swapV1(pHead, pTail);
        ++pHead;
        --pTail;
    }
    cout << "before  : " << sInput << endl;
    cout << "after   : " << pInput << endl;
    return 0;

}


void swap(char& cA, char& cB){
    char cTemp;
    cTemp = cA;
    cA = cB;
    cB = cTemp;
}

void swapV1(char* pA, char* pB){
    char cTemp;
    cTemp = *pA;
    *pA = *pB;
    *pB = cTemp;
}
