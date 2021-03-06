//--------------------------------------------------------------------------- 

#include "dmer.h"
#include <iostream>
#include <fstream>

//---------------------------------------------------------------------------  

Dmer::Dmer(const char * name, int MaxIter, int MaxTime)
{ 
  /* tempo inicial */
  t_ini  = (unsigned long int) clock();

  strcpy(nome, name);
  le_dados_grasp(MaxIter, MaxTime);   /* carrega a estrutura custo a partir do arquivo de entrada e executa grasp */

} 

//--------------------------------------------------------------------------- 
 
/* funcao de tempo */
double Dmer::calcula_tempo(const unsigned long int ini, const unsigned long int fim)
{
  double r;

  if(fim >= ini)
    r = ((double)(fim - ini)) / CLOCKS_PER_SEC;
  else
    r = ((double)( (fim + (unsigned long int)-1) - ini)) / CLOCKS_PER_SEC;
  return r;
}

//--------------------------------------------------------------------------- 
 
void Dmer::le_dados_grasp(int MaxIter, int MaxTime)
{ 
  int           jj;
  char          arq[256];
  std::ifstream fin; 
  Array<int>    f; 
  Array<int>    f2; 
  Array<int>    f3;
  Array<int>    f4;
  Array<int>    f5;
  Array<int>    f6;
  Array<int>    atc;

  //int    DEPU         = 1;
  int    TEST         = 0;
  
  unsigned long int   t_ini2;
 
  strcpy(arq,nome);
  fin.open(arq);

  /* constroi grafo de sinais */
  sg.ini(fin);

  /* aloca */
  f.aloca(sg.n+5);
  f2.aloca(sg.n+5);
  f3.aloca(sg.n+5);
  f4.aloca(sg.n+5);
  f5.aloca(sg.n+5);
  f6.aloca(sg.n+5);

  /* Grasp */
  std::ofstream myfile ("saida.txt");

  for (int i = 1; i <= 10; i++) {
    t_ini2  = (unsigned long int) clock();
    jj = sg.grasp_sig_v2(sg.vet1, f, sg.vet2, f2, sg.vet3, f3, sg.vet4, f4, f5, f6, MaxIter, MaxTime, TEST);
    std::cout<<std::endl<<nome<<" GRASP = "<<jj<<" Tempo = "<<calcula_tempo(t_ini2, (unsigned long int) clock())<<std::endl;

    myfile<<nome<<" GRASP = "<<jj<<" Tempo = "<< calcula_tempo(t_ini2, (unsigned long int) clock())<<std::endl;
  }
  myfile.close();

  /* desaloca */
  r.desaloca();
  b.desaloca();
  J.desaloca();
  f.desaloca();
  f2.desaloca();
  f3.desaloca();
  f4.desaloca();
  f5.desaloca();
  f6.desaloca();
  atc.desaloca();
  sg.fini();

  fin.close();
} 


  
