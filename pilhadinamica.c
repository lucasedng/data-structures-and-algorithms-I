/*
Tarefa 04 - Pilha dinâmica
Descrição
Neste código, deve ser criada uma pilha por meio de apontadores. Um vetor será apresentado ao programa. Para cada valor, se ele for positivo, deve ser empilhado. Caso negativo, deve-se desempilhar.

Entrada
int n: o tamanho do vetor a ser lido.

int: cada um dos n valores a serem lidos, tanto positivos quanto negativos.

Saída
No final, imprima a pilha resultante, desempilhando e imprimindo cada item.

Exemplo
Entrada

aluno@ubuntu:~$ ./pilha
6
10 71 74 27 -9 17
Saída esperada

17.0000 74.0000 71.0000 10.0000
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef float TItem;

typedef struct SCelula *TApontador;

typedef struct SCelula
{
  TItem Item;
  TApontador Prox;
} TCelula;

// IMPLEMENTE: typedef struct TPilha
typedef struct
{
  TApontador Topo;
  int Tamanho;
} TPilha;

// IMPLEMENTE: void TPilha_Inicia(TPilha *pPilha)
void TPilha_Inicia(TPilha *pPilha)
{
  pPilha->Topo = NULL;
  pPilha->Tamanho = 0;
}

// IMPLEMENTE: int TPilha_EhVazia(TPilha *pPilha), verificando o topo
int TPilha_EhVazia(TPilha *pPilha)
{
  if (pPilha->Topo == NULL)
    return 1;
  return 0;
}

// IMPLEMENTE: int TPilha_Tamanho(TPilha *pPilha)
int TPilha_Tamanho(TPilha *pPilha)
{
  return (pPilha->Tamanho);
}

// IMPLEMENTE: int TPilha_Empilha(TPilha *pPilha, TItem x)
int TPilha_Empilha(TPilha *pPilha, TItem x)
{
  TApontador pNovo;

  pNovo = (TApontador)malloc(sizeof(TCelula));
  pNovo->Item = x;
  pNovo->Prox = pPilha->Topo;
  pPilha->Topo = pNovo;
  pPilha->Tamanho++;
  return 1;
}
// IMPLEMENTE: int TPilha_Desempilha(TPilha *pPilha, TItem *pX)
int TPilha_Desempilha(TPilha *pPilha, TItem *pX)
{
  TApontador pAux;

  if (TPilha_EhVazia(pPilha))
    return 0;

  pAux = pPilha->Topo;
  pPilha->Topo = pAux->Prox;
  *pX = pAux->Item;
  free(pAux);
  pPilha->Tamanho--;

  return 1;
}

int main()
{
  TItem valor;
  TPilha *pPilha;
  int i, n;

  pPilha = (TPilha *)malloc(sizeof(TPilha));
  TPilha_Inicia(pPilha);

  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    scanf("%f", &valor);
    if (valor < 0)
      TPilha_Desempilha(pPilha, &valor);
    else
      TPilha_Empilha(pPilha, valor);
  }

  // Desempilha tudo e imprime
  while (!TPilha_EhVazia(pPilha))
  {
    TPilha_Desempilha(pPilha, &valor);
    printf("%.4f ", valor);
  }

  free(pPilha);

  return 0;
}