



//-----------------------------------------------------
// Class for input/output data for NN
//-----------------------------------------------------

#ifndef PATTERN
#define PATTERN

#define fori(x) for (int i = 0; i < (x); i++)

#include <stdio.h>
#include <stdlib.h>
#include <fstream.h>
#include <stdarg.h>

class Pattern
{
private:
	double *in_set;
	double *out_set;
	int id;
	int in_size;
	int out_size;
public:
	Pattern(int in, int out);
	Pattern(int in, int out, int data_id, ...);
	Pattern(int in, int out, int data_id, double *in_array, double *out_array);
	Pattern(int in, int out, std::ifstream &infile);
	~Pattern(void);
	virtual inline double In(int id);
	virtual inline double Out(int id);
	virtual inline void Set_In(int id, double value);
	virtual inline void Set_Out(int id, double value);
	virtual inline int In_Size(void);
	virtual inline int Out_size(void);
	virtual void Save(std::ofstream &outfile);
	virtual void Load(std::ifstream &infile); 
	virtual void Print(void);
	virtual inline int Get_IF(void);
	virtual void Copy(Pattern &in); 
};

Pattern::Pattern(int in, int out)
{
	in_size = in;
	out_size = out;
	in_set = new double[in_size];
	out_set = new double[out_size];
};

Pattern::Pattern(int in, int out, int data_id, ...)
{
	in_size = in;
	out_size = out;
	in_set = new double[in_size];
	out_set = new double[out_size];
	
	id = data_id;
	va_list vl;
	va_start(vl, data_id);
	
	fori(in_size)
		in_set[i] = va_arg(vl, double);

	fori(out_size)
		out_set[i] = va_arg(vl, double);

	va_end(vl);
};

Pattern::Pattern(int in, int out, int data_id,
			double *in_array, double *out_array)
{
	in_size = in;
	out_size = out;
	id = data_id;
	
	in_set = new double[in_size];		
	fori(in_size)
		in_set[i] = in_array[i];
	
	out_set = new double[out_size];
	fori(out_size)
		out_set[i] = out_array[i];
};

Pattern::Pattern( int in, int out, std::ifstream &infile)
{
	in_size = in;
	out_size = out;
	infile >> id;
	
	in_set = new double[in_size];
	out_set = new double[out_size];
	
	Load(infile);
};

Pattern::~Pattern(void)
{
	if (in_set) delete []in_set;
	if (out_set) delete []out_set;
};




#endif

