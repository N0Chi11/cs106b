/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

// 引入控制台相关的头文件，用于控制台的输入输出等操作
#include "console.h"
// 引入简单输入输出操作的头文件，例如获取用户输入的行
#include "simpio.h"
// 引入栈数据结构的头文件，栈是一种后进先出（LIFO）的数据结构
#include "stack.h"
// 使用标准命名空间，这样可以直接使用标准库中的类和函数，无需加 std:: 前缀
using namespace std;

// 函数声明：判断一个字符串中的括号是否平衡
bool isBalancedParenthesisString(const string& str);
// 函数声明：判断一个字符是否为左括号
bool isOpenParenthesis(char c);
// 函数声明：判断一个字符是否为右括号
bool isCloseParenthesis(char c);
// 函数声明：判断一个左括号和一个右括号是否匹配
bool isParenthesisMatch(char open, char close);

// 主函数，程序的入口点
int main()
{
    // 注释掉的代码：提示用户输入一个括号不匹配的字符串
    //string unmatchedstring = getLine("Input the unmatched string:");
    // 定义一个测试用的字符串，包含不匹配的括号
    string unmatchedstring = "{{]";

    // 输出布尔值时，使用文字形式（true 或 false）而非 1 或 0
    cout << boolalpha << isBalancedParenthesisString(unmatchedstring) << endl;

    // 程序正常结束，返回 0
    return 0;
}

// 函数定义：判断一个字符串中的括号是否平衡
bool isBalancedParenthesisString(const string& str)
{
    // 创建一个字符类型的栈，用于存储左括号
    Stack<char> myParenthesisStack;
    // 遍历字符串中的每个字符
    for(char c : str)
    {
        // 如果当前字符是左括号
        if(isOpenParenthesis(c))
            // 将左括号压入栈中
            myParenthesisStack.push(c);
        else
            // 如果当前字符是右括号
            if(isCloseParenthesis(c))
            {
                // 如果栈为空，说明没有对应的左括号，返回 false
                if(myParenthesisStack.isEmpty())
                    return false;
                // 弹出栈顶的左括号
                char openParenthesis = myParenthesisStack.pop();
                // 如果弹出的左括号和当前右括号不匹配，返回 false
                if(!isParenthesisMatch(openParenthesis,c))
                    return false;
            }
    }

    // 如果遍历完字符串后栈为空，说明所有括号都匹配，返回 true；否则返回 false
    return myParenthesisStack.isEmpty();

}

// 函数定义：判断一个字符是否为左括号
bool isOpenParenthesis(char c)
{
    // 如果字符是 (、{ 或 [，返回 true；否则返回 false
    return c=='('||c=='{'||c=='[';
}

// 函数定义：判断一个字符是否为右括号
bool isCloseParenthesis(char c)
{
    // 如果字符是 )、} 或 ]，返回 true；否则返回 false
    return c==')'||c=='}'||c==']';
}

// 函数定义：判断一个左括号和一个右括号是否匹配
bool isParenthesisMatch(char open, char close)
{
    // 如果左括号是 ( 且右括号是 )，或者左括号是 { 且右括号是 }，或者左括号是 [ 且右括号是 ]，返回 true；否则返回 false
    return open=='('&&close==')'||
           open=='{'&&close=='}'||
           open=='['&&close==']';
}
