

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

void BP_Link::Save(std::ofstream &outfile)
{
	outfile << std::setw(4) << id << " " << std::setprecision(18)
		<< value[WEIGHT] << " " << std::setw(4)
		<< In_Node()->Get_ID() << " "
		<< std::setw(4) << Out_Node()->Get_ID() << std::endl;
};

char *BP_Link::Get_Name(void)
{
	static char name[] = "BP_LINK";
	return name;
};

void BP_Link::Update_Weight(double new_val)
{
	double momentum = Out_Node()->Get_Value(MOMENTUM);
	value[WEIGHT] += new_val + (momentum * value[DELTA]);
	// update weight with current change times the momentum, 
	// and store the previous value for next calculation

	value[DELTA] += new_val;
};

BP_Output_Node::BP_Output_Node(double lr, double mt, int v_size, int e_size) : BP_Node(v_size, e_size)
{
	value[LEARNING_RATE] = lr;
	value[MOMENTUM] = mt;
};

double BP_Output_Node::Compute_Error(int mode);
{
	return value[NODE_VALUE] * (1.0 - value[NODE_VALUE]) * (error[NODE_ERROR] - value[NODE_VALUE]);
};

void BP_Output_Node::Learn(int mode)
{
	double delta;
	error[NODE_ERROR] = Compute_Error();	
	in_links.Reset_To_Head();
	Base_Link *link;
	int cnt = in_links.Count();
	
	fori(cnt)
	{
		link = in_links.Curr();
		delta = value[LEARNING_RATE] * error[NODE_ERROR] * link->In_Value(); // delta rule
		link->Update_Weight(delta);
		in_links.Next();
	}

};

char *BP_Output_Node::Get_Name(void)
{
	static char name[] = "BP_OUTPUT_NODE";
	return name;
};

BP_Middle_Node::BP_Middle_Node(double lr, double mt, int v_size, int e_size) : BP_Output_Node(lr, mt, v_size, e_size) {};

char *BP_Middle_Node::Get_Name(void)
{
	static char name[] = "BP_MIDDLE_NODE";
	return name;
};

double BP_Middle_Node::Compute_Error(int mode)
{
	double total = 0;
	out_links.Reset_To_Head();
	int cnt = out_links.Count();
	fori(cnt)
	{
		total += out_links.Curr()->Weighted_Out_Error();
		out_links.Next();
	}
	return value[NODE_VALUE] * ( 1.0 - value[NODE_VALUE]) * total;
};

char *BP_Middle_Node::Get_Name(void)
{
	static char name[] = "BP_MIDDLE_NODE";
	return name;
};

class Backprop_Network : public ADALINE_Network
{
protected:
	int num_layers;
	int first_middle_node;
	int first_output_node;
	int *node_cnt;
	double momentum_term;
	virtual void Create_Network(void);

public:
	Backprop_Network(char filename[]);
	Backprop_Network(double lr, double mt, int layers, ...);
	Backprop_Network(double lr, double mt, int layers, int nodes[]);
	Backprop_Network(void);
	~Backprop_Network(void);
	virtual	double Get_Error(int id = 0);
	virtual void Set_Error(double new_val, int id = 0);
	virtual void Set_Error(Pattern *input_pattern);
	virtual double Get_Value(int id = 0);
	virtual void Save(std::ofstream &outfile);
	virtual void Load(std::ifstream &infile);
	virtual void Run(int mode = 0);
	virtual void Learn(int mode = 0);
	virtual char *Get_Name(void);
	virtual int Get_Num_Layers(void);
	virtual int Get_Layer_Count(int id);
};

void Backprop_Network::Create_Network(void)
{
	



#endif

