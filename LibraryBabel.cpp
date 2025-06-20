/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

// 引入控制台库，用于控制台输入输出
#include "console.h"
// 引入简单输入输出库，提供更便捷的输入输出函数
#include "simpio.h"
// 引入队列库，队列是一种先进先出（FIFO）的数据结构
#include "queue.h"
// 引入向量库，向量是一种动态数组
#include "vector.h"
// 引入字符串库，用于处理字符串
#include <string>

// 使用标准命名空间，这样可以直接使用标准库中的类和函数
using namespace std;
// 定义一个常量 MAXLENGTH，用于限制生成字符串的最大长度
const int MAXLENGTH = 5;

// 主函数，程序的入口点
int main()
{
    // 声明一个存储字符串的队列 librarybabel
    Queue<string> librarybabel;
    // 声明一个存储字符串的向量 stringTable，并初始化它包含两个元素 "A" 和 "B"
    Vector<string> stringTable = {"A", "B"};

    // 向队列 librarybabel 中添加一个空字符串
    librarybabel.enqueue("");

    // 当队列 librarybabel 不为空时，执行循环体
    while(!librarybabel.isEmpty())
    {
        // 从队列 librarybabel 中取出队首元素，并将其赋值给字符串变量 str
        string str = librarybabel.dequeue();
        // 输出当前取出的字符串
        cout << str << endl;
        // 如果当前字符串的长度小于 MAXLENGTH
        if(str.length()<MAXLENGTH)
            // 遍历向量 stringTable 中的每个字符串元素 ss
            for(const string& ss:stringTable)
                // 将当前字符串 str 与 ss 拼接后，再添加到队列 librarybabel 中
                librarybabel.enqueue(str+ss);

    }

    // 程序正常结束，返回 0
    return 0;
}
