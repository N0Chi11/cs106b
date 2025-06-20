#include "set.h"
#include "vector.h"
#include "map.h"
#include "lexicon.h"
#include "error.h"
#include <iostream>
#include <string>
using namespace std;

/* ============== 容器相关问题 ============== */

/* 问题一：谁在格林图书馆里面 */
Set<int> peopleInsideGreen(const Vector<int>& idScans) {
    Set<int> insiders; // 存储当前在图书馆内的人员ID集合
    
    // 遍历所有刷卡记录，切换人员的进出状态
    for (int id : idScans) {
        if (insiders.contains(id)) {
            insiders -= id; // 如果ID在集合中，说明人员离开，从集合移除
        } else {
            insiders += id; // 如果ID不在集合中，说明人员进入，添加到集合
        }
    }
    
    return insiders; // 返回当前在馆内的人员集合
}

/* 问题二：判断两人是否在同一家公司 */
string ceoOf(string person, const Map<string, string>& bosses) {
    // 循环查找直至找到公司CEO（不在bosses映射中的人）
    while (bosses.containsKey(person)) {
        person = bosses[person]; // 更新为当前人的上级
    }
    return person; // 返回公司CEO
}

bool areAtSameCompany(const string& p1, const string& p2, const Map<string, string>& bosses) {
    // 判断两人的CEO是否相同
    return ceoOf(p1, bosses) == ceoOf(p2, bosses);
}

/* 问题三：寻找包含最多子单词的单词 */
string mostXzibitWord(const Lexicon& words) {
    string result; // 记录当前找到的最佳单词
    int numSubwords = 0; // 记录最佳单词包含的子单词数量
    
    // 遍历词典中的每个单词
    for (string word : words) {
        Lexicon ourSubwords; // 存储找到的子单词，避免重复计数
        
        // 考虑所有可能的子串起始位置
        for (int start = 0; start < word.length(); start++) {
            // 考虑所有可能的子串结束位置
            for (int stop = start; stop <= word.length(); stop++) {
                string candidate = word.substr(start, stop - start); // 获取当前子串
                
                // 优化：如果子串不是任何合法单词的前缀，跳过后续扩展
                if (!words.containsPrefix(candidate)) break;
                
                // 如果子串是单词，添加到子单词集合
                if (words.contains(candidate)) {
                    ourSubwords.add(candidate);
                }
            }
        }
        
        // 更新最佳单词和子单词数量
        if (numSubwords < ourSubwords.size()) {
            result = word;
            numSubwords = ourSubwords.size();
        }
    }
    
    return result; // 返回包含最多子单词的单词
}

/* 问题四：计算社交网络的k-核心（方法一） */
Set<string> allPeopleIn(const Map<string, Set<string>>& network) {
    Set<string> result; // 存储网络中所有人员
    for (string person : network) {
        result += person; // 添加每个人到集合
    }
    return result;
}

Set<string> kCoreOf(const Map<string, Set<string>>& network, int k) {
    auto core = allPeopleIn(network); // 初始核心为所有人员
    
    // 循环查找并移除朋友数少于k的人
    while (true) {
        string lonelyPerson; // 记录孤独的人（朋友数不足k）
        bool isLonelyPerson = false; // 标记是否找到孤独的人
        
        // 遍历核心中的每个人
        for (string person : core) {
            // 计算与核心中朋友的数量
            if ((network[person] * core).size() < k) {
                lonelyPerson = person; // 记录孤独的人
                isLonelyPerson = true; // 标记找到
                break;
            }
        }
        
        if (!isLonelyPerson) break; // 没有找到则结束循环
        core -= lonelyPerson; // 从核心中移除孤独的人
    }
    
    return core; // 返回k-核心
}

