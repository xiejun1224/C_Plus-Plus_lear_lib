#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "priority_queue.h"
using namespace std;

//int main()
//{
//    // ========== 测试1：默认大根堆（less，最大值优先弹出）==========
//    cout << "===== 测试1：大根堆（最大元素先出）=====\n";
//    bit::priority_queue<int> max_heap;
//    // 依次插入数字
//    max_heap.push(5);
//    max_heap.push(9);
//    max_heap.push(2);
//    max_heap.push(7);
//    max_heap.push(1);
//
//    cout << "元素个数：" << max_heap.size() << endl;
//    cout << "弹出顺序：";
//    while (!max_heap.empty())
//    {
//        cout << max_heap.top() << " ";
//        max_heap.pop();
//    }
//    cout << "\n\n";
//
//    // ========== 测试2：小根堆（greater，最小值优先弹出）==========
//    cout << "===== 测试2：小根堆（最小元素先出）=====\n";
//    bit::priority_queue<int, vector<int>, bit::greater<int>> min_heap;
//    min_heap.push(5);
//    min_heap.push(9);
//    min_heap.push(2);
//    min_heap.push(7);
//    min_heap.push(1);
//
//    cout << "弹出顺序：";
//    while (!min_heap.empty())
//    {
//        cout << min_heap.top() << " ";
//        min_heap.pop();
//    }
//    cout << "\n\n";
//
//    // ========== 测试3：数组迭代器初始化堆（批量建堆）==========
//    cout << "===== 测试3：数组直接初始化大根堆 =====\n";
//    int arr[] = { 4, 1, 8, 3, 6, 10, 0 };
//    int len = sizeof(arr) / sizeof(arr[0]);
//    bit::priority_queue<int> heap2(arr, arr + len);
//
//    cout << "弹出顺序：";
//    while (!heap2.empty())
//    {
//        cout << heap2.top() << " ";
//        heap2.pop();
//    }
//    cout << "\n\n";
//
//    // ========== 测试4：字符串类型测试（自定义类型排序）==========
//    cout << "===== 测试4：string字符串大根堆（字典序大的优先）=====\n";
//    bit::priority_queue<string> str_heap;
//    str_heap.push("banana");
//    str_heap.push("apple");
//    str_heap.push("pear");
//    str_heap.push("orange");
//
//    cout << "弹出顺序：";
//    while (!str_heap.empty())
//    {
//        cout << str_heap.top() << " ";
//        str_heap.pop();
//    }
//    cout << endl;
//
//    return 0;
//}
void shellSort(int* a, int n)
{
    int d = n;
    while (d > 1) {
        d = d / 3 + 1;
        for (int i = 0; i < n - d; i++) {
            int end = i;
            int tmp = a[end + d];
            while (end >= 0)
            {
                if (a[end] > tmp)
                {
                    a[end + d] = a[end];
                    end -= d;
                }
                else
                {
                    break;
                }
            }
            a[end + d] = tmp;
        }
    }
}
int main()
{
    //int arr[] = { 8, 4, 9, 1, 3, 6, 2, 7, 5 };
    int arr[] = { 3, 1, 4, 2, 7, 6, 9, 8 };
    int len = sizeof(arr) / sizeof(arr[0]);

    shellSort(arr, len);

    printf("升序排序结果：");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}