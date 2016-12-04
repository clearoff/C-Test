//#include <iostream>
//using namespace std;
//#include <boost\shared_ptr.hpp>
//using namespace boost;
////#include <memory>
//
//struct ListNode
//{
//	shared_ptr<ListNode> next;
//	shared_ptr<ListNode> prev;
//
//	ListNode(const int& a)
//		:_a(a)
//	{}
//
//	int _a;
//
//	~ListNode()
//	{
//		cout << "~ListNode()" << endl;
//	}
//};
//
//void Test()
//{
//	shared_ptr<ListNode> p1(new ListNode(5));
//	shared_ptr<ListNode> p2(new ListNode(6));
//
//	p1->next = p2;
//	p2->prev = p1;
//
//
//}
//
//int main()
//{
//	//shared_ptr<int> p1(new int(5));
//	//int *q = p1.get();
//	//cout << *q << endl;
//	//delete q;            //p1所指向的内存也被释放，并且指向一块随机值
//
//	//unique_ptr<int> p2 = new int(5);      //error 
//	//unique_ptr<int> p2(new int(5));
//	////unique_ptr<int> p3(p2);              //error unique_ptr不支持拷贝构造和运算符重载
//	////unique_ptr<int> p3 = p2;
//	//p2.release();
//	/*Test();*/
//	int a = 5;
//	shared_ptr<int> p1(&a);
//	shared_ptr<int> p2(&a);
//
//	return 0;
//}


//
//#include<iostream>
//using namespace std;
//
//class A
//{
//public:
//	A()
//		:_a(10)
//	{}
//protected:
//	int _a;
//};
//
//class B :public A
//{
//public :
//	B()
//		:_b(5)
//	{}
//protected:
//	int _b;
//};
//
//template<class Base=A,class Derive=B>
//bool IsDerived(const Base* a, const Derive* b)
//{
//	Derive* c;
//	c=dynamic_cast<Derive>(a);
//	if (c == NULL)
//	{
//		return false;
//	}
//	else
//		return true;
//}
//
//int main()
//{
//	A a;
//	B b;
//	cout<<IsDerived(&a,&b)<<endl;
//	return 0;
//}

////判断一个类能否被另一个类继承
#include<iostream>
using namespace std;

class A
{
public:
	A()
		:_a(10)
	{}
protected:
	int _a;
};

class B :public A
{
public:
	B()
		:_b(20)
	{}
protected:
	int _b;
};

template<typename Derive, typename Base> 
class IsDerived
{
public:
	static int t(Base* base)        //如果子类的父类是Base类则能进入这个函数
	{
		return 1;            //返回int类型的临时变量
	}
	static char t(void* t2)       //除了Base类的其他对象会自动调用这个函数
	{
		return 0;            //返回一个char类型的临时变量
	}

	static bool IsDerive()
	{
		/*bool Result = (sizeof(int) == sizeof(t((Derive*)NULL)));*/
		bool Result = (sizeof(int) == sizeof(t(new Derive())));  //这里比较两个变量的大小从而确定是否存在继承关系
		return Result;
	};
};


int main()
{
	bool   AISDerviedFromB;
	AISDerviedFromB= IsDerived<B, A>::IsDerive();
	cout << AISDerviedFromB << endl;
	return 0;
}



////C++11定义一个不能被继承的类
//#include <iostream>
//using namespace std;
//
//class A 
//{
//private:
//	~A()
//	{}
//
//	A()
//		:_a(10)
//	{}
//protected:
//	int _a;
//};
//
////class B :public A   //error
////{
////
////};
//
//
//int main()
//{
//	A b;
//	return 0;
//}