#include "DrawInfoLinkedList.h"

DrawInfoLinkedList::DrawInfoLinkedList()
{
	this->first = NULL;
	this->last = NULL;
	this->length = 0;
}

int DrawInfoLinkedList::getLength()
{
	return this->length;
}

void DrawInfoLinkedList::add(DrawInfo* info)
{
	// ––”ö‚É’Ç‰Á
	if (this->getLength() == 0)
	{
		this->first = new Node(info);
	}
	else if (this->getLength() == 1)
	{
		Node* next = new Node(info);
		this->first->setNext(next);
		this->last = next;
	}
	else
	{
		Node* next = new Node(info);
		this->last->setNext(next);
		this->last = next;
	}
	this->length++;
}

DrawInfo* DrawInfoLinkedList::pop()
{
	// æ“ª‚ðŽæ‚Á‚ÄƒŠƒXƒg‚©‚çíœ
	if (this->getLength() == 0)
	{
		return NULL;
	}

	DrawInfo* info = this->first->getInfo();

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
		Node* tempFirst = this->first;
		this->first = this->first->getNext();
		delete tempFirst;
	}
	this->length--;
	return info;
}

Node::Node(DrawInfo* info)
{
	this->info = info;
	this->next = NULL;
}

void Node::setNext(Node* next)
{
	this->next = next;
}

Node* Node::getNext()
{
	return this->next;
}

DrawInfo* Node::getInfo()
{
	return this->info;
}
