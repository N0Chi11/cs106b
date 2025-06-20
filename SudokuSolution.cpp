/*
 * File: SudokuSolution.cpp
 * -----------------------
 * This program reads a 9x9 Sudoku grid from a file and gives a
 * complete leagal layout.
 */

// 引入输入输出流库，用于文件和标准输入输出操作
#include <iostream>
// 引入文件流库，用于文件的读写操作
#include <fstream>
// 引入字符串库，用于处理字符串
#include <string>
// 引入错误处理库，用于抛出和处理错误
#include "error.h"
// 引入文件操作库，提供文件相关的辅助函数
#include "filelib.h"
// 引入网格库，用于处理二维网格数据
#include "grid.h"
// 引入映射库，提供键值对的映射功能
#include "map.h"
// 引入集合库，用于处理集合数据
#include "set.h"
// 引入控制台库，提供控制台相关的操作
#include "console.h"
// 引入简单输入输出库，提供简单的输入输出函数
#include "simpio.h"
// 引入Windows系统相关的库，用于Windows系统特定的功能
#include "windows.h"

// 使用标准命名空间，避免每次使用标准库的类和函数时都要写std::
using namespace std;

// 定义一个结构体DigitsSets，用于存储每行、每列和每个3x3子网格中已经使用的数字集合
struct DigitsSets
{
    // 存储每行已经使用的数字集合，共9行
    Set<int> DigitsRowSet[9];
    // 存储每列已经使用的数字集合，共9列
    Set<int> DigitsColumnSet[9];
    // 存储每个3x3子网格已经使用的数字集合，共9个3x3子网格
    Set<int> DigitsBoxSet[9];
};

/* Constant Variables */

// 定义一个常量集合completeDigitsSet，包含1到9的所有数字
static const Set<int> completeDigitsSet = {1,2,3,4,5,6,7,8,9};

/* Function prototypes */

// 从输入流中读取数独网格数据到二维网格对象中
void readSudokuGrid(istream & infile, Grid<int> & grid);
// 统计数独网格中的空单元格，并记录每行、每列和每个3x3子网格中已经使用的数字
void countEmptyCells(const Grid<int>& gridSudoku, Vector<int>& emptyCells, DigitsSets& usedDigitsSets);
// 尝试解决数独问题，如果能解决则返回true，否则返回false
bool canSolveSudoku(Grid<int>& gridSudoku, Vector<int>& emptyCells, DigitsSets& usedDigitsSets);
// 显示数独网格，包括标题和网格内容
void displaySudokuGrid(string title, const Grid<int>& gridSudoku);

/* Main program */

// 主函数，程序的入口点
int main()
{
    // 无限循环，直到用户输入空文件名退出程序
    while(1)
    {
        // 定义一个输入文件流对象，用于打开和读取文件
        ifstream infile;

        // 提示用户输入数独网格文件的名称，并读取用户输入
        string fileName = getLine("Sudoku grid file: ");

        // 如果用户输入为空文件名
        if (fileName == "")
        {
            // 输出程序终止信息
            cout<<"Program terminated! Bye!"<<endl<<endl;
            // 跳出循环，结束程序
            break;
        }

        // 打开用户指定的文件
        infile.open(fileName.c_str());

        // 如果文件打开成功
        if(!infile.fail())
        {
            // 创建一个9x9的二维网格对象，用于存储数独网格数据
            Grid<int> gridSudoku(9,9);

            // 从文件中读取数独网格数据到二维网格对象中
            readSudokuGrid(infile, gridSudoku);
            // 关闭文件
            infile.close();

            // 显示初始的数独网格布局
            displaySudokuGrid("Initial layout", gridSudoku);

            // 定义一个向量对象，用于存储空单元格的位置
            Vector<int> emptyCells;
            // 定义一个DigitsSets结构体对象，用于存储已经使用的数字集合
            DigitsSets usedDigitsSets;

            // 统计数独网格中的空单元格，并记录已经使用的数字
            countEmptyCells(gridSudoku, emptyCells, usedDigitsSets);

            // 尝试解决数独问题
            if (canSolveSudoku(gridSudoku, emptyCells, usedDigitsSets))
                // 如果能解决，显示完成后的数独网格布局
                displaySudokuGrid("Finished layout", gridSudoku);
            else
                // 如果不能解决，输出错误信息
                cout<<"Something is wrong!"<<endl;
        }
        else
            // 如果文件打开失败，输出错误信息并提示用户重试
            cout<<"file open error! Try again!"<<endl<<endl;
    }
    // 程序正常结束，返回0
    return 0;
}

// 显示数独网格，包括标题和网格内容
void displaySudokuGrid(string title, const Grid<int>& gridSudoku)
{
    // 输出标题，使用横线分隔
    cout<<"---------------- "<<title<<" ---------------------"<<endl;
    // 遍历数独网格的每一行
    for(int i = 0; i<9 ;i++)
    {
        // 定义一个字符串变量，用于存储当前行的数字字符串
        string lineString;
        // 遍历数独网格的每一列
        for(int j = 0; j<9; j++)
            // 将当前单元格的数字转换为字符串，并添加到lineString中，后面加上一个空格
            lineString += integerToString(gridSudoku[i][j]) + " ";
        // 输出当前行的数字字符串
        cout<<lineString<<endl;
    }
    // 输出一个空行，用于分隔不同的网格显示
    cout<<endl;

}

