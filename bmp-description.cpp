#include <vector>
#include <string>
	
class BmpFile
{
private:
	struct bmp_info;
	
	struct BmpHeader;
	struct PixelArray;
};

struct BmpFile::bmp_info
{
	unsigned int info;
	size_t size;
};

class BmpFile::BmpHeader
{
	const bmp_info initial_char_first = {'B', 1};
	const bmp_info initial_char_second = {'M', 1};
	bmp_info total_file_size = {70, 4};
	const bmp_info application_specific_gap = {0, 4};
	const bmp_info offset_start_image = {54, 4};

public:
	std::vector<bmp_info> vector()
	{
		std::vector<bmp_info> v(5);
		v[0] = initial_char_first;
		v[1] = initial_char_second;
		v[2] = total_file_size;
		v[3] = application_specific_gap;
		v[4] = offset_start_image;
		
		return v;
	};
};

struct BmpFile::DibHeader
{
};

int main()
{
	
	
	
	return 0;
}



