#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <deque>


//class Base
//{
//public:
//	Base()
//	{
//		cout << "Base()" << endl;
//	}
//
//
//	//当使用dynamic_cast向下转型时，父类必须要含有虚析构函数
//	virtual ~Base()
//	{
//		cout << "~Base()" << endl;
//	}
//};
//
//class Dervise:public  Base
//{
//public:
//	Dervise()
//	{
//		cout << "Dervise()" << endl;
//	}
//
//	~Dervise()
//	{
//		cout << "~Dervise()" << endl;
//	}
//};
//
//
////使用dynamic_cast向下转型   RTTI
//
//int main()
//{
//	Base* pb=new Base;
//	Dervise* pd = dynamic_cast<Dervise*>(pb);
//	return 0;
//}


////函数重载
//
//int Add(int a, int b)
//{
//	return a + b;
//}
//
//float Add(float a, float b)
//{
//	return a + b;
//}
//
//
//int main()
//{
//	float a1 = 1.2;
//	float a2 = 3.4;
//	cout << Add(a1, 3.4) << endl;
//	return 0;
//}


//
//class A
//{
//public:
//	//缺省参数的构造函数
//	A(int a=10)
//	{
//		_a = a;
//	}
//
//	//拷贝构造函数
//	//如果参数不是引用，在调用拷贝构造函数时，会产生一份临时拷贝，临时拷贝又需要调用拷贝构造函数
//	//这样就会产生无限递归
//	A(const A& a)
//		:_a(a._a)
//	{}
//
//
//	//返回值设置成类的引用可以实现连等
//	A& operator=(const A& a)
//	{
//		_a = a._a;
//	}
//protected:
//	int _a;
//};
//
//
//int main()
//{
//	int a1 = 10;
//	A a(20);
//	A a2(a);
//	A a3(1);
//	a=a3 = a2;
//	return 0;
//}


//构造函数的初始化列表
//
//class A
//{
//public:
//	A(int a)
//		:_a(a)
//	{}
//private:
//	int _a;
//};
//
//
//class B
//{
//public:
//	B(A& pa, int b, int c, int d)
//		:a(pa)
//		, _c(c)
//		, _d(d)
//	{
//		b = _b;
//	}
//private:
//	A a;
//	int _b;
//	int& _c;
//	const int _d;
//};


//构造函数的初始化列表更高效

//class A
//{
//public:
//	A()
//	{
//		cout << "A()" << endl;
//		_a = 0;
//	}
//
//	A(const A& pa)
//		:_a(pa._a)
//	{
//		cout << "A(const A& pa)" << endl;
//	}
//
//	A& operator=(const A& pa)
//	{
//		cout << "operator(const A& pa)" << endl;
//		_a = pa._a;
//		return *this;
//	}
//
//	~A()
//	{
//		cout << "~A()" << endl;
//	}
//private:
//	int _a;
//};
//
//class B
//{
//public:
//	//构造函数初始化列表为什么高效？
//	//两步变一步  构造函数+赋值运算符重载->拷贝构造函数
//	B(const A& a)
//		//:_pa(a)
//	{
//	/*	cout << "构造函数初始化列表初始化" << endl;*/
//		cout << "常规初始化方式" << endl;
//		_pa = a;       //调用了构造函数
//	}
//private:
//	A _pa;
//};
//
//int main()
//{
//	A a;
//	B b(a);
//	return 0;
//}


//
//class A
//{
//public:
//	A(int a=10)
//		:_a(a)
//	{}
//
//	void setvalue(int a)
//	{
//		this->_a = a;
//		//this->show();
//	}
//
//	void show() const
//	{
//		cout << "the value is:" << this->_a << endl;
//	}
//private:
//	int _a;
//};
//
//
//int main()
//{
//	A a;           //非const对象
//	a.SetValue(20);
//	a.Show();
//
//	const A pa;
//	//pa.SetValue(20);   //const 对象不能调用非const 对象成员函数
//	pa.Show();           //const对象可以调用const成员函数
//	return 0;
//}

//友元类
//class Time
//{
//	//在一个类中将另一个类声明为友元类，那么
//	//被声明的这个类可以访问这个类中的任意成员
//	friend class Date;
//	int m_minute;
//	int m_hour;
//public:
//	Time(int hour=59, int minute=20)
//		:m_minute(hour)
//		, m_hour(minute)
//	{}
//
//	void Show() const
//	{
//		cout << this->m_hour << ":" << this->m_minute << endl;
//	}
//};
//
//
//class Date
//{
//	//友元函数
//	friend void Display(const Date& date);
//	int m_year;
//	int m_month;
//	int m_day;
//	Time m_t;
//public:
//	Date(int year = 1996,int month = 3, int day = 24)
//		:m_year(year)
//		, m_month(month)
//		, m_day(day)
//		, m_t(22,22)
//	{}
//
//	void Show()
//	{
//		cout << m_year << "-" << m_month << "-" << m_day << endl;
//		cout << m_t.m_hour << ":" << m_t.m_minute << endl;
//	}
//
//	//输入输出运算符重载函数必须要有返回值
//	friend ostream& operator<<(ostream& os,const Date& date)
//	{
//		os << date.m_year << "-" << date.m_month << "-" << date.m_day << endl;
//		return os;
//	}
//
//};
//
////友元函数不是类的成员函数
////友元函数可以通过对象来访问类的成员 
//void Display(const Date& date)
//{
//	cout << date.m_year << "-" << date.m_month << "-" << date.m_day << endl;
//}
//
//int main()
//{
//	Date d;
//	//Display(d);
//	//
//	//cout << (d) << endl;
//	d.Show();
//	return 0;
//}


