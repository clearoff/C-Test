#include <iostream>
using namespace std;
#include <string>


struct  __TrueType
{
	bool  Get()
	{
		return  true;
	}
};
struct  __FalseType
{
	bool  Get()
	{
		return  false;
	}
};
template  <class  _Tp>
struct  TypeTraits
{
	typedef  __FalseType    __IsPODType;
};

//通过类的特化来把内置类型萃取为POD
template  <>
struct  TypeTraits<  bool>
{
	typedef  __TrueType       __IsPODType;
};
template  <>
struct  TypeTraits<  char>
{
	typedef  __TrueType       __IsPODType;
};
template  <>
struct  TypeTraits<  unsigned  char  >
{
	typedef  __TrueType       __IsPODType;
};
template  <>
struct  TypeTraits<  short>
{
	typedef  __TrueType       __IsPODType;
};
template  <>
struct  TypeTraits<  unsigned  short  >
{
	typedef  __TrueType       __IsPODType;
};
template  <>
struct  TypeTraits<  int>
{
	typedef  __TrueType       __IsPODType;
};
template  <>
struct  TypeTraits<  unsigned  int  >
{
	typedef  __TrueType       __IsPODType;
};

template  <>
struct  TypeTraits<  long>
{
	typedef  __TrueType       __IsPODType;
};

template  <>
struct  TypeTraits<  unsigned  long  >
{
	typedef  __TrueType       __IsPODType;
};

template  <>
struct  TypeTraits<  long  long  >
{
	typedef  __TrueType       __IsPODType;
};
template  <>
struct  TypeTraits<  unsigned  long  long>
{
	typedef  __TrueType       __IsPODType;
};
template  <>
struct  TypeTraits<  float>
{
	typedef  __TrueType       __IsPODType;
};
template  <>
struct  TypeTraits<  double>
{
	typedef  __TrueType       __IsPODType;
};
template  <>
struct  TypeTraits<  long  double  >
{
	typedef  __TrueType       __IsPODType;
};
template  <class  _Tp>
struct  TypeTraits<  _Tp*>
{
	typedef  __TrueType       __IsPODType;
};


template  <class  T>
void  Copy(const  T*  src, T*  dst, size_t  size, __FalseType)      //如果不含内嵌型别 那么选用最安全的拷贝方式(深拷贝)
{
	cout << "__FalseType:" << typeid(T).name() << endl;
	for (size_t i = 0; i < size; ++i)
	{
		dst[i] = src[i];
	}
}
template  <class  T>
void  Copy(const  T*  src, T*  dst, size_t  size, __TrueType)       //如果是内嵌型别，那么选用最高效的拷贝方式
{
	cout << "__TrueType:" << typeid(T).name() << endl;
	memcpy(dst, src, size*sizeof  (T));
}

  //使用萃取判断类型的Get函数判断是否是  POD类型来处理

template  <class  T>
void  Copy(const  T*  src, T*  dst, size_t  size)
{
	cout << "__TrueType:" << typeid(T).name() << endl;
	if (TypeTraits  <T>::__IsPODType().Get())
	{
		memcpy(dst, src, size*sizeof  (T));
	}
	else
	{
		//memcpy(dst, src, size*sizeof  (T));
		for (size_t i = 0; i < size; ++i)
		{
			dst[i] = src[i];
		}
	}
}
void  Test1()
{
	string  s1[10] = { "1", "2", "3", "4444444444444444444444444" };
	string  s2[10] = { "11", "22", "33" };
	Copy(s1, s2, 10, TypeTraits  <string>::__IsPODType());
	Copy(s1, s2, 10);
	int  a1[10] = { 1, 2, 3 };
	int  a2[10] = { 0 };
	Copy(a1, a2, 10, TypeTraits  <int>::__IsPODType());
	Copy(a1, a2, 10);
}

void test2()
{
	//int arr1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	//int arr2[10];
	string s1[] = { "aaaaa", "bbbbb", "cccccc", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" };
	for (int i = 0; i < sizeof(s1) / sizeof(s1[0]); i++)
	{
		cout << s1[i] << " ";
	}
	cout << endl;
	string s2[4];
	Copy(s1, s2, 4);
	for (int i = 0; i < sizeof(s2) / sizeof(s2[0]); i++)
	{
		cout << s2[i] << " ";
	}
	cout << endl;
}
int main()
{
	Test1();
	test2();
	return 0;
}


