/* File: DNA.cpp
 *
 * 一个用于探索DNA链的程序。
 */
#include <iostream>
#include <string>
#include <algorithm> // 用于swap函数
#include "simpio.h"
#include "strlib.h"  // 用于toUpperCase函数
#include "console.h"
using namespace std;

// 判断两个字符是否能配对
bool pairsWith(char one, char two) {
    /* 小技巧：对字符进行排序，使one <= two。
     * 这样我们只需要检查两种可能的配对情况。
     */
    if (one >= two) swap(one, two);

    // 如果是A和T配对或者C和G配对，则返回true
    return (one == 'A' && two == 'T') ||
           (one == 'C' && two == 'G');
}

/* 给定两条DNA链，判断它们是否互补 */
bool areComplementary(string one, string two) {
    /* 基本情况1：如果两条字符串都为空，那么它们是互补的 */
    if (one == "" && two == "") {
        return true;
    }
    /* 基本情况2：如果恰好有一条字符串为空而另一条不为空，那么它们不是互补的
     *
     * 思考问题：为什么这个只说“至少有一条字符串为空”的语句意味着“恰好有一条字符串为空”？
     */
    else if (one == "" || two == "") {
        return false;
    }
    /* 基本情况3：如果第一个字符不能配对，那么这两条字符串不是互补的 */
    else if (!pairsWith(one[0], two[0])) {
        return false;
    }
    /* 递归情况：第一个字符匹配，那么如果剩余的字符也互补，这两条字符串就是互补的 */
    else {
        return areComplementary(one.substr(1), two.substr(1));
    }

    /* 思考问题：如果我们将基本情况3和递归情况一起替换为以下内容会发生什么？
     *
     *     return pairsWith(one[0], two[0]) && areComplementary(one.substr(1), two.substr(1));
     *
     * 或者，这样呢？
     *
     *     return areComplementary(one.substr(1), two.substr(1)) && pairsWith(one[0], two[0]);
     */
}

int main() {
    while (true) {
        // 获取用户输入的第一条DNA链，并转换为大写
        string first  = toUpperCase(getLine("第一条DNA链: "));
        // 获取用户输入的第二条DNA链，并转换为大写
        string second = toUpperCase(getLine("另一条DNA链: "));

        /* 思考问题：你会如何修改上述代码行来验证输入确实只由A、C、G和T组成？ */

        // 判断两条DNA链是否互补
        if (areComplementary(first, second)) {
            cout << "你找到了你的基因灵魂伴侣！" << endl;
        } else {
            cout << "基因库中还有很多选择。" << endl;
        }

        cout << endl;
    }
}
