
#include <fstream>
#include <iostream>
#include <stdarg.h>

#ifndef PATTERN
#define PATTERN

class Pattern {
private:
	double *in_set, *out_set;
	int id, in_size, out_size;

public:
	Pattern(int in, int out);
	Pattern(int in, int out, int data_id, ...);
	Pattern(int in, int out, int data_id,
		double *in_array, double *out_array);
	Pattern(int in, int out, std::ifstream &infile);
	~Pattern(void);

	virtual inline double In(int id);
	virtual inline double Out(int id);	

	virtual inline void Set_In(int id, double value);
	virtual inline void Set_Out(int id, double value);
	
	virtual inline int In_Size(void);
	virtual inline int Out_Size(void);	 
	
	virtual void Save(std::ofstream& outfile);
	virtual void Load(std::ifstream& infile);
	
	virtual void Print(void);
	virtual inline int Get_ID(void);
};

#endif
