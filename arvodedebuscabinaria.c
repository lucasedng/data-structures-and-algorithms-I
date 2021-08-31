/*
Questão 08 - Árvore de Busca Binária
Descrição
Neste código, deve ser criada uma árvore de busca binária. Após isso, uma determinada chave deve ser removida.

Entrada
int n: a quantidade de elementos a serem inseridos na árvore.

int chave: cada um dos n elementos.

int chave_rem: a chave a ser removida da árvore.

Saída
No final, deve-se imprimir a árvore após a remoção da chave.

Protótipos das funções a serem implementadas: pode copiá-los na folha de prova
TABB TABB_Inicia()

int TABB_Insere(TABB *pRaiz, TItem x)

Exemplo
Entrada

aluno@ubuntu:~$ ./questao08
10
4339 16070 16766 7711 13352 3530 24823 9093 2256 19300
4339
Saída esperada

(C7711(C3530(C2256()())())(C16070(C13352(C9093()())())(C16766()(C24823(C19300()())()))))
*/

#include <stdio.h>
#include <stdlib.h>

typedef int TChave;

typedef struct
{
    TChave Chave;
    // outros compomentes
} TItem;

typedef struct SNo *TABB;

typedef struct SNo
{
    TItem Item;
    TABB Esq, Dir;
} TNo;

// IMPLEMENTE A FUNCAO PARA INICIALIZACAO DE UMA ARVORE
//
TABB TABB_Inicia()
{
    return NULL;
}

// Cria novo no
TABB TABB_CriaNo(TItem x, TABB Esq, TABB Dir)
{
    TABB No;

    No = (TABB)malloc(sizeof(TNo));
    No->Item = x;
    No->Esq = Esq;
    No->Dir = Dir;

    return No;
}

// Libera uma arvore da memoria (fc recursiva)
void TABB_Libera(TABB No)
{
    if (No != NULL)
    {
        TABB_Libera(No->Esq);
        TABB_Libera(No->Dir);
        free(No);
    }
}

// Imprime o conteudo de uma arvore (fc recursiva)
void TABB_Imprime(TABB No)
{
    if (No != NULL)
    {
        printf("(C%d", No->Item.Chave);
        TABB_Imprime(No->Esq);
        TABB_Imprime(No->Dir);
        printf(")");
    }
    else
        printf("()");
}

// IMPLEMENTE A FUNCAO PARA PESQUISAR (BUSCAR) UMA CHAVE NA ARVORE
//
// Retorna o no correspondente, caso encontrado.
// Retorna NULL, caso a chave procurada nao exista.
TABB TABB_Pesquisa(TABB Raiz, TChave x)
{
    TABB No;
    No = Raiz;
    while ((No != NULL) && (x != No->Item.Chave))
    {
        if (x < No->Item.Chave)
            No = No->Esq;
        else if (x > No->Item.Chave)
            No = No->Dir;
    }
    return No;
}

// IMPLEMENTE A FUNCAO PARA INSERCAO DE UM VALOR NA ARVORE
// Retorna 1, se inserir com sucesso.
// Retorna 0, caso contrário.
//
int TABB_Insere(TABB *pRaiz, TItem x)
{
    TABB TNo;
    if ((*pRaiz) == NULL)
    {
        (*pRaiz) = (TABB)malloc(sizeof(TNo));
        (*pRaiz)->Dir = NULL;
        (*pRaiz)->Esq = NULL;
        (*pRaiz)->Item = x;
        return 1;
    }
    else if (x.Chave < (*pRaiz)->Item.Chave)
        return TABB_Insere(&(*pRaiz)->Esq, x);
    else if (x.Chave > (*pRaiz)->Item.Chave)
        return TABB_Insere(&(*pRaiz)->Dir, x);
    else
        return 0;
}

// O no r, passado como parametro, sera sempre o q->Dir,
// portanto espera-se encontrar o menor valor, que seja maior que q->Item.
// Apos encontrado, esse valor eh atribuido a q.
// Para entender melhor, basta ver o exemplo dos slides de numero 64 a 79.
void TABB_Sucessor(TABB *q, TABB *r)
{
    if ((*r)->Esq != NULL)
        TABB_Sucessor(q, &(*r)->Esq);
    else
    {                            // Apos encontrar o no mais a esquerda de r
        (*q)->Item = (*r)->Item; // atribui o Item desse valor mais a esqueda no no q
        *q = *r;                 // Guarda o endereco de memoria do no q, para posterior liberacao de memoria

        // O no mais a esquerda dara lugar ao teu filho mais a direita. Lembre-se que ele nao tem mais filhos a direita.
        *r = (*r)->Dir;
    }
}

// Remove uma dada chave da arvore
int TABB_Remove(TABB *pRaiz, TChave x)
{
    TABB *p, q;

    p = pRaiz;
    while ((*p != NULL) && (x != (*p)->Item.Chave))
    {
        if (x < (*p)->Item.Chave)
            p = &(*p)->Esq;
        else if (x > (*p)->Item.Chave)
            p = &(*p)->Dir;
    }

    if (*p != NULL)
    {
        q = *p;
        if (q->Esq == NULL) // Nao possui o filho da esquerda
            *p = q->Dir;
        else if (q->Dir == NULL) // Nao possui o filho da direita
            *p = q->Esq;
        else                            // possui dois filhos
            TABB_Sucessor(&q, &q->Dir); // equivalente a Predecessor(&q, &(*q)->Esq);

        free(q);
        return 1;
    }

    return 0; // retorna 0 caso o item nao esteja na arvore
}

void Carrega(TABB *pNo)
{
    int i, n;
    TItem x;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &x.Chave);
        TABB_Insere(pNo, x);
    }
}

int main()
{
    TABB Raiz;
    TItem x;

    Raiz = TABB_Inicia();
    Carrega(&Raiz);
    scanf("%d", &x.Chave);
    if (TABB_Pesquisa(Raiz, x.Chave) == NULL)
        TABB_Insere(&Raiz, x);
    else
        TABB_Remove(&Raiz, x.Chave);
    TABB_Imprime(Raiz);
    TABB_Libera(Raiz);

    return 0;
}
