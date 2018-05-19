

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "../../lib/base.h"


int main(void) 
{
	Base_Node Node[6];
	Base_Link Link[8];
	Connect(Node[0], Node[2], Link[0]);	
	Connect(Node[0], Node[3], Link[1]);
	Connect(Node[1], Node[2], Link[2]);
	Connect(Node[1], Node[3], Link[3]);
	Connect(Node[2], Node[4], Link[4]);
	Connect(Node[2], Node[5], Link[5]);
	Connect(Node[3], Node[4], Link[6]);
	Connect(Node[3], Node[5], Link[7]);

	std::ofstream outfile("src/329/output.dta");
	
	for (int i = 0; i < 6; i++)
		Node[i].Print(outfile);
	
	outfile.close();
	return 0;
}








