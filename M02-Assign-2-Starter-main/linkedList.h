// linked list by D.S. Malik and Angela Venable
#pragma once

#include "linkedListIterator.h"
#include <iostream>

template <class Type>
class linkedList
{
public:
	const linkedList<Type> &operator=(const linkedList<Type> &);
	void initializeList();
	bool isEmptyList() const;
	void print(std::ostream &) const;
	int length() const;
	void destroyList();
	Type front() const;
	Type back() const;
	virtual bool search(const Type &searchItem) const = 0;
	virtual void insertFirst(const Type &newItem) = 0;
	virtual void insertLast(const Type &newItem) = 0;
	virtual void deleteNode(const Type &deleteItem) = 0;
	linkedListIterator<Type> begin();
	linkedListIterator<Type> end();
	linkedList();
	linkedList(const linkedList<Type> &otherList);
	~linkedList();

protected:
	int count;
	node<Type> *first;
	node<Type> *last;

private:
	void copyList(const linkedList<Type> &otherList);
};

template <class Type>
bool linkedList<Type>::isEmptyList() const
{
	return (first == nullptr);
}

template <class Type>
linkedList<Type>::linkedList()
{
	first = nullptr;
	last = nullptr;
	count = 0;
}

template <class Type>
void linkedList<Type>::destroyList()
{
	node<Type> *temp;
	while (first != nullptr)
	{
		temp = first;
		first = first->link;
		delete temp;
	}
	last = nullptr;
	count = 0;
}

template <class Type>
void linkedList<Type>::initializeList()
{
	destroyList();
}

template <class Type>
void linkedList<Type>::print(std::ostream &out) const
{
	node<Type> *current;
	current = first;
	while (current != nullptr)
	{
		out << *(current->info) << std::endl;
		current = current->link;
	}
}

template <class Type>
int linkedList<Type>::length() const
{
	return count;
}

template <class Type>
Type linkedList<Type>::front() const
{
	assert(first != nullptr);
	return first->info;
}

template <class Type>
Type linkedList<Type>::back() const
{
	assert(last != nullptr);
	return last->info;
}

template <class Type>
linkedListIterator<Type> linkedList<Type>::begin()
{
	linkedListIterator<Type> temp(first);
	return temp;
}

template <class Type>
linkedListIterator<Type> linkedList<Type>::end()
{
	linkedListIterator<Type> temp(nullptr);
	return temp;
}

template <class Type>
void linkedList<Type>::copyList(const linkedList<Type> &otherList)
{
	node<Type> *newNode;
	node<Type> *current;
	if (first != nullptr)
		destroyList();
	if (otherList.first == nullptr)
	{
		first = nullptr;
		last = nullptr;
		count = 0;
	}
	else
	{
		current = otherList.first;
		count = otherList.count;

		first = new node<Type>;
		first->info = current->info;
		first->link = nullptr;

		last = first;
		current = current->link;
		while (current != nullptr)
		{
			newNode = new node<Type>;
			newNode->info = new Type(*current->info);
			newNode->link = nullptr;
			last->link = newNode;
			last = newNode;
			current = current->link;
		}
	}
}

template <class Type>
linkedList<Type>::~linkedList()
{
	destroyList();
}

template <class Type>
linkedList<Type>::linkedList(const linkedList<Type> &otherList)
{
	first = nullptr;
	copyList(otherList);
}

template <class Type>
const linkedList<Type> &linkedList<Type>::operator=(const linkedList<Type> &otherList)
{
	if (this != &otherList)
	{
		copyList(otherList);
	}

	return *this;
}
