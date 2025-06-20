/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

// 引入控制台库，可能是斯坦福cslib中的库，用于控制台交互
#include "console.h"
// 引入简单输入输出库，可能是斯坦福cslib中的库，提供便捷的输入输出函数
#include "simpio.h"
// 引入标准输入输出流库，用于基本的输入输出操作
#include <iostream>
// 引入文件流库，用于文件的读写操作
#include <fstream>
// 使用标准命名空间，这样可以直接使用标准库中的类和函数
using namespace std;

// 声明一个函数，用于对数组进行排序
// 参数：arr - 待排序的整数数组，num - 数组中元素的数量
void sortArray(int arr[], int num);

// 程序的入口函数
int main()
{
    // 打开名为 "rawfile" 的文件以进行读取操作
    ifstream in("rawfile");
    // 检查文件是否成功打开
    if (!in) {
        // 如果文件打开失败，输出错误信息到标准错误流
        cerr << "open file error\n";
        // 返回错误码1，表示程序异常结束
        return 1;
    }

    // 初始化一个变量i，用于数组的索引
    int i = 0;
    // 定义一个包含20个整数的数组
    int myarray[20];

    // 从文件中读取整数，并将其存储到数组中
    // 当文件读取成功时，循环继续
    while (in >> myarray[i++]);
    // 关闭输入文件流
    in.close();

    // 计算数组中实际存储的元素数量
    int arrayElementNumber = i - 1;

    // 调用sortArray函数对数组进行排序
    sortArray(myarray, arrayElementNumber);

    // 打开名为 "outfile" 的文件以进行写入操作
    ofstream out("outfile");

    // 遍历数组，将排序后的元素写入到输出文件中
    for(int j = 0; j < arrayElementNumber; j++){
        // 将数组元素和一个空格写入到输出文件
        out << myarray[j] << " ";
    }

    // 关闭输出文件流
    out.close();
    // 返回0，表示程序正常结束
    return 0;
}

// 定义sortArray函数，使用冒泡排序算法对数组进行排序
void sortArray(int arr[], int num)
{
    // 外层循环控制排序的轮数
    for(int i = 0; i < num - 1; i++){
        // 内层循环控制每一轮比较的次数
        for(int j = 0; j < num - i - 1; j++){
            // 如果当前元素大于下一个元素
            if(arr[j] > arr[j + 1])
                // 交换这两个元素的位置
                swap(arr[j], arr[j + 1]);
        }
    }
}
