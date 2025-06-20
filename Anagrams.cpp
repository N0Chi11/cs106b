/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

// 引入控制台相关的头文件，用于在控制台进行输入输出操作
#include "console.h"
// 引入简单输入输出操作的头文件，例如获取用户输入的字符串
#include "simpio.h"
// 引入向量容器的头文件，向量是一种动态数组
#include "vector.h"
// 引入词典类的头文件，用于加载和操作词典
#include "lexicon.h"
// 引入映射类的头文件，映射是一种键值对容器
#include "map.h"

// 使用标准命名空间，这样可以直接使用标准库中的类和函数
using namespace std;

// 声明一个函数，用于获取一个字符串的按字母排序后的形式
string getSortedOrderString(const string& word);

// 主函数，程序的入口点
int main()
{
    // 创建一个词典对象，加载英文单词文件 "EnglishWords.txt"
    Lexicon english("EnglishWords.txt");

    // 创建一个映射对象，键是按字母排序后的字符串，值是一个词典，存储具有相同排序字符串的单词
    Map<string, Lexicon> wordsBySortedOrderString;
    // 遍历英文词典中的每个单词
    for(const string& word:english){
        // 获取当前单词的按字母排序后的字符串
        // 并将该单词添加到对应排序字符串的词典中
        wordsBySortedOrderString[getSortedOrderString(word)].add(word);
    }

    // 提示用户输入一个单词，并获取用户输入的字符串
    string word = getLine("Please input your word:");
    // 根据用户输入的单词的排序字符串，从映射中找到对应的词典，并输出该词典
    cout << wordsBySortedOrderString[getSortedOrderString(word)] << endl;
    // 程序正常结束，返回 0
    return 0;
}

// 定义函数，用于获取一个字符串的按字母排序后的形式
string getSortedOrderString(const string& word)
{
    // 创建一个映射对象，键是字符，值是该字符在字符串中出现的频率
    Map<char,int> letterFreq;
    // 遍历输入字符串中的每个字符
    for(char ch:word)
        // 统计每个字符的出现频率
        letterFreq[ch]++;

    // 用于存储排序后的字符串
    string result;
    // 遍历映射中的每个字符（按字符顺序）
    for(char ch:letterFreq)
    {
        // 根据字符的出现频率，将字符添加到结果字符串中
        for(int i=0; i<letterFreq[ch]; i++)
            result+= ch;
    }
    // 返回排序后的字符串
    return result;
}
