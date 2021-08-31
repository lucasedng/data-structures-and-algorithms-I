/*
Descrição
Neste código, deve ser criada uma lista circular duplamente encadeada por meio de apontadores. Um vetor será apresentado ao programa. Para cada valor, se ele for positivo, deve ser inserido no final da lista. Caso seja negativo, deve-se remover da lista a posição correspondente ao módulo do valor lido. Por exemplo, se for lido o valor -1, deve-se remover a posição 1, se ela existir.

Entrada
int n: o tamanho do vetor a ser lido.

int: cada um dos n valores a serem lidos, tanto positivos quanto negativos.

Saída
No final, imprima a lista resultante, retirando e imprimindo cada item.

Exemplo
Entrada

aluno@ubuntu:~$ ./dupla
7
10 71 -9 74 27 -1 17
Saída esperada

10 74 27 17
*/

#include <stdio.h>
#include <stdlib.h>

typedef int TItem;

typedef struct SCelula *TApontador;

// IMPLEMENTE: typedef struct SCelula TCelula
typedef struct SCelula
{
  TItem Item;
  TApontador Prox;
  TApontador Ant;
} TCelula;

// IMPLEMENTE: typedef struct TLista
typedef struct
{
  TApontador Primeiro;
  TApontador Ultimo;
  int Tamanho;
} TLista;

// IMPLEMENTE: int TLista_EhVazia(TLista *pLista)
int TLista_EhVazia(TLista *pLista)
{
  if (pLista->Tamanho == 0)
    return 1;
  return 0;
}

// IMPLEMENTE: void TLista_Inicia(TLista *pLista)
void TLista_Inicia(TLista *pLista)
{
  pLista->Ultimo = (TApontador)malloc(sizeof(TCelula));
  pLista->Ultimo->Prox = pLista->Ultimo;
  pLista->Ultimo->Ant = pLista->Ultimo;
  pLista->Tamanho = 0;
}

// IMPLEMENTE: int TLista_Tamanho(TLista *pLista)
int TLista_Tamanho(TLista *pLista)
{
  return (pLista->Tamanho);
}

// IMPLEMENTE: /* Insere um item na lista na posicao apontada por p */
// int TLista_Insere(TLista *pLista, TApontador p, TItem x)
int TLista_Insere(TLista *pLista, TApontador p, TItem x)
{
  TApontador pNovo;
  if (p == NULL)
    return 0;
  pNovo = (TApontador)malloc(sizeof(TCelula));
  pNovo->Item = x;
  pNovo->Prox = p;
  pNovo->Ant = p->Ant;
  p->Ant->Prox = pNovo;
  if (p->Ant == pLista->Ultimo)
    pLista->Ultimo = pNovo;
  p->Ant = pNovo;
  pLista->Tamanho++;
  return 1;
}

/* Retira o item da lista da posicao apontada por p */
int TLista_Retira(TLista *pLista, TApontador p, TItem *pX)
{
  TApontador pAux;

  if (TLista_EhVazia(pLista))
    return 0;

  pAux = p;
  p->Ant->Prox = p->Prox;
  p->Prox->Ant = p->Ant;
  if (pAux == pLista->Ultimo)
    pLista->Ultimo = p->Ant;
  *pX = pAux->Item;
  free(pAux);
  pLista->Tamanho--;
  return 1;
}

/* Retorna um apontador para o p-ésimo item da lista */
TApontador TLista_Retorna(TLista *pLista, int p)
{
  TApontador pApontador;
  int Posicao;

  Posicao = 0;
  pApontador = pLista->Ultimo->Prox->Prox;
  while ((pApontador != pLista->Ultimo->Prox) && (Posicao != p))
  {
    pApontador = pApontador->Prox;
    Posicao++;
  }

  return pApontador;
}

int main()
{
  TLista *pLista;
  TItem valor;
  TApontador pApontador;
  int p;

  pLista = (TLista *)malloc(sizeof(TLista));
  TLista_Inicia(pLista);

  p = 0;
  int i, n;

  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    scanf("%d", &valor);
    if (valor < 0)
    {
      if (abs(valor) < TLista_Tamanho(pLista))
      {
        pApontador = TLista_Retorna(pLista, abs(valor));
        if (pApontador != NULL)
          TLista_Retira(pLista, pApontador, &valor);
      }
    }
    else
    {
      p = TLista_Tamanho(pLista);
      TLista_Insere(pLista, TLista_Retorna(pLista, p++), valor);
    }
  }

  // Imprime a lista, retirando os elementos
  while (TLista_Retira(pLista, TLista_Retorna(pLista, 0), &valor))
    printf("%d ", valor);
  free(pLista);
  return 0;
}
