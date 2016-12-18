#pragma once 
#include <iostream>
using namespace std;


struct InputIteratorTag {};												//只读类型的迭代器
struct OutputIteratorTag {};											//只写类型的迭代器
struct ForwardIteratorTag : public InputIteratorTag {};					//可以进行读写操作的迭代器
struct BidirectionalIteratorTag : public ForwardIteratorTag {};			//可双向移动的迭代器
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};    //涵盖所有指针算数运算能力的迭代器


template <class Category, class T, class Distance = size_t,
class Pointer = T*, class Reference = T&>
struct Iterator
{
	typedef Category			IteratorCategory;
	typedef T					ValueType;
	typedef Distance			DifferenceType;
	typedef T*					Pointer;
	typedef T&					Reference;
};

//类型萃取
template <class Iterator>
struct IteratorTraits
{
	typedef typename Iterator::IteratorCategory IteratorCategory;
	typedef typename Iterator::ValueType        ValueType;
	typedef typename Iterator::DifferenceType   DifferenceType;
	typedef typename Iterator::Pointer           Pointer;
	typedef typename Iterator::Reference         Reference;
};

//原生指针的类型萃取
template <class T>
struct IteratorTraits<T*>
{
	typedef RandomAccessIteratorTag	   IteratorCategory;
	typedef T                          ValueType;
	typedef ptrdiff_t                  DifferenceType;
	typedef T*                         Pointer;
	typedef T&                         Reference;
};


//针对const T*的类型萃取
template <class T>
struct IteratorTraits<const T*>
{
	typedef RandomAccessIteratorTag	   IteratorCategory;
	typedef T                          ValueType;
	typedef ptrdiff_t                  DifferenceType;
	typedef T*                         Pointer;
	typedef T&                         Reference;
};

//普通类型的求两个迭代器之间距离的函数
template <class InputIterator>
inline size_t __Distance(InputIterator first, InputIterator last, InputIteratorTag) {
	size_t n = 0;
	while (first != last) {
		++first; ++n;
	}
	return n;
}


//RandomAccessIteratorTag类型的求两个迭代器之间距离的函数
template <class RandomAccessIterator>
inline size_t __Distance(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIteratorTag)
{
	size_t n = 0;
	n += last - first;
	return n;
}


//求两个迭代器之间的距离的函数
template <class InputIterator>
inline size_t Distance(InputIterator first, InputIterator last) {
	return __Distance(first, last, IteratorTraits<InputIterator>::IteratorCategory());
}

