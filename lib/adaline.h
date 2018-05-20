


#ifndef ADALINE
#define ADALINE

#include "base.h"
#include "common.h"
#include "pattern.h"



class ADALINE_Node : public Feed_Forward_Node
{
protected:
	virtual double Transfer_Function(double value);
}




#endif
