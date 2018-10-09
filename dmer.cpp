//--------------------------------------------------------------------------- 

#include "dmer.h"
#include <fstream>
#define PARALLEL

#ifdef PARALLEL
#include "mpi.h"
#endif

using namespace std;
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
  //int           jj;
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

#ifdef PARALLEL

  int my_rank, p;
  MPI_Status status;

  int argc = 0;
  char** argv = NULL;
  MPI_Init(&argc, &argv);
  //start = MPI_Wtime();
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  MaxIter = MaxIter/p;

#endif

  /* Grasp */
  //srand(5);
  ofstream arquivo("saida.txt");

  for (int i = 0; i < 10; i++) {
    srand(p * i + my_rank);
    t_ini2  = (unsigned long int) clock();
    int jj = sg.grasp_sig_v2(sg.vet1, f, sg.vet2, f2, sg.vet3, f3, sg.vet4, f4, f5, f6, MaxIter, MaxTime, TEST);  
    cout<< "Local maxIter = " <<MaxIter <<endl;
    cout<<"Processo: " << my_rank << " ";
    //cout<<nome<<" GRASP = "<<jj<<" Tempo = "<<calcula_tempo(t_ini2, (unsigned long int) clock())<<endl ;
    cout<<"LOCAL GRASP = "<<jj<<" Tempo = "<<calcula_tempo(t_ini2, (unsigned long int) clock())<<endl ;

    int globalJJ;
    MPI_Reduce(&jj,&globalJJ,1,MPI_INT,MPI_MAX,0, MPI_COMM_WORLD);

    if(my_rank == 0)
    {
    	cout<<"GLOBAL GRASP = "<<globalJJ<<" Tempo = "<<calcula_tempo(t_ini2, (unsigned long int) clock())<<endl ;
      arquivo << "GLOBAL GRASP = "<<globalJJ<<" Tempo = "<<calcula_tempo(t_ini2, (unsigned long int) clock())<<endl;
    }
  }

  arquivo.close();

#ifdef PARALLEL
  MPI_Finalize();
#endif

  

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


  
