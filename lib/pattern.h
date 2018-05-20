



//-----------------------------------------------------
// Class for input/output data for NN
//-----------------------------------------------------

#ifndef PATTERN
#define PATTERN

#define fori(x) for (int i = 0; i < (x); i++)

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
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
	virtual inline int Out_Size(void);
	virtual void Save(std::ofstream &outfile);
	virtual void Load(std::ifstream &infile); 
	virtual void Print(void);
	virtual inline int Get_ID(void);
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

double Pattern::In(int id) { return in_set[id]; };

double Pattern::Out(int id) { return out_set[id]; };

void Pattern::Set_In(int id, double value) { in_set[id] = value; };

void Pattern::Set_Out(int id, double value) { out_set[id] = value; };

int Pattern::In_Size(void) { return in_size; };

int Pattern::Out_Size(void) { return out_size; };

int Pattern::Get_ID(void) { return id; };

void Pattern::Save(std::ofstream & outfile)
{
	outfile << id << "\t";
	fori(in_size)
		outfile << in_set[i] << "\t";
	
	fori(out_size)
	{
		outfile << out_set[i];
		if (i != out_size-1) outfile << "\t";
	}
	outfile << std::endl;
};

void Pattern::Load(std::ifstream & infile)
{
	fori(in_size)
		infile >> in_set[i];
	
	fori(out_size)
		infile >> out_set[i];
	
	char ch;
	ch = infile.peek();
	while (ch == '\n' || ch == EOF)
	{
		ch = infile.get();
		if (ch == EOF) break;
		ch = infile.peek();
	}	
};

void Pattern::Print(void) 
{
	std::cout << "ID: " << id << "   In: ";
	fori(in_size)
		std::cout << in_set[i] << " ";
	std::cout << "   Out: ";
	fori(out_size)
		std::cout << out_set[i] << " ";
	std::cout << std::endl;
};

void Pattern::Copy(Pattern &original)
{
	int i;
	if (original.In_Size() == in_size)
		fori(in_size)
			in_set[i] = original.In(i);
	if (original.Out_Size() == out_size)
		fori(out_size)
			out_set[i] = original.Out(i);
};




#endif

