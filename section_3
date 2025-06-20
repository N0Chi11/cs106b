#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;

// 问题一：吃巧克力问题（计算吃法数量）
int numWaysToEat(int numSquares) {
    // 不能有负的巧克力块数
    if (numSquares < 0) {
        // 错误处理：输入负数
        cerr << "Negative chocolate? YOU MONSTER!" << endl;
        exit(1);
    }
    // 基本情况：0块巧克力只有一种吃法（不吃）
    if (numSquares == 0) {
        return 1;
    }
    // 递归情况：尝试所有可能的一口吃的块数（1到numSquares）
    else {
        int result = 0;
        // 遍历所有可能的一口吃的块数
        for (int biteSize = 1; biteSize <= numSquares; biteSize++) {
            // 累加所有可能的吃法数量
            result += numWaysToEat(numSquares - biteSize);
        }
        return result;
    }
}

// 问题一：打印所有吃法（方法1）
void printWaysToEatRec(int numSquares, const vector<int>& soFar) {
    // 基本情况：没有巧克力块剩下，打印当前吃法
    if (numSquares == 0) {
        cout << "[";
        for (size_t i = 0; i < soFar.size(); i++) {
            if (i > 0) cout << ", ";
            cout << soFar[i];
        }
        cout << "]" << endl;
    }
    // 递归情况：尝试所有可能的一口吃的块数
    else {
        for (int biteSize = 1; biteSize <= numSquares; biteSize++) {
            // 复制当前吃法并添加新的一口
            vector<int> newSoFar = soFar;
            newSoFar.push_back(biteSize);
            // 递归处理剩余的巧克力块
            printWaysToEatRec(numSquares - biteSize, newSoFar);
        }
    }
}

void printWaysToEat(int numSquares) {
    if (numSquares < 0) {
        cerr << "You owe me some chocolate!" << endl;
        exit(1);
    }
    // 从空的吃法开始
    printWaysToEatRec(numSquares, {});
}

// 问题一：返回所有吃法的集合（方法2）
set<vector<int>> waysToEatRec(int numSquares, const vector<int>& soFar) {
    // 基本情况：没有巧克力块剩下，返回当前吃法
    if (numSquares == 0) {
        return {soFar};
    }
    // 递归情况：尝试所有可能的一口吃的块数
    else {
        set<vector<int>> result;
        for (int biteSize = 1; biteSize <= numSquares; biteSize++) {
            // 复制当前吃法并添加新的一口
            vector<int> newSoFar = soFar;
            newSoFar.push_back(biteSize);
            // 合并递归调用返回的所有吃法
            set<vector<int>> subResult = waysToEatRec(numSquares - biteSize, newSoFar);
            result.insert(subResult.begin(), subResult.end());
        }
        return result;
    }
}

set<vector<int>> waysToEat(int numSquares) {
    if (numSquares < 0) {
        cerr << "You owe me some chocolate!" << endl;
        exit(1);
    }
    // 从空的吃法开始
    return waysToEatRec(numSquares, {});
}

// 问题二：递归追踪（有bug的函数）
int batken(const vector<int>& v) {
    // 基本情况：空向量返回-1
    if (v.empty()) {
        return -1;
    }
    int total = 0;
    // 遍历向量元素（注意：循环只会执行一次，因为有return语句）
    for (int i = 1; i < v.size(); i++) {
        total += v[i];
        // 递归调用并返回结果（导致循环只能执行一次）
        return batken(vector<int>(v.begin() + i, v.end()));
    }
    return total;
}

// 问题三：分摊账单
void listPossiblePaymentsRec(int total, const set<string>& people, const map<string, int>& payments) {
    // 基本情况：只剩一个人，他需要支付剩余全部金额
    if (people.size() == 1) {
        map<string, int> finalPayments = payments;
        finalPayments.insert({*people.begin(), total});
        cout << "Payment: ";
        for (const auto& pair : finalPayments) {
            cout << pair.first << ": $" << pair.second << "  ";
        }
        cout << endl;
    }
    // 递归情况：当前人尝试支付0到total的所有可能金额
    else {
        string firstPerson = *people.begin();
        for (int payment = 0; payment <= total; payment++) {
            // 更新当前支付方案
            map<string, int> updatedPayments = payments;
            updatedPayments[firstPerson] = payment;
            // 递归处理剩余金额和剩余人员
            set<string> remainingPeople = people;
            remainingPeople.erase(firstPerson);
            listPossiblePaymentsRec(total - payment, remainingPeople, updatedPayments);
        }
    }
}

