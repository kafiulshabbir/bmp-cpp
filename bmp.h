#pragma once
#include <vector>
#include <string>

class bmp
{	
	class hex;
	struct colour;
	
	std::string file_name;
	
	struct Header;
	struct Pixels;
	
	Header header;
	Pixels pixels;
	
public:
	bmp() = delete;
	bmp(const std::string& file_name, int width_in_pixels, int height_in_pixels);
	~bmp();
	
	void save() const;
};

