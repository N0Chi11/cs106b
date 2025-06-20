/*****************************************************
 * File: Main.cpp
 *
 * A program to run simple tests on our custom Queue.
 */
// 包含输入输出流库，用于基本的输入输出操作
#include <iostream>
// 包含标准库，提供一些常用的函数和类型，如内存分配和随机数生成相关的函数
#include <cstdlib>
// 包含时间库，用于获取当前时间，可用于随机数种子的设置
#include <ctime>
// 包含输入输出操作库，用于设置输出格式，如设置字段宽度等
#include <iomanip>
// 包含自定义队列类的头文件，以便使用自定义的队列功能
#include "OurQueue.h"
// 包含自定义的输入输出库，提供更方便的输入输出函数
#include "simpio.h"
// 包含随机数生成库，用于生成随机数
#include "random.h"
// 包含控制台操作库，用于控制台相关的设置和操作
#include "console.h"
// 使用标准命名空间，避免每次使用标准库的函数和对象时都要写 std::
using namespace std;

// 定义一个常量，表示要入队的元素数量
const int kNumElems = 4;

// 主函数，程序的入口点
int main() {
    // 创建一个 OurQueue 类的对象，即自定义的队列实例
    OurQueue queue;

    // 输出提示信息，表示开始将元素入队
    cout << "Enqueuing elements into the queue:" << endl;
    // 循环 kNumElems 次，将随机生成的元素入队
    for (int i = 0; i < kNumElems; i++) {
        // 生成一个 0 到 1000 之间的随机整数
        int value = randomInteger(0, 1000);
        // 输出该随机数，使用 setw(6) 设置输出宽度为 6
        cout << setw(6) << "value=" << value << endl;
        // 将该随机数入队
        queue.enqueue(value);
    }
    // 输出空行，用于分隔入队和出队的输出信息
    cout << endl;

    // 输出提示信息，表示开始将元素出队
    cout << "Dequeuing elements from the queue:" << endl;
    // 当队列不为空时，持续出队元素并输出
    while (!queue.isEmpty()) {
        // 出队一个元素并输出，使用 setw(6) 设置输出宽度为 6
        cout << setw(6) << queue.dequeue() << endl;
    }
    // 输出空行，用于结束出队操作的输出信息
    cout << endl;

    // 主函数正常结束，返回 0 表示程序成功执行
    return 0;
}

// 预处理指令，防止头文件被重复包含
#ifndef OURQUEUE_H
// 定义宏，用于判断头文件是否已经包含
#define OURQUEUE_H
// 定义 OurQueue 类
class OurQueue {
  public:
    // 构造函数，用于初始化队列对象
    OurQueue();
    // 析构函数，用于在对象销毁时释放队列占用的内存
    ~OurQueue();
    // 查看队列头部元素的值，但不出队
    int peek() const;
    // 将一个整数元素入队
    void enqueue(int value);
    // 将队列头部元素出队，并返回该元素的值
    int dequeue();
    // 返回队列中元素的数量
    int size() const;
    // 判断队列是否为空
    bool isEmpty() const;
  private:
    // 定义内部结构体 Cell，用于表示队列中的节点
    struct Cell {
        // 节点存储的整数值
        int value;
        // 指向下一个节点的指针
        Cell* next;
    };
    // 记录队列中元素的数量
    int numofelems;
    // 指向队列头部节点的指针
    Cell* head;
    // 指向队列尾部节点的指针
    Cell* tail;
};
// 结束预处理指令，标志头文件定义结束
#endif // OURQUEUE_H

// 包含自定义队列类的头文件，以便实现类的成员函数
#include "OurQueue.h"
// 包含输入输出流库，用于输出错误信息
#include <iostream>
// 使用标准命名空间，避免每次使用标准库的函数和对象时都要写 std::
using namespace std;

// 构造函数的实现
OurQueue::OurQueue()
{
    // 初始化队列的头部和尾部指针为空，表示队列为空
    head = tail = nullptr;
    // 初始化队列中元素的数量为 0
    numofelems = 0;
}

// 析构函数的实现
OurQueue::~OurQueue()
{
    // 当队列头部指针不为空时，持续释放节点内存
    while(head)
    {
        // 保存下一个节点的指针
        Cell *next = head->next;
        // 释放当前头部节点的内存
        delete head;
        // 将头部指针指向下一个节点
        head = next;
    }
}

// 实现 size 函数，返回队列中元素的数量
int OurQueue::size() const
{
    return numofelems;
}

// 实现 isEmpty 函数，判断队列是否为空
bool OurQueue::isEmpty() const
{
    // 如果头部指针为空，则队列为空
    return !head;
}

// 实现 dequeue 函数，将队列头部元素出队
int OurQueue::dequeue()
{
    // 检查队列是否为空
    if(isEmpty())
    {
        // 若为空，输出错误信息
        cout << "The queue is empty!" << endl;
        // 返回最小整数值表示错误
        return INT_MIN;
    }
    else
    {
        // 保存下一个节点的指针
        Cell* next = head->next;
        // 保存当前头部节点的值
        int result = head->value;
        // 释放当前头部节点的内存
        delete head;
        // 将头部指针指向下一个节点
        head = next;
        // 若出队后队列为空，将尾部指针置为空
        if(isEmpty())
            tail = nullptr;
        // 队列元素数量减 1
        numofelems--;
        // 返回出队元素的值
        return result;
    }

}

// 实现 enqueue 函数，将一个元素入队
void OurQueue::enqueue(int value)
{
    // 创建一个新的节点
    Cell* newcell = new Cell;
    // 将传入的值赋给新节点
    newcell->value = value;
    // 将新节点的下一个指针置为空
    newcell->next = nullptr;

    // 检查队列是否为空
    if(isEmpty())
        // 若为空，将头部和尾部指针都指向新节点
        head = tail = newcell;
    else
    {
        // 若不为空，将尾部节点的下一个指针指向新节点
        tail->next = newcell;
        // 将尾部指针指向新节点
        tail = newcell;
    }
    // 队列元素数量加 1
    numofelems++;
}

// 实现 peek 函数，查看队列头部元素的值
int OurQueue::peek() const
{
    // 检查队列是否为空
    if(!isEmpty())
        // 若不为空，返回头部节点的值
        return head->value;
    else
    {
        // 若为空，输出错误信息
        cout << "The queue is empty!" << endl;
        // 返回最小整数值表示错误
        return INT_MIN;
    }
}
