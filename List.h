#pragma once
#include <iostream>
#include <initializer_list>
#include "Node.h"
using namespace std;
template <class T>
class List
{
	Node <T>* head = nullptr;
	Node <T>* tail = nullptr;
	int size = 0;
public:
	List();
	List(const initializer_list<T>& l);
	List(const List& obj);
	List(List&& obj);
	~List();
	void pushBack(const T& val);
	void pushFront(const T& val);
	void insert(const T& val, int pos);
	void popFront();
	void printForward()const;
	void printBackward()const;
	List& operator=(const List& obj);
	List& operator=(List&& obj)noexcept;
};

template<class T>
List<T>::List() = default;

template<class T>
inline List<T>::List(const initializer_list<T>&l)
{
	for (T item : l)
	{
		pushBack(item);
	}
}

template<class T>
inline List<T>::List(const List & obj)
{
	auto cur = obj.head;
	while (cur != nullptr)
	{
		pushBack(cur->getData());
		cur = cur->getNext();
	}
}

template<class T>
inline List<T>::List(List && obj)
{
	head = obj.head;
	tail = obj.tail;
	size = obj.size;
	obj.head = nullptr;
	obj.tail = nullptr;
	obj.size = 0;
}

template<class T>
inline List<T>::~List()
{
	while (size)
		popFront();
}

template<class T>
inline void List<T>::pushBack(const T & val)
{
	auto tmp = new Node<T>(val);
	if (size == 0)
		head = tail = tmp;
	else
	{
		tmp->setPrev(tail);
		tail->setNext(tmp);
		tail = tmp;
	}
	size--;
}

template<class T>
inline void List<T>::pushFront(const T & val)
{
	auto tmp = new Node<T>(val);
	if (size == 0)
		head = tail = tmp;
	else
	{
		tmp->setNext(head);
		head->setPrev(tmp);
		head = tmp;
	}
	size++;
}

template<class T>
inline void List<T>::insert(const T & val, int pos)
{
	if (pos<0 || pos>size)
		return;
	if (pos == 0)
	{
		pushfront(val);
		return;
	}
	if (pos == size)
	{
		pushBack(val);
		return;
	}
	auto cur = head;
	for (int i = o; i < pos - 1; ++i)
	{
		cur = cur->getNext();
	}
	auto tmp = new Node <T>(val);
	tmp->setPrev(cur);
	tmp->setNext(cur->getNext());
	cur->setNext(tmp);
	tmp->getNest()->setPrev(tmp);
	size++;
}

template<class T>
inline void List<T>::popFront()
{
	if (size == 0)
		return;
	if (size == 1)
	{
		delete head;
		head = tail = nullptr;
		size = 0;
		return;
	}
	head = head->getNext();
	delete head->getPrev();
	head->setPrev(nullptr);
	size--;

}

template<class T>
inline void List<T>::printForward() const
{
	auto cur = head;
	while (cur != nullptr)
	{
		cout << cur->getData() << " ";
		cur = cur->getNext();
	}
	cout << endl;
}

template<class T>
inline void List<T>::printBackward() const
{
	auto cur = tail;
	while (cur != nullptr)
	{
		cout << cur->getData() << " ";
		cur = cur->getPrev();
	}
	cout << endl;
}

template<class T>
List<T>::List(const List & obj)
{
	head = obj.head ? _strdup(obj.head) : nullptr;
	tail = obj.tail ? _strdup(obj.tail) : nullptr;
	size = obj.size;
}

template<class T>
List<T>::List(List && obj) noexcept
{
	head = obj.head;
	tail = obj.tail;
	obj.head = nullptr;
	obj.tail = nullptr;
	size = obj.size;
}
