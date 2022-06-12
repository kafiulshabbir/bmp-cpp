#include "drw.h"

namespace drw
{
	//--Class::hex------------------------------------------------------
	hex::hex(unsigned int value, unsigned int size): value(value), size(size) {}
	std::string hex::binary() const
	{
		std::string s(size, '\0');
		
		for(unsigned int i = 0; i < size; ++ i)
		{
			s[i] = (value >> (size_of_byte * i));
		}
		
		return s;
	}
	
	//--Function-vector<hex> -> binary----------------------------------
	std::string binary(const std::vector<hex>& vector_hex)
	{
		std::string string_binary;
		for(const auto& elem_vector_hex: vector_hex)
		{
			string_binary += elem_vector_hex.binary();
		}
		
		return string_binary;
	}

	//--Class::colour---------------------------------------------------

	colour::colour(): red(0), green(0), blue(0) {}
	colour::colour(unsigned char red, unsigned char green, unsigned char blue): red(red), green(green), blue(blue) {}
	std::string colour::binary() const
	{
		return binary(std::vector<hex>{hex(blue, 1), hex(green, 1), hex(red, 1)});
	}

	//--Class::matrix_colours-------------------------------------------
	matrix_colours::matrix_colours(int height, int width, const colour& bg_colour): matrix(height, std::vector<colour>(width, bg_colour)) {}
	colour& matrix_colours::operator () (int row, int col)
	{
		return matrix[matrix.size() - row - 1][col];
	}
	colour matrix_colours::operator () (int row, int col) const
	{
		return matrix[matrix.size() - row - 1][col];
	}
	int matrix_colours::height const
	{
		return matrix.size();
	}
	int matrix_colours::width() const
	{
		return matrix.front().size();
	}
	
	
	//--Class::bmp------------------------------------------------------
	///---Constructors--------------------------------------------------
	bmp::bmp(const std::string& file_name, int height, int width, const colour& bg_colour):
	file_name(file_name), height(height), width(width), padding(padding_calculate()), bg_colour(bg_colour), fg_colour(black), matrix(height, width, bg_colour){}
	bmp::~bmp()
	{
		save();
	}
	
	///---Binary-generators---------------------------------------------
	std::string bmp::binary_head() const
	{
		// BMP Header, size  = 14
		const hex initial_char_first('B', 1);
		const hex initial_char_second('M', 1);
		const hex total_file_size(size_file(), 4); //[SIZE]
		const hex application_specific_gap(0, 4);
		const hex offset_start_image(SIZE_HEADER_BMP, 4);
		
		//Dip Header, size = 40
		const hex dib_header_size(SIZE_DIB_HEADER_BMP, 4);
		const hex width_in_pixels(width, 4);
		const hex height_in_pixels(height, 4);
		
		const hex number_of_colour_planes_used(1, 2);
		const hex bits(24, 2);
		const hex compression(0, 4);
		
		const hex size_raw_bitmap(size_bitmap(), 4); //[SIZE] if raw bit map data including padding
		const hex resolution_horizontal(2835, 4); //print resolution in pixel/meter
		const hex resolution_vertical(2835, 4);

		const hex number_of_colours_in_palette(0, 4);
		const hex important_colours(0, 4); //0 implies that all col;ours are important
		
		return binary(vector<hex> v
		{
			initial_char_first,	initial_char_second, total_file_size, application_specific_gap,	offset_start_image,		
			dib_header_size, width_in_pixels, height_in_pixels,	number_of_colour_planes_used, bits,	compression,
			size_raw_bitmap, vresolution_horizontal, resolution_vertical, number_of_colours_in_palette, important_colours,
		});
		
	}
	std::string bmp::binary_bitmap() const
	{
		std::string s;
		s.reserve(size_bitmap());
		for(const auto& row: matrix)
		{
			for(const auto& x: row)
			{
				s += x.binary();
			}
			
			s += std::string(padding, '\0');
		}
		
		return s;
	}
	std::string bmp::binary() const
	{
		return binary_head() + binary_bitmap();
	}
	void bmp::save() const
	{
		std::ofstream fout(file_name, std::ios::binary);
		std::string = binary();
		fout.write(s.data(), s.size());
	}
	
