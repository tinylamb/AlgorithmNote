/*
 * =========================================================
 *       Filename:  vector_type.cpp
 *    Description:  
 *
 * =========================================================
 */
#include <iostream>
#include <vector>

using namespace std;
int main(){
    vector<int> ivec(0); // vector是类模版, vector<int> 是数据类型
    vector<int>::size_type len = ivec.size();
    cout << "len of ivec is " << len << endl;

    // ivec(10)  push_back(i)时 ivec.size()也在增长  i永远都比ivec.size()小
    for(vector<int>::size_type i = 0; i != 10; i++)
        ivec.push_back(i); // ivec[i] = i 是没有用的 []操作只能获取已存在的数值


    for(vector<int>::size_type i = 0; i != ivec.size(); i++)
        cout << ivec[i] << " ";
    cout << endl;

    for(vector<int>::iterator it = ivec.begin(); it != ivec.end(); it++) // 类比指针
        *it = 2 * (*it);

    for(vector<int>::size_type i = 0; i != ivec.size(); i++)
        cout << ivec[i] << " ";
    cout << endl;

    return 0;
}

