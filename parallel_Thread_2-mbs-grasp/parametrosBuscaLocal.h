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
		this->A = Array<int>(A);
		this->a = Array<int>(a);
		this->B = Array<int>(B);
		this->b = Array<int>(b);
		this->C = Array<int>(C);
		this->c = Array<int>(c);
		this->cand1 = Array<int>(cand1);
		this->cand2 = Array<int>(cand2);
		this->b_A = Array<int>(b_A);
		this->b_B = Array<int>(b_B);
		this->ITMAX = ITMAX; 
		this->TIMEMAX = TIMEMAX; 
		this->TEST = TEST;
		this->sol = sol;

	};




};