//静态成员变量和静态成员函数
//class Student
//{
//public:
//	Student(char* name="leap", int age=21)
//		:_name(name)
//		, _age(age)
//	{
//		_count++;
//	}
//
//	void Show()
//	{
//		cout << "Num:" << this->_count << endl;
//		cout << "Name:" << _name << endl;
//		cout << "Age:" << _age << endl;
//	}
//
//
//	//静态成员函数只能访问静态成员变量
//	//不能够访问非静态成员变量
//	static void Print()
//	{
//		cout << _count << endl;
//	}
//public:
//	static int _count;
//private:
//	string _name;
//	int _age;
//};
//
//
////1.类的静态成员变量必须要在类外定义，在类中仅仅是声明
////2.类的静态成员变量属于整个类，而不是某一个对象
//
//int Student::_count ;
//
//int main()
//{
//	Student s1;
//	//s1.Show();
//	//cout << Student::_count << endl;
//	s1.Print();
//	Student::Print();
//	return 0;
//}

//
//class A
//{
//public:
//	A(int)
//	{}
//
//	A()
//	{};
//
//	void Fun()
//	{
//		cout << _a << endl;
//	}
//private:
//	int _a;
//};
//
//int main()
//{
//	A a(10);
//	a.Fun();
//	A b();
//	return 0;
//}

//
//int main()
//{
//	vector<int> v1;
//	v1.resize(10);
//	v1[0] = 1;
//	v1.at(11)=1;
//	return 0;
//}


//int main()
//{
//	int a[][2] = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
//	int *ptr =(int*) (&a + 1);
//	int *ptr1 = (int*)(a + 1);
//	int *ptr2 = a[0] + 1;         //
//	int *ptr3 = &a[0][0] + 1;     //
//
//	printf("%d\n", sizeof(double));
//	return 0;
//}
//
//class A {
//public:
//	int GetValue() const {
//	    vv = 1;
//		return vv;
//	}
//private:
//	mutable int vv;
//};
//
//int main()
//{
//	A a;
//	a.GetValue();
//	return 0;
//}


//struct A
//{
//	int a;
//	char data[0];
//};
//
//int main()
//{
//	printf("size=%d\n", sizeof(A));
//	A* a=new A;
//	a->data
//	return 0;
//}


//int main()
//{
//	//string str="abcdef";
//	//str[5] = 'c';
//	return 0;
//}



//错题
//#include <iostream>
//using namespace std;
//struct Foo {
//	Foo() {}
//	Foo(int) {}
//	void fun() {}
//};
//int main(void) {
//	Foo a(10); //语句1  
//	a.fun(); //语句2  
//	Foo b(); //语句3    编译器会认为语句3时一个函数声明，所以b对象并没有定义
//	b.fun(); //语句4  
//	return 0;
//	16.
//}

//int main()
//{
//	deque<int> q;
//	q.push_back(1);
//	cout << q[0] << endl;
//	return 0;
//}


//int main()
//{
//	int* p1 = (int*)malloc(sizeof(int)* 10);
//	for (int i = 0; i < 10; i++)
//	{
//		p1[i] = i;
//	}
//	int* p2 = (int*)realloc(p1, sizeof(int)* 20);
//	for (int i = 10; i < 20; i++)
//	{
//		p2[i] = i;
//	}
//
//
//	return 0;
//}

//
//struct A
//{
//	int m;
//};
//
//struct B
//{
//	~B()
//	{}
//
//	int m;
//};
//
//class C
//{
//	//C()
//	//:m()
//	//{}
//
//	//~C()
//	//{}
//protected:
//	int m;
//};
//
//int main()
//{
//	A* pa1 = new A;       //POD type
//	A* pa2 = new A();
//
//	B* pb1 = new B;       //non-pod
//	B* pb2 = new B();
//
//	C* pc1 = new C;      //non-pod
//	C* pc2 = new C();
//	return 0;
//}



//定位new表达式


//class Arr
//{
//public:
//	Arr(int size = 10)
//		:_size(10)
//		, _pArr(NULL)
//	{
//		cout << "Construct Function" << endl;
//		if (_size > 0)
//		{
//			_pArr = new int[_size]();
//		}
//	}
//private:
//	int _size;
//	int* _pArr;
//};
//
//int main()
//{
//	Arr* pArr = (Arr*)malloc(sizeof(Arr));
//	new(pArr) Arr(20);             //调用定位new表达式初始化对象
//	return 0;
//}