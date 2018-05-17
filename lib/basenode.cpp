

#include "basenode.h"
#define NODE_ERROR 0
#define NODE_VALUE 0


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

double Random(double lower_bound, double upper_bound);

