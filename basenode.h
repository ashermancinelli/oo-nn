


#include <iostream>
#include <fstream>
#include "baselink.h"

#ifndef BASE_NODE
#define BASE_NODE

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
	friend void Disconnect(Base_Node *from_node, Base_Node *to_node);
	friend double Random(double lower_bound, dobule upper_bound);
};

#endif