void listPossiblePayments(int total, const set<string>& people) {
    // 错误处理：金额不能为负，至少有一个人
    if (total < 0) {
        cerr << "Guess you're an employee?" << endl;
        exit(1);
    }
    if (people.empty()) {
        cerr << "Dine and dash?" << endl;
        exit(1);
    }
    // 从空的支付方案开始
    listPossiblePaymentsRec(total, people, {});
}

// 问题四：最大无偏群体
set<string> largestGroupInRec(const map<string, set<string>>& network, const set<string>& permissible) {
    // 基本情况：没有可选人员，返回空集合
    if (permissible.empty()) return {};
    // 选择一个人进行决策
    string next = *permissible.begin();
    // 情况1：不选这个人，递归处理剩余人员
    set<string> without = largestGroupInRec(network, set<string>(permissible.begin() + 1, permissible.end()));
    // 情况2：选这个人，递归处理非朋友的人员
    set<string> friends = network.at(next);
    set<string> withPermissible = permissible;
    withPermissible.erase(next);
    for (const string& friendName : friends) {
        withPermissible.erase(friendName);
    }
    set<string> with = largestGroupInRec(network, withPermissible);
    with.insert(next);
    // 返回两种情况中较大的群体
    return with.size() > without.size() ? with : without;
}

set<string> largestUnbiasedGroupIn(const map<string, set<string>>& network) {
    // 收集所有人员
    set<string> everyone;
    for (const auto& pair : network) {
        everyone.insert(pair.first);
    }
    return largestGroupInRec(network, everyone);
}

// 问题五：社交距离排列（方法1）
bool endsWith(const string& s, const string& suffix) {
    if (s.length() < suffix.length()) return false;
    return s.substr(s.length() - suffix.length()) == suffix;
}

set<string> safeArrangementsRec(int lineLength, int numPeople, const string& soFar) {
    // 基本情况：达到行长度，检查是否安置了所有人
    if (soFar.length() == lineLength) {
        return numPeople == 0 ? {soFar} : set<string>();
    }
    // 情况1：添加一个空位置
    set<string> result = safeArrangementsRec(lineLength, numPeople, soFar + ".");
    // 情况2：添加一个人（如果条件允许）
    if (numPeople > 0 && !endsWith(soFar, "P") && !endsWith(soFar, "P.")) {
        result.insert(safeArrangementsRec(lineLength, numPeople - 1, soFar + "P").begin(), 
                     safeArrangementsRec(lineLength, numPeople - 1, soFar + "P").end());
    }
    return result;
}

set<string> safeArrangementsOf(int lineLength, int numPeople) {
    return safeArrangementsRec(lineLength, numPeople, "");
}

// 问题五：社交距离排列（方法2）
set<string> safeArrangementsRec2(int lineLength, int numPeople, const string& soFar, int distance) {
    // 基本情况：达到行长度，检查是否安置了所有人
    if (soFar.length() == lineLength) {
        return numPeople == 0 ? {soFar} : set<string>();
    }
    // 情况1：添加一个空位置，距离增加
    set<string> result = safeArrangementsRec2(lineLength, numPeople, soFar + ".", distance + 1);
    // 情况2：添加一个人（如果距离足够）
    if (numPeople > 0 && distance >= 2) {
        result.insert(safeArrangementsRec2(lineLength, numPeople - 1, soFar + "P", 0).begin(), 
                     safeArrangementsRec2(lineLength, numPeople - 1, soFar + "P", 0).end());
    }
    return result;
}

set<string> safeArrangementsOf2(int lineLength, int numPeople) {
    // 初始距离设为2，相当于没有前置人员
    return safeArrangementsRec2(lineLength, numPeople, "", 2);
}

