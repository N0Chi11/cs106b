#include "OurStack.h"
// 引入错误处理相关的头文件
#include "error.h" 
// 引入输入输出流库
#include <iostream> 
// 使用标准命名空间
using namespace std; 

/* Constant controlling the default size of our stack. */
// 定义栈的初始容量常量
const int kInitialSize = 4; 

// 构造函数，用于初始化栈对象
OurStack::OurStack() {
  // 逻辑大小初始化为 0，表示栈中没有元素
  logicalSize = 0; 
  // 分配的内存大小初始化为初始容量
  allocatedSize = kInitialSize; 
  // 动态分配一个大小为 allocatedSize 的整数数组
  elems = new int[allocatedSize]; 
}

// 析构函数，用于释放栈对象占用的内存
OurStack::~OurStack() {
  // 释放动态分配的数组内存
  delete[] elems; 
}

// 向栈中压入一个元素
void OurStack::push(int value) {
  // 如果逻辑大小等于分配的内存大小，说明栈已满，需要扩容
  if(logicalSize==allocatedSize)
     // 调用扩容函数
     grow(); 
  // 将元素存入栈顶位置，并将逻辑大小加 1
  elems[logicalSize++] = value; 
}

// 查看栈顶元素，但不弹出
int OurStack::peek() const {
  // 如果栈为空
  if(isEmpty())
      // 输出错误信息
      cout << "error" << endl; 
  else
      // 返回栈顶元素
      return elems[logicalSize-1]; 
  // 如果栈为空，返回 INT_MIN 表示错误
  return INT_MIN; 
}

// 从栈中弹出一个元素
int OurStack::pop() {
   // 调用 peek 函数获取栈顶元素
   int result = peek(); 
   // 如果 peek 返回 INT_MIN，说明栈为空
   if(result == INT_MIN)
       // 输出栈为空的信息
       cout << "Stack is empty!" << endl; 
   else
       // 逻辑大小减 1，表示弹出一个元素
       logicalSize--; 
   // 返回栈顶元素
   return result; 
}

// 获取栈中元素的数量
int OurStack::size() const {
    // 返回逻辑大小
    return logicalSize; 
}

// 判断栈是否为空
bool OurStack::isEmpty() const {
    // 如果栈中元素数量为 0，则栈为空
    return size() == 0; 
}

// 扩容函数，当栈满时调用
void OurStack::grow()
{
    // 将分配的内存大小扩大为原来的 2 倍
    allocatedSize*=2; 
    // 动态分配一个新的数组，大小为扩大后的内存大小
    int* newelems = new int[allocatedSize]; 
    // 将原数组中的元素复制到新数组中
    for(int i=0; i<size(); i++)
        newelems[i] = elems[i]; 
    // 释放原数组的内存
    delete[] elems; 
    // 将新数组的指针赋值给 elems
    elems = newelems; 
}

/*****************************************************
 * File: SimpleTest.cpp
 *
 * A program to run simple tests on our custom Stack.
 *****************************************************/
// 引入输入输出流库
#include <iostream> 
// 引入自定义栈的头文件
#include "OurStack.h" 
// 引入简单输入输出相关的头文件
#include "simpio.h" 
// 引入随机数生成相关的头文件
#include "random.h" 
// 引入控制台相关的头文件
#include "console.h" 
// 使用标准命名空间
using namespace std; 

// 定义要测试的元素数量常量
const int kNumElems = 9; 

// 主函数，程序的入口点
int main() {
    // 创建一个 OurStack 类的对象
	OurStack stack; 
	
	/* Load the stack with random values. */
    // 输出提示信息，表示开始向栈中压入元素
    cout << "Pushing values onto the stack:" << endl;
    // 循环 kNumElems 次，向栈中压入随机元素
	for (int i = 0; i < kNumElems; i++) {
      // 生成一个 0 到 1000 之间的随机整数
      int value = randomInteger(0, 1000);
      // 输出随机生成的元素
      cout << "  " << value << endl;
      // 将随机元素压入栈中
      stack.push(value);
	}

    // 输出提示信息，表示开始从栈中弹出元素
    cout << "Popping values from the stack: " << endl;
	
	/* See what those values are. */
    // 当栈不为空时，循环弹出元素
	while (!stack.isEmpty()) {
      // 输出弹出的元素
      cout << "  " << stack.pop() << endl;
	}
	
	// 程序正常结束，返回 0
	return 0;
}

/*********************************************************
 * File: OurStack.h
 *
 * A class representing a stack that holds integers.
 */
// 头文件保护宏，防止头文件被重复包含
#ifndef OurStack_Included
// 定义头文件保护宏
#define OurStack_Included

// 定义一个名为OurStack的类，用于表示一个存储整数的栈
class OurStack {
public:
    // 类的构造函数，用于初始化对象
    OurStack();
    // 类的析构函数，用于在对象销毁时释放资源
    ~OurStack();

    // 向栈中压入一个整数值的成员函数
    void push(int value);
    // 从栈中弹出并返回栈顶元素的成员函数
    int  pop();
    // 查看栈顶元素的值但不弹出该元素的成员函数，使用const修饰表示该函数不会修改对象的状态
    int  peek() const;

    // 返回栈中元素数量的成员函数，使用const修饰表示该函数不会修改对象的状态
    int size() const;
    // 判断栈是否为空的成员函数，使用const修饰表示该函数不会修改对象的状态
    bool isEmpty() const;

private:
    // 用于扩展栈容量的私有成员函数
    void grow();
    // 指向存储栈元素的动态数组的指针
    int* elems;
    // 栈当前分配的数组大小
    int  allocatedSize;
    // 栈中实际存储的元素数量
    int  logicalSize;
};

// 结束头文件保护宏的定义
#endif
