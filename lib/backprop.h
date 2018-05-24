

#ifndef BACKPROP
#define BACKPROP

#include "../../lib/base.h"
#include "../../lib/common.h"
#include "../../lib/adaline.h"

#define DELTA 1
#define MOMENTUM 2
#define fori(x) for (int i = 0; i < (x); i++)

class BP_Node : public Feed_Forward_Node
{
protected:
	virtual double Transfer_Function(double value);
public:
	BP_Node(int v_size = 1, int e_size = 0);
	virtual char *Get_Name(void);
};

class BP_Link : public Base_Link
{
public:
	BP_Link(int size=2);
	virtual void Save(std::ofstream &outfile);	
	virtual void Load(std::ifstream &infile);
	virtual char *Get_Name(void);
	virtual void Update_Weight(double new_val);
};

class BP_Output_Node : public BP_Node
{
public:
	BP_Output_Node(double lr, double mt, int v_size=3, int e_size=1);
	// default value set is: NODE_VALUE, LEARNING_RATE, MOMENTUM
	// default error set is: NODE_ERROR
protected:
	virtual double Compute_Error(int mode=0);
	virtual void Learn(int mode=0);
	virtual char *Get_Name(void);
};

class BP_Middle_Node : public BP_Output_Node
{
public:
	BP_Middle_Node(double lr, double mt, int v_size=3, int e_size=1);
	// Same defuatl values as BP_Output_Node
	virtual char *Get_Name(void);
protected:
	virtual double Compute_Error(int mode=0);
};

double BP_Node::Transfer_Function(double value)
{
	return 1.0/(1.0 + exp(-value)); // Sigmoid function
};

BP_Node::BP_Node(int v_size, int e_size) : Feed_Forward:Node(v_size, e_size) {};

char *BP_Node::Get_Name(void)
{
	static char name[] = "BP_NODE";
	return name;
};

BP_Link::BP_Link(int size)
{
	value[WEIGHT] = Random(-1.0, 1.0);
	value[DELTA] = 0.0;
};









#endif

