


#ifndef BASELINK
#define BASELINK

class Base_Link
{
private:
	// Used to give each link a unique ticket
	static int ticket;

protected:
	int id;
	double *value;	
	Base_Node *in_node, *out_node;
	int value_size;

public:
	Base_Link(int size=1);
	~Base_Link(void);
	virtual void Save(ofstream &outfile);
	virtual void Load(ifstream &infile);
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


#endif
