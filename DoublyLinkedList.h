#pragma once
#define DEBUGMODE true
#include "list.h"
#include <iostream>

using namespace std;

template <typename T>
class DoublyLinkedList:
	public list{

	struct node {
		node(const T& t) :data(t), next(nullptr), prev(nullptr) { };
		node():next(nullptr),prev(nullptr) {};
		T data;
		node* next;
		node* prev;
	} *head;
	node* tail;

	void deleteNode(node* n)
	{
		delete n;
		--s;
	}
	void deleteNode(node* n, node*& prev, node*& next)
	{
		delete n;
		prev->next = next;
		next->prev = prev;
		--s;
	}
	void addNode(node*& newNode, node*& prev, node*& next)
	{
		newNode->next = next;
		newNode->prev = prev;
		newNode->prev->next = newNode;
		newNode->next->prev = newNode;
		++s;
	}
	void copyNode(node* n)
	{
		node* newNode = new node(n->data);
		addNode(newNode, this->tail->prev, this->tail);
	}

public:
	class ListIterator {
		friend class DoublyLinkedList;
		node* cur;
		node* getNode() const
		{
			return this->cur;
		}
	public:
		ListIterator(node* n = 0) :cur(n) {};
		ListIterator& operator++()
		{
			cur = cur->next;
			return *this;
		}
		ListIterator& operator++(T)
		{
			ListIterator* temp(this->cur);
			++(*this);
			return temp;
		}
		ListIterator& operator--()
		{
			cur = cur->prev;
			return *this;
		}
		ListIterator& operator--(T)
		{
			ListIterator* temp(this->cur);
			--(*this);
			return temp;
		}
		T& operator*() {
			return cur->data;
		}
		bool operator==(const ListIterator& rh) {
			return this->cur == rh.cur;
		}
		bool operator!=(const ListIterator& rh) {
			return this->cur != rh.cur;
		}
	};
	typedef ListIterator iterator;

	iterator begin() {
		return ++iterator(head);
	}
	iterator end() {
		return iterator(tail);
	}

	DoublyLinkedList()
	{
		// sentinel
		this->head = new node();
		this->tail = new node();
		head->next = this->tail;
		tail->prev = this->head;
	}
	~DoublyLinkedList()
	{
		this->clear();
		delete this->head;
		delete this->tail;

		if(s != 0)
			std::cout << "there may be memory leak : " << s << std::endl;
	}

	DoublyLinkedList(const DoublyLinkedList& rhs)
	{
		if (DEBUGMODE)
			cout << "copy construct called" << endl;
		// sentinel
		this->head = new node();
		this->tail = new node();
		head->next = this->tail;
		tail->prev = this->head;
		*this = rhs;
	}

	T& front()
	{
		return this->head->next->getNode()->data;
	}

	T& back()
	{
		return this->tail->prev->getNode()->data;
	}

	void push_front(const T& data)
	{
		node* n = new node(data);
		addNode(n, this->head, this->head->next);
	}

	void push_front(T&& data)
	{
		node* n = new node(data);
		addNode(n, this->head, this->head->next);
	}

	void push_back(const T& data)
	{
		node* n = new node(data);
		addNode(n, this->tail->prev, this->tail);
	}

	void push_back(T&& data)
	{
		node* n = new node(data);
		addNode(n, this->tail->prev, this->tail);
	}

	void pop_front()
	{
		node* next = this->head->next->next;
		deleteNode(this->head->next, this->head, next);
	}

	void pop_back()
	{
		node* prev = this->tail->prev->prev;
		deleteNode(this->tail->prev, prev, this->tail);
	}

	void clear()
	{
		node* cur = this->head->next;
		while (cur != this->tail)
		{
			node* next = cur->next;
			deleteNode(cur);
			cur = next;
		}
		this->head->next = this->tail;
		this->tail->prev = this->head;
	}
	void empty()
	{
		return !this->s;
	}

	iterator insert(const iterator& it, T&& data) // O(n) rvalue
	{
		node* cur = it.getNode();
		node* n = new node(data);
		addNode(n, cur->prev, cur);
		return n;
	}

	iterator insert(const iterator& it, const T& data) // O(n)
	{
		node* cur = it.getNode();
		node* n = new node(data);
		addNode(n, cur->prev, cur);
		return n;
	}

	iterator insert(const iterator& position, iterator& first, iterator& last)
	{
		node* end = position.getNode();
		node* start = position.getNode()->prev;
		node* lastNode, *firstNode, *prevNode;
		node* nodes = lastNode = prevNode = new node();
		int cnt = 0;
		while (first != last)
		{
			lastNode->next = new node(*first);
			lastNode = lastNode->next;
			prevNode->next = lastNode;
			lastNode->prev = prevNode;
			prevNode = prevNode->next;
			++first;
			++cnt;
		}

		firstNode = nodes->next;
		
		firstNode->prev = start;
		lastNode->next = end;
		start->next = firstNode;
		end->prev = lastNode;

		this->s += cnt;

		delete nodes;

		return lastNode;
	}

	iterator remove(const iterator& position)
	{
		node* prev = position.getNode()->prev;
		node* next = position.getNode()->next;
		deleteNode(position.getNode(), prev, next);

		return next;
	}

	iterator remove(const iterator& first, const iterator& last)
	{
		node* start = first.getNode()->prev;
		node* end = last.getNode();

		node* cur = first.getNode();
		node* next;
		while (cur != end)
		{
			next = cur->next;
			deleteNode(cur);
			cur = next;
		}

		start->next = end;
		end->prev = start;

		return end;
	}

	void remove(const T& data)
	{
		node* cur = this->head->next;
		while (cur != this->tail)
		{
			if (cur->data == data)
			{
				node* prev = cur->prev;
				node* next = cur->next;
				deleteNode(cur,prev,next);
			}
			cur = cur->next;
		}
	}

	void remove_if(bool (&func)(const T&))
	{
		auto it = this->begin();
		while (it != this->end())
		{
			if (func(*it))
				it = remove(it);
		}
	}

	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& rhs)
	{
		if (this->s != 0)
			this->clear();
		node* temp = rhs.head->next;
		while (temp != rhs.tail)
		{
			copyNode(temp);
			temp = temp->next;
		}

		return *this;
	}

	DoublyLinkedList<T>& operator=(DoublyLinkedList&& rhs)
	{
		return *this = rhs;
	}

	const DoublyLinkedList<T> operator+(const DoublyLinkedList<T>& rhs)
	{
		return DoublyLinkedList<T>(*this) += rhs;
	}

	DoublyLinkedList<T>& operator+=(const DoublyLinkedList<T>& rhs)
	{
		node* n = rhs.head->next;
		while (n != rhs.tail)
		{
			push_back(n->data);
			n = n->next;
		}

		return *this;
	}

	void swap(DoublyLinkedList<T>& rhs)
	{
		node* tHead, * tTail;
		int size = this->s;

		tHead = this->head->next;
		tTail = this->tail->prev;

		this->head->next = rhs.head->next;
		this->head->next->prev = this->head;
		this->tail->prev = rhs.tail->prev;
		this->tail->prev->next = this->tail;
		this->s = rhs.s;

		rhs.head->next = tHead;
		tHead->prev = rhs.head;
		rhs.tail->prev = tTail;
		tTail->next = rhs.tail;
		rhs.s = size;

	}


};