#ifndef HEADER_B_H
#define HEADER_B_H

#include <iostream>

class c
{
public:

	int ass;

	c() = default;
	c(int abs)
	{
		ass = abs;
	}
	
};

class b
{
	int number;
	int temp = 4;
	c c_with_ass(temp);
	
public:
	b(int n);
	void print();
};

#endif
