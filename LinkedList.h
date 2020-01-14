#pragma once
#include "list.h"
#include <iostream>

template <typename T>
class LinkedList :
	public list
{
	struct node {
		node(T& t) :data(t), next(nullptr) { };
		T data;
		node* next;
	} *head;

	void deleteNode(node* n)
	{
		--s;
		delete n;
	}

public:
	class ListIterator {
		friend class LinkedList;
		node* cur;
		node* getNode()
		{
			return this->cur;
		}
	public:
		ListIterator(node* n=0) :cur(n) {};
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

	LinkedList() {

	}

	~LinkedList() {
		node* cur=this->head;
		while (cur != nullptr)
		{
			node* next = cur->next;
			this->deleteNode(cur);
			cur = next;
		}
		if (s > 0)
			std::cout <<"there may be memory leak : "<<s<< std::endl;
	}

	iterator begin() {
		return iterator(head);
	}
	iterator end() {
		return iterator(0);
	}

	void push_back(T&& data) // O(n) rvalue
	{
		node* point = this->head;
		while (point != nullptr)
			point = point->next;

		node* n = new node(data);
		point = n;
		++s;
	}

	void push_back(T& data) // O(n)
	{
		node* point = this->head;
		while (point != nullptr)
			point = point->next;

		node* n = new node(data);
		point = n;
		++s;
	}

	void push_front(T&& data) // O(1) rvalue
	{
		node* point = this->head;
		node* n = new node(data);
		this->head = n;
		n->next = point;
		++s;
	}

	void push_front(T& data) // O(1)
	{
		node* point = this->head;
		node* n = new node(data);
		this->head = n;
		n->next = point;
		++s;
	}

	void pop_back() // O(n)
	{
		if (this->head == nullptr)
			return;

		node* point = this->head;

		while (point->next != nullptr)
			point = point->next;

		this->deleteNode(point);
		point = nullptr;
	}

	void pop_front() // O(1)
	{
		if (s == 0)
			return;
		node* next = this->head->next;
		this->deleteNode(this->head);
		this->head = next;
	}

	void clear()
	{
		node* cur = this->head;
		while (cur != nullptr)
		{
			node* next = cur->next;
			this->deleteNode(cur);
			cur = next;
		}
		this->head = nullptr;
	}

	void empty()
	{
		return !this->s;
	}



	iterator insert(const iterator& it, T&& data) // O(n) rvalue
	{
		iterator i = this->begin();
		node* n = new node(data);

		if (i == it)
		{
			node* next = this->head;
			this->head = n;
			n->next = next;
			i = this->begin();
		}
		else {
			auto in = ++(this->begin());
			node* prev = this->head;
			while (in != it)
			{
				++in;
				++i;
				prev = prev->next;
			}
			node* next = prev->next;
			prev->next = n;
			n->next = next;
			++i;
		}
		++s;

		return i;
	}

	iterator insert(const iterator& it, T& data) // O(n)
	{
		iterator i = this->begin();
		node* n = new node(data);

		if (i == it)
		{
			node* next = this->head;
			this->head = n;
			n->next = next;
			i = this->begin();
		}
		else {
			auto in = ++(this->begin());
			node* prev = this->head;
			while (in != it)
			{
				++in;
				++i;
				prev = prev->next;
			}
			node* next = prev->next;
			prev->next = n;
			n->next = next;
			++i;
		}
		++s;

		return i;
	}

	iterator insert(const iterator& it, iterator first, const iterator last)
	{
		node* firstNode = new node(*first);;
		node* lastNode = firstNode;
		int cnt = 1;
		for (; first != last; lastNode = lastNode->next)
		{
			lastNode->next = new node(*(++first));
			++cnt;
		}

		iterator i = this->begin();
		if (i == it)
		{
			node* next = this->head;
			this->head = firstNode;
			lastNode->next = next;
			i = this->begin();
		}
		else {
			auto in = ++(this->begin());
			node* prev = this->head;
			while (in != it)
			{
				++in;
				++i;
				prev = prev->next;
			}
			node* next = prev->next;
			prev->next = firstNode;
			lastNode->next = next;
			for(int j=0;j<cnt;j++)
				++i;
		}

		this->s += cnt;
		return i;
	}

	iterator remove(const iterator& position) {
		auto i = this->begin();
		if (i == position)
		{
			this->pop_front();
			i = this->begin();
		}
		else
		{
			auto in = ++(this->begin());
			node* prev = this->head;
			while (in != position)
			{
				++in;
				++i;
				prev = prev->next;
			}
			node* next = prev->next->next;
			this->deleteNode(prev->next);
			prev->next = next;
			++i;
		}

		return i;
	}

	iterator remove(const iterator& first, const iterator& last)
	{
		auto i = this->begin();
		node* prev = this->head;
		node* cur = this->head;
		node* next = nullptr;

		if (i != first)
		{
			while (++i != first)
				prev = prev->next;

			cur = prev->next;
		}
		while (i != last)
		{
			++i;
			next = cur->next;
			this->deleteNode(cur);
			cur = next;
		}

		prev == this->head ? this->head = next : prev->next = next;

		return last;
	}

	void sort(void (*func)() = nullptr) {
		std::cout << "hello" << std::endl;
		func();
	}
};

