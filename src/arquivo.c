#define _GNU_SOURCE//usada para acessar funcoes da GNU/linux e acessar funcoes de baixo nível que não podem ser portáteis.
/*Conjunto de bibliotecas criadas com funções especificas para auxiliar o programa*/
#include "../headers/arquivo.h"
#include "../headers/util.h"

void
inicializarTabela() {
  FILE* tabelaReg = fopen(REG_FILE, "wb");//criar um arquivo para escrita, ou deletar e criar um novo se já existir

  if (tabelaReg == NULL) {//Neste caso o ponteiro não esta apontando para nenhum valor na memoria, logo havera erro no arquivo
    perror("Erro ao abrir arquivo");
    EXIT_FAILURE;
  }
  
  Tabela tab;//declaração de uma nova variável 
  tab.qtde = 0;//atribuição de uma quantidade inicial 

  fwrite(&tab, sizeof(Tabela), 1, tabelaReg);//permite a escrita de um bloco de bytes no arquivo binario tabelaReg
  fclose(tabelaReg);//fecha o arquivo tabelaReg
}


void 
criarTabelaRegistros (char* caminho) { //função de criação da tabela do registro que será salvo o caminho
  inicializarTabela();//chamada da função
  
  FILE *arquivoTXT = fopen(caminho, "r");//abertura do arquivoTXT para leitura
  FILE *tabelaReg  = fopen(REG_FILE, "wb");//criação de uma tabela binaria para leitura e escrita na função
	
  if(tabelaReg == NULL || arquivoTXT == NULL) {//Neste caso o ponteiro não esta apontando para nenhum valor na memoria, logo havera erro no arquivo
    perror("Erro ao abrir arquivo");
    EXIT_FAILURE;
  }
  
  size_t len = 100;//para armazenar o tamanho de qualquer tipo de objeto em bytes
  char* registro = mallocSafe(len);//Alocando a memória de maneira segura evitando erros de alocação de heap e no malloc, realloc e free.
  const char delim[2] = ",";//declaração de uma constante do tipo char que ocupara um espaço fixo na ram e o valor nao será alterado
  char *info;
  
  Tabela cabecalho;
  cabecalho.qtde = 0;

  fseek(tabelaReg, sizeof(Tabela), SEEK_SET);//define a posição do arquivo do stream para o deslocamento especificado

  while (getline(&registro, &len, arquivoTXT) > 0) {//extrai caracteres do fluxo de entrada e os anexa ao objeto string até que o caractere delimitador seja encontrado
    int campo = 0;
    Paciente paciente;
    
    info = strtok(registro, delim);//quebrar a string registro usando o delimitador informado e retornar suas partes
    while (info != NULL) {//enquanto info aponte para algo diferente de nulo
      switch (campo) {//neste bloco irá ser repassado todos os dados pertinentes a estrutura apontada das informações arquivadas dos Pacientes
        case 0: paciente.id = atoi(info); break;//converter string id em numero
        case 1: paciente.anoNascimento = atoi(info); break;//converter string ano em numero 
        case 2: strncpy(paciente.nome, info, TAM); break;//copia os primeiro Tam caracteres  de info para nome
        case 3: strncpy(paciente.endereco, info, TAM); break;
        case 4: strncpy(paciente.nomeMae, info, TAM); break;
        case 5: strncpy(paciente.nomePai, info, TAM); break;
        case 6:
          strncpy(paciente.CPF, info, TAM);
          strcat(paciente.CPF, ",");//concatena a palavra chave com vírgula
          break;
        default:
          strcat(paciente.CPF, info);//concatena a palavra chave com a informacao que recebeu o registro dividido
          strcat(paciente.CPF, ",");
          break;
      }
      
      campo++;//incrementação da variavel
      info = strtok(NULL, delim);//strtok recebe NULL como entrada, para encontrar as informação subssequentes.
    }  
    
    paciente.CPF[strlen(paciente.CPF) - 1] = '\0';//adiciona /0 ao final da palavra chave
    
    fwrite(&paciente, sizeof(paciente), 1, tabelaReg);
    cabecalho.qtde++;
  }
  
  rewind(tabelaReg);// retornar ao começo do arquivo.voltar o ponteiro de leitura ao começo do arquivo
  fwrite(&cabecalho, sizeof(Tabela), 1, tabelaReg);
  
  free(registro);
  fclose(arquivoTXT);
  fclose(tabelaReg);//fechando arquivos
}


void importarTabela () {
  FILE *tabelaReg = fopen(REG_FILE, "rb");
  
  if (tabelaReg == NULL) {
    perror("Erro ao abrir arquivo");
    EXIT_FAILURE;
  }
  
  BPTreeInicializar();//chamando funcao

  Tabela cabecalho;
  Paciente paciente;
  
  fread(&cabecalho, sizeof(Tabela), 1, tabelaReg);//leitura de um bloco armazenado em tabelaReg com tamanho 1, e numero de elementos da Tabela,e o fluxo será definido pelo cabecalho 

  for(int i = 0; i < cabecalho.qtde; i++){
    fread(&paciente, sizeof(paciente), 1, tabelaReg);
    BPTreeInserir(paciente.id, i);
  }

  fclose(tabelaReg);
}
