#pragma once
class list
{
protected:
	unsigned int s;
public:
	list()
	{
		s = 0;
	}
	virtual bool isEmpty()
	{
		return s == 0;
	}
	virtual unsigned int size()
	{
		return s;
	}
};

