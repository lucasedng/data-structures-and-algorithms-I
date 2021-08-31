/*
Questão 07 - Grafos (Lista de Adjacências)
Descrição
Neste código, deve ser criada uma lista de adjacências para um grafo. As arestas são lidas do arquivo.

Entrada
int v: a quantidade de vértices do grafo.

int e: a quantidade de arestas do grafo.

int u: o vértice de origem.

int v: o vértice de destino.

Saída
Para cada vértice, imprimir, seperado por espaços: O índice, o Grau de Entrada, o Grau de Saida, cada vértice adjacente. Essa lista de informações de cada vértice deve estar em uma linha. Incremente o índice para que comece em 1. Não existe espaço nos extremos das linhas. Deve-se ter uma nova linha no fim da saída.

Protótipos das funções a serem implementadas: pode copiá-los na folha de prova
*int TGrafo_Inicia(TGrafo pGrafo, int NVertices)**

*int TGrafo_InsereAresta(TGrafo pGrafo, TVertice u, TVertice v, TAresta e)**

Exemplo
Entrada

aluno@ubuntu:~$ ./questao07
5 7
1 3
1 5
2 1
3 2
3 4
4 1
5 2
Saída esperada

1 2 2 3 5
2 2 1 1
3 1 2 2 4
4 1 1 1
5 1 1 2
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXVERTICES 100

typedef int TVertice;

typedef int TAresta;

typedef struct
{
	TVertice Vertice;
	TAresta Aresta;
} TAdjacencia;

#define INICIO 0
#define MAXTAM MAXVERTICES

typedef TAdjacencia TItem;

typedef int TApontador;

typedef struct
{
	TItem Item[MAXTAM];
	TApontador Primeiro, Ultimo;
} TLista;

// ------------------ TAD LISTA - INICIO --------------------------//

/* Inicia as variaveis da lista */
void TLista_Inicia(TLista *pLista)
{
	pLista->Primeiro = INICIO;
	pLista->Ultimo = pLista->Primeiro;
}

/* Retorna se a lista esta vazia */
int TLista_EhVazia(TLista *pLista)
{
	return (pLista->Primeiro == pLista->Ultimo);
}

/* Retorna o tamanho da lista */
int TLista_Tamanho(TLista *pLista)
{
	return (pLista->Ultimo - pLista->Primeiro);
}

/* Insere um item na lista na posicao apontada por p */
int TLista_Insere(TLista *pLista, TApontador p, TItem x)
{
	TApontador q;

	if ((pLista->Ultimo == MAXTAM) || (p < pLista->Primeiro) || (p > pLista->Ultimo))
		return 0;

	for (q = pLista->Ultimo - 1; q >= p; q--)
		pLista->Item[q + 1] = pLista->Item[q];
	pLista->Item[p] = x;
	pLista->Ultimo++;

	return 1;
}

/* Retira o item da lista da posicao apontada por p */
int TLista_Retira(TLista *pLista, TApontador p, TItem *pX)
{
	TApontador q;

	if (TLista_EhVazia(pLista) || (p < pLista->Primeiro) || (p >= pLista->Ultimo))
		return 0;

	*pX = pLista->Item[p];
	for (q = p + 1; q < pLista->Ultimo; q++)
		pLista->Item[q - 1] = pLista->Item[q];

	pLista->Ultimo--;

	return 1;
}

int TLista_Retorna(TLista *pLista, TApontador p, TItem *pX)
{
	if (TLista_EhVazia(pLista) || (p < pLista->Primeiro) || (p > pLista->Ultimo))
	{
		return 0;
	}

	*pX = pLista->Item[p];

	return 1;
}

// ------------------ TAD LISTA - FIM ----------------------------//

// ----------------------- TAD GRAFO -----------------------------//

typedef struct
{
	TLista Adj[MAXVERTICES];
	int NVertices;
	int NArestas;
} TGrafo;

//Implemente a funcao para inicializacao do grafo
int TGrafo_Inicia(TGrafo *pGrafo, int NVertices)
{
	int i;
	pGrafo->NArestas = 0;
	pGrafo->NVertices = NVertices;

	for (i = 0; i < NVertices; i++)
		TLista_Inicia(&pGrafo->Adj[i]);
	return 1;
}

/* Retorna o numero de vertices do grafo */
int TGrafo_NVertices(TGrafo *pGrafo)
{
	return (pGrafo->NVertices);
}

