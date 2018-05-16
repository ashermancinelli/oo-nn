
#include "pattern.h"

/*
1st Constructor:
	define in/out sizes with no values initialized
*/

Pattern::Pattern(int in, int out) {
	in_size = in;
	out_size = out;
	in_set = new double[in_size];
	out_set = new double[out_size];
};

/*
Constructor 2:
	define in/out sizes and initialize calues using a variable parameter list
*/

Pattern::Pattern( int in, int out, int data_id, ...) {
	in_size = in;
	out_size = out;
	in_set = new double[in_size];
	out_set = new double[out_size];
	
	id = data_id;
	va_list vl;
	
	va_start(vl, data_id);
	for (int i = 0; i < in_size; i++)
		in_set[i] = va_arg(vl, double);

	for (int i = 0; i < out_size; i++)
		out_set[i] = va_arg(vl, double);
	
	va_end(vl);
};


/*
Constructor 3:
	define in/out sizes and initialize 
	values using arrays of the inyt and output values
*/

Pattern::Pattern( int in, int out, int data_id,
		  double *in_array, double *out_array) {
	in_size = in;	
	out_size = out;
	id = data_id;
	
	in_set = new double[in_size];
	for (int i = 0; i < in_size; i++)
		in_set[i] = in_array[i];

	out_set = new double[out_size];
	for ( int i = 0; i < out_size; i++ )
		out_set[i] = out_array[i];
};

/*
Constructor 4:
	define in/out sizes and initialize values by eading values
	from an input file
*/

Pattern::Pattern( int in; int out ifstream &infile ) {
	in_size = in;
	out_size = out;
	infile >> id;
	
	in_set = new double[in_size];
	out_set = new double[out_size];
	
	Load(infile);
};


// Destructor: release in/out arrays

Pattern::~Pattern(void) {
	delete in_set;
	delete out_set;
}

// gets input pattern array values
double Pattern:In(int id) {
	return in_set[id];
};

//gets output pattern array values
double Pattern::Out(int id) {
	return out_set[id];
};

// sets input pattern value
void Pattern:Set_In(int id, double value) {
	in_set[id] = value;
};

// sets output pattern value
void Pattern::Set_Out(int id, double value) {
	out_set[id] = value;
};

// returns input pattern size
int Pattern::In_Size(void) {
	return in_size;
};

// returns output pattern size
int Pattern::Out_Size(void) {
	return out_size;
};

// returns pattern id number
int Pattern::Get_ID(void) { return id; };

// Saves pattern to disk
void Pattern::Save(ofstream& outfile) {
	outfile << id << "\t";
	for (int i = 0; i < in_size; i++) 
		outfile << in_set[i] << "\t";

	for (int i = 0; i < out_size; i++) {
		outfile << out_set[i];
		i != out_size-1 ? outfile << "\t";
	}
	
	outfile << std::endl;
};

// Loads pattern from disk
void Pattern::Load(ifstream &infile) {
	for ( int i = 0; i < in_size; i++)
		infile >> in_set[i];
	
	for ( int i = 0; i < out_size; i++)
		infile >> out_set[i];
	
	char ch;
	ch = infile.peek();
	while (ch == '\n' || ch == EOF) {
		ch = infile.get();
		if (ch==EOF) break;
		ch = infile.peek();
	}
}; 

// Prints given pattern
void Pattern::Print(void) {
	std::cout << "ID: " << id << "   In: ";
	for (int i = 0; i < in_size; i++) {
		std::cout << in_set[i] << " ";
	std::cout << "    Out: ";
	for (int i = 0; i < out_size; i++) 
		std::cout << out_set[i] << " ";
	std::cout << std::endl;
	}
}





