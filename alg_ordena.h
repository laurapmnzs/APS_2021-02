#include <stdio.h>
#include <stdlib.h>

#define Item unsigned int
#define key(A) (A)
#define less(A,B) (key(A) < key(B))
#define exch(A, B) do {unsigned int t = (A); (A) = (B); (B) = t;} while (0)

// ****************************************** //
// Algoritmo Bubblesort - Ordenacao por bolha //
// ****************************************** //
// Esse algoritmo percorre o vetor trocando elementos adjacentes, se necessario.
// Parametros: vetor de elementos do tipo 'unsigned int'
//             número total de elementos no vetor
// 

void bubblesort (Item a[], int N)
{
    int i; 
	for (i=0; i < N-1; i++) 
	{
		int sorted = 1 ;
		int j;
		for (j = N-1; j > i; j--)
		{
			if (less(a[j], a[j-1]))
			{
				exch(a[j-1], a[j]);
				sorted = 0 ;
			}
		}
	if (sorted) return ;
	}
}

// ******************************** //
// Partition - Ordenar por Particao //
// ******************************** //
// Essa funcao seleciona um valor do vetor como pivo e particiona o vetor em duas partes:
// valores menores que o pivo e valores maiores que o pivo
// Parametros: vetor de elementos do tipo 'unsigned int'
//             int l (left), elemento que esta, mais a  esquerda no vetor (inicio do vetor)
//             int r (right), elemento que esta¡ mais a direita no vetor (fim do vetor / total de elementos no vetor)
//             

int partition(Item a[], int l, int r)
{
    unsigned int v, i, j, t;
    i = l-1; j = r; v = a[r];
    do {
        do{i = i+1; /* esquerda*/
            } while ((a[i] < v) && (i < r)) ;
        do{j = j-1; /* direita*/
            } while ((a[j] > v) && (j > 0));
        t = a[i]; a[i] = a[j]; a[j] = t;
    } while (j > i);
    a[j] = a[i];
    a[i] = a[r];
    a[r] = t;
    return (i);
}

// ******************* //
// Algoritmo Quicksort //
// ******************* //
// Desenvolvido por Tony Hoare em 1959, e publicado em 1961.
// "Dividir para conquistar"
// Esse algoritmo divide o vetor em dois sub-vetores (funcao partition), e os classifica independentemente.
// Para¢metros: o metodo quicksort utiliza os mesmos parametros da funcao partition.
//

void quicksort(Item a[], int l, int r)
{
    if (r <= l) return ;
    int i = partition(a, l, r);
    quicksort(a, l, i-1);
    quicksort(a, i +1, r);
}

// ************************************************* //
// Algoritmo Insertion sort - Ordenacao por insercao //
// ************************************************* //
// Esse metodo divide o vetor em duas partes: a parte ordenada e a parte que ainda nao foi ordenada.
// O metodo percorre o vetor, comparando cada elemento com o anterior, inserindo o elemento na posicao correta quando necessario.
// Parametros: vetor de elementos do tipo 'unsigned int'
//   	   	   numero total de elementos no vetor
//  

void insertion (Item a[], int N)
{
/*get a sentinel*/
	int min = 0 ;
	int i;
	for (i = 1; i < N; i++)
	if (less(a[i], a[min])) min = i;
	exch(a[0], a[min]);
/*sort the array*/
    
	for (i = 1; i < N; i++)
	{
		int j = i;
		Item v = a[i] ;
		while (less(v, a[j-1]))
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = v;
	}
}

// ************************************* //
// Algoritmo Shellsort - Metodo de Shell //
// ************************************* //
// Criado por Donald Shell em 1959.
// E uma versao otimizada do metodo Insertion sort.
// Diferente do metodo de insercao (troca de elementos adjacentes), o metodo de Shell permite a troca de elementos distantes.
// Parametros: vetor de elementos do tipo 'unsigned int'
//             numero total de elementos no vetor
//

void shellsort(Item a[], int N)
{
    int l = 0, r = N-1, i, h ;
    for (h = r-l+1; h > 0; h = ((h > 1) && (h < 5)) ? 1 : 5*h/11)
    {
        for (i = l+h; i <= r; i++)
        {
			int j = i;
			Item v = a[i];
			while (j >= l+h && less(v, a[j-h]))
			{
				a[j] = a[j-h];
				j -= h;
			}
        a[j] = v;
        }
    }
}
