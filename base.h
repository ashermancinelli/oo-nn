


#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BASE
#define BASE

#define NODE_VALUE 0
#define LEARNING_RATE 1
#define NODE_ERROR 0
#define WEIGHT 0


class Base_Node;

//----------------------------------------------------------------------

class Base_Link
{
private:
	// Used to give each link a unique ticket
	static int ticket;

protected:
	int id;
	double *value;	
	Base_Node *in_node;
	Base_Node *out_node;
	int value_size;

public:
	Base_Link(int size=1);
	~Base_Link(void);
	virtual void Save(std::ofstream &outfile);
	virtual void Load(std::ifstream &infile);
	inline virtual double Get_Value(int id=WEIGHT);
	inline virtual void Set_Value(double new_val, int id=WEIGHT);
	inline virtual void Set_In_Node( Base_Node *node, int id );
	inline virtual void Set_Out_Node( Base_Node *node, int id );
	inline virtual Base_Node *In_Node(void);
	inline virtual Base_Node *Out_Node(void);
	inline virtual char *Get_Name(void);
	inline virtual void Update_Weight(double new_val);
	inline int Get_ID(void);
	inline virtual double In_Value(int mode=NODE_VALUE);
	inline virtual double Out_Value(int mode=NODE_VALUE);
	inline virtual double In_Error(int mode=NODE_ERROR);
	inline virtual double Out_Error(int mode=NODE_ERROR);
	inline virtual double Weighted_In_Value(int mode=NODE_VALUE);
	inline virtual double Weighted_Out_Value(int mode=NODE_VALUE);

	// This was originally `mode=NODE_VALUE`, but that didn't seem right so I changed it
	inline virtual double Weighted_In_Error(int mode=NODE_ERROR); 
	inline virtual double Weighted_Out_Error(int mode=NODE_ERROR);
	inline virtual int Get_Set_Size(void);
	inline virtual void Epoch(int mode=0);
};


//----------------------------------------------------------------------


class LList
{
private:
	struct NODE
	{
		NODE *next, *prev;
		Base_Link *element;
	}
	
	NODE *head, *tail, *curr;
	int count;

public:	
	LList(void);
	~LList(void);
	int Add_To_Tail(Base_Link *element);
	int Add_Node(Base_Link *element);
	int Del_Node(void);
	int Del(Base_Link *element);
	int Find(Base_Link *element);
	inline void Clear(void);	
	inline int Count(void);
	inline void Reset_To_Head(void);
	inline void Reset_To_Tail(void);
	inline Base_Link *Curr(void);
	inline void Next(void);
	inline void Prev(void);
};


//----------------------------------------------------------------------
// Base Link Implementation
//----------------------------------------------------------------------

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

void Base_Link::Save(std::ofstream &outfile) 
{
	outfile << id << std::endl;
	outfile << value_size;
	if (value) delete[] value;
	value = new double[value_size];
	for (int i = 0; i < value_size; i++)
		outfile << " " << setprecision(18) << value[i];
	outfile << std::endl;
};

void Base_Link::Load(std::ifstream &infile) 
{
	infile >> id;
	infile >> value_size;
	if (value) delete []value;
	value = new double[value_size];
	for (int i = 0; i < value_size; i++)
		infile >> value[i];	
};

int Base_Link::Get_ID(void) { return id; };

char *Base_Link::Get_Name(void) 
{
	static char name[] = "BASE_LINK";	
	return name;
};

double Base_Link::In_Value(int mode) { return in_node->Get_Value(mode); };

double Base_Link::Out_Value(int mode) { return out_mode->Get_Value(mode); };

double Base_Link::In_Error(int mode) { return in_node->Get_Error(mode); };

double Base_Link::Out_Error(int mode) { return out_node->Get_Error(mode); };

double Base_Link::Weighted_In_Value(int mode) 
{
	return in_node->Get_Value(mode) * value[WEIGHT];
};

double Base_Link::Weighted_Out_Value(int mode)
{
	return out_node->Get_Value(mode) * value[WEIGHT];	
};

double Base_Link::Weighted_In_Error(int mode) 
{
	return in_node->Get_Error(mode) * value[WEIGHT];
};

double Base_Link::Weighted_Out_Error(int mode)
{
	return out_node->Get_Error(mode) * value[WEIGHT];
};

int Base_Link::ticket=-1;

