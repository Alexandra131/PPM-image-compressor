#include "fisier.h"
//Corcodel Alexandra Andreea 315Cb
// task1 de aici
Tarb ConstrFr(int x, int y, int z) /* -> adresa frunza cu informatia x, sau
                NULL daca nu exista spatiu */
{
    Tarb aux = (Tarb)malloc(sizeof(TNod));
    if (!aux)
        return NULL;
    aux->info.rosu = x; //punem in frunza informatia
    aux->info.verde = y;
    aux->info.albastru = z;
    aux->st1 = aux->dr1 = aux->st2 = aux->dr2 = NULL;
    return aux;
}

Tarb constrArb(Tculoare **matrice, int x, int y, int factor, int size)
{ //construirea arborelui dupa aflarea matricei de adiacenta
    int a = 0, b = 0, c = 0;
    Tarb arb = ConstrFr(a, b, c); //construire frunza
    if (!arb)
        return NULL;

    if (size == 0)
        return NULL;
    int linie = sizeof(matrice) / sizeof(matrice[0]); //calculare linie matrice
    int coloana = sizeof(matrice[0]) / sizeof(int); //calculare coada matrice
    int rosu = 0, verde = 0, albastru = 0;
    int sumar = 0, sumav = 0, sumaa = 0;
    long long suma1 = 0;
    long long mean = 0;
    for (int i = x; i < x + size; i++) //calculare rosu
    {
        for (int j = y; j < y + size; j++)
        {
            sumar = sumar + matrice[i][j].rosu;
        }
    }
    rosu = sumar / (size * size);

    for (int i = x; i < x + size; i++) //calculare verde
    {
        for (int j = y; j < y + size; j++)
        {
            sumav = sumav + matrice[i][j].verde;
        }
    }
    verde = sumav / (size * size);

    for (int i = x; i < x + size; i++) //aflare rezultat albastru
    {
        for (int j = y; j < y + size; j++)
        {
            sumaa = sumaa + matrice[i][j].albastru;
        }
    }
    albastru = sumaa / (size * size);

    for (int i = x; i < x + size; i++)
    {
        for (int j = y; j < y + size; j++)
        { //calculul pentru suma  
            suma1 = suma1 + ((rosu - matrice[i][j].rosu) * (rosu - matrice[i][j].rosu));

            suma1 = suma1 + ((verde - matrice[i][j].verde) * (verde - matrice[i][j].verde));

            suma1 = suma1 + ((albastru - matrice[i][j].albastru) * (albastru - matrice[i][j].albastru));
        }
    }

    mean = suma1 / (3 * size * size); //calculare propriu zis mean
    // printf("%lld m\n", mean);
    if (mean > factor) //caz in care avem nod intern
    {
        arb->tip = '0'; //tipul este 0
        arb->st1 = constrArb(matrice, x, y, factor, size / 2); //parcurgem recursiv functia pt toti fii
        arb->st2 = constrArb(matrice, x, y + size / 2, factor, size / 2);
        arb->dr1 = constrArb(matrice, x + size / 2, y + size / 2, factor, size / 2);
        arb->dr2 = constrArb(matrice, x + size / 2, y, factor, size / 2);
    }
    else if (mean <= factor)
    {  //caz in care avem frunza
        arb->tip = '1'; // frunza
        arb->info.rosu = rosu; //punem informatia in frunza cu ajutorul sumelor de mai sus
        arb->info.verde = verde;
        arb->info.albastru = albastru;
        return arb;
    }
    return arb;
}

int NrNiv(Tarb r) /* numar niveluri (0 pentru arbore vid) */
{
    int ns1, nd1, ns2, nd2, ns, nd;
    if (!r)
        return 0;
    ns1 = NrNiv(r->st1);
    nd1 = NrNiv(r->dr1);
    ns2 = NrNiv(r->st2);
    nd2 = NrNiv(r->dr2);
    if (ns1 > ns2) // comparam nivelul sd1 cu sd2 
    {
        ns = ns1; //luam nr maxim
    }
    else
    {
        ns = ns2;
    }
    if (nd1 > nd2) //comparam dr1 cu dr2
    {
        nd = nd1; //luam maximul
    }
    else
    {
        nd = nd2;
    }
    return 1 + (ns >= nd ? ns : nd); //returnam nivelul maxim
}

int nrfrunze(Tarb arb) //numara toate frunzele din arbore
{
    if (!arb) 
        return 0;
    if (arb->tip == '0')
    {//caz in care avem radacina
        return nrfrunze(arb->st1) + nrfrunze(arb->st2) + nrfrunze(arb->dr1) + nrfrunze(arb->dr2);
    }
    else if (arb->tip == '1')
    { //caz in care avem frunza
        return 1 + nrfrunze(arb->st1) + nrfrunze(arb->st2) + nrfrunze(arb->dr1) + nrfrunze(arb->dr2); 
    }
}

