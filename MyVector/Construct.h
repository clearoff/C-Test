#pragma once 


template<class T, class Value>
inline void Construct(T* node, Value value)
{
	new(node)T(value);             //调用定位new表达式初始化化对象
}


template<class T>
inline void Destory(T* node)
{
	node->~T();                   //调用析构函数
}