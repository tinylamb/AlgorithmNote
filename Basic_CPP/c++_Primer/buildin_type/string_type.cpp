/*
 * =========================================================
 *       Filename:  string_type.cpp
 *    Description:  
 *
 * =========================================================
 */
#include <iostream>
#include <string>
#include <cstring> // char *

using namespace std;
int main(){
    //定义string 对象
    string st("the expense of spirit.");
    cout << "len of " << st << " is " << st.size() << endl;

    string st1;
    if(st1.empty()) // string 是否为空判断
        st1 = st; // string copy
    cout << st1 << endl;
   
    string st2;
    st2 = st + st1; // string 连接.在python 中太常见了
    cout << st2 << endl;

    string st3;
    const char *s = "fuck you."; // cstring 是const类型 .但 string 是可变类型
    st3 = s; // cstring to string .反向不行
    cout << st3 << endl;

    return 0;
}

