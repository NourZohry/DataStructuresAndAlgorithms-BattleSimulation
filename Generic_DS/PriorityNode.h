#pragma once

template < typename T>
class PriorityNode
{
private:
	T item; // A data item
	PriorityNode<T>* next;
	int priority; // Pointer to next node
public:
	PriorityNode();
	PriorityNode(const T & r_Item);	//passing by const ref.
	PriorityNode(const T & r_Item, PriorityNode<T>* nextNodePtr);
	void setItem(const T & r_Item);
	void setNext(PriorityNode<T>* nextNodePtr);
	T getItem() const;
	PriorityNode<T>* getNext() const;
	void setP(int P);
	int getP() const;
}; // end Node


template < typename T>
PriorityNode<T>::PriorityNode()
{
	next = nullptr;
}

template < typename T>
PriorityNode<T>::PriorityNode(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
PriorityNode<T>::PriorityNode(const T& r_Item, PriorityNode<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void PriorityNode<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void PriorityNode<T>::setNext(PriorityNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T PriorityNode<T>::getItem() const
{
	return item;
}

template < typename T>
PriorityNode<T>* PriorityNode<T>::getNext() const
{
	return next;
}
template < typename T>
void PriorityNode<T>::setP(int P)
{
	priority = P;
}
template < typename T>
int PriorityNode<T>::getP() const
{
	return priority;
}