//----------------------------------------------------------------------
// End Base Link Implementation
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// Base Node declaration
//----------------------------------------------------------------------

class Base_Node {
private:
	static int ticket;

protected:
	int id;			
	double value;
	int value_size;
	double value_size;
	double *error;	
	
	LList in_links, out_links;

public:
	Base_Node(int v_size = 1, int e_size = 1);
	~Base_Node(void);
	LList *In_Links(void);
	LList *Out_Links(void);
	virtual void Run(int mode=0);
	virtual void Learn(int mode=0);
	virtual void Epoch(int code=0);
	virtual void Load(std::ifstream &infile);
	virtual void Save(std::ofstream &outfile);
	inline virtual double Get_Value(int id=NODE_VALUE);	
	inline virtual void Set_Value(double new_val, int id=NODE_ERROR);
	inline virtual double Get_Error(int id=NODE_ERROR);
	inline virtual void Set_Error(double new_val, in id=NODE_ERROR);
	inline int Get_ID(void);
	inline virtual char *Get_Name(void);
	void Create_Link_To(Base_Node &to_node, Base_Link *link);
	virtual void Print(std::ofstream &out);

	friend void Connect(Base_Node &from_node, Base_Node &to_node, Base_Link *link);
	friend void Connect(Base_Node &from_node, Base_Node &to_node, Base_Link &link);
	friend void Connect(Base_Node *from_node, Base_Node *to_node, Base_Link *link);
	friend int Disconnect(Base_Node *from_node, Base_Node *to_node);
	friend double Random(double lower_bound, dobule upper_bound);
};


//----------------------------------------------------------------------
// End Base Node declaration
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// Base Node Implementation
//----------------------------------------------------------------------

Base_Node::Base_Node(int v_size, int e_size)
{
	id = ++ticket;
	if (v_size <= 0) { value_size = 0; value = NULL; }
	else {
		value_size = v_size;
		value = new double[v_size];
	}
	
	for (int i = 0; i < v_size; i++)
		value[i] = 0.0;
	
	if ( e_size <= 0 ) { error_size = 0; error = NULL; }
	else { 
		error_size = e_size;
		error = new double[e_size];
	}
	
	for ( int i = 0; i < e_size; i++ ) 
		error[i] = 0.0;

};

Base_Node::~Base_Node(void) 
{
	if (value_size > 0) delete[] value;
	if (error_size > 0) delete[] error;
}

LList Base_Node::*In_Links(void) {
	return &in_links;
};

LList Base_Node::*Out_Links(void) {
	return &out_links;
};

void Base_Node::Run(int mode=0) {};

void Base_Node::Learn(int mode=0) {};

void Base_Node::Epoch(int code=0) {};

void Base_Node::Load(std::ifstream &infile)
{
	infile >> id;
	infile >> value_size;
	if ( value ) delete[] value;
	value = new double[value_size];
	for ( int i = 0; i < value_size; i++ )	
		infile >> value[i];
	infile >> error_size;
	if (error) delete[] error;
	error = new double[error_size];
	for ( int i = 0; i < error_size; i++ ) 
		infile >> error[i];
};

void Base_Node::Save(std::ofstream &outfile) 
{
	outfile << setw(4) << id << std::endl;
	outfile << value_size;
	for ( int i = 0; i < value_size; i++ ) 
		outfile << " " << setprecision(18) << value[i];
	outfile << std::endl;
	outfile << error_size;
	for ( int i = 0; i < error_size; i++ ) 
		outfile << " " << setprecision(18) << error[i];
	outfile << std::endl;	
};

double Base_Node::Get_Value(int id=NODE_VALUE) { return value[id]; };

void Base_Node::Set_Value(double new_val, int id=NODE_ERROR) { value[id] = new_val; };

double Base_Node::Get_Error(int id=NODE_ERROR) { return error[id]; };

void Base_Node::Set_Error(double new_val, in id=NODE_ERROR) { error[id] = new_val; };

int Base_Node::Get_ID(void) { return id; };

// This ought to be overwritten by inherited classes to be 
// more descriptive of their function
char *Base_Node::Get_Name(void) {
	static char name[] = "BASE_LINK";
	return name;
};

void Base_Node::Create_Link_To(Base_Node &to_node, Base_Link *link) {
	out_links.Add_To_Tail(link);
	to_node.In_Links()->Add_To_Tail(link);
	link->Set_In_Node(this, id);
	link->Set_Out_Node(&to_node, to_node.Get_ID());
};

