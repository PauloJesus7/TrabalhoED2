#ifndef PAGINA_H_
#define PAGINA_H_

#include "util.h"
#include "bplustree.h"

typedef enum folha{
    interna,
    folha
} Folha;

typedef struct pagina{
    int chave[MAX];
    int filho[MAX+1];
    int pai;
    int proximo;
    int nivel;
    int qtde;
    int index;
    Folha tipo;
} Pagina;

void inicializar(BPTree*, Pagina*);
void inserirFolha (Pagina*, int, int);
void ordenarFolha(Pagina*);
void ordenarInterna(FILE*, Pagina*);
Folha ehFolha(Pagina);
bool verificarOverflow(Pagina *);
bool verificarUnderflow(Pagina *);
void liberar(Pagina*);
void imprimir(Pagina*);

#endif