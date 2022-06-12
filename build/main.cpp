#include "drw.h"

int main()
{
	drw::bmp a("a.bmp", 1000, 1000);
	a.writeText(0, 0, 50, "[123456789.]");
	return 0;
}
