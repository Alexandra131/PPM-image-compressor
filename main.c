#include "fisier.h"
#include <string.h>
#define f1 "-c"
#define f2 "-c1"
#define f3 "-c2"
#define f4 "-d"
//Corcodel Alexandra Andreea 315 CB
int main(int argc, char const *argv[])
{
  unsigned int nr_pix;
  int nr_max, nr_nivele;
  unsigned int linie, coloana;
  Tculoare **matrice; //matircea pe care o citim
  TCoada *c = InitQ(); //coada task2
  TCoada *coada2 = InitQ(); //coada task 2
  TCoada *coada3 = InitQ(); //coada task 3

  Tarb arbore = (Tarb)malloc(sizeof(TNod)); //alocam cei 2 arbori
  Tarb arbore2 = (Tarb)malloc(sizeof(TNod));
  // int factor = atoi(argv[2]);
  char const *task = argv[1];
  if (strstr(task, f1))
  {
    FILE *in = fopen(argv[3], "rb");
    FILE *fout = fopen(argv[4], "w+");
    char tip[3];
    fgets(tip, 3, in); //citim tipul
    fscanf(in, "%d", &linie); //linia
    fscanf(in, "%d", &coloana); //coloana
    fscanf(in, "%d", &nr_max); //cata intensitate max are o culoare
    int factor = atoi(argv[2]);
    char const *task = argv[1];

    matrice = (Tculoare **)malloc(linie * sizeof(Tculoare *)); // alocarea matrice
    for (int i = 0; i < linie; i++)
    {
      matrice[i] = (Tculoare *)malloc(coloana * sizeof(Tculoare));
    }
    fgetc(in); //construire matrice
    for (int i = 0; i < linie; i++)
    {
      for (int j = 0; j < coloana; j++)
      {
        fread(&matrice[i][j].rosu, sizeof(unsigned char), 1, in);
        fread(&matrice[i][j].verde, sizeof(unsigned char), 1, in);
        fread(&matrice[i][j].albastru, sizeof(unsigned char), 1, in);
      }
    }
    nr_pix = linie * coloana; //calcul nr pixeli
    int niv_min = 100;
    int size_retrunat = 0;
    arbore = constrArb(matrice, 0, 0, factor, linie); //construirea arborelui
    if (strstr(task, f2))
    {
      int nr_size = dimesniunefrunza(arbore, 0, &niv_min, linie, &size_retrunat);
      //calculare dimensiune frunza cea mai apropiata de radacina
      int nr_frunze = nrfrunze(arbore); //numar total frunze
      nr_nivele = NrNiv(arbore); //nr niveluri
      fprintf(fout, "%d\n", nr_nivele); //printarea informatiilor de mai sus
      fprintf(fout, "%d\n", nr_frunze);
      fprintf(fout, "%d\n", nr_size);
    }
    else if (strstr(task, f3))
      afisarearb(arbore, c, fout, linie, coada2);
  }
  // else if (strstr(task, f4))
  // {
  //   FILE *n = fopen(argv[2], "rb");
  //   FILE *fn = fopen(argv[3], "wb");
  //   unsigned int nr_afis;
  //   printf("%s", argv[2]);
  //   unsigned char nr;
  //   fread(&nr_afis, sizeof(unsigned int), 1, n);
  //   // printf("%d\n", linie);

  //   //  while (fread(&nr, sizeof(unsigned char), 1, n))
  //   //  {
  //   //    
  //   // printf("%d\n", nr);

  //   //   if (nr == '0')
  //   //   { printf("alhhh\n");
  //   //     IntrQnr(coada3, '0', nr, nr, nr); }
  //   //   if (nr == '1')
  //   //   { printf("rrr\n");
  //   //     unsigned char nr1, nr2, nr3;
  //   //     fread(&nr1, sizeof(unsigned char), 1, n);
  //   //     fread(&nr2, sizeof(unsigned char), 1, n);
  //   //     fread(&nr3, sizeof(unsigned char), 1, n);
  //   //     IntrQnr(coada3, '1', nr1, nr2, nr3);
  //   // }
  //   // }
  //   //  arbore2 = returnArb(coada3, &arbore2);
  //   // afisareA(arbore2);
  // }
  return 0;
}
