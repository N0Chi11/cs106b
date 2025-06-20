/* File: Crosswords.cpp
 *
 * A program to generate dense crosswords.
 */
// 引入输入输出流库，用于处理标准输入输出
#include <iostream>
// 引入字符串库，用于处理字符串类型的数据
#include <string>
// 引入自定义的词典类，用于存储和操作单词集合
#include "lexicon.h"
// 引入自定义的网格类，用于表示和操作二维网格
#include "grid.h"
// 引入自定义的控制台类，用于控制台相关的操作
#include "console.h"
// 使用标准命名空间，避免每次使用标准库中的类和函数时都要加std::前缀
using namespace std;

/**
 * Given a grid and a column, extracts the word at that column up to a certain
 * number of characters.
 *
 * @param grid The grid in question.
 * @param col Which column to extract
 * @param numRows How many rows to read
 * @return The contents of that column.
 */
// 函数定义，用于提取网格中指定列的前numRows个字符组成的字符串
string contentsOfColumn(const Grid<char>& grid, int col, int numRows) {
    // 定义一个空字符串，用于存储提取的字符
    string result;
    // 循环遍历指定列的前numRows行
    for (int row = 0; row < numRows; row++) {
        // 将当前行和指定列的字符添加到结果字符串中
        result += grid[row][col];
    }
    // 返回提取的字符串
    return result;
}

/**
 * Given a grid, reports whether every column is a prefix of some legal
 * English word.
 *
 * @param grid The grid in question.
 * @param colWords A collection of all words that can fit in a column.
 * @param maxRow The maximum row to descend down to.
 * @return Whether all columns are feasible prefixes of real words.
 */
// 函数定义，用于检查网格中每一列的前maxRow个字符是否是合法英文单词的前缀
bool areColumnsFeasible(const Grid<char>& grid, int maxRow, const Lexicon& colWords) {
    // 遍历网格的每一列
    for (int col = 0; col < grid.numCols(); col++) {
        // 调用contentsOfColumn函数提取当前列的前maxRow个字符组成的字符串
        string prefix = contentsOfColumn(grid, col, maxRow);
        // 检查提取的字符串是否不是任何合法英文单词的前缀
        if (!colWords.containsPrefix(prefix)) return false;
    }
    // 如果所有列的前缀都是合法英文单词的前缀，返回true
    return true;
}

/**
 * Prints a crossword to the console.
 *
 * @param crossword The crossword in question.
 */
// 函数定义，用于将一个网格形式的填字游戏打印到控制台
void printCrossword(const Grid<char>& crossword) {
    // 遍历网格的每一行
    for (int row = 0; row < crossword.numRows(); row++) {
        // 遍历当前行的每一列
        for (int col = 0; col < crossword.numCols(); col++) {
            // 输出当前行和列的字符
            cout << crossword[row][col];
        }
        // 每一行输出完后换行
        cout << endl;
    }
}

/**
 * Returns whether it's possible to extend a partial crossword into a full one.
 * If so, the crossword is updated to contain the solution.
 *
 * @param crossword The partial crossword.
 * @param nextRow The next row that needs to be filled in.
 * @param rowWords All words that can fit in the rows.
 * @param colWords All words that can fit in the columns.
 * @return Whether the crossword can be extended.
 */
// 递归函数定义，用于尝试将一个部分填好的填字游戏扩展为完整的填字游戏
bool canMakeCrosswordRec(Grid<char>& crossword,
                         int nextRow,
                         const Lexicon& rowWords,
                         const Lexicon& colWords) {
    /* Base case: If any of the columns cannot be extended into a word, stop searching. */
    // 基本情况：如果当前网格的列无法扩展成合法英文单词，停止搜索
    if (!areColumnsFeasible(crossword, nextRow, colWords)) return false;

    /* Base case: If we've finished all the rows, we're done! */
    // 基本情况：如果已经填满了所有行，说明找到了一个完整的填字游戏
    if (nextRow == crossword.numRows()) return true;

    /* Otherwise, try placing each word down here. */
    // 否则，尝试将每一个适合行的单词填入当前行
    for (string word: rowWords) {
        /* Copy the word in. */
        // 将当前单词的每个字符依次填入当前行的每一列
        for (int i = 0; i < crossword.numCols(); i++) {
            crossword[nextRow][i] = word[i];
        }

        /* See if this works! */
        // 递归调用canMakeCrosswordRec函数，尝试填充下一行
        if (canMakeCrosswordRec(crossword, nextRow + 1, rowWords, colWords)) return true;
    }

    // 如果所有单词都尝试过了，仍然无法扩展成完整的填字游戏，返回false
    return false;
}

/**
 * Returns whether the crossword grid can be filled in so that each row and
 * column are words.
 *
 * @param crossword The partial crossword.
 * @param english All English words.
 */
// 函数定义，用于判断一个部分填好的填字游戏是否可以被填满，使得每一行和每一列都是合法英文单词
bool canMakeCrossword(Grid<char>& crossword, const Lexicon& english) {
    /* Split the Lexicon into two smaller lexicons, one for words that can appear
     * in rows, and one for words that can appear in columns.
     */
    // 定义两个词典，分别存储适合行和列的单词
    Lexicon rowWords, colWords;
    // 遍历所有英文单词
    for (string word: english) {
        // 如果单词的长度等于网格的列数，将其添加到行单词词典中
        if (word.length() == crossword.numCols()) rowWords += word;

        /* No else here - the grid could be a square! */
        // 如果单词的长度等于网格的行数，将其添加到列单词词典中
        if (word.length() == crossword.numRows()) colWords += word;
    }

    // 调用递归函数尝试填充填字游戏，并返回结果
    return canMakeCrosswordRec(crossword, 0, rowWords, colWords);
}

// 程序的主函数，程序的入口点
int main() {
    // 从文件中读取所有英文单词，存储在english词典中
    Lexicon english("EnglishWords.txt");
	
    /* The dimensions here are arbitrary but give rise to some pretty cool words! */
    // 创建一个4行7列的字符网格，用于表示填字游戏
    Grid<char> crossword(4, 7);

    // 输出提示信息，表示程序开始运行
    cout << "Starting..." << endl;

    // 调用canMakeCrossword函数尝试填充填字游戏
    if (canMakeCrossword(crossword, english)) {
        // 如果成功填充，打印填字游戏
        printCrossword(crossword);
	} else {
        // 如果无法填充，输出提示信息
		cout << "No solution found." << endl;
	}
    // 程序正常结束，返回0
    return 0;
}
