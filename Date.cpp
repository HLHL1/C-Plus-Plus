#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<assert.h>
using namespace std;
class Date
{
public:

	//判断日期是否非法，合法返回false，非法返回true
	bool InvalidDate(int year, int month, int day)
	{
		if (year > 0 && \
			month > 0 && month <= 12 && \
			day > 0 && day <= GetMonthDay(year, month))//判断日期是否合法
		{
			return false;
		}
		return true;
	}


	//打印日期
	void Show()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
	//得到一个月的天数
	int GetMonthDay(int year, int month)
	{
		int monthday[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if ((month == 2) && \
			((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))//判断是否是闰年的二月
		{
			return 29;
		}
		return monthday[month];
	}
	//设置日期
	void SetDate(int year, int month, int day)
	{
		if (!InvalidDate(year, month, day))//判断日期是否合法
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "非法日期:" << year << "-" << month << "-" << day << endl;
		}
	}


	//构造函数(支持函数重载）
	//无参构造函数
	/*Date()
	{
	_year = 1990;
	_month = 1;
	_day = 1;
	cout << "Date()" << endl;
	}*/
	//类函数也可以在类外面定义，类里面声明
	//Date();

	//带参构造函数
	//Date(int year,int month,int day)
	//{
	//	assert(!InvalidDate(year, month, day));//检查日期是否合法
	//	_year = year;
	//	_month = month;
	//	_day = day;
	//	cout << "Date(int year,int month,int day)" << endl;
	//}

	//全缺省值构造函数就相当于把上面无参的构造函数和带参的构造函数合并在一起（但是全缺省值的构造函数不能和无参和带参的构造函数同时存在）
	Date(int year = 1990, int month = 1, int day = 1)
	{
		assert(!InvalidDate(year, month, day));//检查日期是否合法
		_year = year;
		_month = month;
		_day = day;
		cout << "Date(int year,int month,int day)" << endl;
	}

	//拷贝构造
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
		cout << "Date(Date& d)" << endl;
	}

	//析构函数:用来释放空间(一般动态申请的空间才会调用析构函数)
	~Date()
	{
		cout << "~Date()" << endl;
	}


	//运算符重载

	//operator=赋值
	//下段代码是有缺陷的，如果是自己给自己赋值呢(d1=d1)？如果连续赋值呢？(d1=d2=d3)
	/*void operator=(const Date& d)
	{
	_year = d._year;
	_month = d._month;
	_day = d._day;
	}*/

	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}


	//operator==判断两个日期是否相等
	bool operator==(const Date& d)
	{
		return (_year == d._year) && \
			(_month == d._month) && \
			(_day == d._day);
	}


	//d1>d2->operator(&d1,d2)
	bool operator>(const Date& d)
	{
		if (_year > d._year\
			|| (_year == d._year&&_month > d._month)\
			|| (_month == d._month&&_day > d._day))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//d1>=d2
	bool operator>=(const Date& d)
	{
		return (*this > d) || (*this == d);
	}
	//d1<d2
	bool operator<(const Date& d)
	{
		return !(*this >= d);
	}
	//d1<=d2
	bool operator<=(const Date& d)
	{
		return (*this < d) || (*this == d);
	}
	//d1!=d2
	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}


	Date operator+(int day)
	{
		if (day<0)
		{
			return *this - (-day);
		}
		Date d(*this);//拷贝构造
		d._day += day;
		while (d._day> GetMonthDay(d._year, d._month))
		{
			d._day -= GetMonthDay(d._year, d._month);
			d._month++;
			if (d._month > 12)
			{
				d._year++;
				d._month = 1;
			}
		}
		return d;
	}

	Date operator - (int day)
	{
		if (day<0)
		{
			return *this + (-day);
		}
		Date d(*this);//拷贝构造
		d._day -= day;
		while (d._day <= 0)
		{
			d._month--;
			if (d._month<1)
			{
				d._year--;
				d._month = 12;
			}
			d._day += GetMonthDay(d._year, d._month);
		}
		return d;
	}

	Date& operator += (int day)
	{
		return *this = *this + day;
	}
	Date& operator -= (int day)
	{
		return *this = *this - day;
	}
	int  operator - (const Date& d)
	{
		int daynum = 0;
		Date ret;
		if (*this <= d)
		{
			ret = *this;
			while (ret != d)
			{
				daynum++;
				ret += 1;
			}
			return -daynum;
		}
		else
		{
			ret = d;
			while (*this != ret)
			{
				daynum++;
				ret += 1;
			}
			return daynum;
		}
	}

	//前置++   ->d1.operator++(&d1)
	Date& operator++()
	{
		return *this += 1;
	}

	//后置++  ->d1.operator++(&d1,0)
	Date operator++(int)
	{
		Date ret(*this);
		*this += 1;
		return ret;
	}

	//前置--   ->d1.operator--(&d1)
	Date& operator--()
	{
		return *this -= 1;
	}

	//后置--    ->d1.operator--(&d1,0)
	Date operator--(int)
	{
		Date ret(*this);
		*this -= 1;
		return ret;
	}
	//私有的类成员变量不可以在类外面直接访问但是可以在类里面直接访问
private:
	int _year;
	int _month;
	int _day;
};
//Date::Date()
//{
//	_year = 1990;
//	_month = 1;
//	_day = 1;
//	cout << "Date()" << endl;
//}
void Test1()
{
	Date d1(2018, 6, 19);
	Date d2(2000, 6, 29);
	++d1;
	d1.Show();
	d2++;
	d2.Show();
	//cout << (d1-d2) << endl;
	/*d2 = d2-(-19);
	d2.Show();*/
	/*d1=d3 = d2;
	d3.Show();*/
	//cout << (d1.operator==(d2)) << endl;
	//cout << (d1 == d2) << endl;//(d1 == d2) 加括号考虑到运算符的优先级的问题
	//d1.Show();
	//Date d1(2018, 6, 18);//构造函数
	//Date d2(d1);//拷贝构造函数
	//d1.Show();
	//d2.Show();
	/*d1.Show();
	Date d2(2018, 6, 18);
	d2.Show();
	d1.SetDate(2018, 6, 18);
	d1.Show();
	d1.SetDate(2017, 2, 29);
	Date d3(2018, 2, 29);*/
}
int main()
{
	Test1();
	system("pause");
	return 0;
}
