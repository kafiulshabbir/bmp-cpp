#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
const std::string INPUT_BINARY_NAME = "input.bmp";

char IntToChar(int n)
{
	if(n < 10)
	{
		return '0' + n;
	}
	
	return 'A' + n - 10;
}

int ByteSectionToInt(char c, int a, int b)
{
	int pow = 1;
	int sum = 0;
	for(int i = a; i < b; ++ i)
	{
		sum += pow * ((c >> i) & 1);
		pow *= 2;
	}
	
	//std::cout << "char is: " << c << " int: " << int(c) << " from " << a << " to " << b << " is sum = " << sum << '\n';
	return sum;
}

std::string ByteToHex(char c)
{
	return {IntToChar(ByteSectionToInt(c, 4, 8)), IntToChar(ByteSectionToInt(c, 0, 4))};
}
	
std::vector<int> Read()
{
	std::ifstream ipt(INPUT_BINARY_NAME, std::ios::binary);
	char buffer[100];
	std::cout << "current adddress: " << &buffer << std::endl;
	
	ipt.read(buffer, 100);
	
	std::cout << "final address: " << &buffer << std::endl;
	for(int i = 0; i < 100; ++ i)
	{
		std::cout << ByteToHex(buffer[i]) << ' ';
	}
	
	return std::vector<int>{1,2 ,3};
}

int main()
{
	Read();
	
	return 0;
	
}