// 问题六：最少硬币问题（基础版）
int fewestCoinsFor(int cents, const set<int>& coins) {
    // 错误处理：不能有负金额
    if (cents < 0) {
        cerr << "You owe me money, not the other way around!" << endl;
        exit(1);
    }
    // 基本情况：0分钱需要0硬币
    else if (cents == 0) {
        return 0;
    }
    // 基本情况：没有硬币，返回不可能的标记值
    else if (coins.empty()) {
        return cents + 1;
    }
    // 递归情况：尝试使用当前硬币的不同数量
    else {
        int bestSoFar = cents + 1;
        int coin = *coins.begin();
        // 尝试使用0到最大可能数量的当前硬币
        for (int copies = 0; copies * coin <= cents; copies++) {
            set<int> remainingCoins = coins;
            remainingCoins.erase(coin);
            // 计算当前选择的硬币数量加上剩余金额的最少硬币数
            int thisChoice = copies + fewestCoinsFor(cents - copies * coin, remainingCoins);
            // 更新最优解
            if (thisChoice < bestSoFar) {
                bestSoFar = thisChoice;
            }
        }
        return bestSoFar;
    }
}

// 问题六：最少硬币问题（带记忆化）
int fewestCoinsRec(int cents, const vector<int>& coins, int startIndex, vector<vector<int>>& memo) {
    // 基本情况：0分钱需要0硬币
    if (cents == 0) {
        return 0;
    }
    // 基本情况：没有硬币可选，返回不可能的标记值
    else if (startIndex == coins.size()) {
        return cents + 1;
    }
    // 基本情况：已计算过，直接返回结果
    else if (memo[cents][startIndex] != -1) {
        return memo[cents][startIndex];
    }
    // 递归情况：尝试使用当前硬币的不同数量
    else {
        int bestSoFar = cents + 1;
        int coin = coins[startIndex];
        // 尝试使用0到最大可能数量的当前硬币
        for (int copies = 0; copies * coin <= cents; copies++) {
            // 计算当前选择的硬币数量加上剩余金额的最少硬币数
            int thisChoice = copies + fewestCoinsRec(cents - copies * coin, coins, startIndex + 1, memo);
            // 更新最优解
            if (thisChoice < bestSoFar) {
                bestSoFar = thisChoice;
            }
        }
        // 记忆化存储结果
        memo[cents][startIndex] = bestSoFar;
        return bestSoFar;
    }
}

int fewestCoinsForMemo(int cents, const set<int>& coins) {
    // 错误处理：不能有负金额
    if (cents < 0) {
        cerr << "You owe me money, not the other way around!" << endl;
        exit(1);
    }
    // 转换为向量以便索引
    vector<int> coinVec(coins.begin(), coins.end());
    // 初始化记忆化表格
    vector<vector<int>> memo(cents + 1, vector<int>(coinVec.size() + 1, -1));
    // 调用递归函数
    return fewestCoinsRec(cents, coinVec, 0, memo);
}

// 问题七：生成所有可能的和
set<int> numbersMadeFromRec(const set<int>& values, int totalSoFar) {
    // 基本情况：没有数字可选，返回当前总和
    if (values.empty()) {
        return {totalSoFar};
    }
    // 递归情况：选择包含或不包含当前数字
    else {
        int number = *values.begin();
        set<int> without = numbersMadeFromRec(set<int>(values.begin() + 1, values.end()), totalSoFar);
        set<int> with = numbersMadeFromRec(set<int>(values.begin() + 1, values.end()), totalSoFar + number);
        without.insert(with.begin(), with.end());
        return without;
    }
}

set<int> numbersMadeFrom(const set<int>& values) {
    return numbersMadeFromRec(values, 0);
}

// 问题七：判断是否能达到目标和
bool canMakeTargetRec(const set<int>& values, int target, int totalSoFar) {
    // 基本情况1：达到目标和
    if (totalSoFar == target) {
        return true;
    }
    // 基本情况2：没有数字可选且未达到目标
    else if (values.empty()) {
        return false;
    }
    // 递归情况：选择包含或不包含当前数字
    else {
        int number = *values.begin();
        set<int> remaining(values.begin() + 1, values.end());
        return canMakeTargetRec(remaining, target, totalSoFar) || 
               canMakeTargetRec(remaining, target, totalSoFar + number);
    }
}

