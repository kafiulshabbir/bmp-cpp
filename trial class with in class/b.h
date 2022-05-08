#ifndef HEADER_B_H
#define HEADER_B_H

#include <iostream>

class c
{
public:

	int ass;

	c()
	{
		ass = 4;
	}
	
};

class b
{
	int number;
	c c_with_ass;
	
public:
	b(int n);
	void print();
};

#endif
