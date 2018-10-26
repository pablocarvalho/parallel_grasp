
#ifndef STRUCT
#define STRUCT

#ifndef PRECISAO
#define PRECISAO 0.00001
#endif

#ifndef INFINITO
#define INFINITO 1000000000
#endif

#ifndef TEMPOMAXGRASP
#define TEMPOMAXGRASP 300
#endif
#include <iostream>
// estrutura aresta do grafo
typedef struct edge_st
{
  bool pos;
  bool neg;
} str_e;

inline std::ostream &operator<<(std::ostream &os, str_e const &m) { 
    return os << "(" << m.pos << "," << m.neg << ");";
}

// estrutura pilha
struct ststackno
{
   int ind;
   struct ststackno* proximo;
};
typedef struct ststackno* ptstackno;

#endif
