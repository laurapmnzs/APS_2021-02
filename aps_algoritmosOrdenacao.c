#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <alg_ordena.h> 
// #include <stdio_ext.h>

#define Item unsigned int
#define key(A) (A)
#define less(A,B) (key(A) < key(B))
#define exch(A, B) do {unsigned int t = (A); (A) = (B); (B) = t;} while (0)

#if defined(__MINGW32__) || defined(_MSC_VER) ||defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__)
#define limpar_tela() system("cls")
#else
#define limpar_tela() system("clear")
#endif


Item * a = NULL;
long unsigned int totLinhas = 0; 

// lê valores do arquivo e armazena no vetor a de tipo Item (unsigned int)
//
void leArquivo(char *nomeArquivo)
{
  FILE *arq;
  char Linha[10];
  char *result;
  unsigned long int i=0;


  arq = fopen(nomeArquivo, "rt");
  if (arq == NULL)  // Se houve erro na abertura
  {
     printf("Problemas na abertura do arquivo\n");
     return;
  }
  
  i = 1;
 
  while (!feof(arq)) //Contando total de linhas do arquivo.
  {
      result = fgets(Linha, 10, arq);  
      if (result)  
      i++;
      
  }
  fclose(arq);
  arq = fopen(nomeArquivo, "rt");
  
  totLinhas = i-1;
  i = 1;
  
  free(a);

  a =  (Item *) calloc(totLinhas, sizeof(Item)); //Redimensionando o vetor para o total de linhas do arquivo.

  while (!feof(arq)) //Lendo as linhas do arquivo e armazenando no vetor.
  {
      result = fgets(Linha, 10, arq);  
      if (result){  
		a[i-1] = strtol(Linha, NULL, 10);
	  }
      i++;
  }
  fclose(arq);
}


// Salva os valores ordenados em um arquivo com nome do arquivo 
// prefixado pelo nome do metodo (bubblesort_<nomearquivo.txt>, quicksort_<nomearquivo.txt>, etc
//
void salva_arquivo_ordenado(char metodo[], char nomeArquivo[], Item a[], long unsigned int totLinhas) {
		
  FILE *arq_Salvo;
  char nomeArquivo_Salvo[100];
  //intf("%s \n", nomeArquivo_Salvo);
  unsigned long int i;

  // Define o nome o arquivo Ã  ser salvo
  strcpy(nomeArquivo_Salvo,metodo);			// Coloca o valor da variavel metodo em nomeArquivo_Salvo
  strcat(nomeArquivo_Salvo,nomeArquivo);	// Concatena nomeArquivo_Salvo com o nomeArquivo
  
 
  arq_Salvo = fopen(nomeArquivo_Salvo, "wt");
  if (arq_Salvo == NULL)  // Se houve erro na abertura
  {
     printf("Problemas no salvamento do arquivo\n");
     return;
  }

  for(i=0; i<=totLinhas-1; i++)
  {
      fprintf(arq_Salvo, "%d\n", a[i]);
  }
  fclose(arq_Salvo);
	
}

int main(int argc, char *argv[]) // Funcao principal com passagem de parametro na linha de comando.
{
	clock_t inicio, fim; // Definicao de variaveis para o temporizador.
	double tempo;
	
	limpar_tela();
	printf("===========================================================================================\n");
	printf("   Avaliacao de Algoritmos de Ordenacao - CC - Estrutura de Dados - Prof. Alvaro Prado\n");
	printf("===========================================================================================\n");
	
	leArquivo(argv[1]);
	printf("Nome do arquivo avaliado  : %s\n", argv[1]);
	printf("Total de linhas avaliadas : %ld\n\n", totLinhas);
	printf("===========================================================================================\n");
	
	// Avaliacao algoritmo Bubblesort
	inicio = clock();
	bubblesort(a, totLinhas);
	fim = clock();
	tempo = (double)(fim - inicio) / (CLOCKS_PER_SEC); 
	printf("Tempo Bubblesort    = %3.6f s\n", tempo);
	
	salva_arquivo_ordenado("BubbleSort_", argv[1], a, totLinhas);

	leArquivo(argv[1]);
	// Avaliacao algoritmo Insertion Sort.
	inicio = clock();
	insertion(a, totLinhas);
	fim = clock();
	tempo = (double)(fim - inicio) / (CLOCKS_PER_SEC);
	printf("Tempo Insertionsort = %3.6f s\n", tempo);

    salva_arquivo_ordenado("InsertionSort_", argv[1], a, totLinhas);
	
	leArquivo(argv[1]);
	// Avaliacao algoritmo Quicksort
	inicio = clock();
	quicksort(a, 0, totLinhas);
	fim = clock();
	tempo = (double)(fim - inicio) / (CLOCKS_PER_SEC);
	printf("Tempo Quicksort     = %3.6f s\n", tempo);

    salva_arquivo_ordenado("QuickSort_", argv[1], a, totLinhas+1);
	
	leArquivo(argv[1]);
	// Avaliacao algoritmo Shellsort
	inicio = clock();
	shellsort(a, totLinhas);
	fim = clock();
	tempo = (double)(fim - inicio) / (CLOCKS_PER_SEC);
	printf("Tempo Shellsort     = %3.6f s\n", tempo);
	
    salva_arquivo_ordenado("ShellSort_", argv[1], a, totLinhas);	
	
	printf("===========================================================================================\n");
	
	free(a);
	
}