/* 问题四：计算社交网络的k-核心（方法二） */
Set<string> kCoreOfV2(const Map<string, Set<string>>& network, int k) {
    auto coreNet = network; // 复制原始网络作为核心网络
    
    // 循环查找并移除朋友数少于k的人
    while (true) {
        string lonelyPerson; // 记录孤独的人
        bool isLonelyPerson = false; // 标记是否找到
        
        // 遍历核心网络中的每个人
        for (string person : coreNet) {
            // 检查朋友数量
            if (coreNet[person].size() < k) {
                lonelyPerson = person; // 记录孤独的人
                isLonelyPerson = true; // 标记找到
                break;
            }
        }
        
        if (!isLonelyPerson) break; // 没有找到则结束循环
        
        // 从网络中删除该人，并更新其朋友的朋友列表
        for (string acquaintance : coreNet[lonelyPerson]) {
            coreNet[acquaintance] -= lonelyPerson; // 从朋友列表中移除该人
        }
        coreNet.remove(lonelyPerson); // 从核心网络中移除该人
    }
    
    // 构建k-核心人员集合
    Set<string> result;
    for (string member : coreNet) {
        result += member;
    }
    
    return result; // 返回k-核心
}

/* 问题四：计算社交网络的k-核心（递归方法） */
Set<string> kCoreOfRec(const Map<string, Set<string>>& network, int k, const Set<string>& remainingFolks) {
    string lonelyPerson; // 记录孤独的人
    bool isLonelyPerson = false; // 标记是否找到
    
    // 遍历剩余人员
    for (string person : remainingFolks) {
        // 计算与剩余人员中朋友的数量
        if ((network[person] * remainingFolks).size() < k) {
            lonelyPerson = person; // 记录孤独的人
            isLonelyPerson = true; // 标记找到
            break;
        }
    }
    
    // 基本情况：没有孤独的人，剩余人员构成k-核心
    if (!isLonelyPerson) return remainingFolks;
    
    // 递归情况：移除孤独的人，继续计算剩余人员的k-核心
    return kCoreOfRec(network, k, remainingFolks - lonelyPerson);
}

Set<string> kCoreOfV3(const Map<string, Set<string>>& network, int k) {
    Set<string> everyone; // 存储所有人员
    for (string person : network) {
        everyone += person; // 添加每个人到集合
    }
    return kCoreOfRec(network, k, everyone); // 调用递归函数计算k-核心
}

/* 问题四：计算社交网络的k-核心（另一种递归方法） */
Set<string> kCoreOfV4(const Map<string, Set<string>>& network, int k) {
    Map<string, Set<string>> coreNetwork; // 核心网络
    Set<string> core; // 核心人员集合
    
    // 复制有至少k个朋友的人到核心网络
    for (string person : network) {
        if (network[person].size() >= k) {
            coreNetwork[person] = network[person];
            core += person;
        }
    }
    
    // 如果核心包含所有人，直接返回
    if (core.size() == network.size()) return core;
    
    // 过滤核心网络中每个人的朋友列表，只保留核心中的人
    for (string person : coreNetwork) {
        coreNetwork[person] *= core;
    }
    
    return kCoreOfV4(coreNetwork, k); // 递归处理新的核心网络
}

/* ============== 递归相关问题 ============== */

/* 问题五：递归字符串处理函数 */
string hoy(const string& lawe) {
    // 基本情况：字符串长度小于等于1时直接返回
    if (lawe.length() <= 1) {
        return lawe;
    } else {
        // 递归处理前半部分和后半部分，并交换顺序
        string hawt = hoy(lawe.substr(0, lawe.size() / 2));
        string may = hoy(lawe.substr(lawe.size() / 2));
        return may + hawt; // 返回后半部分+前半部分
    }
}

/* 问题六：计算吃巧克力棒的方式数量 */
int numWaysToEat(int numSquares) {
    // 错误处理：负数方块
    if (numSquares < 0) {
        error("Negative chocolate? YOU MONSTER!");
    }
    
    // 基本情况：0或1块巧克力只有1种吃法
    if (numSquares <= 1) {
        return 1;
    } else {
        // 递归情况：先吃1块或先吃2块，方式数为两种情况之和
        return numWaysToEat(numSquares - 1) + numWaysToEat(numSquares - 2);
    }
}

