// 包含用于生成随机数的头文件
#include "random.h"
// 包含用于图形窗口操作的头文件
#include "gwindow.h"
// 包含用于图形对象操作的头文件
#include "gobjects.h"
// 包含用于图形事件处理的头文件
#include "gevent.h"
// 包含控制台输入输出操作的头文件，常用于处理控制台输入
#include <conio.h>
// 包含标准输入输出库的头文件，提供基本的输入输出功能
#include <stdio.h>
// 包含控制台相关功能的头文件，用于控制台操作
#include "console.h"
// 包含Set容器的头文件，用于集合操作
#include "set.h"
// 包含输入输出流的头文件，用于标准输入输出
#include <iostream>
// 使用标准命名空间，这样可以直接使用标准库中的类和函数，而无需加std::前缀
using namespace  std;

// 递归函数，用于列出集合的所有子集
// remaining：表示还未处理的元素集合
// used：表示已经处理过的元素集合
void listSubsetsRec(const Set<char>& remaining, const Set<char>& used)
{
    // 如果剩余元素集合为空，说明已经处理完所有元素
    if(remaining.isEmpty())
        // 输出当前已经处理过的元素集合，即一个子集
        cout << used << endl;
    else
    {
        // 取出剩余元素集合中的第一个元素
        char elem = remaining.first();
        // 递归调用，包含当前元素的情况
        // 从剩余元素集合中移除当前元素，同时将当前元素加入已处理元素集合
        listSubsetsRec(remaining - elem, used + elem);
        // 递归调用，不包含当前元素的情况
        // 从剩余元素集合中移除当前元素，已处理元素集合不变
        listSubsetsRec(remaining - elem, used);
    }
}

// 封装函数，用于调用递归函数列出集合的所有子集
// remaining：表示要处理的元素集合
void listSubsets(const Set<char>& remaining)
{
    // 调用递归函数，初始时已处理元素集合为空
    listSubsetsRec(remaining,{});
}

// 主函数，程序的入口点
int main() 
{
    // 定义一个字符集合，并初始化元素
    Set<char> remaining = {'A', 'H', 'I'};
    // 调用封装函数列出集合的所有子集
    listSubsets(remaining);
    // 程序正常结束，返回0
    return 0;
}
