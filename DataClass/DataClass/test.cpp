#define _CRT_SECURE_NO_WARNINGS 1
#include"Data.h"

//class Stack {
//public:
//	Stack(int n = 4)
//	{
//		a = (int*)malloc(sizeof(int) * n);
//		if (a == nullptr)
//		{
//			perror("malloc fail");
//			return;
//		}
//		capacity = n;
//		size = 0;
//	}
//	~Stack()
//	{
//		free(a);
//		a = nullptr;
//		capacity = size = 0;
//	}
//	//栈的深拷贝
//	Stack(const Stack& p)
//	{
//		int*tmp = (int*)malloc(sizeof(int) * p.capacity);
//		if (tmp == nullptr)
//		{
//			perror("malloc fail");
//			return;
//		}
//		a = tmp;
//		memcpy(a, p.a, sizeof(int) * p.size);
//		capacity = p.capacity;
//		size = p.size;
//	}
//	void StackPush(int n)
//	{
//		if (capacity == size)
//		{
//			int newcapacity = 2 * capacity;
//			int* tmp = (int*)realloc(a, sizeof(int) * newcapacity);
//			if (tmp == nullptr)
//			{
//				perror("realloc fail");
//				return;
//			}
//			a = tmp;
//			capacity = newcapacity;
//		}
//		a[size] = n;
//		++size;
//	}
//private:
//	int* a;
//	int capacity;
//	int size;
//};
//
//class Data {
//public:
//	Data(int year=2026, int month=5, int day=5)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	Data(const Data& d)
//	{
//		_year = d._year;
//		_month = d._month;
//		_day = d._day;
//	}
//	void Print()
//	{
//		std::cout << _year << "_" << _month << "_" << _day << std::endl;
//	}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//
//};
//void func1(Data d)
//{
//	std::cout << "xiejunzhenshuai" << std::endl;
//}
//void func2(Stack d)
//{
//	std::cout << "谢军最帅" << std::endl;
//}
//int main()
//{
//	using namespace std;
//	//Data d1(1,1,1);
//	/*Data d2=d1;
//	d2.Print();*/
//	//func1(d1);
//	Stack p1;
//	p1.StackPush(1);
//	p1.StackPush(2);
//	Stack p2 = p1;
//	func2(p2);
//	return 0;
//}
using namespace std;
void test1()
{
	Date d1(2025, 5, 10);
	d1 += -31;
	d1.Print();
}
void test2()
{
	Date d1(2026, 2, 28);
	d1.Print();
}
void test3()
{
	Date d1(2026, 5, 10);
	Date d2(2026, 6, 7);
	int day = d2 - d2;
	cout << day << endl;

}
void test4()
{
	Date d1(2026, 6, 7);
	Date d2 = d1 + 30;
	cout << d1 << d2<<endl;
}
void test5()
{
	Date d1;
	Date d2;
	cin >> d1 >> d2;
	cout << d1 << d2;

}
void test6()
{
	const Date d1;
	d1.Print();
	cout << &d1;

}
int main()
{
	//Date d1(2026, 5, 5);
	//Date d2=d1-1;
	////d1 -= 10000;
	////d2 = d1;
	////d1 += 100;
	////d1.Print();
	//d1.Print();
	//d2.Print();
	//if (d2 > d1)
	//{
	//	cout << "d2>d1" << endl;
	//}
	//else if(d2==d1)
	//{
	//	cout << "d2=d1" << endl;
	//}
	//else
	//{
	//	cout << "d2<d1" << endl;
	//}
	//return 0;
	test6();
	return 0;
}
