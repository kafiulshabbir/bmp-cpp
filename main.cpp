#include "drw.h"

int main()
{
	drw::bmp image("image.bmp", 1000, 200, drw::green);
	image.drawRectangle(10, 20, 30, 50, drw::blue);
	image.writeText(10, 10, 30, "0123456789");
	return 0;
}
