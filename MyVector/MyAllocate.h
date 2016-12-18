#pragma once 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <cstdlib>
#include <cassert>
#include <stdarg.h>
#include <vector>

#define __DEBUG__
FILE* fo = fopen("Trace.log", "w");
static string  GetFileName(const string&  path)
{
	char ch ='/';
#ifdef _WIN32
	ch = '\\';
#endif
	size_t  pos = path.rfind(ch);
	if(pos == string::npos)
		return path;
	else
		return path.substr(pos + 1);
}
//用于调试追溯的trace  log
inline  static  void  __trace_debug(const  char*  function,const  char*  filename, int  line, char* format,...)
{
#ifdef __DEBUG__
	//输出调用函数的信息
	fprintf(stdout,"【%s: %d】%s",GetFileName(filename).c_str(), line, function);
	fprintf(fo,"【%s: %d】%s",GetFileName(filename).c_str(), line, function);
	//输出用户打的trace信息
	va_list args;
	va_start(args, format);
	vfprintf (stdout, format, args);
	vfprintf(fo, format, args);
	va_end(args);
#endif
}
#define __TRACE_DEBUG(...) __trace_debug(__FUNCTION__, __FILE__, __LINE__, __VA_ARGS__);

typedef void(*ALLOC_COM_FUN)();
template <int inst>
class _MallocAllocTemplate
{
	static ALLOC_COM_FUN  _MallocAllocOomHandler;    /*static void(*__MallocAllocOomHandler)();*/
private:
	static void* OomMalloc(size_t n)          //处理内存不足的函数
	{
		ALLOC_COM_FUN MyMallocHanlder = 0;   // _MallocAllocOomHandler;
		void* result;

		while (1)
		{
			MyMallocHanlder = _MallocAllocOomHandler;
			if (MyMallocHanlder == 0)
			{
				cout << "out of memory" << endl;
				exit(-1);
			}
			(*MyMallocHanlder)();
			
			result = malloc(n);
			if (result != 0)
				return result;
		}
	}
public:
	static void * allocate(size_t n)
	{
		__TRACE_DEBUG("使用一级空间配置器分配%uBytes个空间\n", n);
		assert(n >= 0);
		void* result = malloc(n);
		if (result == 0)
		{
			OomMalloc(n);                  //如果内存开辟失败调用内存不足处理函数
		}
		return result;
	}

	static void deallocate(void *p, size_t  n)
	{
		__TRACE_DEBUG("使用一级空间配置器释放%uBytes个空间---0x%p \n", n,p);
		free(p);
		p = NULL;
	}

	static void(*set_malloc_handler(void(*f)()))()  //set_malloc_handler(void(*f)())
	{
		ALLOC_COM_FUN Old = _MallocAllocOomHandler;
		_MallocAllocOomHandler = f;
		return old;
	}
};

template<int inst>
ALLOC_COM_FUN _MallocAllocTemplate<inst>::_MallocAllocOomHandler = 0;      //对句柄进行初始化


template <bool threads, int inst>
class __DefaultAllocTemplate
{
	enum { _ALIGN = 8 };                        //FreeList[]排列间隔
	enum { _MAXBYTES = 128 };                   //FreeList bytes最大值
	enum { _NFREELISTS = _MAXBYTES / _ALIGN };  //FreeList 大小

	static size_t RoundUP(size_t bytes)          //提升至8的倍数
	{
		return (((bytes)+_ALIGN - 1) & ~(_ALIGN - 1));
	}

	static  size_t FreeListIndex(size_t bytes)    //返回 bytes对应的自由链表的index
	{
		return ((bytes+_ALIGN-1)/_ALIGN-1);
	}

