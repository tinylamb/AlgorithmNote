/* 
链接 http://www.hawstein.com/posts/1.1.html
原文：

Implement an algorithm to determine if a string has all unique characters. What if you can not use additional data structures?

译文：

实现一个算法来判断一个字符串中的字符是否唯一(即没有重复).不能使用额外的数据结构。 (即只使用基本的数据结构)
  
*/

/* 
分析:
input : string
output : 0-没有重复 1-有重复
1 先从基本的字符集入手。ASCII  ASCII码使用指定的7位或8位二进制数组合来表示128或256种可能的字符
1-1 用长度为256的数组计数,数组下标-key-ASCII字符.映射的思想
1-2 Bitmap.节约空间
 */
#include <iostream>
#include <string>
#define ASCIIMAX 256
#define BITCHECKONE(a, b)  (a & (1 << b)) //检查a的第b位是否为1
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
    uint32_t ascii[ASCIIMAX] = {0}; //trick! 如果没有={0} 数组的初始值就不是预期的每个都为0
    uint32_t limit = 1;
    while(*pinput != '\0'){ //如果写 while(pinput) 就是灾难 指针飞了
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
    while(*pinput != '\0'){ //注意这里要在{}中出现 pinput++
        uint32_t index = (*pinput) / 32;
        uint32_t off = (*pinput) % 32;
        if (BITCHECKONE(map[index], off)) //如果检查到某位上已经为1了 说明出现了重复的字符
            return 1;
        else{
            BITSETONE(map[index], off); //字符第一次出现时,将对应的位设置为1
            ++pinput;
        }
    }
    delete [] map;
    return 0;


}
