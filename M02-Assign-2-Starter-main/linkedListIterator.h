// linked list by D.S. Malik and Angela Venable
#pragma once

template <class Type>
struct node
{
	Type *info;
	node<Type> *link;
	~node()
	{
		delete info;
	}
};

template <class Type>
class linkedListIterator
{
public:
	linkedListIterator();
	linkedListIterator(node<Type> *ptr);
	Type &operator*();
	linkedListIterator<Type> operator++();
	bool operator==(const linkedListIterator<Type> &right) const;
	bool operator!=(const linkedListIterator<Type> &right) const;

private:
	node<Type> *current;
};

template <class Type>
linkedListIterator<Type>::linkedListIterator()
{
	current = nullptr;
}

template <class Type>
linkedListIterator<Type>::linkedListIterator(node<Type> *ptr)
{
	current = ptr;
}

template <class Type>
Type &linkedListIterator<Type>::operator*()
{
	return *current->info;
}

template <class Type>
linkedListIterator<Type> linkedListIterator<Type>::operator++()
{
	current = current->link;
	return *this;
}

template <class Type>
bool linkedListIterator<Type>::operator==(const linkedListIterator<Type> &right) const
{
	return (current == right.current);
}

template <class Type>
bool linkedListIterator<Type>::operator!=(const linkedListIterator<Type> &right) const
{
	return (current != right.current);
}