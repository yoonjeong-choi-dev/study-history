#ifndef __LINKED_LIST_NODE_STRUCTURE__
#define __LINKED_LIST_NODE_STRUCTURE__


template<typename T>
struct OneWayNode
{
	T data;
	OneWayNode<T>* next;
};


template<typename T>
struct DoubleWayNode
{
	T data;
	DoubleWayNode<T>* before;
	DoubleWayNode<T>* next;
};



#endif
