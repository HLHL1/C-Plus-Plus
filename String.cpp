#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<string.h>
#include<assert.h>
using namespace std;

//管理字符串的类
class String{

public:
	//构造函数（这个只是让_str和str指针指向同一块空间）
	//String(char* str)
	//	:_str(str)//如果传过来的是字符串常量就不能改变其内容
	//{
	//}

	//构造函数
	String (char* str="")//缺省参数给个空串，防止不传参构造时程序可能崩溃问题
		:_str(new char[strlen(str)+1])//开辟空间
		, _size(strlen(str))
		, _capacity(_size )
	{
		strcpy(_str, str);
	}

	//拷贝构造（浅拷贝）
	//String(const String& s)
	//	:_str(s._str)//_str和str_str指针指向同一块空间，修改一个另一个也会被修改，重要的bug是一块空间析构两次，是程序崩溃
	//{

	//}
	//拷贝构造（深拷贝）
	String(const String & s)
		:_str(new char[strlen(s._str)+1])
		, _size(strlen(s._str))
		, _capacity(_size)
	{
		strcpy(_str, s._str);
	}

	//运算符赋值->s1=s2(深拷贝）
	String&operator=(const String& s)
	{
		if (this != &s)
		{
			delete[]_str;
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
			_size=strlen(s._str);
			_capacity = (_size);
		}
		return *this;
	}
	//析构函数
	~String()
	{
		if (_str)
		{
			delete[]_str;
			_str = NULL;
			_size = 0;
			_capacity = 0;
		}
	}

	//重载运算符[](功能类似于数组，可以随意访问字符）
	char& operator[](size_t pos)
	{
		assert(pos < strlen(_str));
		return _str[pos];
	}

	//打印
	char* c_str()
	{
		return _str;
	}
	

	//增容到n
	void Reserve(size_t n, char ch = '0')
	{
		if (n > _capacity)
		{
			_Expand(n);
		}
	}


	//增容并且初始化
	void Resize(size_t n, char ch = '0')
	{
		if (n<_size)//缩容
		{
			_size = n;
			_str[_size] = '\0';
		}
		if (n>_capacity)
		{
			_Expand(n);
		}
		for (int i = _size; i < n; i++)
		{
			_str[i] = ch;
		}
		_size = n;
		_str[_size] = '\0';
	}

	//插入一个字符
	void PushBack(char ch)
	{
		if (_size == _capacity)
		{
			_Expand(_capacity*2);
		}
		_str[_size] = ch;
		_size++;
		_str[_size] = '\0';
	}
	//插入一个字符串
	void Append(const char* str)
	{
		int len = strlen(str);
		if (_size + len > _capacity)
		{
			_Expand(_size + len);
		}
		strcpy(_str + _size, str);
		_size += len;
	}
	//s1+"111"
	String operator+(const char*s)
	{
		String ret(*this);
		ret.Append(s);
		return ret;
	}
	//s1+="111"
	String& operator+=(const char*s)
	{
		Append(s);
		return *this;
	}

	//删除最后一个字符串
	void push()
	{
		assert(_size > 0);
		--_size;
		_str[_size] = '\0';
	}
	//在指定的位置插入一个字符
	void Insert(size_t pos,char ch)
	{
		assert(pos<=_size);
		if (_size == _capacity)
		{
			_Expand(_capacity * 2);
		}
		for (int i = _size+1; i > pos; i--)
		{
			_str[i] = _str[i - 1];
		}
		_str[pos] = ch;
		_size++;
	}
	//在指定位置插入一段字符串
	void Insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		int len = strlen(str);
		if (_size + len > _capacity)
		{
			_Expand(_capacity * 2);
		}
		for (int i = _size + len; i >= pos + len; i--)
		{
			_str[i] = _str[i - len];
		}
		int j = 0;
		for (int i = pos; i<pos + len; i++)
		{
			_str[i] = str[j++];
		}
		_size += len;
	}
	//在指定位置删除定长的字符串
	void Erase(size_t pos, size_t len = 1)
	{
		assert(pos <= _size);
		if (len >= _size - pos)
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			for (int i = pos; i <= _size - len; i++)
			{
				_str[i] = _str[i + len];
			}
			_size -= len;
		}

	}


	//寻找字符->找到返回下标，找不到返回-1
	size_t Find(char ch)const
	{
		for (int i = 0; i < _size; i++)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return -1;
	}

	//寻找子串->找到返回下标，找不到返回-1
	size_t Find(const char* sub)const
	{
		int len = strlen(sub);
		if (len > _size)
		{
			return -1;
		}
		else
		{
			for (int i = 0; i <= _size - len; i++)
			{
				int j = 0;
				int k = i;
				while ((sub[j]!='\0')&&(_str[k] == sub[j]))
				{
					k++;
					j++;
				}
				if (sub[j] == '\0')
				{
					return i;
				}
			}
		}
		return -1;
	}

	//比较两个字符串的大小
	bool operator<(const String&s)
	{
		const char* str1 = _str;
		const char* str2 = s._str;
		while ((*str1) && (*str2))
		{
			if (*str1<*str2)
			{
				return true;
			}
			else
			{
				if (*str1 == *str2)
				{
					str1++;
					str2++;
				}
				else
				{
					return false;
				}
			}
		}
		if (((*str1) == '\0') && ((*str2) != '\0'))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator<=(const String&s)
	{
		return (*this < s) || (*this == s);
	}
	bool operator==(const String&s)
	{
		const char* str1 = _str;
		const char* str2 = s._str;
		while ((*str1) && (*str2))
		{
			if ((*str1) != (*str2))
			{
				return false;
			}
			else
			{
				str1++;
				str2++;
			}
		}
		if (((*str1) == '\0') && ((*str2) == '\0'))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator!=(const String&s)
	{
		return !(*this == s);
	}

	bool operator>(const String&s)
	{
		return !(*this <= s);
	}

	bool operator>=(const String&s)
	{
		return !(*this < s);
	}
private:
	char* _str;
	size_t _size;
	size_t _capacity;
	//扩容
	void _Expand(size_t n)
	{
		if (n>_capacity)
		{
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete[]_str;
			_str = tmp;
			_capacity = n;
		}
	}

};
void Test()
{
	String s1("abcdef");
	String s2("bbc");
	cout << s1.Find("def") << endl;
	//cout << (s1<= s2) << endl;
	/*s2 = s1;
	s2.Insert(2,"WWWW");
	s1.Erase(1,2 );*/
	/*s1.PushBack('W');
	s1.Append(" world");*/
	/*s2 = s1 + "111";
	s1 += "1213";*/
	cout << s1.c_str() << endl;
	cout << s2.c_str() << endl;
	/*String s2(s1);
	s2 = s1;
	s1[1] = 'M';
	cout << s1[1] << endl;*/
	//String s1("Hello");//字符串常量不能修改
	//char* p1 = new char[10];
	//p1 = "World";
	//String s2(p1);//堆上开辟了一段空间，可以修改
}
int main()
{
	Test();
	system("pause");
	return 0;
}