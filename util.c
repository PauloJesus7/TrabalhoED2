#define _GNU_SOURCE//usada para acessar funcoes da GNU/linux e acessar funcoes de baixo nível que não podem ser portáteis.
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
/*Conjunto de bibliotecas criadas com funções especificas para auxiliar o programa*/
#include "../headers/util.h"
#include "../headers/bplustree.h"
#include "../headers/pagina.h"

#define ERROR(msg) fprintf(stderr, "[!]: %s\n", #msg)

void *
mallocSafe (size_t nbytes) {//função para alocamento de espaço com segurança de um tipo de dado nao assinado positivo de tamanho nbytes 
  void *ptr = malloc (nbytes);//alocamento dinamico no ponteiro ptr
  
  if (ptr == NULL) {//No caso de não houver memória suficiente
    ERROR(erro ao alocar memória);
    exit(EXIT_FAILURE);//valor padrão para retornar a rescisão mal-sucedida
  }

  return ptr;//ao fim a função retorna o ponteiro com o espaço alocado
}

  
void
imprimirArtigo(int id) {//sera usada para impressao dos dados dos pacientes
  int posPag, posArt = -1;//posicao de paginas e dos artigos  
  
  if(!BPTreeProcurarElemento(id, &posPag)){//funcao de pesquisa por id na arvore
    printf("Paciente não encontrado!!!\n");//no caso de passar um id inexistente
    return;
  }
  
  FILE *arquivoArvore = fopen(TREE_FILE, "rb");//Funcao para abrir arquivo binario para leitura referente a arvore 
  
  Pagina pag;//variavel do tipo pagina
  fseek(arquivoArvore, sizeof(BPTree) + (posPag * sizeof(Pagina)), SEEK_SET);//permite realizar operações de leitura e escrita em arquivos de forma randômica
  fread(&pag, sizeof(Pagina), 1, arquivoArvore);//permite a leitura de um bloco de bytes do arquivo binário pagina
  
  for(int i = 0; i < pag.qtde; i++){//bloco para atribuir paginas na arvore
    if(pag.chave[i] == id){
      posArt = pag.filho[i];
    }
  }

  fclose(arquivoArvore);//fechando o arquivo arvore que estava aberto
  
  FILE *tabelaReg = fopen(REG_FILE, "rb");//abrindo o arquivo da tabela

  if (tabelaReg == NULL) {//caso o arquivo não esteja preenchido havera erro
    perror("Erro ao abrir arquivo");//aceita um parâmetro como um ponteiro para uma string terminada em nulo que contém uma mensagem descritiva sobre o erro.
    EXIT_FAILURE;//valor padrão para retornar a rescisão mal-sucedida
  }
  
  fseek(tabelaReg, sizeof(Tabela) + (posArt * sizeof(Artigo)), SEEK_SET);//permite realizar operações de leitura e escrita em arquivos de forma randômica
  Artigo artigo;//declaracao de variavel
  fread(&artigo, sizeof(Artigo), 1, tabelaReg);//permite a leitura de um bloco de bytes do arquivo binário pagina
  fclose(tabelaReg);//fecha arquivo tabela
	//imprimir todos os dados do paciente
  printf("\nId.........: %d", artigo.id);//id do paciente
  printf("\nAnoNascimento........: %d", artigo.ano);//ano paciente nasceu
  printf("\nNOME......: %s", artigo.autor);//nome do paciente
  printf("\nendereco.....: %s", artigo.titulo);//endereço do paciente
  printf("\nnomeMae....: %s", artigo.revista);//mae do paciente
  printf("\nnomePai........: %s", artigo.DOI);//pai do paciente
  printf("\nCPF...: %s\n", artigo.palavraChave);//CPF do paciente
}
