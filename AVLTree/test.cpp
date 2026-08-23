#define _CRT_SECURE_NO_WARNINGS 1
#include "AVLTree.h"
#include <iostream>
#include <vector>
#include <random>
#include<string>
using namespace std;

// 测试1: 插入功能测试
void TestInsert()
{
    cout << "========== 测试1: 插入功能 ==========" << endl;
    AVLTree<int, string> tree;

    // 正常插入
    cout << "插入: (5, five)" << endl;
    tree.insert({ 5, "five" });
    tree.Print();  // 应输出: 5

    cout << "插入: (3, three)" << endl;
    tree.insert({ 3, "three" });
    tree.Print();  // 应输出: 3 5

    cout << "插入: (7, seven)" << endl;
    tree.insert({ 7, "seven" });
    tree.Print();  // 应输出: 3 5 7

    cout << "插入: (2, two)" << endl;
    tree.insert({ 2, "two" });
    tree.Print();  // 应输出: 2 3 5 7

    cout << "插入: (4, four)" << endl;
    tree.insert({ 4, "four" });
    tree.Print();  // 应输出: 2 3 4 5 7

    // 重复插入
    cout << "\n尝试插入重复键: (5, five_again)" << endl;
    bool result = tree.insert({ 5, "five_again" });
    cout << "插入结果: " << (result ? "成功" : "失败") << endl;
}

// 测试2: 旋转测试
void TestRotation()
{
    cout << "\n========== 测试2: 旋转测试 ==========" << endl;

    // 左单旋 (RR)
    cout << "--- 左单旋测试 (RR) ---" << endl;
    AVLTree<int, int> tree1;
    tree1.insert({ 10, 10 });
    tree1.insert({ 20, 20 });
    tree1.insert({ 30, 30 });  // 触发左旋
    tree1.Print();  // 应输出: 10 20 30

    // 右单旋 (LL)
    cout << "--- 右单旋测试 (LL) ---" << endl;
    AVLTree<int, int> tree2;
    tree2.insert({ 30, 30 });
    tree2.insert({ 20, 20 });
    tree2.insert({ 10, 10 });  // 触发右旋
    tree2.Print();  // 应输出: 10 20 30

    // 左右双旋 (LR)
    cout << "--- 左右双旋测试 (LR) ---" << endl;
    AVLTree<int, int> tree3;
    tree3.insert({ 30, 30 });
    tree3.insert({ 10, 10 });
    tree3.insert({ 20, 20 });  // 触发LR双旋
    tree3.Print();  // 应输出: 10 20 30

    // 右左双旋 (RL)
    cout << "--- 右左双旋测试 (RL) ---" << endl;
    AVLTree<int, int> tree4;
    tree4.insert({ 10, 10 });
    tree4.insert({ 30, 30 });
    tree4.insert({ 20, 20 });  // 触发RL双旋
    tree4.Print();  // 应输出: 10 20 30
}

// 测试3: 随机插入测试
void TestRandomInsert()
{
    cout << "\n========== 测试3: 随机插入测试 ==========" << endl;
    AVLTree<int, int> tree;
    vector<int> nums = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 90 };

    cout << "插入顺序: ";
    for (int num : nums)
    {
        cout << num << " ";
        tree.insert({ num, num });
    }
    cout << endl;

    cout << "中序遍历结果: ";
    tree.Print();

    cout << "查找测试:" << endl;
    for (int num : {20, 50, 90, 100})
    {
        auto result = tree.find(num);
        if (result)
            cout << "  找到键 " << num << "，值为 " << result->_kv.second << endl;
        else
            cout << "  未找到键 " << num << endl;
    }
}

// 测试4: 拷贝构造测试
void TestCopyConstructor()
{
    cout << "\n========== 测试4: 拷贝构造测试 ==========" << endl;

    AVLTree<int, string> tree1;
    tree1.insert({ 1, "one" });
    tree1.insert({ 2, "two" });
    tree1.insert({ 3, "three" });
    cout << "原树: ";
    tree1.Print();

    AVLTree<int, string> tree2(tree1);
    cout << "拷贝树: ";
    tree2.Print();

    // 修改原树
    tree1.insert({ 4, "four" });
    cout << "修改原树后: ";
    tree1.Print();
    cout << "拷贝树 (应不变): ";
    tree2.Print();
}

