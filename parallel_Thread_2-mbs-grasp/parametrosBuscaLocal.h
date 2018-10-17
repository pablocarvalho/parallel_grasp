#include <fstream>
#include <string.h>
#include <stdlib.h>

// --------------------------------------------------------------------------
#include "abstractThreadClass.h"
#include "array.cpp"
#include "matriz.cpp" 
#include "structs.h"

class ParametrosBuscaLocal : public AbstractThreadClass
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
	

	  

	ParametrosBuscaLocal(Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C, Array<int> &c, Array<int> &cand1, 
		Array<int> &cand2, Array<int> &b_A, Array<int> &b_B, int ITMAX, int TIMEMAX, int TEST,
		int* sol,Matriz<str_e> &g,Array<int> &stat,int n)
	{    // grafo booleano de arestas positivas e negativas	
	  
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

		this->g = Matriz<str_e>(g);    // grafo booleano de arestas positivas e negativas
		this->stat = Array<int>(stat);
		this->n = n;  

	};

	virtual void ~ParametrosBuscaLocal(){};

	int getSol(){return *sol;};

protected:
   /** Implement this method in your subclass with the code you want your thread to run. */
   virtual void InternalThreadEntry();

private:

	Matriz<str_e> g;    // grafo booleano de arestas positivas e negativas
	Array<int>    stat;
	int           n;             // numero de vertices
	int* sol;

	bool can_move_C_X_v2(int l, Array<int> &x, Array<int> &y, Array<int> &C);
  bool can_2move_C_X_v2(int l1, int l2, Array<int> &x, Array<int> &y, Array<int> &C);
  int  can_move_C_AB_v2(int l, Array<int> &a, Array<int> &b, Array<int> &C, int TEST);
  int  can_2move_C_AB_v2(int l1, int l2, int num_candA, int num_candB, Array<int> &a, Array<int> &b, Array<int> &C, Array<int> &c, int TEST);
  bool move_2_C_AB_v2(int desceu, int origem, Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C , Array<int> &c, Array<int> &cand1, Array<int> &cand2, int TEST);
  bool move_3_C_AB_v2(int desceu1, int desceu2, int origem1, int origem2, Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C, Array<int> &c, Array<int> &cand1, Array<int> &cand2, int TEST);

  void maximiza_solucao_grasp_sig_v2(Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C,  Array<int> &c, Array<int> &cand1, Array<int> &cand2, int TEST);

	void busca_local();
	int  viz_down_A_v2(Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C, Array<int> &c, Array<int> &cand1, Array<int> &cand2, int TEST, unsigned long int t_ini_g);
	int  viz_down_B_v2(Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C, Array<int> &c, Array<int> &cand1, Array<int> &cand2, int TEST, unsigned long int t_ini_g);
	int  viz_2down_A_v2(Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C, Array<int> &c, Array<int> &cand1, Array<int> &cand2, int TEST, unsigned long int t_ini_g, int TIMEMAX);
	int  viz_2down_B_v2(Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C, Array<int> &c, Array<int> &cand1, Array<int> &cand2, int TEST, unsigned long int t_ini_g, int TIMEMAX);
	int  viz_2down_AB_v2(Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C, Array<int> &c, Array<int> &cand1, Array<int> &cand2, int TEST, unsigned long int t_ini_g, int TIMEMAX);
	int  obj_grasp_sig_v2(Array<int> &A, Array<int> &B);
	void testa_particoes_grasp_sig_v2(Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C, Array<int> &c);
	void atualiza_a_b_c(Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C, Array<int> &c);

	double calcula_tempo(const unsigned long int ini, const unsigned long int fim);




};