// 统计数独网格中的空单元格，并记录每行、每列和每个3x3子网格中已经使用的数字
void countEmptyCells(const Grid<int>& gridSudoku, Vector<int>& emptyCells, DigitsSets& usedDigitsSets)
{
    // 遍历9个3x3子网格
    for(int i = 0; i<9; i++)
    {
        // 计算当前3x3子网格的起始行
        int boxRowStart = 3 * (i / 3);
        // 计算当前3x3子网格的起始列
        int boxColumnStart = 3 * (i % 3);

        // 遍历数独网格的每一行
        for(int j = 0; j<9; j++)
        {
            // 如果当前单元格有数字
            if (gridSudoku[i][j])
                // 将该数字添加到当前行已经使用的数字集合中
                usedDigitsSets.DigitsRowSet[i].add(gridSudoku[i][j]);

            // 如果当前单元格有数字
            if (gridSudoku[i][j])
                // 将该数字添加到当前列已经使用的数字集合中
                usedDigitsSets.DigitsColumnSet[j].add(gridSudoku[i][j]);

            // 如果当前3x3子网格中的某个单元格有数字
            if (gridSudoku[boxRowStart + j / 3][boxColumnStart + j % 3])
                // 将该数字添加到当前3x3子网格已经使用的数字集合中
                usedDigitsSets.DigitsBoxSet[i].add(gridSudoku[boxRowStart + j / 3][boxColumnStart + j % 3]);

            // 如果当前单元格为空
            if (!gridSudoku[i][j])
                // 将该单元格的位置添加到空单元格向量中
                emptyCells.add(i*9 +j);
        }
    }
}

// 尝试解决数独问题，如果能解决则返回true，否则返回false
bool canSolveSudoku(Grid<int>& gridSudoku, Vector<int>& emptyCells, DigitsSets& usedDigitsSets)
{
    // 如果没有空单元格，说明数独已经解决
    if (emptyCells.isEmpty())
        return true;

    // 获取第一个空单元格的位置编号
    int cellOrder = emptyCells[0];
    // 计算该空单元格所在的行号
    int rowNo = cellOrder/9;
    // 计算该空单元格所在的列号
    int columnNo = cellOrder%9;
    // 计算该空单元格所在的3x3子网格编号
    int boxNo = rowNo/3*3 + columnNo/3;

    // 计算该空单元格可能填入的数字集合，即1到9中除去当前行、当前列和当前3x3子网格已经使用的数字
    Set<int> candidateDigitsSet = completeDigitsSet - (usedDigitsSets.DigitsRowSet[rowNo]
                                    + usedDigitsSets.DigitsColumnSet[columnNo]
                                    + usedDigitsSets.DigitsBoxSet[boxNo]);

    // 遍历可能填入的数字集合
    for(int digit : candidateDigitsSet)
    {
        // 将该数字填入当前空单元格
        gridSudoku[rowNo][columnNo] = digit;
        // 从空单元格向量中移除该单元格
        emptyCells.remove(0);
        // 将该数字添加到当前行已经使用的数字集合中
        usedDigitsSets.DigitsRowSet[rowNo] += digit;
        // 将该数字添加到当前列已经使用的数字集合中
        usedDigitsSets.DigitsColumnSet[columnNo] += digit;
        // 将该数字添加到当前3x3子网格已经使用的数字集合中
        usedDigitsSets.DigitsBoxSet[boxNo] += digit;

        // 递归调用canSolveSudoku函数，尝试继续解决数独问题
        if (canSolveSudoku(gridSudoku,emptyCells, usedDigitsSets))
            // 如果能解决，返回true
            return true;
        else
        {
            // 如果不能解决，将该单元格重新添加到空单元格向量中
            emptyCells.insert(0,cellOrder);
            // 从当前行已经使用的数字集合中移除该数字
            usedDigitsSets.DigitsRowSet[rowNo] -= digit;
            // 从当前列已经使用的数字集合中移除该数字
            usedDigitsSets.DigitsColumnSet[columnNo] -= digit;
            // 从当前3x3子网格已经使用的数字集合中移除该数字
            usedDigitsSets.DigitsBoxSet[boxNo] -= digit;
        }
    }

    // 如果所有可能的数字都尝试过了，仍然不能解决，将该单元格置为空
    gridSudoku[rowNo][columnNo] = 0;
    // 返回false，表示不能解决
    return false;

}

// 从输入流中读取数独网格数据到二维网格对象中
void readSudokuGrid(istream& infile, Grid<int>& gridSudoku)
{
    // 遍历数独网格的每一行
    for (int rowNo = 0; rowNo < 9; rowNo++)
    {
        // 定义一个字符串变量，用于存储当前行的输入数据
        string line;
        // 定义列号，初始化为0
        int colNo = 0;

        // 从输入流中读取一行数据到line中
        getline(infile, line);

        // 遍历当前行的每个字符
        for (unsigned int i = 0; i < line.length(); i++)
        {
            // 获取当前字符
            char ch = line[i];
            // 如果当前字符不是空格
            if (ch != ' ')
            {
                // 如果当前字符不是0到9之间的数字
                if (ch < '0' || ch > '9')
                    // 抛出错误信息，表示网格文件中包含非法字符
                    error("Illegal character in grid file");
                // 将当前字符转换为数字，并存储到二维网格对象中
                gridSudoku[rowNo][colNo++] = ch - '0';
            }
        }
    }
}