void Base_Node::Print(std::ofstream &out)
{
	out << "Node ID: " << id << "   Node Name: " << Get_Name() << std::endl;	
	out << "Value Set: ";
	for ( int i = 0; i < value_size; i++ )
		out << value[i] << " ";
	out << std::endl;
	out << "Error Set: ";
	for ( int i = 0; i < error_size; i++) 
		out << error[i] << " ";
	out << std::endl;
	
	in_links.Reset_To_Head();
	for ( int i = 0; i < in_links.Count(); i++) 
	{
		out 	<< "   In Link ID: " < in_links.Curr()->Get_ID()
			<< " Link Name: " << in_links.Curr()->Get_Name()
			<< " Source Node: " << in_links.Curr()->In_Node()->Get_ID()
			<< " Value Set: ";
		for (int j = 0; j < in_links.Curr()->Get_Set_Size(); j++)
			out << in_links.Curr()->Get_Value(j) << " ";
		out << std::endl;
		in_links.Next();
	}		
	out_links.Reset_To_Head();
	for ( int i = 0; i < out_links.Count(); i++ )
	{
		out 	<< "   Out Link ID: " << out_links.Curr()->Get_ID()
			<< "   Link Name: " << out_links.Curr()->Get_Name()
			<< "   Dest Node: " << out_links.Curr()->Out_Node()->Get_ID()
			<< "   Value Set: ";
		for ( int j = 0; j < out_links.Curr()->Get_Set_Size(); j++ )
			out << out_links.Curr()->Get_Value(j) << " ";	
		out << std::endl;
		out_links.Next();
	}
	out << std::endl;
};

void Connect(Base_Node &from_node, Base_Node &to_node, Base_Link *link) {
	from_node.Create_Link_To(to_node, link);
}

void Connect(Base_Node &from_node, Base_Node &to_node, Base_Link &link) {
	from_node.Create_Link_To(to_node, &link);
}

void Connect(Base_Node *from_node, Base_Node *to_node, Base_Link *link) {
	from_node.Create_Link_To(*to_node, link);
}

int Disconnect(Base_Node *from_node, Base_Node *to_node) {
	LList *out_links = from_node->Out_Links();
	int flag = 0;	// Flag is set if the link is found
	out_links->Reset_To_Head();
	for (int i = 0; i < out_links->Count(); i++) {
		if (out_links->Curr()->Out_Node() == to_node) {
			flag = 1;
			break;	
		}	
		out_links->Next();
	}

	if (flag == 1) {	
		out_links->Curr()->Out_Node()->In_Links->Del(out_links->Curr());	
		out_links->Del_Node();
		return 1;
	} else {
		return 0;	// link not found 
	}

};

double Random(double lower_bound, double upper_bound) 
{
	return ((double)((rand()%RAND_MAX))/(double)RAND_MAX)*(upper_bound-lower_bound)+lower_bound;
};

int Base_Node::ticket=-1;


//----------------------------------------------------------------------
// End Base Node Implementation
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// Feed Forward Declaration
//----------------------------------------------------------------------

class Feed_Forward_Node : public Base_Node
{
protected:
	virtual double Transfer_Function(double value);
	
public:
	Feed_Forward_Node(int v_size=1, int e_size=1);
	virtual void Run(int mode=0);
	virtual char *Get_Name(void);
};


//----------------------------------------------------------------------
// Feed Forward Implementation
//----------------------------------------------------------------------

double Feed_Forward_Node::Transfer_Function(double value) { return value; };

Feed_Forward_Node::Feed_Forward_Node(int v_size, int e_size):Base_Node(v_size,e_size) {};

void Feed_Forward_Node::Run(int mode)
{
	in_links.Reset_To_Head();
	double total = 0.0;
	int cnt = in_links.Count();
	for (int i = 0; i<cnt; i++)
	{
		total += in_links.Curr()->Weighted_In_Value();
		in_links.Next();	
	}
	value[mode] = Transfer_Function(total);
}

char *Feed_Forward_Node::Get_Name(void) 
{
	static char name[] = "FEED_FORWARD_NODE";
	return name;
}


//----------------------------------------------------------------------
// End Feed Forward Node Implementation
//----------------------------------------------------------------------



#endif
