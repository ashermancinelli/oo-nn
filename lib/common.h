

#include "base.h"


#ifndef COMMON
#define COMMON
#define fori(x) for (int i = 0; i < (x); i++)


class Input_Node : public Base_Node
{
	
public:
	Input_Node(int size=1 )
	{
		fori(size)
		{
			error[i] = 0.0;
			value[i] = 0.0;
		};		
	};

	virtual char *Get_Name(void)
	{
		static char name[] = "INPUT_NODE";
		return name;
	};

};


class Bias_Node : public Input_Node 
{
public:
	Bias_Node(double bias = 1) : Input_Node(1) { value[0] = bias; };
	virtual void Set_Value(double value, int id = 0) {}; // Disabling set value func
	virtual double Get_Value(int id = 0) { return value[0]; };
	virtual char *Get_Name(void) 
	{ 
		static char name[] = "BIAS_NODE";
		return name;
	};
};


#endif


