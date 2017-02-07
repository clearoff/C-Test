#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;


class String
{
public:
	String()
		:_len(0)
		, _data(new char(1))
	{}

	String(const char* str)
		:_len(strlen(str))
	{
		_data = new char[_len + 1 + 1];
		_data[0] = 1;
		strcpy(_data+1, str);
	}

	bool operator==(const String& rhs)
	{
		return this->_data == rhs.C_str();
	}

	bool operator!=(const String& rhs)
	{
		return !(this->operator==(rhs));
	}

	String(const String& rhs)
	{
		if (*this != rhs)
		{
			this->_data = rhs._data;
			_data[0]++;
			_len = rhs._len;
		}
	}

	String& operator=(const String& rhs)
	{

		if (*this != rhs)
		{
			this->~String();      //

			this->_data = rhs._data;
			_data[0]++;
			_len = rhs._len;
		}

		return *this;
	}

	int RefCount() const
	{
		return _data[0] - 0;
	}

	const char* C_str() const
	{
		return this->_data+1;
	}

	char& operator[](size_t index)
	{
		index = index + 1;
		if (index < 0 || index > _len+1||_data==NULL)
		{
			static char nullchar = 0;
			return nullchar;
		}

		_data[0]--;
		char* tmp = new char[_len + 1+1];
		strcpy(tmp+1, _data+1);
		_data = tmp;
		_data[0] = 1;

		return _data[index];
	}


	//write
	String& append(const char* str)
	{
		_data[0]--;    //引用计数减一
		char* tmp = new char[_len + 1 + 1+ strlen(str)];  //重新开辟空间
		strcpy(tmp + 1, _data + 1);
		_data = tmp;
		_data[0] = 1;
		strcpy(_data + _len + 1, str);

		return *this;
	}

	friend ostream& operator<<(ostream& os, const String& rhs)
	{
		os << rhs.C_str();
		return os;
	}

	size_t Size() 
	{
		return _len;
	}

	~String()        //？？？
	{
		_data[0]--;
		if (_data[0] <= 0)
		{
			cout << "Free Memory\n";
			delete[] _data;
		}
	}
protected:
	size_t _len;
	char* _data;
};

int main()
{
	String str("leap");
	cout << str.C_str()<<endl;
	String str1(str);
	String str2("Hehe");
	str2 = str1;
	cout << str2.RefCount() << endl;
	for (int i = 0; i < str2.Size(); i++)
	{
		cout << str2[i];
	}
	cout << endl;

	str2.append(" hehe");
	cout << str2 << endl;
	return 0;
}