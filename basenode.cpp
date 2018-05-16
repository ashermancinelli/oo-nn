

#include "basenode.h"

Base_Node(int v_size = 1, int e_size = 1);

~Base_Node(void);

LList *In_Links(void);

LList *Out_Links(void);

void Base_Node::Run(int mode=0)

void Base_Node::Learn(int mode=0)

void Base_Node::Epoch(int code=0)

void Base_Node::Load(std::ifstream &infile)

void Base_Node::Save(std::ofstream &outfile)

double Base_Node::Get_Value(int id=NODE_VALUE)

void Base_Node::Set_Value(double new_val, int id=NODE_ERROR)

double Base_Node::Get_Error(int id=NODE_ERROR)

void Base_Node::Set_Error(double new_val, in id=NODE_ERROR)

int Base_Node::Get_ID(void)

char *Base_Node::Get_Name(void)

void Base_Node::Create_Link_To(Base_Node &to_node, Base_Link *link) {
	out_links.Add_To_Tail(link);
	to_node.In_Links()->Add_To_Tail(link);
	link->Set_In_Node(this, id);
	link->Set_Out_Node(&to_node, to_node.Get_ID());
};

void Base_Node::Print(std::ofstream &out)