	union Obj
	{
		union Obj* _FreeListLink;               //指向自由链表节点的指针
		char client_data[1];                    /* The client sees this */
	};

protected:
	static Obj* volatile  _FreeList[_NFREELISTS];     //自由链表
	static char* _StartFree;                          //内存池中指向内存池可用空间首地址的指针
	static char* _EndFree;                            //内存池中指向内存池末尾的指针
	static size_t _HeapSize;                          //内存池中空间的大小
public:
	static void* allocate(size_t n)
	{
		__TRACE_DEBUG("使用二级空间配置器分配%u Bytes个空间\n", n);
		if (n > 128)        //要开辟空间的字节数大于128调用一级空间配置器
		{
			void* result = _MallocAllocTemplate<0>::allocate(n);
			return result;
		}
		//如果要开辟的字节数 <=128 bytes  则调用第二季空间配置器
		size_t index = FreeListIndex(RoundUP(n));         //找到自由链表序列对应的下标
		Obj* volatile* MyFreeList = _FreeList + index;
		Obj* head= *MyFreeList;
		if (head == 0)
		{
			void* ret = Refill(RoundUP(n));
			return ret;
		}
		*MyFreeList = head-> _FreeListLink;
		return head;
	}

	static void deallocate(void *p, size_t n)
	{
		__TRACE_DEBUG("使用一级空间配置器释放%uBytes个空间---0x%p \n", n, p);
		Obj* q = (Obj*) p;

		if (n > _MAXBYTES)
		{
			//调用第一级空间配置器
			_MallocAllocTemplate<0>::deallocate(p,n);
			return;
		}

		size_t index = FreeListIndex(n);
		//将要释放的对象的空间直接头插在相应的自由链表下
		q->_FreeListLink = _FreeList[index];
		_FreeList[index] = q;
	}

	static void* Refill(size_t n)
	{
		__TRACE_DEBUG("使用二级空间配置器向内存池申请%uBytes个空间\n", n);
		Obj* volatile* MyFreeList = NULL;
		int nojbs = 20;                 //在这里直接开辟20个自由链表的节点
		Obj* result = NULL;
		char* chunck = ChuncAlloc(n,nojbs);

		if (nojbs == 1)
			return chunck;            //如果ChuncAlloc只开辟了一个nbytes的自由链表节点，则直接返还给对象使用

		size_t index = FreeListIndex(n);
		Obj* CurrentObj=NULL, *NextObj=NULL;

		result = (Obj*)chunck;        

		//把从ChunckAlloc获得的内存块链在对应的freelist下面
		_FreeList[index] = NextObj = (Obj*)(chunck + n);
		for (int i = 2; i < nojbs; i++)
		{
			CurrentObj = NextObj;
			NextObj= (Obj*)((char*)NextObj + n);
			CurrentObj-> _FreeListLink = NextObj;
		}
		NextObj->_FreeListLink = NULL;
		return result;
	}

	//从内存池中开辟大块内存
	static char* ChuncAlloc(size_t n, int& nojbs)
	{
		__TRACE_DEBUG("使用二级空间配置器向内存池申请%uBytes个空间\n", n*nojbs);
		char* result=NULL;
		size_t totalBytes = n*nojbs;                     //要向内存池申请的内存的大小
		size_t leftBytes = _EndFree - _StartFree;        //内存池中剩余的内存的大小

		if (leftBytes >= totalBytes)                       //直接向内存池申请
		{
			__TRACE_DEBUG("内存池分配%d个对象\n",nojbs);
			result = _StartFree;
			_StartFree += totalBytes;                   //改变内存池中指针的位置
			return result;
		}
		if (leftBytes >= n)                              //如果内存池剩余的内存的大小大于一个对象所需要的内存，则直接向内存池申请
		{
			__TRACE_DEBUG("内存池只能分配%d个对象\n", nojbs);
			result = _StartFree;
			nojbs = leftBytes / n;
			_StartFree += nojbs*n;
			return result;
		}
		else                                         //内存池中剩余的内存不够一个对象所使用的，需要向操作系统进行申请
		{ 
			size_t GetBytes = 2 * totalBytes + RoundUP(_HeapSize >> 4);      //向操作系统所申请的内存的大小

			if (leftBytes > 0)                       //把内存池中剩余的内存挂在相应的自由链表下
			{
				//头插
				size_t index = FreeListIndex(RoundUP(leftBytes));
				((Obj*)_StartFree)->_FreeListLink = _FreeList[index];  
				_FreeList[index] = (Obj*)_StartFree;
			}
			_StartFree = (char*)malloc(GetBytes);          //内存池向malloc申请内存

			if (_StartFree == 0)
			{
				//如果申请内存失败，向自由链表要内存
				for (int i = n; i < _MAXBYTES; i += _ALIGN)
				{
					if (_FreeList[i])
					{
						_StartFree = (char*)_FreeList[i];
						_EndFree = (char*)(_StartFree + i);
						_FreeList[i] = _FreeList[i]->_FreeListLink;
						return (ChuncAlloc(n, nojbs));
					}
				}
				_EndFree = 0;   //防止malloc开辟空间失败后使实际没有内存的内存池变得”有内存了“
				//如果自由链表中也没有可用的内存了,则调用一级空间配置器
				_StartFree = (char*)_MallocAllocTemplate<0>::allocate(GetBytes);
			}
			_HeapSize +=GetBytes;
			_EndFree = _StartFree + GetBytes;
			return(ChuncAlloc(n,nojbs));
		}
	}
};
//静态变量的初始化
template <bool threads, int inst>
typename  char* __DefaultAllocTemplate<threads, inst>::_StartFree = 0;

