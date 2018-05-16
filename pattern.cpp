
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
