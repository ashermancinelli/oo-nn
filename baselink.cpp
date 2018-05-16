

#include "baselink.h"

Base_Link::Base_Link(int size)
{
	id = ++ticket;
	value_size = size;
	if (value_size <= 0) value = NULL;
	else value = new double[value_size];
	for (int i = 0; i < value_size; i++)
		value[i] = 0.0;
	in_node = out_node = NULL;
};

Base_Link::~Base_Link(void) 
{
	if (value_size > 0) delete[] value;
};

void Base_Link::Set_In_Node(Base_Node *node, int id) { in_node = node; };

void Base_Link::Set_Out_Node(Base_Node *node, int id) { out_node = node; };

Base_Node Base_Link::In_Node(void) { return in_node; };

Base_Node Base_Link::Out_Node(void) { return out_node; };

void Base_Link::Save(ofstream &outfile) 
{
	outfile << id << std::endl;
	outfile << value_size;
	if (value) delete[] value;
	value = new double[value_size];
	for (int i = 0; i < value_size; i++)
		outfile << " " << setprecision(18) << value[i];
	outfile << std::endl;
};

void Base_Link::Load(ifstream &infile) 
{
	infile >> id;
	infile >> value_size;
	if (value) delete []value;
	value = new double[value_size];
	for (int i = 0; i < value_size; i++)
		infile >> value[i];	
};