template <bool threads, int inst>
typename  char* __DefaultAllocTemplate<threads, inst>::_EndFree = 0;

template <bool threads, int inst>
typename  size_t __DefaultAllocTemplate<threads, inst>::_HeapSize = 0;

template<bool threads,int inst>
typename  __DefaultAllocTemplate<threads,inst>::Obj* volatile  
__DefaultAllocTemplate<threads, inst>::_FreeList[__DefaultAllocTemplate<threads, inst>::_NFREELISTS] = { 0 };

#ifdef __USE_MALLOC
   typedef __MallocAllocTemplate<0> alloc;
#else
   typedef __DefaultAllocTemplate<0, 0> alloc;
#endif //__USE_MALLOC

template<class T, class _Alloc=alloc>
class SimpleAlloc 
{
public:
	static T *allocate(size_t n)
	{
		return 0 == n ? 0 : (T*)_Alloc::allocate(n * sizeof (T));
	}
	static T *allocate(void)
	{
		return (T*)_Alloc::allocate(sizeof (T));
	}
	static void deallocate(T *p, size_t n)
	{
		if (0 != n)_Alloc::deallocate(p, n * sizeof (T));
	}
	static void deallocate(T *p)
	{
		_Alloc::deallocate(p, sizeof (T));
	}
};

void Test1()
{
	vector<pair<int*, size_t>> v;
	v.push_back(make_pair(SimpleAlloc<int>::allocate(129), 129));

	for (size_t i = 0; i < 21; ++i)
	{
		v.push_back(make_pair(SimpleAlloc<int>::allocate(12), 12));
	}

	while (!v.empty())
	{
		SimpleAlloc<int>::deallocate(v.back().first,v.back().second);
		v.pop_back();
	}

	for (size_t i = 0; i < 21; ++i)
	{
		v.push_back(make_pair(SimpleAlloc<int>::allocate(7), 7));
	}

	for (size_t i = 0; i < 10; ++i)
	{
		v.push_back(make_pair(SimpleAlloc<int>::allocate(16), 16));
	}

	while (!v.empty())
	{
		SimpleAlloc<int>::deallocate(v.back().first, v.back().second);
		v.pop_back();
	}
}
//
//void Test3()
//{
//	cout << "测试系统堆内存耗尽" << endl;
//
//	/*SimpleAlloc<char, Alloc>::Allocate(1024 * 1024 * 1024);
//	SimpleAlloc<char, Alloc>::Allocate(1024 * 1024);*/
//
//	//不好测试，说明系统管理小块内存的能力还是很强的。
//	for (int i = 0; i< 100000; ++i)
//	{
//		char*p1 = SimpleAlloc<char, Alloc>::Allocate(128);
//	}
//
//	cout << "分配完成" << endl;
//}