int dimesniunefrunza(Tarb arb, int nivel, int *min_nivel, int size, int *size_returnat)
{ //afisam dimensiunea frunzei care este mai apropiata de radacina
    if (arb == NULL)
        return 0;
    // int size_returnat = 0;
    if (arb->tip == '1')
    { //daca este frunza
        if (nivel < *min_nivel)
        { //daca nivelul pe care ne afla este mai mic decat minimul, le schimbam
            // int size_returnat = 0;
            *min_nivel = nivel;
            *size_returnat = size; //pastram dimensiunea
        }
    } //caz in care este nod intern, parcurgem recursiv
    dimesniunefrunza(arb->st1, nivel + 1, min_nivel, size / 2, size_returnat);
    dimesniunefrunza(arb->st2, nivel + 1, min_nivel, size / 2, size_returnat);
    dimesniunefrunza(arb->dr1, nivel + 1, min_nivel, size / 2, size_returnat);
    dimesniunefrunza(arb->dr2, nivel + 1, min_nivel, size / 2, size_returnat);
    return *size_returnat; //returnam dimensiunea 
}

// final task 1

int afisarearb(Tarb arb, TCoada *coada, FILE *fout, unsigned int latura, TCoada *coada2)
{ //afisare arbore comprimat
    fwrite(&latura, sizeof(unsigned int), 1, fout);
    //scriere latura in fisier binar
    // printf("%d\n", latura);
    if (arb == NULL)
        return 0;
    unsigned char nr_0 = 0;
    unsigned char nr_1 = 1;
    // printf ("%c", nr_1);
    IntrQ(coada, arb); //introducem elemente in coada
    IntrQ(coada2, arb); //introducem elemente in coada
    while (coada->inc != NULL)
    { //cat timp nu avem o coada vida executam

        Tarb coada_copie = ExtrQ(coada); //extragem cate un elemet
        if (coada_copie == NULL)
            return 0;
        if (coada_copie->tip == '0')
        { //daca este de tip 0 printam 0
            fwrite(&nr_0, sizeof(unsigned char), 1, fout);
            // printf("0\n");
        }
        else if (coada_copie->tip == '1')
        { //daca este de tip 1 printam 1 si informatia
            fwrite(&nr_1, sizeof(unsigned char), 1, fout);
            // printf("1\n");
            fwrite(&coada_copie->info.rosu, sizeof(unsigned char), 1, fout);
            fwrite(&coada_copie->info.verde, sizeof(unsigned char), 1, fout);
            fwrite(&coada_copie->info.albastru, sizeof(unsigned char), 1, fout);
            //  printf("{%d,", coada_copie->info.rosu);
            //   printf("%d,", coada_copie->info.verde);
            //   printf("%d}", coada_copie->info.albastru);
        } 
        //daca avem fii, ii introducem in coada
        if (coada_copie->st1 != NULL)
            IntrQ(coada, (coada_copie)->st1);
        IntrQ(coada2, (coada_copie)->st1);
 
        if (coada_copie->st2 != NULL)
            IntrQ(coada, coada_copie->st2);
        IntrQ(coada2, coada_copie->st2);

        if (coada_copie->dr1 != NULL)
            IntrQ(coada, coada_copie->dr1);
        IntrQ(coada2, coada_copie->dr1);
        if (coada_copie->dr2 != NULL)
            IntrQ(coada, coada_copie->dr2);
        IntrQ(coada2, coada_copie->dr2);
    }
    return 1;
}

Tarb returnArb(TCoada *coada2, Tarb *arb)
{

    // printf ("d\n");
    if (coada2->inc == NULL)
        return NULL;

    Tarb arb_copie;
    arb_copie = ExtrQ(coada2);
    if (arb_copie == NULL)
        return NULL;
    printf("%cr\n", arb_copie->tip);
    if (arb_copie->tip == '0')
    {
        printf("d\n");
        int a = 0, b = 0, c = 0;
        *arb = ConstrFr(a, b, c);
        if (!arb)
            return NULL;
        (*arb)->tip = '0';
        (*arb)->st1 = returnArb(coada2, &((*arb)->st1));
        (*arb)->st2 = returnArb(coada2, &((*arb)->st2));
        (*arb)->dr1 = returnArb(coada2, &((*arb)->dr1));
        (*arb)->dr2 = returnArb(coada2, &((*arb)->dr2));
    }
    else if (arb_copie->tip == '1')
    {
        printf("dff");
        (*arb)->tip = '1';
        *arb = ConstrFr(arb_copie->info.rosu, arb_copie->info.verde, arb_copie->info.albastru);
        if (!arb)
            return NULL;
        (*arb)->info.rosu = arb_copie->info.rosu;
        (*arb)->info.verde = arb_copie->info.verde;
        (*arb)->info.albastru = arb_copie->info.verde;
        return *arb;
    }
    return *arb;
}

int afisareA(Tarb arb)
{
    printf("ddt");
    if (arb == NULL)
        return 0;
    if (arb->tip == '0')
    {
        printf("0\n");
        afisareA(arb->st1);
        afisareA(arb->st2);
        afisareA(arb->dr1);
        afisareA(arb->dr2);
    }
    else if (arb->tip == '1')
    {
        printf("1\n");
        printf("{%c,%c,%c}\n", arb->info.rosu, arb->info.verde, arb->info.albastru);
    }
    return 0;
}
