/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

// 引入控制台相关的头文件，用于控制台输入输出操作
#include "console.h"
// 引入输入输出辅助函数的头文件，提供方便的输入函数
#include "simpio.h"
// 引入向量容器的头文件，向量是一种动态数组
#include "vector.h"
// 引入词典类的头文件，用于处理单词集合
#include "lexicon.h"

// 使用标准命名空间，这样就可以直接使用标准库中的类和函数
using namespace std;

// 函数声明：判断一个字符串是否为叠词
// 叠词是指由两个相同的子串拼接而成的字符串
bool isTautonyms(const string& word);

// 程序的入口函数，程序从这里开始执行
int main()
{
    // 创建一个词典对象，从 "EnglishWords.txt" 文件中读取英文单词
    Lexicon english("EnglishWords.txt");

    // 遍历词典中的每一个单词
    for(const string& word:english){
        // 调用 isTautonyms 函数判断当前单词是否为叠词
        if(isTautonyms(word))
            // 如果是叠词，则将其输出到控制台
            cout << word << endl;
    }
    // 程序正常结束，返回 0 表示成功
    return 0;
}

// 函数定义：判断一个字符串是否为叠词
bool isTautonyms(const string& word)
{
    // 如果字符串的长度不是偶数，那么它不可能是叠词，直接返回 false
    if(word.size()%2!=0)
        return false;
    // 提取字符串的前半部分
    string frontString = word.substr(0, word.size()/2);
    // 提取字符串的后半部分
    string backString = word.substr(word.size()/2);
    // 比较前后两部分是否相等，如果相等则返回 true，否则返回 false
    return frontString == backString;
}