bool canMakeTarget(const set<int>& values, int target) {
    return canMakeTargetRec(values, target, 0);
}

// 问题七：找到一个达到目标和的组合
int sumOf(const set<int>& values) {
    int result = 0;
    for (int value : values) {
        result += value;
    }
    return result;
}

bool canMakeTargetRecWithSolution(const set<int>& values, int target, const set<int>& soFar, set<int>& solution) {
    // 基本情况1：达到目标和，记录解决方案
    if (sumOf(soFar) == target) {
        solution = soFar;
        return true;
    }
    // 基本情况2：没有数字可选且未达到目标
    else if (values.empty()) {
        return false;
    }
    // 递归情况：选择包含或不包含当前数字
    else {
        int number = *values.begin();
        set<int> remaining(values.begin() + 1, values.end());
        // 不包含当前数字
        if (canMakeTargetRecWithSolution(remaining, target, soFar, solution)) {
            return true;
        }
        // 包含当前数字
        set<int> newSoFar = soFar;
        newSoFar.insert(number);
        if (canMakeTargetRecWithSolution(remaining, target, newSoFar, solution)) {
            return true;
        }
        return false;
    }
}

bool canMakeTarget(const set<int>& values, int target, set<int>& solution) {
    return canMakeTargetRecWithSolution(values, target, {}, solution);
}

// 问题八：天平称重问题
bool isMeasurableRec(int amount, const vector<int>& weights, int index) {
    // 基本情况：没有权重可选，只有当目标为0时可测量
    if (index == weights.size()) {
        return amount == 0;
    }
    // 递归情况：尝试三种放置方式（不放、放左边、放右边）
    else {
        int weight = weights[index];
        // 不放当前权重、放在左边（增加重量）、放在右边（减少重量）
        return isMeasurableRec(amount, weights, index + 1) ||
               isMeasurableRec(amount + weight, weights, index + 1) ||
               isMeasurableRec(amount - weight, weights, index + 1);
    }
}

bool isMeasurable(int target, const vector<int>& weights) {
    return isMeasurableRec(target, weights, 0);
}

// 主函数：测试各个问题
int main() {
    // 测试问题一
    cout << "问题一：吃巧克力问题（4块）" << endl;
    cout << "吃法数量：" << numWaysToEat(4) << endl;
    cout << "所有吃法：" << endl;
    printWaysToEat(4);
    
    // 测试问题二
    cout << "问题二：递归追踪" << endl;
    vector<int> v = {1, 2, 3, 4};
    cout << "batken({1,2,3,4}) 返回：" << batken(v) << endl;
    
    // 测试问题三
    cout << "问题三：分摊账单（总金额4，3人）" << endl;
    set<string> people = {"A", "B", "C"};
    listPossiblePayments(4, people);
    
    // 测试问题五
    cout << "问题五：社交距离排列（12米，4人）" << endl;
    set<string> arrangements = safeArrangementsOf(12, 4);
    cout << "有效排列数量：" << arrangements.size() << endl;
    
    // 测试问题六
    cout << "问题六：最少硬币（24分，硬币{1,12,14,63}）" << endl;
    set<int> coins = {1, 12, 14, 63};
    cout << "最少硬币数：" << fewestCoinsFor(24, coins) << endl;
    
    // 测试问题七
    cout << "问题七：生成所有可能的和（{1,2,5,9}）" << endl;
    set<int> values = {1, 2, 5, 9};
    set<int> sums = numbersMadeFrom(values);
    cout << "可生成的和：";
    for (int s : sums) cout << s << " ";
    cout << endl;
    
    // 测试问题八
    cout << "问题八：天平称重（2，{1,3}）" << endl;
    vector<int> weights = {1, 3};
    cout << "2是否可测量：" << (isMeasurable(2, weights) ? "是" : "否") << endl;
    
    return 0;
}
