#pragma once
#include "./drawInfos/DrawInfo.h"

class Node
{
private:
	DrawInfo* info;
	Node* next;
public:
	Node(DrawInfo* info);
	void setNext(Node* next);
	Node* getNext();
	DrawInfo* getInfo();
};

class DrawInfoLinkedList
{
private:
	Node* first;
	Node* last;
	int length;
public:
	DrawInfoLinkedList();
	int getLength();
	void add(DrawInfo* info);
	DrawInfo* pop();
};

