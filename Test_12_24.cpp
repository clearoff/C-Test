#include <iostream>
using namespace std;
#include <cassert>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
using namespace boost;


//void* MyMemmove(void* dst,const void* src,const size_t size)
//{
//	assert(dst);
//	assert(src);
//
//	char* _dst = (char*)dst;
//	char* _src = (char*)src;
//
//	if (size == 0)
//	{
//		return NULL;
//	}
//	//从前向后拷贝的情况
//	//memmove()
//	if (_dst <= _src || _dst > (_src + size))
//	{
//		for (size_t i = 0; i < size; i++)
//		{
//			*_dst = *_src;
//			_dst++;
//			_src++;
//		}
//	}
//	else
//	{
//		//从后向前拷贝的情况
//		_dst = _dst + size-1;
//		_src = _src + size-1;
//		for (size_t i = 0; i < size; i++)
//		{
//			*_dst = *_src;
//			_dst--;
//			_src--;
//		}
//	}
//	return _dst;
//}
//
//
//void TestMemmove()
//{
//	char a[] = "abcdef";
//	char b[10] = { 0 };
//	MyMemmove(b, a, sizeof(a)/sizeof(a[0]));
//	for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); i++)
//	{
//		cout << b[i] << " ";
//	}
//	cout << endl;
//	MyMemmove(a+3, a, 3);
//	//memmove(a + 3, a, 3);
//	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
//	{
//		cout << a[i] << " ";
//	}
//	cout << endl;
//}

//void TestSmartPtr()
//{
//	/*int a = 10;*/
//	unique_ptr<int> pa(new int(1));
//	//unique_ptr<int> pa1(pa);   不能够拷贝构造
//	unique_ptr<int> pa2(new int(10));
//	//pa2 = pa;                   不能够进行赋值运算符重载
//}


////返回一个动态开辟vector
//vector<int> ReturnVector(const int* a,size_t size)
//{
//	 /*vector<int> tmp(a, a + size);*/
//	//vector<int>* tmp = new vector<int>(a, a + size);  //在这里tmp的内存没有被释放
//	auto tmp = make_shared<vector<int>>(a, a + size);
//	 return *tmp;
//}
//
//vector<int>	ReadVector(const vector<int>& v)
//{
//	//vector<int> tmp(v.begin(), v.end());
//	auto tmp = make_shared<vector<int>>(v.begin(),v.end());
//	return *tmp;
//}
//
//void PrintVector(vector<int>& v)
//{
//	vector<int>::const_iterator it = v.cbegin();
//	while (it != v.cend())
//	{
//		cout << *it << " ";
//		it++;
//	}
//	cout << endl;
//}


//void TestPrimer()
//{
//	int a[] = { 1, 2, 3, 4, 5, 6 };
//	vector<int> v1 = ReturnVector(a, sizeof(a) / sizeof(a[0]));
//	for (size_t i = 0; i < v1.size(); i++)
//	{
//		cout << v1[i] << " ";
//	}
//	cout << endl;
//	ReadVector(v1);
//	PrintVector(v1);
//}


//template<class T>
//void Delete(T* _del)
//{
//	cout << "使用定制删除器删除对象" << endl;
//	delete _del;
//}
//
//void Func()
//{
//	shared_ptr<int> p1(new int(1), Delete<int>);
//}

//void TestUniquePtr()
//{
//	//unique_ptr<int> p1(new int(1));
//	//unique_ptr<int> p2(p1.release());      //release返回p1所指向的内存空间，并将p1置为NULL
//	//cout << *p2 << endl;
//
//	unique_ptr<string> p1(new string("hehe"));
//	unique_ptr<string> p2(new string("haha"));
//	cout <<"p2->data::"<< *p2 << endl;
//	p2.reset(p1.release());					//会释放p2原来所指向的内存空间的内存，并把p1所指向的内存空间赋值给p2
//	cout << "p2->data::" << *p2 << endl;
//}

//循环引用问题
struct ListNode
{
	boost::weak_ptr<ListNode> _prev;
	boost::weak_ptr<ListNode> _next;
	int _data;

	ListNode()
		:_data(0)
	{}

	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};

void TestWeakPtr()
{
	boost::shared_ptr<ListNode> sp1(new ListNode);
	boost::shared_ptr<ListNode> sp2(new ListNode);

	cout <<	"p1的引用计数::"<< sp1.use_count() << endl;
	cout << "p2的引用计数::" << sp2.use_count() << endl;

	sp1->_next = sp2;
	sp2->_prev = sp1;

	cout << "p1的引用计数::" << sp1.use_count() << endl;
	cout << "p2的引用计数::" << sp2.use_count() << endl;
}
int main()
{
	TestWeakPtr();
	return 0;
}