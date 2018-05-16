

#include "basenode.h"
#include "baselink.h"
#include "llink.h"

Base_Node(int v_size = 1, int e_size = 1);

~Base_Node(void);

LList *In_Links(void) {
	return &in_links;
};

LList *Out_Links(void) {
	return &out_links;
};

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

double Random(double lower_bound, dobule upper_bound);

