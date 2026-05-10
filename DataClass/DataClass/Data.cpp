#define _CRT_SECURE_NO_WARNINGS 1
#include"Data.h"
//构造函数
Date::Date(int year, int month, int day)
{
	assert((month > 0 && month <= 12) && (day <= GetMonthDay(year, month)));
	_year = year;
	_month = month;
	_day = day;
}
//拷贝构造
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}
//打印
void Date::Print()const
{
	std::cout <<_year << "_" << _month << "_" << _day << std::endl;
}
//+=运算符重载
Date& Date:: operator+=(int day)
{
	if (day < 0) {
		return operator-=(-day);
	}

	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month == 13)
		{
			_year++;
			_month = 1;
		}
	}
	return *this;
}
//+运算符重载
Date Date:: operator+(int day)const
{
	Date tmp = *this;
	/*tmp._day += day;
	while (tmp._day > GetMonthDay(tmp._year, tmp._month))
	{
		tmp._day -= GetMonthDay(tmp._year, tmp._month);
		tmp._month++;
		if (tmp._month == 13)
		{
			tmp._month = 1;
			tmp._year++;
		}
	}*/
	tmp += day;
	return tmp;
}
////-运算符重载
//Date Date::operator-(int day)
//{
//	Date tmp = *this;
//	tmp._day -= day;
//	while (tmp._day <= 0)
//	{
//		tmp._month--;
//		//tmp._day += GetMonthDay(tmp._year, tmp._month);这里是错误的如果month==0就蛋糕了
//		if (tmp._month == 0)
//		{
//			tmp._year--;
//			tmp._month = 12;
//		}
//		tmp._day += GetMonthDay(tmp._year, tmp._month);
//	}
//	return tmp;
//}
//赋值重载
Date& Date::operator=(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
	return *this;
}
//-=运算符重载
Date& Date::operator-=(int day)
{
	if (day < 0) {
		return operator+=(-day);
	}
	_day -= day;
	while (_day <= 0)
	{
		_month--;
		if (_month == 0)
		{
			_year--;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}
	return*this;
}
// 日期-天数

Date Date::operator-(int day)const
{
	Date tmp = *this;
	tmp -= day;
	return tmp;
}

//>运算符重载
bool Date::operator>(const Date& d)const
{
	/*if (_year > d._year)
		return true;
	else if (_year == d._year)
	{
		if (_month > d._month)
			return true;
		else if (_month == d._month)
		{
			if (_day > d._day)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;*/
	if (_year != d._year)
		return _year > d._year;
	if (_month != d._month)
		return _month > d._month;
	return _day > d._day;
}
//==运算符重载
bool Date::operator==(const Date& d)const
{
	return _year == d._year && _month == d._month && _day == d._day;
}
//>=运算符重载
bool Date::operator >= (const Date& d)const
{
	if (_year != d._year)
		return _year > d._year;
	if (_month != d._month)
		return _month > d._month;
	return _day >= d._day;
}
//前置++
Date& Date::operator++()
{
	*this+=1;
	return *this;
}
//后置++
Date Date::operator++(int)
{
	Date tmp = *this;
	*this += 1;
	return tmp;
}

// 后置--

Date Date::operator--(int)
{
	Date tmp = *this;
	*this -= 1;
	return tmp;
}

// 前置--

Date& Date::operator--()
{
	return *this -= 1;
}

// <运算符重载

bool Date::operator < (const Date& d)const
{
	return !operator>=(d);
}

// <=运算符重载

bool Date::operator <= (const Date& d)const
{
	return !operator>(d);
}


// !=运算符重载

bool Date::operator != (const Date& d)const
{
	return !operator==(d);
}

int Date::operator-(const Date& d)const
{
	Date min = d;
	Date max = *this;
	int flag = 1;
	if (*this < d)
	{
		min = *this;
		max = d;
		flag = -1;
	}
	int n = 0;
	while (min != max)
	{
		++min;
		++n;
	}
	return n * flag;
}

ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "年" << d._month << "月" << d._day << "日"<<endl;
	return out;
}

istream& operator>>(istream& in,  Date& d)
{
	while (1)
	{
		cout << "请输入年月日" << endl;
		in >> d._year >> d._month >> d._day;
		if (d._month <= 0 || d._month > 12 || d._day > d.GetMonthDay(d._year, d._month))
		{
			cout << "输入日期非法，请重新输入";
		}
		else
			break;
	}
	return in;
}
