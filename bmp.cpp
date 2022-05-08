#include "bmp.h"

//----------------------bmp::hex----------------------//
class bmp::hex
{
	unsigned int info;
	unsigned int size;
public:
	hex() = delete;
	hex(unsigned int info, unsigned int size);
	unsigned int& operator();
	std::string binary();
};

bmp::hex::hex(unsigned int info, unsigned int size):
	info(info), size(size) {}

unsigned int& bmp::hex::operator[]
{
	return info;
}

std::string bmp::hex::binary()
{
	std::string s(size, '\0');
	for(unsigned int i = 0; i < size; ++ i)
	{
		s[i] = (info >> (8 * i));
	}
	
	return s;
}

//----------------------bmp::colour----------------------//
struct bmp::colour
{
	unsigned int blue;
	unsigned int green;
	unsigned int red;
	
	static unsigned int size_bytes = 3;
	
	std::string binary();	
};

std::string bmp::colour::binary()
{
	std::string s(3, '\0');
	s[0] = blue;
	s[1] = green;
	s[2] = red;
	
	return s;
}
	
//----------------------bmp::BmpHeader----------------------//
class bmp::Header
{
	const unsigned int bmp_header_size = 54;
	const unsigned int padding_factor = 4;
	
	// BMP Header, size  = 14
	const hex initial_char_first('B', 1);
	const hex initial_char_second('M', 1);
	hex total_file_size(bmp_header_size, 4); //[SIZE]
	const hex application_specific_gap(0, 4);
	const hex offset_start_image(54, 4);
	
	//Dip Header, size = 40
	const hex dib_header_size(40, 4);
	hex width_in_pixels(0, 4);
	hex height_in_pixels(0, 4);
	
	unsigned int padding;
	
	const hex number_of_colour_planes_used(1, 2);
	const hex bits(24, 2);
	const hex compression(0, 4);
	
	hex size_raw_bitmap(0, 4); //[SIZE] if raw bit map data including padding
	hex resolution_horizontal(2835, 4); //print resolution in pixel/meter
	hex resolution_vertical(2835, 4);

	const hex number_of_colours_in_palette(0, 4);
	const hex important_colours(0, 4); //0 implies that all col;ours are important
	
	static unsigned int pad(unsigned int a,  unsigned int b);

public:
	void set_width(unsigned int width_in_pixels);
	void set_height(unsigned int height_in_pixels);
	
	void update_padding();
	void update_size();
	
	std::vector<hex> vector();
};

void bmp::Header::update_padding()
{
	padding = pad(colour::size_bytes * width, padding_factor);
}

void bmp::Header::set_width(unsigned int width_in_pixels)
{
	width_in_pixels[] = width_in_pixels;
}

void bmp::Header::set_height(unsigned int height_in_pixels)
{
	height_in_pixels[] = height_in_pixels;
}

void bmp::Header::update_size()
{
	size_raw_bitmap[] = ((width_in_pixcels[] * colour::size_bytes) + padding) * height_in_pixels[];
}
	
std::vector<bmp::hex> bmp::Header::vector()
{
	std::vector<bmp_info> v(16);
	v[0] = initial_char_first;
	v[1] = initial_char_second;
	v[2] = total_file_size;
	v[3] = application_specific_gap;
	v[4] = offset_start_image;
		
	v[5] = dib_header_size;
	v[6] = width_in_pixels;
	v[7] = height_in_pixels;
	
	v[8] = number_of_colour_planes_used;
	v[9] = bits;
	v[10] = compression;
	
	v[11] = size_raw_bitmap;
	v[12] = resolution_horizontal;
	v[13] = resolution_vertical;

	v[14] = number_of_colours_in_palette;
	v[15] = important_colours;
	
	return v;
}

static unsigned int bmp::Header::pad(unsigned int a,  unsigned int b)
{
	return ((a + b - 1) / b ) * b - a;
}

//--------------------Pixcels-------------------
struct bmp::Pixcels
{
	vector<vector<colour>> matrix;
	
	
};

//------------------bmp::main_functions()--------------------
bmp::bmp(const std::string& bmp_file_name, int width_in_pixels, int height_in_pixels)
{
	file_name = bmp_file_name;
	header.set_width(width_in_pixels);
	header.set_height(height_in_pixels);
	
	header.update_padding();
	header.update_size();
}

bmp::~bmp()
{
	save();
}

void bmp::save() const
{
	
}