/* 打印吃巧克力棒的所有方式（递归辅助函数） */
void printWaysToEatRec(int numSquares, const Vector<int>& soFar) {
    // 基本情况：没有剩余方块，打印当前吃法
    if (numSquares == 0) {
        cout << soFar << endl;
    }
    // 基本情况：剩余1块，添加到当前吃法并打印
    else if (numSquares == 1) {
        cout << soFar + 1 << endl;
    }
    // 递归情况：尝试先吃1块或2块
    else {
        printWaysToEatRec(numSquares - 1, soFar + 1); // 先吃1块
        printWaysToEatRec(numSquares - 2, soFar + 2); // 先吃2块
    }
}

void printWaysToEat(int numSquares) {
    // 错误处理：负数方块
    if (numSquares < 0) {
        error("You owe me some chocolate!");
    }
    
    // 调用递归函数，初始吃法为空
    printWaysToEatRec(numSquares, {});
}

/* 返回吃巧克力棒的所有方式（递归辅助函数） */
Set<Vector<int>> waysToEatRec(int numSquares, const Vector<int>& soFar) {
    // 基本情况：没有剩余方块，返回当前吃法
    if (numSquares == 0) {
        return {soFar};
    }
    // 基本情况：剩余1块，返回添加当前块的吃法
    else if (numSquares == 1) {
        return {soFar + 1};
    }
    // 递归情况：合并先吃1块和先吃2块的所有吃法
    else {
        return waysToEatRec(numSquares - 1, soFar + 1) + 
               waysToEatRec(numSquares - 2, soFar + 2);
    }
}

Set<Vector<int>> waysToEat(int numSquares) {
    // 错误处理：负数方块
    if (numSquares < 0) {
        error("You owe me some chocolate!");
    }
    
    // 调用递归函数，初始吃法为空
    return waysToEatRec(numSquares, {});
}

/* 主函数：测试所有功能 */
int main() {
    // 测试问题一
    Vector<int> idScans = {137, 106, 137, 161, 261, 137, 106};
    cout << "问题一：当前在格林图书馆的人: " << peopleInsideGreen(idScans) << endl;
    
    // 测试问题二
    Map<string, string> bosses;
    bosses["e"] = "b";
    bosses["b"] = "a";
    bosses["h"] = "g";
    bosses["g"] = "d";
    bosses["d"] = "a";
    cout << "问题二：e和j是否在同一家公司: " << (areAtSameCompany("e", "j", bosses) ? "是" : "否") << endl;
    
    // 测试问题三（需先加载Lexicon，此处简化）
    // Lexicon english("EnglishWords.dat");
    // cout << "问题三：最多子单词的单词: " << mostXzibitWord(english) << endl;
    
    // 测试问题四（简化测试）
    Map<string, Set<string>> network;
    network["A"] = {"B", "C", "D"};
    network["B"] = {"A", "D"};
    network["C"] = {"A", "D", "E", "F"};
    network["D"] = {"A", "B", "C", "E", "F"};
    network["E"] = {"C", "D", "F"};
    network["F"] = {"C", "D", "E"};
    cout << "问题四：3-核心: " << kCoreOf(network, 3) << endl;
    
    // 测试问题五
    cout << "问题五：hoy(\"res\") = " << hoy("res") << endl;
    cout << "问题五：hoy(\"sawt\") = " << hoy("sawt") << endl;
    
    // 测试问题六
    cout << "问题六：5块巧克力的吃法数量: " << numWaysToEat(5) << endl;
    cout << "问题六：5块巧克力的所有吃法:" << endl;
    printWaysToEat(5);
    
    return 0;
}
