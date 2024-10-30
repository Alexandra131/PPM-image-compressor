#include "fisier.h"
//Corcodel Alexandr Andreea 315 CB
TCoada *InitQ()
{                   /* creeaza coada vida cu elemente de dimensiune d;
           anumite implementari pot necesita si alti parametri */
  TCoada *c = NULL; /* spatiu pentru descriptor coada */
  c = (TCoada *)malloc(sizeof(TCoada));
  if (!c)
    return NULL; /* nu exista spatiu -> "esec" */

  c->inc = c->sf = NULL;
  return c; /* intoarce adresa descriptorului cozii */
}

int IntrQ(TCoada *c, Tarb arb) /* adauga element la sfarsitul cozii */
{
  TLista aux = NULL;
  aux = (TLista)malloc(sizeof(TCelula)); /* aloca o noua celula */
  if (!aux)
    return 0; /* alocare imposibila -> "esec" */

  aux->info = arb;

  aux->urm = NULL;
  // aux->valoare = y;
  if (c->sf != NULL)  /* coada nevida */
    c->sf->urm = aux; /* -> leaga celula dupa ultima din coada */
  else                /* coada vida */
    c->inc = aux;     /* -> noua celula se afla la inceputul cozii */
  c->sf = aux;        /* actualizeaza sfarsitul cozii */
  return 1;           /* operatie reusita -> "succes" */
}
int IntrQnr(TCoada *co, int a, int b, int c, int d) /* adauga element la sfarsitul cozii */
{
  TLista aux;
  aux = (TLista)malloc(sizeof(TCelula)); /* aloca o noua celula */
  if (!aux)
    return 0; /* alocare imposibila -> "esec" */
  aux->info->tip = a;
  aux->info->info.rosu = b;
  aux->info->info.verde = c;
  aux->info->info.albastru = d;
  aux->urm = NULL;

  if (co->sf != NULL)  /* coada nevida */
    co->sf->urm = aux; /* -> leaga celula dupa ultima din coada */
  else                 /* coada vida */
    co->inc = aux;     /* -> noua celula se afla la inceputul cozii */
  co->sf = aux;        /* actualizeaza sfarsitul cozii */
  return 1;            /* operatie reusita -> "succes" */
}

Tarb ExtrQ(TCoada *c)
{
  // extragere element din coada
  TLista aux = (TLista)malloc(sizeof(TCelula));
  if (!aux)
    return NULL;
  if (c->inc->urm == NULL)
  { // coada care contine un sg element
    aux = c->inc;

    c->inc = NULL;
    c->sf = NULL;
    return aux->info;
  }
  else if (c->inc->urm != NULL)
  { // coada care nu contine un sg el
    aux = c->inc;
    c->inc = aux->urm;

    return aux->info;
  }
}

void DistrQ(TCoada **c) /* distruge coada */
{
  TLista p = NULL, aux = NULL;
  p = (*c)->inc;
  while (p) // parcurgere
  {
    aux = p;
    p = p->urm;
    free(aux); // eliberare celula
  }
  free(*c);
  *c = NULL;
}
