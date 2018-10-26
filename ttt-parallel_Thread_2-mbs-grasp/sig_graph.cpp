#include <mpi.h>
#include "sig_graph.h"
#include "parametrosBuscaLocal.h"

// gera grafo a partir de um arquivo .G
float Sigraph::ini(std::ifstream &fin)
{
	int i, j, n_are, a1, a2, at, ip, in;
	str_e e;
	int DEPU = 0;
	float cont_pos = 0, cont_neg = 0;
	if (DEPU)
		std::cout << "construindo sg, " << std::endl;

	/* aloca */
	fin >> n;
	fin >> n_are;
	n_c = 0;
	n_iso = 0;
	n_niso = 0;
	n_vizig = 0;
	n_pontes = 0;
	n_add_preproc = 0;
	/* aloca */
	g.aloca(n, n);
	Gp.aloca(n, n);
	Gn.aloca(n, n);
	map.aloca(n);
	stat.aloca(n);
	comp.aloca(n);
	vet1.aloca(n);
	vet2.aloca(n);
	vet3.aloca(n);
	vet4.aloca(n);

	/* atribui */
	e.pos = false;
	e.neg = false;
	g.set(e);
	Gp.set(-1);
	Gn.set(-1);
	stat.set(1);
	comp.set(-1);

	/*insere arestas (i,j) em g */
	if (DEPU)
		std::cout << " insere arestas" << std::endl;
	for (i = 1; i <= n_are; ++i)
	{
		fin >> a1;
		fin >> a2;
		fin >> at;

		/* + */
		if ((at == 1) || (at == 2))
		{
			g(a1, a2).pos = true;
			g(a2, a1).pos = true;

			if (at != 2)
				cont_pos += 1;
		}

		/* - */
		if ((at == -1) || (at == 2))
		{
			g(a1, a2).neg = true;
			g(a2, a1).neg = true;

			if (at != 2)
				cont_neg += 1;
		}
	}

	/* Constroi Gp e Gn */
	if (DEPU)
		std::cout << " constroi Gp e Gn" << std::endl;
	for (i = 0; i < n; ++i)
	{
		ip = in = 0;
		for (j = 0; j < n; ++j)
		{
			if (g(i, j).pos)
				Gp(i, ip++) = j;
			if (g(i, j).neg)
				Gn(i, in++) = j;
		}
	}
	if (DEPU)
		Gp.imprime();
	if (DEPU)
		Gn.imprime();

	return (cont_neg / cont_pos);
}

//-------------------------------------------------------------------------------

void Sigraph::fini()
{
	/* desaloca */
	g.desaloca();
	Gp.desaloca();
	Gn.desaloca();
	map.desaloca();
	stat.desaloca();
	comp.desaloca();
}

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------

