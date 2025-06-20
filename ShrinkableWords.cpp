/* File: ShrinkableWords.cpp
 *
 * Code to find all the shrinkable words in English!
 */
// 引入输入输出流库，用于输入输出操作
#include <iostream>
// 引入字符串库，用于处理字符串
#include <string>
// 引入自定义的Lexicon库，用于管理单词词典
#include "lexicon.h"
// 引入自定义的Vector库，用于管理动态数组
#include "vector.h"
// 引入自定义的console库，可能用于控制台相关操作
#include "console.h"
// 使用标准命名空间，避免每次使用标准库的类和函数时都要加std::前缀
using namespace std;

// 定义一个递归函数，用于判断一个单词是否是可收缩的
// word: 待判断的单词
// english: 英语单词词典
// vs: 用于存储收缩过程中经过的所有单词的向量
bool isShrinkable(const string& word, const Lexicon& english, Vector<string>& vs) {
    // 如果当前单词不在词典中，说明它不是有效的英语单词，返回false
    if (!english.contains(word)) return false;
    // 如果当前单词长度为1，说明已经收缩到了最小，将其添加到向量中并返回true
    if (word.length() == 1) {
        vs += word;
        return true;
    }

    // 遍历当前单词的每个字符
    for (int i = 0; i < word.length(); i++) {
        // 构造一个新的单词，该单词是原单词去掉第i个字符后的结果
        string shrunken = word.substr(0, i) + word.substr(i + 1);
        // 递归调用isShrinkable函数，判断新单词是否可收缩
        if (isShrinkable(shrunken, english, vs))
        {
            // 如果新单词可收缩，将当前单词添加到向量中
            vs += word;
            // 返回true，表示当前单词可收缩
            return true;
        }
    }
    // 如果遍历完所有可能的收缩情况都没有找到可收缩的路径，返回false
    return false;
}

// 程序的主函数，程序的入口点
int main() {
    // 创建一个Lexicon对象，从文件EnglishWords.txt中读取英语单词词典
    Lexicon english("EnglishWords.txt");

    // 遍历词典中的每个单词
    for (string word: english) {
        // 创建一个空的Vector对象，用于存储收缩过程中的单词
        Vector<string> vs={};
        // 只处理长度大于等于9的单词，并且判断该单词是否可收缩
        if (word.length() >= 9 && isShrinkable(word, english, vs)) {
            // 从向量的最后一个元素开始，逆序输出收缩过程中的所有单词
            for(int i = vs.size() - 1; i >= 0;  i--)
                cout << vs[i] << " ";
            // 输出完一个单词的收缩过程后换行
            cout << endl;
        }
    }

    // 程序正常结束，返回0
    return 0;
}
