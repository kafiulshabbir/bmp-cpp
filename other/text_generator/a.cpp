#include <fstream>
#include <string>

int main()
{
	std::ofstream out("out.txt");
	const int height = 5;
	const int width = 3;
	out << "const std::vector<std::vector<bool>> asii_bool\n{\n";
	
	for(int c = 0; c <= 127; ++ c)
	{
		char q = c;
		out << "\t//char_n = " << c << ", char='" << q << "'\n";
		out << "\t{\n";
		for(int r = 0; r < height; ++ r)
		{
			out << "\t\t";
			for(int l = 0; l < width; ++ l)
			{
				out << '1';
				if(r + 1 < height || l + 1 < width)
				{
					out << ", ";
				}
			}
			
			out << '\n';
		}
		
		out << "\t}";
		if(c < 127)
		{
			out << ",\n";
		}
		out << '\n';
	}
	
	out << "};";
		
	return 0;
}
