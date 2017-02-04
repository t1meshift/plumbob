#include <iostream>

#include "rawhid\hid.h"

int pb_init();
int pb_set_color(int r, int g, int b);

int main()
{
	if (pb_init() <= 0)
	{
		std::cout << "Plumbob not found!";
		return 1;
	}
	if (pb_set_color(0,0,128) != -1)
		std::cout << "Done!" << std::endl;
	else
		std::cout << "An error has occured!" << std::endl;
	return 0;
}

//returns connected Plumbobs count
int pb_init()
{
	return rawhid_open(1, 0x1038, 0x1500, 0xFFC0, 0x0001); // USB\VID_1038&PID_1500
}

//returns -1 on error
int pb_set_color(int r, int g, int b)
{
	unsigned char buf[64];
	buf[0] = 0x07; //looks like special header
	buf[1] = 0x00; //if i change this, plumbob won't respond
	buf[2] = r;   //R
	buf[3] = g;   //G
	buf[4] = b;   //B
	for (int i = 5; i < 64; i++) {
		buf[i] = 0; //because our packets are 64 byte long
	}
	return rawhid_send(0, buf, 32, 100);
}

