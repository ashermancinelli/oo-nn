

#include <fstream>

#include "../../lib/base.h"
#include "../../lib/common.h"
#include "../../lib/adaline.h"
#define fori(x) for (int i = 0; i < (x); i++)

int main()
{
	double x, y, y1, output;
	std::ofstream outfile("lin2var.train");
	fori(250)
	{
		x = ((double)rand()/(double)RAND_MAX)*2.0-1;		
		y = ((double)rand()/(double)RAND_MAX)*2.0-1;		
		y1 = (-5*x - 2) / -4; 	// Random linear function for adaline to learn
		if (y < y1) output = 1;
		else output = -1;
		
		outfile << i << " " << x << " " << y << " " << " " << output << std::endl;
	}
	outfile.close();
}
