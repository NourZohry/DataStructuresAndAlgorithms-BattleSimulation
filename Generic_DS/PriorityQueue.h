#include<iostream>
#include"PriorityNode.h"
#pragma once
using namespace std;

template<class T>
class PriorityQueue
{
private:
	PriorityNode<T>* Head;
	int count;
public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue& pq);
	~PriorityQueue();
	bool isEmpty() const;
	bool add(const T& newEntry, int x);
	bool remove(T &TopEntry);
	bool peek(T &TopEntry);
	const T* toArray(int& count);
};
template<class T>
PriorityQueue<T>::PriorityQueue()
{
	Head = NULL;
	count = 0;
}
template<class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& aPqueue)
{
	PriorityNode<T>* orgptr = aPqueue->Head;
	if (orgptr == NULL)
	{
		Head = NULL;
		count = 0;
	}
	else
	{
		Head = new PriorityNode<T>();
		Head->setItem(orgptr->getItem());
		Head->setP(orgptr->getP());
		PriorityNode<T>* newChainPtr = Head;
		while (orgptr != NULL)
		{
			orgptr = orgptr->getNext();
			T nextItem = orgptr->getItem();
			PriorityNode<T>* newNodePtr = new PriorityNode<T>(nextItem);
			newNodePtr->setP(orgptr->getP());
			newChainPtr->setNext(newNodePtr);
			// Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();
		}
		newChainPtr->setNext(nullptr);
	}
}
template<class T>
bool PriorityQueue<T>::isEmpty() const
{
	if (!Head)
	{
		return true;
	}
	return false;
}
template<class T>
bool PriorityQueue<T>::remove(T &TopEntry)
{
	if (isEmpty())
		return false;
	PriorityNode<T>* nodeToDeletePtr = Head;
	TopEntry = Head->getItem();
	Head = Head->getNext();
	count--;



	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;
}
template<class T>
bool PriorityQueue<T>::add(const T& newEntry, int x)
{
	PriorityNode<T>*newNode = new PriorityNode<T>(newEntry);
	if (newNode == nullptr)
	{
		return false;
	}
	newNode->setP(x);
	PriorityNode<T>*ptr = Head;
	if (isEmpty())
	{
		Head = newNode;
		Head->setNext(NULL);
		count++;
		return true;
	}
	if (newNode->getP() > Head->getP())
	{
		newNode->setNext(Head);
		Head = newNode;
		count++;
		return true;
	}
	while (ptr->getNext() && newNode->getP() < ptr->getNext()->getP())
	{
		ptr = ptr->getNext();
	}
	count++;
	newNode->setNext(ptr->getNext());
	ptr->setNext(newNode);
	return true;
}
template<class T>
bool PriorityQueue<T>::peek(T &TopEntry)
{
	if (isEmpty())
		return false;

	TopEntry = Head->getItem();
	return true;
}
template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
}
template <typename T>
const T* PriorityQueue<T>::toArray(int& count)
{
	count = 0;

	if (!Head)
		return nullptr;
	//counting the no. of items in the Queue
	PriorityNode<T>* p = Head;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = Head;
	for (int i = 0; i < count;i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}