/* vizinhanca do GRASP para o problema do grafo de sinais */
void Sigraph::testa_particoes_grasp_sig_v2(Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C, Array<int> &c)
{
	int ii, jj;
	bool achou;

	// testa A,B
	for (ii = 0; ii < n; ii++)
		for (jj = ii + 1; jj < n; jj++)
			if ((A[ii] == 1) && (A[jj] == 1) && (g(ii, jj).neg))
			{
				std::cout << "vertice " << ii << " (A)"
									<< " e vertice " << jj << " (A) tem are neg" << std::endl;
				abort();
			}

	for (ii = 0; ii < n; ii++)
		for (jj = ii + 1; jj < n; jj++)
			if ((B[ii] == 1) && (B[jj] == 1) && (g(ii, jj).neg))
			{
				std::cout << "vertice " << ii << " (B)"
									<< " e vertice " << jj << " (B) tem are neg" << std::endl;
				abort();
			}

	for (ii = 0; ii < n; ii++)
		for (jj = 0; jj < n; jj++)
			if ((A[ii] == 1) && (B[jj] == 1) && (g(ii, jj).pos))
			{
				std::cout << "vertice " << ii << " (A)"
									<< " e vertice " << jj << " (B) tem are pos" << std::endl;
				abort();
			}

	for (ii = 0; ii < n; ii++)
		if (A[ii] + B[ii] + C[ii] != 1)
		{
			std::cout << "soma do vertice " << ii << " = " << A[ii] + B[ii] + C[ii] << std::endl;
			abort();
		}

	// testa a,b,c
	for (ii = 0; a[ii] != -1; ii++)
		if ((a[ii] != -2) && (A[a[ii]] == 0))
		{
			std::cout << "vertice " << a[ii] << " em (a), mas nao esta em (A)" << std::endl;
			abort();
		}

	for (ii = 0; b[ii] != -1; ii++)
		if ((b[ii] != -2) && (B[b[ii]] == 0))
		{
			std::cout << "vertice " << b[ii] << " em (b), mas nao esta em (B)" << std::endl;
			abort();
		}

	for (ii = 0; c[ii] != -1; ii++)
		if ((c[ii] != -2) && (C[c[ii]] == 0))
		{
			std::cout << "vertice " << c[ii] << " em (c), mas nao esta em (C)" << std::endl;
			abort();
		}

	for (ii = 0; ii < n; ii++)
		if (A[ii] == 1)
		{
			for (achou = false, jj = 0; a[jj] != -1; jj++)
				if (a[jj] == ii)
				{
					achou = true;
					break;
				}
			if (!achou)
			{
				std::cout << "vertice " << ii << " em (A), mas nao esta em (a)" << std::endl;
				abort();
			}
		}

	for (ii = 0; ii < n; ii++)
		if (B[ii] == 1)
		{
			for (achou = false, jj = 0; b[jj] != -1; jj++)
				if (b[jj] == ii)
				{
					achou = true;
					break;
				}
			if (!achou)
			{
				std::cout << "vertice " << ii << " em (B), mas nao esta em (b)" << std::endl;
				abort();
			}
		}

	for (ii = 0; ii < n; ii++)
		if (C[ii] == 1)
		{
			for (achou = false, jj = 0; c[jj] != -1; jj++)
				if (c[jj] == ii)
				{
					achou = true;
					break;
				}
			if (!achou)
			{
				std::cout << "vertice " << ii << " em (C), mas nao esta em (c)" << std::endl;
				abort();
			}
		}
}

/* atualiza vetores a e b */
void Sigraph::atualiza_a_b_c(Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C, Array<int> &c)
{
	int temA, temB, temC, i;

	for (temA = temB = temC = i = 0; i < n; i++)
	{
		if (A[i] == 1)
		{
			a[temA] = i;
			temA++;
		}
		if (B[i] == 1)
		{
			b[temB] = i;
			temB++;
		}
		if (C[i] == 1)
		{
			c[temC] = i;
			temC++;
		}
	}
	a[temA] = -1;
	b[temB] = -1;
	c[temC] = -1;
}

