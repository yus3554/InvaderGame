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
	Node<T>* head;
	int length;
public:
	LinkedList();
	~LinkedList();
	Node<T>* getHead();
	void Substitute(Node<T>* head, int length);
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
	this->head = NULL;
	this->length = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	this->clear();
}

template <typename T>
Node<T>* LinkedList<T>::getHead()
{
	return this->head;
}

template <typename T>
void LinkedList<T>::Substitute(Node<T>* head, int length)
{
	// headとlengthを代入する。
	this->head = head;
	this->length = length;
}

template <typename T>
int LinkedList<T>::getLength()
{
	return this->length;
}

template <typename T>
void LinkedList<T>::add(T* info)
{
	Node<T>* next = new Node<T>(info);

	// 末尾に追加
	if (this->getLength() == 0)
	{
		this->head = next;
	}
	else
	{
		Node<T>* temp = this->head;
		while (temp->getNext() != NULL)
		{
			temp = temp->getNext();
		}
		temp->setNext(next);
	}
	this->length++;
}

template <typename T>
T* LinkedList<T>::pop()
{
	// 先頭を取ってリストから削除
	if (this->getLength() == 0)
	{
		return NULL;
	}

	T* value = this->head->getValue();

	if (this->getLength() == 1)
	{
		delete this->head;
		this->head = NULL;
	}
	else
	{
		Node<T>* tempHead = this->head;
		this->head = this->head->getNext();
		delete tempHead;
	}
	this->length--;
	return value;
}

template <typename T>
T* LinkedList<T>::get(int index)
{
	if (index >= this->getLength())
		throw "out of range for index.";

	Node<T>* temp = this->head;
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

	Node<T>* tempCurrent = this->head;
	Node<T>* tempNext = this->head->getNext();
	if (index == 0)
	{
		delete tempCurrent;
		this->head = tempNext;
	}
	else
	{
		for (int i = 1; i < index; i++)
		{
			tempCurrent = tempNext;
			tempNext = tempCurrent->getNext();
		}
		if (tempNext == NULL)
			throw "tempNextがNULLです。";
		tempCurrent->setNext(tempNext->getNext());
		delete tempNext;
	}
	this->length--;
}

template <typename T>
void LinkedList<T>::clear()
{
	while(this->pop() != NULL){}
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