	///---Size-generators-----------------------------------------------
	int bmp::size_bitmap() const
	{
		return height * (width * colour::size_colour_bytes + padding);
	}
	int bmp::size_file() const
	{
		return SIZE_HEADER_BMP + size_bitmap();
	}
	int bmp::padding_calculate() const
	{
		return ((colour::size_colour_bytes * width + PADDING_FACTOR_BMP - 1) / PADDING_FACTOR_BMP) * PADDING_FACTOR_BMP - colour::size_colour_bytes * width;
	}
	
	///---Tools---------------------------------------------------------
	void intercept(int row, int col, const matrix_colours& cover_matrix, bool transperency)
	{
		for(int i = 0; i < cover_matrix.height(); ++ i)
		{
			for(int j = 0; j < cover_matrix.width(); ++ j)
			{
				if(transperency && cover_matrix(i, j) == bg_colour)
				{
					continue;
				}
				main_matrix(row + i, col + j) = cover_matrix(i, j);
			}
		}
	}
	void bmp::setBgColour(const colour& bg_colour_new)
	{
		bg_colour = bg_colour_new;
	}
	void bmp::setFgColour(const colour& fg_colour_new)
	{
		fg_colour = fg_colour_new;
	}
	
	///---Drawing-------------------------------------------------------
	void drawRectangle(int row_from, int col_from, int row_to, int col_to)
	{
		drawRectangle(row_from, row_to, col_from, col_to, fg_colour);
	}
	void bmp::drawRectangle(int row_from, int col_from, int row_to, int col_to, const colour& colour_draw);
	{
		int row1 = std::min(row_from, row_to);
		int row2 = std::max(row_from, row_to);
		
		int col1 = std::min(col_from, col_to);
		int col2 = std::max(col_from, col_to);
		
		intercept(row1, col1, matrix_colours(row2 - row1 + 1, col2 - col1 + 1, colour_draw), false);
	}
	void drawCentreRectangle(int row_centre, int col_centre, int height, int width)
	{
		drawCentreRectangle(row_centre, col_centre, height, width, fg_colour);
	}
	void drawCentreRectangle(int row_centre, int col_centre, int height, int width, const colour& colour_draw)
	{
		drawRectangle(row_centre - (height - 1) / 2, col_centre - (width - 1) / 2, row_centre + height / 2, col_centre + width / 2, colour_draw);
	}
	void drawCentreSquare(int row_centre, int col_centre, int diamension)
	{
		drawCentreSquare(int row_centre, int col_centre, int diamension, fg_colour);
	}
	void drawCentreSquare(int row_centre, int col_centre, int diamension, const colour& colour_draw)
	{
		drawCentreRectangle(row_centre, col_centre, diamension, diamension, colour_draw);
	}
	
	///---Text-------------------------------------------------------
	matrix_colours bmp::makeChar(int symbol, int scale, const colour& colour_text, const colour& colour_text_back)
	{
		const std::vector<bool>& vec_char_bool = drw_text::ascii_bool[c];
		matrix_colours char_matrix(drw_text::height * scale, drw_text::width * scale, colour_text_back)
		
		for(int row = 0; row < char_matrix.height(); ++ row)
		{
			for(int col = 0; col < char_matrix.width(); ++ col)
			{
				int i = row / drw_text::height;
				int j = col / drw_text::width;
				
				char_matrix(row, col) = 
		
		
	}
	void bmp::writeChar(int x, int y, int scale, int character, const colour& colour_text)
	{
		std::vector<std::vector<bool>> matrix_char = ascii_matrix(character);
		std::vector<std::vector<bool>> w = scale_char(matrix_char, scale);
		
		for(const auto& row_char: w)
		{
			int col = x;
			for(auto cell: row_char)
			{
				if(cell)
				{
					matrix[y][col] = colour_text;
				}
				++ col;
			}
			++ y;
		}
	}
	void writeText(int row, int col, int height, const std::string& text)
	{
		writeText(row, col, height, text, fg_colour);
	}
	void writeText(int row, int col, int height, const std::string& text, const colour& colour_text)
	{
		int scale = std::min(1, height / drw_text::height);
		for(char symbol: text)
		{
			writeChar(row, col, scale, symbol, colour_text);
			col += (drw_text::width + 1) * scale;
		}
	}	
}