/* metodo construtivo do GRASP para o problema do grafo de sinais */
int Sigraph::metodo_construtivo_grasp_sig_v2(Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C, Array<int> &c, Array<int> &cand1, Array<int> &cand2, int TEST)
{
	int i, j, v, vez, temA, temB, num_cand, num_sol;
	bool e_cand;

	int DEPU = 0;

	if (DEPU)
		std::cout << std::endl
							<< "*************  metodo_construtivo_grasp_sig  ****************** " << std::endl;

	/* inicializa conjuntos */
	A.set(0);
	B.set(0);
	C.set(1);

	/* escolhe vertice inicial aleatorio e coloca em A */
	for (v = (int)(rand() % n); stat[v] != 1; v++)
		if (v == (n - 1))
			v = -1;
	A[v] = 1;
	C[v] = 0;
	num_sol = 1;

	if (DEPU)
		std::cout << " v_ini = " << v << " em A" << std::endl;

	/* tenta botar a proxima vez no lado B */
	vez = 0;
	temA = 1;
	temB = 1;

	while ((temA == 1) || (temB == 1))
	{
		/* preenche candidatos a entrar em A */
		if (vez == 1)
		{
			cand1.set(0);
			for (i = 0, num_cand = 0; i < n; i++)
				if ((stat[i] == 1) && (C[i] == 1))
				{
					/* checa vizinhanca em A */
					for (e_cand = true, j = 0; j < n && e_cand == true; j++)
						if ((A[j] == 1) && (g(i, j).neg))
							e_cand = false;

					/* checa vizinhanca em B */
					for (j = 0; j < n && e_cand == true; j++)
						if ((B[j] == 1) && (g(i, j).pos))
							e_cand = false;

					if (e_cand)
					{
						cand1[i] = 1;
						num_cand++;
					}
				}

			/* não tem mais vertice para inserir em A */
			if (num_cand == 0)
				temA = 0;
		}
		else
		{
			/* preenche candidatos a entrar em B */
			cand1.set(0);
			for (i = 0, num_cand = 0; i < n; i++)
				if ((stat[i] == 1) && (C[i] == 1))
				{
					/* checa vizinhanca em A */
					for (e_cand = true, j = 0; j < n && e_cand == true; j++)
						if ((A[j] == 1) && (g(i, j).pos))
							e_cand = false;

					/* checa vizinhanca em B */
					for (j = 0; j < n && e_cand == true; j++)
						if ((B[j] == 1) && (g(i, j).neg))
							e_cand = false;

					if (e_cand)
					{
						cand1[i] = 1;
						num_cand++;
					}
				}

			/* não tem mais vertice para inserir em B */
			if (num_cand == 0)
				temB = 0;
		}

		/* insere em A */
		if ((vez == 1) && (num_cand > 0))
		{
			/* escolhe vertice candidato aleatorio e coloca em A */
			for (v = (int)(rand() % n); (stat[v] != 1 || cand1[v] != 1); v++)
				if (v == (n - 1))
					v = -1;
			A[v] = 1;
			C[v] = 0;
			num_sol++;
			if (DEPU)
				std::cout << "   " << v << " em A" << std::endl;
		}

		/* insere em B */
		if ((vez == 0) && (num_cand > 0))
		{
			/* escolhe vertice candidato aleatorio e coloca em B */
			for (v = (int)(rand() % n); (stat[v] != 1 || cand1[v] != 1); v++)
				if (v == (n - 1))
					v = -1;
			B[v] = 1;
			C[v] = 0;
			num_sol++;
			if (DEPU)
				std::cout << "   " << v << " em B" << std::endl;
		}

		/* escolhe proxima particao para ser inserido vertice */
		if (temA == 1 && temB == 1)
			vez = (int)(rand() % 2);
		else if (temA == 1)
			vez = 1;
		else
			vez = 0;
		if (DEPU)
			std::cout << "escolhe de " << vez << " agora" << std::endl;

	} /* while ((temA == 1) || (temB == 1)) */

	// /* prenche vetores "a" e "b" */
	if (DEPU)
		std::cout << "prenche vetores a e b" << std::endl;
	atualiza_a_b_c(A, a, B, b, C, c);

	if (TEST)
		testa_particoes_grasp_sig_v2(A, a, B, b, C, c);
	return num_sol;
}

/* calculo do tempo */
double Sigraph::calcula_tempo(const unsigned long int ini, const unsigned long int fim)
{
	double r;

	if (fim >= ini)
		r = ((double)(fim - ini)) / CLOCKS_PER_SEC;
	else
		r = ((double)((fim + (unsigned long int)-1) - ini)) / CLOCKS_PER_SEC;
	return r;
}

// gera um arquivo .sol de solucao a partir do grafo
void Sigraph::write_sol(const char *name, Array<int> &A, Array<int> &B)
{
	int i;
	std::ofstream arq_out;
	char name_G[256];

	/* abre arquivo de saida */
	strcpy(name_G, name);
	strcat(name_G, ".sol");
	arq_out.open(name_G);

	/* escreve vertices de A */
	for (i = 0; i < n; i++)
		if (A[i] == 1)
			arq_out << i << std::endl;

	/* escreve vertices de A */
	for (i = 0; i < n; i++)
		if (B[i] == 1)
			arq_out << (-i) << std::endl;

	/* fecha arquivo de saida */
	arq_out.close();
}

