#include <iostream>
#include "pcapx.h"

using namespace std;

int create()
{
	PcapIfs *ifs = new PcapIfs;
	return 0;
}

#include <WinBase.h>

int main(int argc, char* argv[])
{
	try {
		
		create();
	
	}
	catch (...)
	{
		
		return 0;
	}
	/*Netif netif;
	netif.list();

	cout << "device number to open: " << flush;
	unsigned int index = 0;
	cin >> index;
	netif.open(index);

	return 0; */
}

