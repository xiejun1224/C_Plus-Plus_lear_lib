#define _CRT_SECURE_NO_WARNINGS 1
#include "my_list.h"
//using namespace std;
//
//int main()
//{
//	// 测试1: 空列表
//	xiejun::list<int> ls1;
//	cout << "=== 测试1: 空列表 ===" << endl;
//	cout << "size: " << ls1.size() << endl;
//	cout << "empty: " << ls1.Empty() << endl;
//
//	// 测试2: push_back + 迭代器遍历
//	cout << "\n=== 测试2: push_back ===" << endl;
//	ls1.push_back(1);
//	ls1.push_back(2);
//	ls1.push_back(3);
//	xiejun::list<int>::iterator it = ls1.begin();
//	for (; it != ls1.end(); ++it)
//		cout << *it << " ";
//	cout << endl;
//	cout << "size: " << ls1.size() << endl;
//
//	// 测试3: push_front + 迭代器遍历
//	cout << "\n=== 测试3: push_front ===" << endl;
//	ls1.push_front(10);
//	ls1.push_front(20);
//	ls1.push_front(30);
//	it = ls1.begin();
//	for (; it != ls1.end(); ++it)
//		cout << *it << " ";
//	cout << endl;
//	cout << "size: " << ls1.size() << endl;
//
//	// 测试4: pop_back
//	cout << "\n=== 测试4: pop_back ===" << endl;
//	ls1.pop_back();
//	ls1.pop_back();
//	it = ls1.begin();
//	for (; it != ls1.end(); ++it)
//		cout << *it << " ";
//	cout << endl;
//	cout << "size: " << ls1.size() << endl;
//
//	// 测试5: pop_front
//	cout << "\n=== 测试5: pop_front ===" << endl;
//	ls1.pop_front();
//	it = ls1.begin();
//	for (; it != ls1.end(); ++it)
//		cout << *it << " ";
//	cout << endl;
//	cout << "size: " << ls1.size() << endl;
//
//	// 测试6: 清空列表
//	cout << "\n=== 测试6: 逐个pop直到空 ===" << endl;
//	while (!ls1.Empty())
//		ls1.pop_front();
//	cout << "size: " << ls1.size() << endl;
//	cout << "empty: " << ls1.Empty() << endl;
//
//	// 测试7: string类型
//	cout << "\n=== 测试7: string类型 ===" << endl;
//	xiejun::list<string> ls2;
//	ls2.push_back("hello");
//	ls2.push_back("world");
//	ls2.push_front("hi");
//	xiejun::list<string>::iterator it2 = ls2.begin();
//	for (; it2 != ls2.end(); ++it2)
//		cout << *it2 << " ";
//	cout << endl;
//
//	return 0;
//}

using namespace std;
using namespace xiejun;

void PrintList(const list<int>& lst)
{
    cout << "const print: ";
    for (auto it = lst.begin(); it != lst.end(); ++it)
    {
        cout << *it << " ";
        // *it = 10;  // 取消注释会报错 ✅ const不能改
    }
    cout << endl;
}
template<class Container>
void Print_container(const Container& it)
{
    auto It = it.begin();
    while (It != it.end())
    {
        cout << *It << " ";
            ++It;
    }
    cout << endl;
}

//int main()
//{
    //// Test1: 非 const 可修改
    //cout << "===== Test1 =====" << endl;
    //list<int> lst;
    //lst.push_back(1);
    //lst.push_back(2);
    //lst.push_back(3);

    //for (auto it = lst.begin(); it != lst.end(); ++it)
    //    *it *= 10;  // ✅ 非 const 可以改

    //PrintList(lst);  // 10 20 30
    //cout << "✅ Test1 通过\n\n";

    //// Test2: const 只读
    //cout << "===== Test2 =====" << endl;
    //const list<int>& clst = lst;
    //for (auto it = clst.begin(); it != clst.end(); ++it)
    //    cout << *it << " ";  // 只能读
    //cout << "\n✅ Test2 通过\n\n";

    //// Test3: 基础功能
    //cout << "===== Test3 =====" << endl;
    //list<int> lst2;
    //lst2.push_back(100);
    //lst2.push_back(200);
    //lst2.push_front(50);
    //lst2.push_front(25);
    //cout << "size = " << lst2.size() << " (应为4)\n";
    //PrintList(lst2);
    //lst2.pop_back();
    //lst2.pop_front();
    //cout << "size = " << lst2.size() << " (应为2)\n";
    //PrintList(lst2);
    //cout << "✅ Test3 通过\n\n";

    //// Test4: insert & erase
    //cout << "===== Test4 =====" << endl;
    //auto it = lst2.begin();
    //++it;
    //lst2.insert(it, 75);
    //PrintList(lst2);  // 50 75 100
    //it = lst2.begin();
    //lst2.erase(it);
    //PrintList(lst2);  // 75 100
    //cout << "✅ Test4 通过\n\n";

    //// Test5: 箭头运算符
    //cout << "===== Test5 =====" << endl;
    //struct Point { int x, y; };
    //list<Point> plst;
    //plst.push_back({ 1, 2 });
    //plst.push_back({ 3, 4 });
    //for (auto it = plst.begin(); it != plst.end(); ++it)
    //    cout << "(" << it->x << "," << it->y << ") ";
    //cout << "\n✅ Test5 通过\n\n";

    //cout << "🎉 全部测试通过！" << endl;
    //return 0;
//}
#include<vector>
int main()
{
    list<int> ls;
    ls.push_back(1);
    ls.push_back(2);
    ls.push_back(3);
    ls.push_back(4);
    ls.push_back(5);
    Print_container(ls);
    /*vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);
    Print_container(v1);*/
    list<int> ls2(ls);
    Print_container(ls2);
    list<int> ls3;
    ls3 = ls2;
    Print_container(ls3);
    return 0;
}