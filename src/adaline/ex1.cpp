

/*
Purpose:
	To showcase the use of ADALINE Nodes. The data is created 
	with the training file in the same dir. Uses nodes at 
	the most basic level to their flexibility can be demonstrated
*/

#define fori(x) for (int i = 0; i < (x); i++)
#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <curses.h>
#include <cassert>
#include "../../lib/adaline.h" 
#include "../../lib/common.h"

int main()
{
	std::srand(1);
	int i;

	// Loading training set
	std::cout << "Loading training data:\n";
	Pattern *data[250];
	std::ifstream infile("src/adaline/lin2var.train");
	
	if(infile.fail())
	{
		std::cout << "Unable to open training data file...\n";
		return 1;		
	}
	
	fori(250)
	{
		data[i] = new Pattern(2, 1, infile);
		data[i]->Print();
	}
	
	infile.close();

	// Create ADALINE Network
	std::cout << "Creating ADALINE Network:\n";
	Base_Node *Node[4];
	Base_Link *Link[3];
	
	Node[0] = new Input_Node;
	Node[1] = new Input_Node;
	Node[2] = new Bias_Node;
	Node[3] = new ADALINE_Node(0.45);	// Learning rate of 0.45
	
	
	Link[0] = new ADALINE_Link;
	Link[1] = new ADALINE_Link;
	Link[2] = new ADALINE_Link;

	Connect(Node[0], Node[3], Link[0]);	
	Connect(Node[1], Node[3], Link[1]);
	Connect(Node[2], Node[3], Link[2]);

	// Training step
	std::cout << "Training Network:\n";
	int iteration = 0;
	int good = 0;

	// good is the number of patterns fed to the 
	// network that the network gets correct.
	// In this case, the acceptable error is 0, 
	// so this will run until the network gets 
	// every pattern correct. The good var is 
	// reset becasue adjusting weights will 
	// change performance on other data sets, and adaline 
	// has to be perfect on every dataset
	while (good < 250)
	{
		good = 0;
		fori(250)
		{
			Node[0]->Set_Value(data[i]->In(0));
			Node[1]->Set_Value(data[i]->In(1));
			
			Node[3]->Run();
	
			if (data[i]->Out(0) != Node[3]->Get_Value())
			{
				Node[3]->Learn();
				break;
			}
			else good++;
		}
		std::cout << iteration << ".  " << good << "/250" << std::endl;
		iteration++;
	}	

	// Save ADALINE Node weights 
	std::cout << "Saving ADALINE Node weights:\n";
	
	std::ofstream outfile("src/adaline/adaline1.net");

	fori(4)
		Node[i]->Save(outfile);
	fori(3)
		Link[i]->Save(outfile);

	outfile.close();
	
	fori(4)
		delete Node[i];
	fori(3)
		delete Link[i];

	// Create another ADALINE Network
	std::cout << "Re-creating ADALINE Network:\n";
	Node[0] = new Input_Node;
	Node[1] = new Input_Node;
	Node[2] = new Bias_Node;
	Node[3] = new ADALINE_Node;

	Link[0] = new ADALINE_Link;	
	Link[1] = new ADALINE_Link;
	Link[2] = new ADALINE_Link;

	Connect(Node[0], Node[3], Link[0]);	
	Connect(Node[1], Node[3], Link[1]);
	Connect(Node[2], Node[3], Link[2]);

	// Load ADALINE Weights into the network 
	std::cout << "Loading previous weigts into network:\n";
	infile.open("src/adaline/adaline1.net");
	fori(4)
		Node[i]->Load(infile);
	fori(3)
		Link[i]->Load(infile);
	infile.close();
	
	// Run the network reloaded into topography
	std::cout << "Running the reloaded network:\n";

	int correct = 0;
	int total = 0;

	fori(250)
	{
		Node[0]->Set_Value(data[i]->In(0));
		Node[1]->Set_Value(data[i]->In(1));
		// Node 2 does not need to be set because 
		// it is a bias node and will always yeild 1

		Node[3]->Run();
		
		std::cout << "Pattern: " << std::setw(3) << i << " Input: ("
			<< data[i]->In(0) << ","
			<< data[i]->In(1) << ")  ADALINE:"
			<< std::setw(3) << Node[3]->Get_Value() << "  Actual:"
			<< std::setw(3) << data[i]->Out(0) << std::endl;
		if (Node[3]->Get_Value() == data[i]->Out(0)) correct++;
		total++;
	}
	
	std::cout << "ADALINE's score: " << correct << "/" << total << std::endl;	
	std::cout << "Cleaning up...\n";
	fori(4)
		delete Node[i];
	fori(3)
		delete Link[i];

	return 0;
}




