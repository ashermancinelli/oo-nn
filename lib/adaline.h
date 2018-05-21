


#ifndef ADALINE
#define ADALINE

#include "base.h"
#include "common.h"
#include "pattern.h"



class ADALINE_Node : public Feed_Forward_Node
{
protected:
	virtual double Transfer_Function(double value);
public:
	ADALINE_Node(void);
	ADALINE_Node(double lr);
	virtual void Learn(int mode);
	virtual char *Get_Name(void);
};

double ADALINE_Node::Transfer_Function(double value)
{
	if (value < 0) return -1.0;
	else return 1;
};

ADALINE_Node::ADALINE_Node(void) : Feed_Forward_Node(2, 1) {};

ADALINE_Node::ADALINE_Node(double lr) : Feed_Forward_Node(2, 1) 
{
	value[LEARNING_RATE] = lr;
};

void ADALINE_Node::Learn(int mode)
{
	error[NODE_ERROR] = value[NODE_VALUE]*-2.0;
	Base_Link *link;
	in_links.Reset_To_Head();
	int cnt = in_links.Count();
	double delta;
	fori(cnt)
	{
		link = in_links.Curr();
		delta = value[LEARNING_RATE] * link->In_Value() * error[NODE_ERROR];
		link->Update_Weight(delta);
		in_links.Next();		
	}
};

char *ADALINE_Node::Get_Name(void)
{
	static char name[] = "ADALINE_NODE";
	return name;
};

class ADALINE_Link : public Base_Link
{
public:
	ADALINE_Link(void);
	virtual void Save( std::ofstream &outfile );	
	virtual void Load( std::ifstream &infile );
	virtual char *Get_Name(void);
};

// Link is automatically initialized to random initial value
ADALINE_Link::ADALINE_Link(void) : Base_Link()
{
	value[WEIGHT] = Random(-1.0, 1.0);
};

void ADALINE_Link::Save( std::ofstream &outfile ) 
{
	outfile << std::setw(4) << id << " " << std::setprecision(18)
		<< value[WEIGHT] << " " << std::setw(4) << In_Node()->Get_ID() << " "
		<< std::setw(4) << Out_Node()->Get_ID() << std::endl;
};

void ADALINE_Link::Load( std::ifstream &infile )
{
	infile >> id;
	infile >> value[WEIGHT];
	int temp;
	
	// Node id's are ignored from save file
	infile >> temp;
	infile >> temp; 
};

char *ADALINE_Link::Get_Name(void)
{
	static char name[] = "ADALINE_LINK";
	return name;
};

class ADALINE_Network : public Base_Network
{
protected:
	virtual void Create_Network(void);
	virtual void Load_Inputs(void);
	double learning_rate;

public:
	ADALINE_Network(const char filename[]);	
	ADALINE_Network(int size);
	ADALINE_Network(int size, double lr);
	ADALINE_Network(void);
	virtual	double Get_Value(int id=0);
	virtual void Set_Value(double new_val, int id=0);
	virtual void Set_Value(Pattern *input_pattern);
	virtual void Save(std::ofstream &infile);
	virtual void Load(std::ifstream &outfile);
	virtual void Run(int mode=0);
	virtual void Learn(int mode=0);
	virtual char *Get_Name(void);
};

void ADALINE_Network::Create_Network(void)
{
	node = new Base_Node*[num_nodes];
	link = new Base_Link*[num_links];
	fori(num_nodes-2)
		node[i] = new Input_Node;
	
	node[num_nodes-2] = new Bias_Node;
	
	node[num_nodes-1] = new ADALINE_Node(learning_rate);
	
	fori(num_links)
		link[i] = new ADALINE_Link;
		
	fori(num_links)
		Connect(node[i], node[num_nodes-1], link[i]);
};

void ADALINE_Network::Load_Inputs(void)
{
	int cnt = in_links.Count();
	if (cnt > 0)
	{
		in_links.Reset_To_Head();
		fori(cnt)
		{
			Set_Value(in_links.Curr()->In_Value(), i);
			in_links.Next();
		}
	}
};

ADALINE_Network::ADALINE_Network( const char filename[]) : Base_Network()
{
	std::ifstream infile(filename);
	Load(infile);
	infile.close();
};
	
ADALINE_Network::ADALINE_Network(int size) : Base_Network()
{
	// num_nodes equals the input layer,
	// so size + bias node + adaline node
	num_nodes = size + 2;
	
	num_links = size + 1;
	learning_rate = 0;
	Create_Network();	
};
	
ADALINE_Network::ADALINE_Network(int size, double lr) : Base_Network()
{
	num_nodes = size + 2;
	num_links = size + 1;
	learning_rate = lr;
	Create_Network();
};

ADALINE_Network::ADALINE_Network(void) : Base_Network() {};

double ADALINE_Network::Get_Value(int id)
{
	// return only the value for the adaline node
	return node[num_nodes-1]->Get_Value();
};

void ADALINE_Network::Set_Value(double new_val, int id) {
	node[id]->Set_Value(new_val);
};

void ADALINE_Network::Set_Value(Pattern* input_pattern) 
{
	// Load input patterns values into input nodes of network
	fori(input_pattern->In_Size())
		node[i]->Set_Value(input_pattern->In(i));
};

void ADALINE_Network::Save(std::ofstream &outfile)
{
	outfile << id << std::endl;
	Save_Nodes_Links(outfile);
};

void ADALINE_Network::Load(std::ifstream &infile)
{
	infile >> id;
	Load_Nodes_Links(infile);
};

void ADALINE_Network::Run(int mode)
{
	Load_Inputs();
	
	// Run ADALINE node only
	node[num_nodes-1]->Run();
};

void ADALINE_Network::Learn(int mode)
{
	node[num_nodes-1]->Learn();	// Again, only need to run/learn adaline node
};

char *ADALINE_Network::Get_Name(void)
{
	static char name[] = "ADALINE_NETWORK";
	return name;
};


#endif
