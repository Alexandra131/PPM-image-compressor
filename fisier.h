#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
//Corcodel  Alexandra Andreea
typedef struct Tculoare {
   unsigned  char rosu;
    unsigned char verde;
    unsigned char albastru;
} Tculoare;


typedef struct nod {
     
    Tculoare info;
    struct nod *st1, *st2, *dr1, *dr2; 
    unsigned char tip;
} TNod, *Tarb;

typedef struct celula {
  Tarb info;
  char valoare;
  struct celula* urm;
} TCelula, *TLista;

typedef struct coada {
  TLista inc, sf;       /* adresa primei si ultimei celule */
} TCoada;

//Tarb ConstrNod (int x, Tarb s1, Tarb s2, Tarb d1, Tarb d2);
Tarb ConstrFr(int x, int y, int z);
void distruge(Tarb r);
void DistrArb(Tarb *a);
int NrNoduri(Tarb r);
int NrNiv(Tarb r);
int nrfrunze(Tarb arb);
Tarb constrArb(Tculoare **matrice, int x, int y, int factor, int size);
int dimesniunefrunza (Tarb arb, int nivel, int *min_nivel, int size, int *size_returnat);
int IntrQ(TCoada *c, Tarb arb);
Tarb ExtrQ(TCoada *c);
TCoada *InitQ();
int afisarearb(Tarb arb, TCoada *coada,FILE *fout, unsigned int latura, TCoada *coada2);
int IntrQnr(TCoada *coada, int a, int b, int c, int d);
Tarb returnArb(TCoada *coada2, Tarb *arb);
int afisareA(Tarb arb);