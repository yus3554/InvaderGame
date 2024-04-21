#pragma once
#include <stdlib.h>

template <typename T>
class Node
{
private:
	T* value;
	Node<T>* next;
public:
	Node(T* value);
	void setNext(Node* next);
	Node<T>* getNext();
	T* getValue();
};

template <typename T>
class LinkedList
{
private:
	Node<T>* first;
	Node<T>* last;
	int length;
public:
	LinkedList();
	~LinkedList();
	int getLength();
	void add(T* value);
	T* pop();
	T* get(int index);
	void remove(int index);
	void clear();
};


template <typename T>
LinkedList<T>::LinkedList()
{
	this->first = NULL;
	this->last = NULL;
	this->length = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	this->clear();
}

template <typename T>
int LinkedList<T>::getLength()
{
	return this->length;
}

template <typename T>
void LinkedList<T>::add(T* info)
{
	// ––”ö‚É’Ç‰Á
	if (this->getLength() == 0)
	{
		this->first = new Node<T>(info);
	}
	else if (this->getLength() == 1)
	{
		Node<T>* next = new Node<T>(info);
		this->first->setNext(next);
		this->last = next;
	}
	else
	{
		Node<T>* next = new Node<T>(info);
		this->last->setNext(next);
		this->last = next;
	}
	this->length++;
}

template <typename T>
T* LinkedList<T>::pop()
{
	// æ“ª‚ðŽæ‚Á‚ÄƒŠƒXƒg‚©‚çíœ
	if (this->getLength() == 0)
	{
		return NULL;
	}

	T* info = this->first->getValue();

	if (this->getLength() == 1)
	{
		delete this->first;
		this->first = NULL;
	}
	else if (this->getLength() == 2)
	{
		delete this->first;
		this->first = this->last;
		this->last = NULL;
	}
	else
	{
		Node<T>* tempFirst = this->first;
		this->first = this->first->getNext();
		delete tempFirst;
	}
	this->length--;
	return info;
}

template <typename T>
T* LinkedList<T>::get(int index)
{
	if (index >= this->getLength())
		throw "out of range for index.";

	Node<T>* temp = this->first;
	for (int i = 1; i <= index; i++)
	{
		temp = temp->getNext();
	}
	return temp->getValue();
}

template <typename T>
void LinkedList<T>::remove(int index)
{
	if (index >= this->getLength())
		throw "out of range for index.";

	Node<T>* temp;
	if (index == 0)
	{
		temp = this->first;
		delete temp;
		this->first = NULL;
	}
	else
	{
		
	}
}

template <typename T>
void LinkedList<T>::clear()
{
	
}

template <typename T>
Node<T>::Node(T* value)
{
	this->value = value;
	this->next = NULL;
}

template <typename T>
void Node<T>::setNext(Node* next)
{
	this->next = next;
}

template <typename T>
Node<T>* Node<T>::getNext()
{
	return this->next;
}

template <typename T>
T* Node<T>::getValue()
{
	return this->value;
}
