#define _CRT_SECURE_NO_WARNINGS 1
#include"my_vector.h"
#include<string>
using namespace std;
void test1()
{
	xiejun::vector<int> v(10, 1);
	for (auto& it : v)
	{
		cout << it<<" ";
	}
	cout << endl;
	cout << "v.size()=" << v.size() << endl;
	cout << "v.capacity()=" << v.capacity() << endl;
	
}
void test2()
{
	xiejun::vector<int> v(10, 1);
	v.push_back(5);
	xiejun::vector<char> v2(10,'a');
	for (auto& it : v)
	{
		cout << it << " ";
	}
	cout << endl;
	cout << "v.size()=" << v.size() << endl;
	cout << "v.capacity()=" << v.capacity() << endl;

	v2.pop_back();
	for (auto& it : v2)
	{
		cout << it << " ";
	}
	cout << endl;
	cout << "v.size()=" << v2.size() << endl;
	cout << "v.capacity()=" << v2.capacity() << endl;

}

void test3()
{
	xiejun::vector<int> v(10, 1);
	xiejun::vector<int> v2(v);
	for (auto& it : v)
	{
		cout << it << " ";
	}
	cout << endl;
	cout << "v.size()=" << v.size() << endl;
	cout << "v.capacity()=" << v.capacity() << endl;

	v2.push_back(5);
	v2.push_back(7);
	v2.push_back(6);
	v2.push_back(4);
	v2.push_back(3);
	for (auto& it : v2)
	{
		cout << it << " ";
	}
	cout << endl;
	cout << "v.size()=" << v2.size() << endl;
	cout << "v.capacity()=" << v2.capacity() << endl;
	v = v2;
	for (auto& it : v)
	{
		cout << it << " ";
	}
	cout << endl;
	cout << "v.size()=" << v.size() << endl;
	cout << "v.capacity()=" << v.capacity() << endl;
}
void test4()
{
	xiejun::vector<string> v1(10, "hellow");
	xiejun::vector<string> v2(v1);
	v2.push_back("hellow");
	v2.push_back("xiejun");
	for (auto& it : v1)
	{
		cout << it << " ";
	}
	cout << endl;
	cout << "v1.size()=" << v1.size() << endl;
	cout << "v1.capacity()=" << v1.capacity() << endl;



	v2.resize(30, "C++");
	for (auto& it : v2)
	{
		cout << it << " ";
	}	
	cout << endl;
	cout << "v2.size()=" << v2.size() << endl;
	cout << "v2.capacity()=" << v2.capacity() << endl;

	cout << v2[29] << endl;
}
void test5()
{
	xiejun::vector<int> v1(10,6);
	v1.insert(v1.begin() + 3, 8);
	v1.insert(v1.begin(), 7);
	v1.insert(v1.begin()+v1.size(), 9);
	v1.insert(v1.end(), 10);
	xiejun::vector<int> v2(v1.begin(), v1.begin() + 4);
	xiejun::vector<int> v3(5,10);
	v3.erase(v3.begin() + 3);
	for (int i = 0; i < v3.size(); i++)
	{
		cout << v3[i]<<" ";
	}
	cout << endl;



	for (auto& it : v1)
	{
		cout << it << " ";
	}
	cout << endl;
	cout << "v1.size()=" << v1.size() << endl;
	cout << "v1.capacity()=" << v1.capacity() << endl;

	for (auto& it : v2)
	{
		cout << it << " ";
	}
	cout << endl;
	cout << "v2.size()=" << v2.size() << endl;
	cout << "v2.capacity()=" << v2.capacity() << endl;

}

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	test5();
	return 0;
}

