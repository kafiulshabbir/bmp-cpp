#include <fstream>
using namespace std;


int main()
{
	ofstream fout("out.dat", ios::binary);
	
	char a[] = {1, 2, 3};
	
	fout.write((char *) &a, 3);
	
	return 0;
}
