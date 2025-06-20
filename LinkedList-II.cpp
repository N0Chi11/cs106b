/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

// 引入控制台库，用于控制台输入输出
#include "console.h"
// 引入简单输入输出库，提供 getLine 等函数
#include "simpio.h"
// 使用标准命名空间
using namespace std;

// 定义一个结构体 Cell，用于表示链表的节点
struct Cell {
    // 节点存储的值，类型为 string
    string value;
    // 指向下一个节点的指针
    Cell* next;
};

// 主函数，程序的入口点
int main()
{
/*
    // 创建一个新的 Cell 节点，并将其地址赋给 list 指针
    Cell* list = new Cell;
    // 给节点的 value 成员赋值为 90，这里会有类型不匹配的问题，因为 value 是 string 类型
    list->value = 90;
    // 为当前节点的 next 指针分配一个新的 Cell 节点
    list->next = new Cell;
    // 给新节点的 value 成员赋值为 89
    list->next->value = 89;
    // 为新节点的 next 指针分配一个新的 Cell 节点
    list->next->next = new Cell;
    // 给新节点的 value 成员赋值为 100
    list->next->next->value = 100;
    // 将最后一个节点的 next 指针置为 nullptr，表示链表结束
    list->next->next->next = nullptr;

    // 初始化变量 sum 用于存储链表节点值的总和，初始值为 0
    int sum = 0, 
    // 初始化变量 counter 用于记录链表节点的数量，初始值为 0
    counter = 0;
    // 使用 for 循环遍历链表
    for(Cell* curr = list; curr!=nullptr; curr = curr->next)
    {
        // 将当前节点的值累加到 sum 中
        sum += curr->value;
        // 节点数量加 1
        counter++;
    }
    // 输出链表节点值的总和以及平均值
    cout << "Sum = " << sum << "  Average = "<< float(sum)/counter << endl;
*/

    // 初始化链表头指针为 nullptr，表示链表为空
    Cell* list = nullptr;
    // 初始化链表尾指针为 nullptr，表示链表为空
    Cell* tail = nullptr;
/*
    // 提示用户输入下一个条目，并将用户输入的内容存储在 line 变量中
    string line = getLine("Next entry? ");
    // 如果用户输入不为空
    if (line != "")
    {
        // 创建一个新的 Cell 节点
        Cell* cell = new Cell;
        // 将用户输入的内容赋值给新节点的 value 成员
        cell->value = line;
        // 将新节点的 next 指针置为 nullptr
        cell->next = nullptr;
        // 让链表头指针和尾指针都指向新节点
        list = tail = cell;
    }
*/
    // 进入一个无限循环，用于持续接收用户输入
    while (true) {
        // 提示用户输入下一个条目，并将用户输入的内容存储在 line 变量中
        string line = getLine("Next entry? ");
        // 如果用户输入为空，跳出循环
        if (line == "") break;
        // 创建一个新的 Cell 节点
        Cell* cell = new Cell;
        // 将用户输入的内容赋值给新节点的 value 成员
        cell->value = line;
        // 将新节点的 next 指针置为 nullptr
        cell->next = nullptr;
        // 如果链表为空
        if(!list)
            // 让链表头指针和尾指针都指向新节点
            list = tail = cell;
        else{
            // 将尾节点的 next 指针指向新节点
            tail->next = cell;
            // 更新尾指针为新节点
            tail = cell;
        }
    }

    // 输出提示信息，准备输出链表内容
    cout << endl << "Output the list:"<< endl;
    // 使用 for 循环遍历链表
    for(Cell *curr = list; curr!=nullptr; curr = curr->next)
        // 输出当前节点的值
        cout << curr->value << endl;

    // 循环释放链表中的所有节点
    while(list)
    {
        // 保存当前节点的下一个节点的地址
        Cell* NEXT = list->next;
        // 释放当前节点的内存
        delete list;
        // 将头指针更新为下一个节点
        list = NEXT;
    }

    // 程序正常结束，返回 0
    return 0;
}
