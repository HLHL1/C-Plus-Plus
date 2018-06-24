#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<string.h>

class String{
public:
	//构造函数
	String(const char* str="")
		:_str(new char[strlen(str)+1])
		, _CowNum(new int(0))
	{
		(*_CowNum)++;
		strcpy(_str, str);
	}

	//拷贝构造函数
	String(const String& s)
		:_str(s._str)
		, _CowNum(s._CowNum)
	{

		strcpy(_str, s._str);
		(*_CowNum)++;
	}

	//运算符赋值
	String& operator=(String& s)
	{
		if (_str !=(s._str))
		{
			if ((--(*_CowNum)) == 0)
			{
				delete[]_str;
				delete _CowNum;
			}
			_str = s._str;
			*(s._CowNum)++;
		}
		return *this;
	}

	//析构函数
	~String()
	{
		if (_str&&((--(*_CowNum))==0))
		{
			delete[]_str;
			delete _CowNum;
		}
	}
private:
	char * _str;
	int *  _CowNum;
};
void Test()
{
	String s1("Hello");
	String s2(s1);
	String s3(s2);
	String s4("world");
	s1 = s4;

}
int main()
{
	Test();
	system("pause");

	return 0;
}