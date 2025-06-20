/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

// 引入控制台库，用于在控制台进行输入输出操作
#include "console.h"
// 引入简易输入输出库，提供一些方便的输入输出函数
#include "simpio.h"
// 引入向量库，向量是一种动态数组，可方便地存储和操作数据
#include "vector.h"
// 使用标准命名空间，避免在使用标准库中的类和函数时需要加上std::前缀
using namespace std;

// 声明一个函数bestCoverageFor，该函数接受一个常量引用类型的Vector<int>对象作为参数，返回一个整数
int  bestCoverageFor(const Vector<int>& cities);

// 主函数，程序的入口点
int main()
{
    // 定义一个Vector<int>对象cities，并初始化为包含7个整数的向量
    Vector<int> cities ={137, 106, 107, 166, 103, 261, 109};
    // 调用bestCoverageFor函数，传入cities向量，计算最大覆盖值，并将结果存储在变量number中
    int number = bestCoverageFor(cities);
    // 将计算得到的最大覆盖值输出到控制台
    cout << number << endl;
    // 主函数正常结束，返回0表示程序成功执行
    return 0;
}

// 定义bestCoverageFor函数，用于计算给定城市向量的最大覆盖值
int  bestCoverageFor(const Vector<int>& cities)
{
    // 判断向量cities是否为空
    if(cities.isEmpty())
        // 如果向量为空，最大覆盖值为0，直接返回0
        return 0;
    else
        // 判断向量cities的大小是否为1
        if(cities.size()==1)
            // 如果向量只有一个元素，最大覆盖值就是该元素的值，返回该元素
            return cities[0];
        else
        {
            // 选项1：不包含第一个塔
            // 递归调用bestCoverageFor函数，传入除去第一个元素后的子向量，计算不包含第一个塔时的最大覆盖值
            int excludeFirstTower = bestCoverageFor(cities.subList(1, cities.size() - 1));

            // 选项2：包含第一个塔
            // 递归调用bestCoverageFor函数，传入除去前两个元素后的子向量，计算包含第一个塔时的最大覆盖值
            // 包含第一个塔时的最大覆盖值等于第一个塔的值加上除去前两个元素后的子向量的最大覆盖值
            int includeFirstTower = cities[0] +
                                    bestCoverageFor(cities.subList(2, cities.size() - 2));

            // 比较不包含第一个塔和包含第一个塔时的最大覆盖值，返回较大的值
            return (excludeFirstTower>includeFirstTower)?excludeFirstTower:includeFirstTower;
        }
}
