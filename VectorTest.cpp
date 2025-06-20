/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

// 引入控制台相关的头文件，通常用于与控制台进行交互
#include "console.h"
// 引入简单输入输出相关的头文件，可能包含一些方便的输入输出函数
#include "simpio.h"
// 引入标准库中的 vector 容器的头文件
#include <vector>
// 引入斯坦福库中的 Vector 容器的头文件
#include "vector.h"

// 使用标准命名空间，这样可以直接使用标准库中的类和函数，无需加上 std:: 前缀
using namespace std;

// 主函数，程序的入口点
int main()
{
    // 定义一个存储整数的标准库 vector 容器
    vector<int> myVector;

    // 向 myVector 中添加元素 10，此时 myVector 内容为 [10]
    myVector.push_back(10); 
    // 向 myVector 中添加元素 20，此时 myVector 内容为 [10, 20]
    myVector.push_back(20); 
    // 向 myVector 中添加元素 30，此时 myVector 内容为 [10, 20, 30]
    myVector.push_back(30); 

    // 在 myVector 的索引 1 处插入元素 15，此时 myVector 内容为 [10, 15, 20, 30]
    myVector.insert(myVector.begin() + 1, 15); 

    // 输出提示信息，表示接下来要输出 vector 的元素
    cout << "Vector elements: ";
    // 使用范围 for 循环遍历 myVector 中的每个元素
    for (int val : myVector) {
        // 输出当前元素，并在元素之间添加一个空格
        cout << val << " ";
    }
    // 换行，使输出格式更清晰
    cout << endl; // 输出: 10 15 20 30

    // 删除 myVector 末尾的元素 30，此时 myVector 内容为 [10, 15, 20]
    myVector.pop_back(); 
    // 删除 myVector 开头的元素 10，此时 myVector 内容为 [15, 20]
    myVector.erase(myVector.begin()); 

    // 输出 myVector 索引 0 处的元素
    cout << "Element at index 0: " << myVector[0] << endl; // 输出: 15

    // 定义一个存储字符的斯坦福库 Vector 容器
    Vector<char> myStandfordVector;
    // 使用 for 循环从字符 'a' 到 'z' 依次添加到 myStandfordVector 中
    for(char c='a'; c<='z'; c++)
        // 向 myStandfordVector 中添加字符 c
        myStandfordVector += c;  // myStandfordVector.add(c);

    // 使用传统的 for 循环遍历 myStandfordVector 中的每个元素
    for(int i=0; i<26; i++)
        // 输出当前元素，并在元素之间添加一个空格
        cout << myStandfordVector[i]<< " ";

    // 换行，使输出格式更清晰
    cout << endl;
    // 使用范围 for 循环遍历 myStandfordVector 中的每个元素
    for(char c : myStandfordVector)
        // 输出当前元素，并在元素之间添加一个空格
        cout << c <<" ";

    // 主函数返回 0，表示程序正常结束
    return 0;
}
