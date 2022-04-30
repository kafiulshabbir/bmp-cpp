#include <fstream>
#include <iostream>
#include <string>
#include <vector>
const std::string INPUT_BINARY_NAME = "input.bmp";

std::vector<int> Read()
{
	std::ifstream ipt(INPUT_BINARY_NAME, std::ios::binary);
	char buffer[100];
	std::cout << "current adddress: " << *buffer << std::endl;
	
	ipt.read(buffer, 100);
	
	std::cout << "final address: " << *buffer << std::endl;
	for(int i = 0; i < 100; ++ i)
	{
		char j = buffer[i];
		std::cout << j << ", ";
	}
	
	return std::vector<int>{1,2 ,3};
}

int main()
{
	Read();
	
	return 0;
	
}
