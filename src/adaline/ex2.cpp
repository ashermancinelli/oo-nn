

// ADALINE Example program 
// Different from ex1.cpp becuase this uses the ADALINE_Network constructor
// instead of manually creating and training all the nodes.

#include <cstdio>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ncurses.h>
#include <cassert>
#include "../../lib/adaline.h" 
#include "../../lib/common.h"

int main()
{
	std::srand(1);

	Pattern *data[250];
	std::ifstream infile("src/adaline/lin2var.train");
	if (infile.fail()) 
	{
		std::cout << "Could not open pattern file...\n";
		return 1;
	}
	fori(250)
		data[i] = new Pattern(2, 1, infile);
	
	infile.close();

	ADALINE_Network a(2, 0.45); // input size of 2, learning rate of 0.45

	int iteration = 0;
	int good = 0;
		
	while (good < 250)
	{
		good = 0;

		fori(250)
		{
			a.Set_Value(data[i]);
	
			a.Run();
	
			if (data[i]->Out(0) != a.Get_Value())
			{
				a.Learn();
				break;
			}
			else good++;
			std::cout << iteration << ".  " << good << "/250\n";
			iteration++;
		}
	}

	std::ofstream outfile("src/adaline/test.data");
	a.Save(outfile);
	outfile.close();
	
	ADALINE_Network b("src/adaline/test.data");

	int total = 0;
	int correct = 0;
	
	fori(250)
	{
		b.Set_Value(data[i]);
		b.Run();
		std::cout << std::setw(3) << i << "  Net: " << std::setprecision(7)
			<< b.Get_Value() << "  Actual: " << std::setprecision(7)
			<< data[i]->Out(0) << std::endl;
		if (b.Get_Value() == data[i]->Out(0)) correct++;
		total++;
	}
	
	std::cout << "ADALINE Performance: " << correct << "/" << total << " correct.\n";

	return 0;
}







