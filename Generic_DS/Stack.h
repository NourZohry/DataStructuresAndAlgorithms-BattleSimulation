#pragma once
#include<iostream>
using namespace std;
#include"Node.h"


template<typename T>
class Stack
{
protected:
	Node<T>*head;
	T data;
	int count;
	
public:
	Stack();
	void push(const T NewItem);
	T peek();
	void pop(); //should be const as it was i.e void pop() const;
	bool isEmpty() const;
	Stack(const Stack<T>&aStack);
	const T* toArray(int& count);

};

template<typename T>
Stack<T>::Stack()
{
	count = 0;
	head = nullptr;
}


template<typename T>
Stack<T>::Stack(const Stack<T>&aStack)
{
	Node<T>*orgptr = aStack->head;
	if (orgptr == nullptr)
	{
		head = nullptr;
	}
	else
	{
		head = new Node<T>();
		head->setItem(orgptr->getItem());
		// Point to first node in new chain
		Node<T>* newChainPtr = head;
		// Copy remaining nodes
		while (orgptr != nullptr)
		{
			// Advance original-chain pointer
			orgptr = orgptr->getNext();
			// Get next item from original chain
			T nextItem = orgptr->getItem();
			// Create a new node containing the next item
			Node<T>* newNodePtr = new Node<T>(nextItem);
			// Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);
			// Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();
		}
		newChainPtr->setNext(nullptr);
	}
}

template<typename T>
bool Stack<T>::isEmpty()const
{
	return head == nullptr;
}
template<typename T>
void Stack<T>:: push(const T NewItem)
{
	Node<T>* newNodePtr = new Node<T>(NewItem, head);
	head = newNodePtr;
	newNodePtr = nullptr;
}
template<typename T>
T Stack<T>::peek()
{
	return head->getItem();
}



template<typename T>
void Stack<T>::pop()
{
	
	if (!isEmpty())
	{
		// Stack is not empty; delete top
		Node<T>* nodeToDeletePtr = head;
		head = head->getNext();
		// Return deleted node to system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
	} // end if

}
template <typename T>
const T* Stack<T>::toArray(int& count)
{
	count = 0;

	if (!head)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = head;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = head;
	for (int i = 0; i < count;i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}
