#include "array.cpp"

class ParametrosBuscaLocal
{
public:	
	Array<int> A;
	Array<int> a; 
	Array<int> B; 
	Array<int> b; 
	Array<int> C; 
	Array<int> c; 
	Array<int> cand1;
	Array<int> cand2; 
	Array<int> b_A;
	Array<int> b_B; 
	int ITMAX;
	int TIMEMAX;
	int TEST;
	int* sol;

	ParametrosBuscaLocal(Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C, Array<int> &c, Array<int> &cand1, Array<int> &cand2, Array<int> &b_A, Array<int> &b_B, int ITMAX, int TIMEMAX, int TEST,int* sol)
	{
		this->A = *A;
		this->a = *a;
		this->B = *B;
		this->b = *b;
		this->C = *C;
		this->c = *c;
		this->cand1 = *cand1;
		this->cand2 = *cand2;
		this->b_A = *b_A;
		this->b_B = *b_B;
		this->ITMAX = ITMAX; 
		this->TIMEMAX = TIMEMAX; 
		this->TEST = TEST;
		this->sol = sol;

	};




};