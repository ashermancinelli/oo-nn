

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







#endif

