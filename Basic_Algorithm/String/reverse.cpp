/* 
���� http://www.hawstein.com/posts/1.2.html
ԭ�ģ�

Write code to reverse a C-Style String. (C-String means that ��abcd�� is represented as five characters, including the null character.)

���ģ�

д���뷭תһ��C�����ַ�����(C������˼��"abcd"��Ҫ��5���ַ�����ʾ������ĩβ�� �����ַ�)
  
*/

/* 
����:
input  : C string
output : reverse string
tips   : �Ӽ������ʼ����
1 ����̳��ȵ�string����,Ҫ��ĩ���¾��ǽ�������charλ��.��ô������string��?
2 Ϊʲô���� ^ ��ʽ�� swap 
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
