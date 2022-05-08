#include "b.h"

b::b(int n)
{
	number = n;
}

void b::print()
{
	std::cout << "hi, the number is: " << number << ", while c.ass is: " << c_with_ass.ass << '\n';
}
