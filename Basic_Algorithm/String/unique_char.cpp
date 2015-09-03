/* 
���� http://www.hawstein.com/posts/1.1.html
ԭ�ģ�

Implement an algorithm to determine if a string has all unique characters. What if you can not use additional data structures?

���ģ�

ʵ��һ���㷨���ж�һ���ַ����е��ַ��Ƿ�Ψһ(��û���ظ�).����ʹ�ö�������ݽṹ�� (��ֻʹ�û��������ݽṹ)
  
*/

/* 
����:
input : string
output : 0-û���ظ� 1-���ظ�
1 �ȴӻ������ַ������֡�ASCII  ASCII��ʹ��ָ����7λ��8λ���������������ʾ128��256�ֿ��ܵ��ַ�
1-1 �ó���Ϊ256���������,�����±�-key-ASCII�ַ�.ӳ���˼��
1-2 Bitmap.��Լ�ռ�
 */
#include <iostream>
#include <string>
#define ASCIIMAX 256
#define BITCHECKONE(a, b)  (a & (1 << b)) //���a�ĵ�bλ�Ƿ�Ϊ1
#define BITSETONE(a, b)  (a |= (1 << b))
using namespace std;


uint32_t uniquechar();//typedef unsigned int uint32_t; typedef unsigned long long   uint64_t;
uint32_t bitmap();

int main(){
    if(1 == bitmap())
        cout << "dumplicated!" << endl;
    else
        cout << "unique charactor" << endl;
    return 0;
}

uint32_t uniquechar(){
    cout << "intput a string : " << endl; 
    string input;
    cin >> input;
    const char* pinput = input.c_str();
    uint32_t ascii[ASCIIMAX] = {0}; //trick! ���û��={0} ����ĳ�ʼֵ�Ͳ���Ԥ�ڵ�ÿ����Ϊ0
    uint32_t limit = 1;
    while(*pinput != '\0'){ //���д while(pinput) �������� ָ�����
        cout << "current " << int(*pinput) << " " << ascii[int(*pinput)] << endl;
        ascii[*pinput] += 1;
        if(ascii[int(*pinput)] > limit){
            cout << "over limit " << ascii[int(*pinput)] << endl;
            return 1;
        }
        else
            ++pinput;
    }
    return 0;
    
}

uint32_t bitmap(){
    uint32_t num = ASCIIMAX / (sizeof(int) * 8);
//    uint32_t map[num] = {0};
    uint32_t* map = new uint32_t[num]();
    cout << "intput a string : " << endl; 
    string input;
    cin >> input;
    const char* pinput = input.c_str();
    while(*pinput != '\0'){ //ע������Ҫ��{}�г��� pinput++
        uint32_t index = (*pinput) / 32;
        uint32_t off = (*pinput) % 32;
        if (BITCHECKONE(map[index], off)) //�����鵽ĳλ���Ѿ�Ϊ1�� ˵���������ظ����ַ�
            return 1;
        else{
            BITSETONE(map[index], off); //�ַ���һ�γ���ʱ,����Ӧ��λ����Ϊ1
            ++pinput;
        }
    }
    delete [] map;
    return 0;


}
