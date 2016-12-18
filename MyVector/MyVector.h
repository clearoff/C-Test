#pragma once
#include "MyAllocate.h"
#include "Construct.h"
#include <cassert>

//template<class T, class Ref, class Ptr>
//struct __VectorIterator
//{
//	typedef
//public:
//	Iterator _start;
//	Iterator  _finish;
//	Iterator _EndOfStorage;
//};

template <class T, class Alloc = alloc>
class Vector
{
public:
	//vector的内嵌型别
	typedef T					ValueType;
	typedef ValueType*			Pointer;
	typedef const ValueType*	ConstPointer;
	typedef ValueType*			Iterator;
	typedef const ValueType*    ConstIterator;
	typedef const ValueType*	ConstPointer;
	typedef ValueType&			Reference;
	typedef const				ValueType& ConstReference;
	typedef size_t				SizeType;
	typedef size_t				DifferenceType;
public:
	Vector()
		: _start(0)
		, _finish(0)
		, _EndOfStorage(0)
	{}

	//Vector()

	Iterator Begin()
	{
		return _start;
	}

	Iterator End()
	{
		return _finish;
	}

	ConstIterator cBegin() const
	{
		return _start;
	}

	ConstIterator cEnd() const
	{
		return _finish;
	}

	ValueType& operator[](const SizeType& n)
	{
		return *(_start + n);
	}

	//Const ValueType& operator[](const SizeType& n) const 
	//{
	//	return *(_start + n);
	//}

	void PushBack(const ValueType& x)
	{
		//扩容
		_CheckCapacity();

		Insert(_finish, x);
	}

	void Insert(Iterator pos,const ValueType& x)
	{
		//SizeType n = pos - _begin;
		//assert(pos>=_start&&pos<=_finish);
		if (pos == _finish)
		{
			Construct(_finish, x);
			_finish++;
		}
		else
		{
			//计算插入点之后的现有元素的个数
		    size_t ElemFront = _finish - pos;

			/*	_finish++;*/
			for (int i = 0; i < ElemFront; i++)
			{
				Iterator CopyPos = _finish - i;
				Construct(CopyPos, *(CopyPos - 1));
			}
			_finish++;
			Construct(pos, x);
		}
	}
	
protected:
	typedef SimpleAlloc<ValueType, Alloc> DataAllocator;
	Iterator _start;
	Iterator  _finish;
	Iterator _EndOfStorage;
protected:
	void _CheckCapacity()
	{
		if (_finish == _EndOfStorage)
		{
			//空间已满，开辟空间
			size_t OldSize = _finish - _start;
			size_t NewSize = OldSize * 2 + 3;
			T* _tmp = DataAllocator::allocate(NewSize);            //开辟新的空间
			for (size_t i = 0; i < OldSize; i++)
			{
				//拷贝原数组当中的成员
				_tmp[i] = _start[i];
			}
			//改变参数
			swap(_start, _tmp);
			_finish = _start + OldSize;
			_EndOfStorage = _start + NewSize;

			//释放空间
			DataAllocator::deallocate(_tmp, OldSize);
		}
	}
};



void TestVector()
{
	Vector<int> v1;

	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.PushBack(5);
	v1.PushBack(6);

	Vector<int>::Iterator it =v1.Begin();

	while (it != v1.End())
	{
		cout << *it << " ";
		it++;
	}

	cout << "Distance?" << Distance(v1.cBegin(), v1.cEnd()) << endl;
	cout << "VectorSize?" << sizeof(Vector<int>) << endl;
}