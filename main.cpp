#include <iostream>
#include "LinkedList.h"
#include "DoublyLinkedList.h"

#include <list>
#include <iterator>

#include <vector>

using namespace std;

enum {SUCESS = 0, FAILCLEAR, FAILPUSH, FAILPOP, FAILINSERT, FAILREMOVE};

int slistTest(LinkedList<int> *l)
{
	int tempValue[] = {30, 14, 90, 65, 100, 34, 76, 54, 104, 200, 200, 12, 1111};
	int length = sizeof(tempValue) / sizeof(int);
	int resultCode = -1;

	// push_front test with iterator
	for(int i=0;i<length;i++)
		l->push_front(tempValue[i]);
	auto it = l->begin();
	for (int i = length-1; i >= 0; i--)
	{
		if (*it != tempValue[i])
			return resultCode;
		++it;
	}

	if (l->size() != length)
		return resultCode;

	resultCode--;

	// pop_front with iterator
	for (int i = 0; i < 5; i++)
		l->pop_front();
	it = l->begin();
	for (int i = length-1 - 5; i >= 0; i--)
	{
		if (*it != tempValue[i])
			return resultCode;
		if(i != 0)
			++it;
	}

	if (l->size() != length-5)
		return resultCode;

	resultCode--;

	// insert with iterator
	auto iit = l->insert(it, 12345);
	if (*iit != 12345)
		return resultCode;
	if (++iit != it)
		return resultCode;


	if (l->size() != length-4)
		return resultCode;

	l->clear();
	if (l->size() != 0)
		return resultCode;

	// insert test
	iit = l->begin();
	for (int i = length -1; i >= 0; i--)
	{
		iit = l->insert(iit, tempValue[i]);
		if (*iit != tempValue[i])
			return resultCode;
	}

	for (int i = 0; i < length-1; i++)
	{
		if(*iit != tempValue[i])
			return resultCode;
		++iit;
	}

	// insert function test required & rvalue

	auto firstIt = l->begin();
	iit = l->begin();
	auto nextIt = ++(++iit);

	iit = l->insert(iit, firstIt, nextIt);
	if (*iit != *nextIt)
		return resultCode;

	// remove
	l->remove(iit);

	l->clear();

	// remove range

	for (int i = length - 1; i >= 0; i--)
	{
		l->insert(l->begin(),tempValue[i]);
		if (*(l->begin()) != tempValue[i])
			return resultCode;
	}
	iit = l->begin();
	for (int i = length - 1; i > 0; i--)
		++iit;

	l->remove(l->begin(),iit);
	if (*iit != tempValue[length - 1])
		return resultCode;


	return 0;
}

bool func(const int& v)
{
	return v > 5;
}

int dlistTest(DoublyLinkedList<int>& dl)
{
	// initializing test
	int* testValues;
	int length = 100;
	testValues = new int[length];
	for (int i = 0; i < length; ++i)
		testValues[i] = i;

	DoublyLinkedList<int>::iterator globalIterator; // global iterator. initialize before use it

	// test begin
	{ 
		// test push_front
		for(int i=0;i<length;++i)
			dl.push_front(i);
		
		globalIterator = dl.end();
		for (int i = 0; i < length; ++i)
		{
			if (testValues[i] != *globalIterator)
				return FAILPUSH;
			--globalIterator;
		}

		// test pop_front
		for (int i = 0; i < length / 2; i++)
		{
			if (dl.front() != testValues[i])
				return FAILPOP;
			dl.pop_front();
		}

		// test pop_back
		for (int i = 0; i < length / 2; i++)
		{
			if (dl.back() != testValues[length - i])
				return FAILPOP;
			dl.pop_back();
		}

		
		// test push_back
		for (int i = 0; i < length; ++i)
			dl.push_back(i);

		globalIterator = dl.begin();
		for (int i = 0; i < length; ++i)
		{
			if (testValues[i] != *globalIterator)
				return FAILPUSH;
			++globalIterator;
		}

		// test clear
		dl.clear();
		if (dl.size() != 0)
			return FAILCLEAR;

		// test insert front with no data in it
		for (int i = 0; i < length; i++)
			dl.insert(dl.begin(), testValues[i]);

		globalIterator = dl.end();
		for (int i = 0; i < length; i++)
		{
			if (*globalIterator != testValues[i])
				return FAILINSERT;
			--globalIterator;
		}

		// test clear
		dl.clear();
		if (dl.size() != 0)
			return FAILCLEAR;

		// test insert next with no data in it
		dl.push_front(testValues[0]);
		globalIterator = dl.begin();
		for (int i = 1; i < length; i++)
			dl.insert(globalIterator++, testValues[i]);

		globalIterator = dl.begin();
		for (int i = 0; i < length; i++)
		{
			if (*globalIterator != testValues[i])
				return FAILINSERT;
			++globalIterator;
		}

		// test remove between iterator
		dl.remove(dl.begin(), dl.end());
		if (dl.size() != 1)
			return FAILREMOVE;

	
	}

	delete testValues;

	return SUCESS;
}

int main()
{
	LinkedList<int> l;

	int result = 0;
	//slistTest(&l);

	DoublyLinkedList<int> dl;
	dl.push_front(13);
	dl.push_front(14);
	dl.push_front(15);
	dl.push_front(16);
	auto a = dl.begin();
	auto b = dl.insert(a, 21);
	auto c = dl.insert(b, 22);

	dl.insert(c,c,a);

	DoublyLinkedList<int> dl2 = dl;

	dl2.clear();

	dl2 = dl;

	dl = dl2;


	DoublyLinkedList<int> dl3 = dl + dl2;

	for (auto at : dl3)
		cout << at << endl;

	dl3.swap(dl);

	dl3.remove_if(func);

	switch (result)
	{
	case 0:
		cout << "All test passed" << endl;
		break;
	default:
		cout << "test failed with "<<result << endl;
		break;
	}


	return 0;
}