// 测试5: 赋值运算符测试
void TestAssignmentOperator()
{
    cout << "\n========== 测试5: 赋值运算符测试 ==========" << endl;

    AVLTree<int, string> tree1;
    tree1.insert({ 1, "one" });
    tree1.insert({ 2, "two" });
    tree1.insert({ 3, "three" });
    cout << "tree1: ";
    tree1.Print();

    AVLTree<int, string> tree2;
    tree2.insert({ 10, "ten" });
    tree2.insert({ 20, "twenty" });
    cout << "tree2 (赋值前): ";
    tree2.Print();

    tree2 = tree1;
    cout << "tree2 (赋值后): ";
    tree2.Print();
}

// 测试6: 查找功能测试
void TestFind()
{
    cout << "\n========== 测试6: 查找功能测试 ==========" << endl;

    AVLTree<int, string> tree;
    tree.insert({ 5, "five" });
    tree.insert({ 3, "three" });
    tree.insert({ 7, "seven" });
    tree.insert({ 2, "two" });
    tree.insert({ 4, "four" });
    tree.insert({ 6, "six" });
    tree.insert({ 8, "eight" });

    cout << "树的中序遍历: ";
    tree.Print();

    cout << "查找结果:" << endl;
    for (int key : {3, 8, 10, 1})
    {
        auto node = tree.find(key);
        if (node)
            cout << "  键 " << key << " 存在，值: " << node->_kv.second << endl;
        else
            cout << "  键 " << key << " 不存在" << endl;
    }
}

// 测试7: 大量数据插入测试（压力测试）
void TestStressTest()
{
    cout << "\n========== 测试7: 压力测试 ==========" << endl;

    AVLTree<int, int> tree;
    const int N = 10000;

    cout << "插入 " << N << " 个随机数..." << endl;
    for (int i = 0; i < N; ++i)
    {
        int num = rand() % (N * 10);
        tree.insert({ num, num });
    }

    cout << "插入完成" << endl;
    cout << "查找测试 (10个随机数)..." << endl;

    for (int i = 0; i < 10; ++i)
    {
        int key = rand() % (N * 10);
        auto node = tree.find(key);
        if (node)
            cout << "  找到键 " << key << endl;
        else
            cout << "  未找到键 " << key << endl;
    }

    // 拷贝构造测试（大数据）
    cout << "大数据拷贝构造测试..." << endl;
    AVLTree<int, int> tree2(tree);
    cout << "拷贝完成" << endl;
}

// 测试8: 边界条件测试
void TestBoundaryConditions()
{
    cout << "\n========== 测试8: 边界条件测试 ==========" << endl;

    // 空树
    AVLTree<int, string> emptyTree;
    cout << "空树中序遍历: ";
    emptyTree.Print();

    cout << "在空树中查找: ";
    auto result = emptyTree.find(5);
    cout << (result ? "找到" : "未找到") << endl;

    // 单节点树
    AVLTree<int, string> singleTree;
    singleTree.insert({ 1, "one" });
    cout << "单节点树: ";
    singleTree.Print();

    // 大量连续插入
    AVLTree<int, int> ascendingTree;
    cout << "插入 1-100 的连续序列..." << endl;
    for (int i = 1; i <= 100; ++i)
        ascendingTree.insert({ i, i });
    cout << "插入完成" << endl;

    // 逆序插入
    AVLTree<int, int> descendingTree;
    cout << "插入 100-1 的逆序序列..." << endl;
    for (int i = 100; i >= 1; --i)
        descendingTree.insert({ i, i });
    cout << "插入完成" << endl;
}

// 测试9: 析构函数测试（内存泄漏检测）
void TestDestructor()
{
    cout << "\n========== 测试9: 析构函数测试 ==========" << endl;
    cout << "创建临时对象..." << endl;
    {
        AVLTree<int, string> tree;
        for (int i = 0; i < 100; ++i)
            tree.insert({ i, "value" + to_string(i) });
        cout << "临时树已创建，即将析构..." << endl;
    }
    cout << "析构完成（应无内存泄漏）" << endl;
}

// 主测试函数
//

void test()
{
    const int N = 100000;
    vector<int> v;
    v.reserve(N);
    srand(time(0));
    for (size_t i = 0; i < N; i++)
    {
        v.push_back(rand() + i);
    }
    size_t begin1 = clock();
    AVLTree<int, int> t;
    for (auto& e : v)
    {
        t.insert(make_pair(e, e));
    }
    size_t end1 = clock();
    cout << "insert:" << end1 - begin1 << endl;
    cout << t.IsBalance() << endl;
    cout << "Heigh:" << t.Height() << endl;
    cout << "Size:" << t.Size() << endl;
}
int main()
{
    test();
    return 0;
}