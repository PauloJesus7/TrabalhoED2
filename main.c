#include <math.h>//permite usar funções matemáticas básicas,
#include <stdio.h>//responsável pela entrada e saída padrão "Standard In/Out"
#include <stdlib.h>//possui funções envolvendo alocação de memória, controle de processos, conversões e outras.
#include <string.h>//contém uma série de funções para manipular strings
#include <unistd.h>//define diversas constantes e tipos simbólicos e declara diversas funções.
#include <limits.h>//define tamanhos de tipos integrais.
//conjunto de bibliotecas contendo as funções a serem utilizadas no programa
#include "../headers/bplustree.h"
#include "../headers/pagina.h"

int main (int argc, char *argv[]) {//argc é um inteiro que indica a quantidade de argumentos passados e argv é um vetor contendo todas as strings
  system("clear");//serve para limpar a janela do console
  int op;//opcoes do menu de funcoes
  
  while (true) {//enquanto verdadeiro
    setbuf(stdin,NULL);//permite colocar o stdin no modo sem bufferização,Os dados são transmitidos logo ao serem escritos.
    printf("\n=----------------MENU----------------=");
    printf(HWHT"\n[1] - Impressão da árvore "reset);
    printf(HWHT"\n[2] - Buscar por um id"reset);
    printf(HGRN"\n[3] - Inserção de um novo paciente"reset);
    printf(HWHT"\n[4] - Remoção de um paciente"reset);
    printf(HWHT"\n[5] - Listar pacientes com id'S dentro de um intervalo de valores"reset);
    
    printf("=--------------------------------------=\n");
    printf(HMAG"Digite a opção [1-5] -> "reset);
    scanf("%d", &op);
  
    switch (op) {//comparar a entrada de uma expressão com uma constante
      case 1: {//sera feito a impressao da arvore ao indicar esta opcao
        char caminho[TAM];
        printf(HMAG"\nInforme o caminho do um arquivo ou 1 para usar o padrão: "reset);
        scanf("%s", caminho);//leitura do caminho do arquivo importado
        if (strcmp(caminho, "1") != 0){//verifica se foi digitado 1, se sim retorna diferente de 0 para criar tabela.
          criarTabelaRegistros(caminho);
        }
        else {//senao for 1, então ira passar um arquivo texto e criar a tabela.
          criarTabelaRegistros(TXT_FILE);
        }
        break;
      }
  
      case 2://sera feito a busca por um id neste item
        importarTabela();
        break;
      case 3:
	//insercao de um novo paciente
      	break;
      case 4://sera feito a remoção de um paciente nesta item
        printf(HGRN"\n[*] Páginas Folhas  \n"reset);
        printf(HYEL"[*] Páginas Internas\n\n"reset);
        BPTreeImprimeArvoreCompleta();//chamada da funcao para imprimir arvore
        break;

      case 5: {//sera feito a listagem dos pacientes com id'S no intervalo
        int id, pos;
        printf(HMAG"\nInforme o ID do registro: "reset);//procura por um id
        scanf("%d", &id);
        imprimirArtigo(id);
        break;
      }
        
      default:
        continue;//Condição do laço continua sendo testada, incremento 	continua sendo executado
    }
  }
  
  EXIT_SUCCESS;//programa bem sucedido; 0
}