/* Retorna o numero de arestas do grafo */
int TGrafo_NArestas(TGrafo *pGrafo)
{
	return (pGrafo->NArestas);
}

// Implementar a funcao que verifica se uma dada aresta (u,v) pertence ao grafo
int TGrafo_ExisteAresta(TGrafo *pGrafo, TVertice u, TVertice v)
{
	int i;
	TAdjacencia aux;
	for (i = 0; i < TLista_Tamanho(&pGrafo->Adj[u]); i++)
		if (TLista_Retorna(&pGrafo->Adj[u], i, &aux))
			if (aux.Vertice == v)
				return i + 1;
	return 0;
}

// Implementar a funcao que insere uma aresta (u,v) no grafo
// Dica: entenda a função TGrafo_ExisteAresta
int TGrafo_InsereAresta(TGrafo *pGrafo, TVertice u, TVertice v, TAresta e)
{
	if (TGrafo_ExisteAresta(pGrafo, u, v))
		return 0;

	TItem x;
	x.Aresta = e;
	x.Vertice = v;

	TLista_Insere(&pGrafo->Adj[u], TLista_Tamanho(&pGrafo->Adj[u]), x);
	return 1;
}

// Implementar a funcao de remocao de uma aresta (u,v) do grafo
// OBS: Lembre-se de retornar a aresta removida no ponteiro TAresta *pE, que esta sendo passado por parametro
int TGrafo_RetiraAresta(TGrafo *pGrafo, TVertice u, TVertice v, TAresta *pE)
{
	TItem x;

	int aux = TGrafo_ExisteAresta(pGrafo, u, v) - 1;
	if (aux == -1)
		return 0;

	TLista_Retira(&pGrafo->Adj[u], aux, &x);
	*pE = x.Aresta;
	return 1;
}

/* Retorna a lista de adjacentes do vertice u no grafo */
TLista *TGrafo_ListaAdj(TGrafo *pGrafo, TVertice u)
{
	TLista *pLista, ListaAdj;
	TAdjacencia Adj;

	pLista = (TLista *)malloc(sizeof(TLista));
	TLista_Inicia(pLista);

	TLista_Inicia(&ListaAdj);
	while (TLista_Retira(&pGrafo->Adj[u], TLista_Tamanho(&pGrafo->Adj[u]) - 1, &Adj))
		TLista_Insere(&ListaAdj, TLista_Tamanho(&ListaAdj), Adj);

	while (TLista_Retira(&ListaAdj, TLista_Tamanho(&ListaAdj) - 1, &Adj))
	{
		TLista_Insere(&pGrafo->Adj[u], TLista_Tamanho(&pGrafo->Adj[u]), Adj);
		TLista_Insere(pLista, TLista_Tamanho(pLista), Adj);
	}

	return pLista;
}

//IMPLEMENTE
int TGrafo_GrauEntrada(TGrafo *pGrafo, TVertice u)
{
	int i, s = 0;
	for (i = 0; i < pGrafo->NVertices; i++)
		if (TGrafo_ExisteAresta(pGrafo, i, u))
			s++;
	return s;
}

/* Retorna o grau de saida do vertice u no grafo */
int TGrafo_GrauSaida(TGrafo *pGrafo, TVertice u)
{
	TVertice v;
	int d;

	d = 0;
	for (v = 0; v < pGrafo->NVertices; v++)
		if (TGrafo_ExisteAresta(pGrafo, u, v))
			d++;

	return d;
}

int main()
{
	TAdjacencia Adj;
	TGrafo *pGrafo;
	TLista *pLista;
	TVertice u, v;
	int i, N, D;

	scanf("%d %d", &N, &D);

	pGrafo = (TGrafo *)malloc(sizeof(TGrafo));
	TGrafo_Inicia(pGrafo, N);

	for (i = 0; i < D; i++)
	{
		scanf("%d %d", &u, &v);
		TGrafo_InsereAresta(pGrafo, u - 1, v - 1, 0);
	}

	for (u = 0; u < TGrafo_NVertices(pGrafo); u++)
	{
		pLista = TGrafo_ListaAdj(pGrafo, u);
		printf("%d %d %d", u + 1, TGrafo_GrauEntrada(pGrafo, u), TGrafo_GrauSaida(pGrafo, u));
		while (TLista_Retira(pLista, 0, &Adj))
			printf(" %d", Adj.Vertice + 1);
		printf("\n");
		free(pLista);
	}

	return 0;
}