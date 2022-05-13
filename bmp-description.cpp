#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class bmp
{
	
	struct hex
	{
		unsigned int info;
		unsigned int size;
		
		unsigned int& operator() ()
		{
			return info;
		}
		
		unsigned int operator() () const
		{
			return info;
		}
		
		std::string binary() const
		{
			std::string s(size, '\0');
			for(unsigned int i = 0; i < size; ++ i)
			{
				s[i] = (info >> (8 * i));
			}
			
			return s;
		}
	};

	struct colour
	{
		unsigned int blue;
		unsigned int green;
		unsigned int red;
		
		static const unsigned int size_bytes = 3;
		
		std::string binary() const
		{
			std::string s(3, '\0');
			s[0] = blue;
			s[1] = green;
			s[2] = red;
			
			return s;
		}
	};
	
	std::string file_name;
	
	
	static const unsigned int bmp_header_size = 54;
	static const unsigned int padding_factor = 4;

	// BMP Header, size  = 14
	const hex initial_char_first{'B', 1};
	const hex initial_char_second{'M', 1};
	hex total_file_size{0, 4}; //[SIZE]
	const hex application_specific_gap{0, 4};
	const hex offset_start_image{bmp_header_size, 4};
	
	//Dip Header, size = 40
	const hex dib_header_size{40, 4};
	hex width_in_pixels{0, 4};
	hex height_in_pixels{0, 4};
	
	unsigned int padding;
	
	const hex number_of_colour_planes_used{1, 2};
	const hex bits{24, 2};
	const hex compression{0, 4};
	
	hex size_raw_bitmap{0, 4}; //[SIZE] if raw bit map data including padding
	hex resolution_horizontal{2835, 4}; //print resolution in pixel/meter
	hex resolution_vertical{2835, 4};

	const hex number_of_colours_in_palette{0, 4};
	const hex important_colours{0, 4}; //0 implies that all col;ours are important
	
	static unsigned int pad(unsigned int a,  unsigned int b)
	{
		return ((a + b - 1) / b ) * b - a;
	}
	
	void update_padding()
	{
		padding = pad(colour::size_bytes * width_in_pixels(), padding_factor);
	}
	
	void update_size()
	{
		size_raw_bitmap() = ((width_in_pixels() * colour::size_bytes) + padding) * height_in_pixels();
		total_file_size() = size_raw_bitmap() + bmp_header_size;
	}
	
	std::vector<hex> vector_heading() const
	{
		std::vector<hex> v(16);
		
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
	
	std::string generate_head() const
	{
		auto v = vector_heading();
		std::string s;
		
		for(const auto& x: v)
		{
			s += x.binary();
		}
		
		return s;
	}
	
	std::string generate_picture() const
	{
		std::string s;
		s.reserve(total_file_size());
		for(const auto& row: matrix)
		{
			for(const auto& x: row)
			{
				s += x.binary();
			}
			
			for(unsigned int i = 0; i < padding; ++ i)
			{
				s += zero;
			}
		}
		
		return s;
	}
	
	std::string give_me_zeros()
	{
		hex zero{0, 1};
		return zero.binary();
	}
	
	const std::string zero = give_me_zeros();
	
	std::vector<std::vector<colour>> matrix;
	void resize_matrix()
	{
		matrix.resize(height_in_pixels(), std::vector<colour>(width_in_pixels(), {255, 0, 255}));
	}
	
	std::string generate_file() const
	{
		std::cout << "head size is: " << generate_head().size() << '\n';
		return generate_head() + generate_picture();
	}
	
public:
	bmp() = delete;
	bmp(const std::string& bmp_file_name, int width_in_pixels, int height_in_pixels)
	{
		file_name = bmp_file_name;
		this->width_in_pixels() = width_in_pixels;
		this->height_in_pixels() = height_in_pixels;
		
		update_padding();
		update_size();
		resize_matrix();
	}
	
	~bmp()
	{
		save();
	}
	
	void save() const
	{
		std::ofstream fout(file_name, std::ios::binary);
		auto s = generate_file();
		fout.write(s.data(), s.size());
	}
};
	

int main()
{
	bmp a("a.bmp", 2000, 2000);
		
	return 0;
}



