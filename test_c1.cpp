#include <iostream>
using namespace std;
#include <string>

//class Person
//{
//public:
//	Person(const char*  name)
//		:_name(name)
//	{
//			cout<< " Person()"  <<endl;
//	}
//	Person(const Person& p)
//		:_name(p._name)
//	{
//			cout<< " Person(const   Person&   p)"<<endl;
//		
//	}
//	Person& operator=(const Person&  p)
//	{
//		cout<< " Person  operator = (const  Person&   p)"<<endl;
//		if (this!= &p)
//		{
//			_name = p._name;
//		}
//		return  *this;
//	}
//	~Person()
//	{
//		cout<< "~ Per s on()"<<endl;
//	}
//protected:
//	string  _name;             // 姓名
//};
//
//class Student:public Person
//{
//public:
//	Student(const char* name, int   num)
//		: Person(name)
//		,_num(num)
//	{
//			cout << " Student ()"  <<endl;
//		
//	}
//
//	Student(const   Student& s)
//		: Person(s)
//		, _num(s._num)
//	{
//			cout<< " S t udent (cons t   S t udent &   s )" <<endl;
//		}
//
//	Student& operator = (const Student& s)
//	{
//		cout << " Student& operator = (const Student& s )"<<endl;
//		if (this!= &s)
//		{
//			Person::operator = (s);
//			_num = s._num;
//		}
//		return  *this;
//	}
//
//	~Student()
//	{
//		cout << "~ Student ()"  << endl;
//	}
//private :
//	int   _num;             //学号
//};
//void  Test()
//{
//	Student   s1   ("jack",18);
//	Student   s2   (s1);
//	Student   s3   ("rose",17);
//	s1 = s3;
//}



//虚函数的作用
//class A
//{
//public:
//	A(int a=10)
//		:_a(a)
//	{
//		cout << "A()" << endl;
//	}
//	A(const A& a)
//	{
//		_a = a._a;
//		cout << "A(const A& a)" << endl;
//	}
//
//	virtual void Fun()
//	{
//		cout << "A::Fun()" << endl;
//	}
//
//protected:
//	int _a;
//};
//class B :public A
//{
//public:
//	B(const int& a=10,const int& b=20)
//		:A(a)
//		, _b(b)
//	{
//		cout << "B()" << endl;
//	}
//
//	B(const B& b)
//	{
//		_b = b._b;
//		A::_a = b._a;
//		cout << "B(const B& b)" << endl;
//	}
//
//
//	void Fun()
//	{
//		cout << _a << endl;
//		cout << "B::Fun()" << endl;
//	}
//private:
//	int _b;
//};


//class Base
//{
//public:
//	Base()
//		:_b(10)
//	{
//		cout << "Base()" << endl;
//	}
//
//	virtual void Fun(int)
//	{
//		cout << "Base::Fun()" << endl;
//	}
//
//	virtual ~Base()
//	{
//		cout << "~Base()" << endl;
//	}
//protected:
//	int _b;
//};
//class Dervise :public Base
//{
//public:
//	Dervise()
//		:_d(20)
//	{}
//
//	void Fun(int)
//	{
//		cout << "Dervise::Fun(int)" << endl;
//	}
//
//	virtual ~Dervise()
//	{
//		cout << "~Dervised()" << endl;
//	}
//protected:
//	int _d;
//};

class Base
{
public:
	Base()
	{}

	virtual Base* Fun()
	{
		cout << "Fun()::Base" << endl;
		return new Base();
	}
protected:
	int _b;
};
class Dervise :public Base
{

public:
	Dervise()
	{}

	virtual Dervise* Fun()
	{
		cout << "Fun()::Dervise" << endl;
		return new Dervise();
	}
protected:
	int _d;
};
void Fun(Base& p)
{
	cout<<sizeof(p)<<"----->";
	p.Fun();
}

int main()
{
	Base b;
	Dervise d;
	cout << sizeof(b) << endl;
	cout << sizeof(d) << endl;
	Fun(b);
	Fun(d);
	return 0;
}