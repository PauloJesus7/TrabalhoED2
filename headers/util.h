#ifndef UTIL_H_
#define UTIL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

// Importações e constantes globais
#define TXT_FILE "../files/artigos.txt"
#define REG_FILE "../files/tabela_registros.bin"
#define TREE_FILE "../files/arvore.bin"
#define D 2
#define MAX (2 * D + 1)
#define TAM 200

// Debugger
#define DEBUG

#define LOG(x, fmt, ...) if (x) { \
  printf("%s:%d: " fmt "\n", __FILE__, __LINE__,__VA_ARGS__); \
}

#define TRY(x,s) if(!(x)) { \
  printf("%s:%d:%s",__FILE__, __LINE__,s); \
}

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) if(!(n)) { \
                  printf("%s - Failed ",#n); \
                  printf("On %s ",__DATE__); \
                  printf("At %s ",__TIME__); \
                  printf("In File %s ",__FILE__); \
                  printf("At Line %d\n",__LINE__); \
                  return(-1);}
#endif

// Estruturas
typedef struct pagina Pagina;
typedef struct bptree BPTree;

typedef enum {
  false,
  true
} bool;

typedef struct artigo {
  int id;
  int ano;
  char autor[TAM];
  char titulo[TAM];
  char revista[TAM];
  char DOI[TAM];
  char palavraChave[TAM];
} Artigo;

void *mallocSafe(size_t);
void imprimirArtigo(int);

#endif