int Sigraph::grasp_sig_v2(Array<int> &A, Array<int> &a, Array<int> &B, Array<int> &b, Array<int> &C, Array<int> &c, Array<int> &cand1, Array<int> &cand2, Array<int> &b_A, Array<int> &b_B, int ITMAX, int TIMEMAX, int TEST, int target)
{
	int sol, b_sol = -1, vez, ii;

	int *solT0 = new int;
	*solT0 = 0;
	int *solT1 = new int;
	*solT1 = 0;

	bool moveu, viz_A, viz_B, viz_AB;
	//bool leftTerminate = false;
	//bool rightTerminate = false;
	bool pediCarga = false;
	bool recebiCarga = false;
	bool pediramCarga = false;
	bool mandeiCarga = false;

	unsigned long int t_ini_g;

	/* PARAMETROS */
	int DEPU = 0;
	/* variaveis MPI */
	int my_rank, p, source;
	int incrementoLeft = 0;
	int incrementoRight = 0;
	int flagLeft = 0;	// flag para envio de carga
	int flagRight = 0; // flag para pedido de carga
	MPI_Status status;
	MPI_Request requestLeft;
	MPI_Request requestRight;

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	//left pede carga para este processo
	//este processo pede carga para right

	int right = (my_rank + 1) % p;
	int left = my_rank - 1;
	if (left < 0)
		left = p - 1;

	t_ini_g = (unsigned long int)clock();

	MPI_Irecv(&incrementoLeft, 1, MPI_INT, left, PedirCarga, MPI_COMM_WORLD, &requestLeft);
	for (int it = 1; it <= ITMAX; it++)
	{
		//std::cout<<calcula_tempo(t_ini_g, (unsigned long int) clock())
		//<<" eu sou o processo "<<my_rank<<" e iniciei " << it <<" de "<< ITMAX<<std::endl;
		sol = metodo_construtivo_grasp_sig_v2(A, a, B, b, C, c, cand1, cand2, TEST);
		*solT0 = sol;
		*solT1 = sol;
		if (DEPU)
			std::cout << std::endl
								<< "IT = " << it << ") solucao inicial com " << sol << " vertices" << std::endl;
		//--------------------inicio threads--------------------------

		ParametrosBuscaLocal pbl0(A, a, B, b, C, c, cand1, cand2, b_A, b_B, ITMAX, t_ini_g, TIMEMAX, TEST, solT0, g, stat, n);
		ParametrosBuscaLocal pbl1(A, a, B, b, C, c, cand1, cand2, b_A, b_B, ITMAX, t_ini_g, TIMEMAX, TEST, solT1, g, stat, n);
		pbl0.StartInternalThread();
		//std::cout << "CRIOU THREAD 1" << std::endl;
		pbl1.StartInternalThread();

		//std::cout << "CRIOU THREAD 2" << std::endl;

		pbl0.WaitForInternalThreadToExit();
		//std::cout << "FIM DA THREAD 1" << std::endl;
		pbl1.WaitForInternalThreadToExit();
		//std::cout << "FIM DA THREAD 2" << std::endl;
		
		//std::cout << "thread 1 sol: " <<*solT0 << std::endl;
		//std::cout << "thread 2 sol: " <<*solT1 << std::endl;

		if (*solT0 > *solT1)
		{
			sol = *solT0;
		}
		else
		{
			sol = *solT1;
		}
		//std::cout << "TERMINOU COMPARAÇÃO" << std::endl;
		
		//Sigraph::busca_local(A, a, B, b, C, c, cand1, cand2, b_A, b_B,  ITMAX,  TIMEMAX,  TEST, solT1);
		//------------------ final paralelização thread -------------------------

		if (sol > b_sol)
		{
			b_sol = sol;
			if (DEPU)
				std::cout << std::endl
									<< "IT = " << it << ") ---------------------------------- MELHOR SOLUCAO COM " << sol << " VERTICES" << std::endl;

			for (ii = 0; ii < n; ii++)
			{
				b_A[ii] = A[ii];
				b_B[ii] = B[ii];
			}

			if (b_sol >= target)
	    		break;
		}

		/* teste de parada por tempo */
		if (DEPU)
			std::cout << std::endl
								<< "TEMPO = " << calcula_tempo(t_ini_g, (unsigned long int)clock()) << " seg" << std::endl;
		if (calcula_tempo(t_ini_g, (unsigned long int)clock()) > TIMEMAX)
			break;

		// testa se tem mensagem pendente, mas nao bloqueia

		//abre um buffer de recebimento de mensagem e só reabre se concluir a comunicação
		// if (flagLeft!=0)
		// {
		// 	MPI_Irecv(&incremento, 1, MPI_INT, left, PedirCarga,MPI_COMM_WORLD,&requestLeft);
		// 	flagLeft=0;
		// }

		std::cout<<calcula_tempo(t_ini_g, (unsigned long int) clock())
		<<" eu sou o processo "<<my_rank<<" terminei " << it <<" de "<< ITMAX<<std::endl;
		MPI_Test(&requestLeft, &flagLeft, &status);
		//testa (linha acima) e conclui a comunicação aberta com MPI_Irecv
		if (flagLeft != 0 && mandeiCarga == false)
		{
			incrementoRight = (ITMAX - it) / 2;
			ITMAX -= incrementoRight;
			MPI_Send(&incrementoRight, 1, MPI_INT, left, PedirCarga, MPI_COMM_WORLD);

			
	      		// std::cout<<calcula_tempo(t_ini_g, (unsigned long int) clock())<<
	      		// " Processo = "<<my_rank<<" enviou(A) "<<incrementoRight<<" iteracoes para "	      		
	      		// <<left<<" total de iteracoes=" <<ITMAX <<" iteracoes em " << my_rank <<std::endl;
	      		
			mandeiCarga = true;
			pediramCarga = true;
		}

		/* testa se realizou a ultima iteracao e pede carga */

		if (it == ITMAX && !pediCarga)
		{
			//incrementoRight=0;

			//if(!pediCarga)
			//{
			MPI_Send(&incrementoRight, 1, MPI_INT, right, PedirCarga, MPI_COMM_WORLD);

			
      		// 	std::cout<<calcula_tempo(t_ini_g, (unsigned long int) clock())<<" Processo = "<<my_rank<<" pediu carga a "
      		// <<right<<std::endl;
      		
			pediCarga = true;
			MPI_Irecv(&incrementoRight, 1, MPI_INT, right, PedirCarga, MPI_COMM_WORLD, &requestRight);
			//}
			//flagRight=-1;
			//for (int i=0;i<50000;i++)
			while (calcula_tempo(t_ini_g, (unsigned long int)clock()) <= TIMEMAX)
			{
				if (!recebiCarga)
				{
					MPI_Test(&requestRight, &flagRight, &status);
					if (flagRight != 0)
					{
						ITMAX += incrementoRight;

						/*
	      				std::cout<<calcula_tempo(t_ini_g, (unsigned long int) clock())<<" Processo = "<<my_rank<<" recebeu "
	      				<< incrementoRight<<" iteracoes do processo "<<right<<std::endl;
	      				*/
						flagRight = 0;
						recebiCarga = true;
						break;
					}
				}

				if (!mandeiCarga) {
					MPI_Test(&requestLeft, &flagLeft, &status);
					//testa (linha acima) e conclui a comunicação aberta com MPI_Irecv
					if (flagLeft != 0)
					{
						incrementoRight = (ITMAX - it) / 2;
						ITMAX -= incrementoRight;
						MPI_Send(&incrementoRight, 1, MPI_INT, left, PedirCarga, MPI_COMM_WORLD);

						
				      		// std::cout<<calcula_tempo(t_ini_g, (unsigned long int) clock())<<
				      		// " Processo = "<<my_rank<<" enviou(A) "<<incrementoRight<<" iteracoes para "	      		
				      		// <<left<<" total de iteracoes=" <<ITMAX <<" iteracoes em " << my_rank <<std::endl;
				      		
						mandeiCarga = true;
						pediramCarga = true;
					}
				}
			}
		}
		//std::cout << "FIM DA ITERAÇÃO" << std::endl;
	} /* for (it=0; it<ITMAX; it++) */
	delete solT0;
	delete solT1;

	/*Caso saia por timeout e ainda esteja aguardando pedido de carga, trata as 
    * comunicações pendentes (left e right)
    */
	//std::cout << calcula_tempo(t_ini_g, (unsigned long int)clock()) << " rank: " << my_rank << " iniciou processo de encerramento" << std::endl;
	//std::cout << "pediCarga="<< pediCarga <<" mandeiCarga="<< mandeiCarga<<std::endl;



	while (!(recebiCarga && mandeiCarga))
	{

		if (pediCarga)
		{
			if (!recebiCarga) 
			{
				incrementoRight = 0;
				MPI_Test(&requestRight, &flagRight, &status);
				if (flagRight != 0)
				{
					recebiCarga=true;
				}
				
			}
		}
		else
		{
			incrementoRight = 0;
			MPI_Send(&incrementoRight, 1, MPI_INT, right, PedirCarga, MPI_COMM_WORLD);
			//std::cout<<calcula_tempo(t_ini_g, (unsigned long int) clock())
			//<<" Processo = "<<my_rank<<" pediu(final) carga para "
			//<<right<<std::endl;
			pediCarga = true;
		}

		if (!mandeiCarga)
		{
			MPI_Test(&requestLeft, &flagLeft, &status);
			incrementoLeft = 0;
			if (flagLeft != 0)
			{
				MPI_Send(&incrementoLeft, 1, MPI_INT, left, PedirCarga, MPI_COMM_WORLD);
				pediramCarga = true;
				mandeiCarga = true;
			}
			
		}
	}
	

	// if (pediCarga)
	// {
	// 	if (!recebiCarga) {
	// 		incrementoRight = 0;
	// 		MPI_Test(&requestRight, &flagRight, &status);
	// 		while (flagRight == 0)
	// 		{
	// 			MPI_Test(&requestRight, &flagRight, &status);
				
	// 	  		/*std::cout<<calcula_tempo(t_ini_g, (unsigned long int) clock()) 
	// 	  		<<" Processo = "<<my_rank<<" recebeu "
	//   			<< incrementoRight<<" iteracoes do processo "<<right<<std::endl;
	//   			*/
	// 		}
	// 		recebiCarga=true;
	// 	}
	// }
	// else
	// {
	// 	incrementoRight = 0;
	// 	MPI_Send(&incrementoRight, 1, MPI_INT, right, PedirCarga, MPI_COMM_WORLD);
	// 	//std::cout<<calcula_tempo(t_ini_g, (unsigned long int) clock())
	// 	//<<" Processo = "<<my_rank<<" pediu(final) carga para "
	// 	//<<right<<std::endl;
	// 	pediCarga = true;
	// }

	// if (!mandeiCarga)
	// {
	// 	MPI_Test(&requestLeft, &flagLeft, &status);
	// 	incrementoLeft = 0;
	// 	while (flagLeft == 0)
	// 	{
	// 		MPI_Test(&requestLeft, &flagLeft, &status);
	// 	}
	// 	MPI_Send(&incrementoLeft, 1, MPI_INT, left, PedirCarga, MPI_COMM_WORLD);
	// 	/*
	//   	std::cout<<calcula_tempo(t_ini_g, (unsigned long int) clock())
	//   	<<" Processo = "<<my_rank<<" enviou(C) "<<incrementoLeft<<" iteracoes para "
	//   		<<left<<std::endl;
	//   		*/

	// 	pediramCarga = true;
	// 	mandeiCarga = true;
	// }

	//std::cout<<calcula_tempo(t_ini_g, (unsigned long int) clock()) <<" Processo = "<<my_rank<< "/Local maxIter = " <<ITMAX <<std::endl;

	return b_sol;
}