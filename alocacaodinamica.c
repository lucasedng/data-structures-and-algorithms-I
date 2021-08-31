/*
Questão 01 - Alocação Dinâmica (Vetor e Matriz 2d)
Descrição
Neste código, deve ser criado um vetor, a ser alocado dinamicamente.

Entrada
int n: o tamanho do vetor a ser alocado. Deve ser verificada a validade do tamanho.

int: cada um dos n valores a serem inseridos no vetor.

int linhas int colunas: a quantidade de linhas e colunas da matriz.

int: cada um dos linhas*colunas valores a serem inseridos na matriz, preenchida por linha.

Saída
Após alocado o vetor, o código irá ler os dados de entrada, inserí-los no final vetor, e finalizar imprimindo o vetor do início para o fim.

Exemplo
Entrada

aluno@ubuntu:~$ ./questao01
3
10 3 5
3 2
7 10
15 20
1 3

Saída esperada

10 3 5
7 10
15 20
1 3

*/

#include <stdio.h>
#include <stdlib.h>

int *Aloca_1d(int n)
{
    int *v;                             /* Variavel "ponteiro" do tipo "inteiro" */
    v = (int *)malloc(sizeof(int) * n); /* Usa a variavel 'v' para alocar um espaco na memoria */
    return (v);                         /* retorna 'v' a variavel que esta com "todos os dados" contidos */
}

int **Aloca_2d(int linhas, int colunas) /* Alocacao em duas dimensoes */
{
    int **m;                                         /* Variavel "ponteiro de ponteiro" do tipo "int" */
    int i;                                           /* Variavel aux */
    m = (int **)malloc(sizeof(int *) * linhas);      /* 'Tipo **' aloca espaco para "ponteiros", quantidade de linhas */
    for (i = 0; i < linhas; i++)                     /* Atribuicao de "locais" para as demais posicoes  */
        m[i] = (int *)malloc(sizeof(int) * colunas); /* Alocacao para as outras posicoes */
    return (m);                                      /* Retorna m */
}

void Libera_vetor_1d(int **A) /* APOS UTILIZADO O ESPACO E NECESSARIO QUE ELE SEJA LIBERADO !! */
{
    if ((*A) != NULL)
    {                /* SE A MEMORIA ESTIVER LIMPA, NEM CONTINUA, CASO CONTRARIO */
        free(*A);    /* LIBERA O ENDERECO DE MEMORIA QUE O VETOR APONTA */
        (*A) = NULL; /* ATRIBUI 'NULL' "ALGO INDEFINIDO" */
    }
}

/*                            * A FUNCAO NAO E OTIMIZADA *
    Libera_vetor_1d(int **A)            * ISSO IMPLICADA QUE MESMO SE NAO NECESSARIA *
    free(*A);                    * A MAQUINA VAI RELIAZAR A OPERACAO *
    (*A) = NULL;
*/

void Libera_vetor_2d(int ***A, int linhas) /* MESMO ESQUEMA PARA 2D */
{
    int i;
    if ((*A) != NULL)
    {
        for (i = 0; i < linhas; i++)
        { /* LACO, JA QUE SAO EM DUAS DIMENSOES */
            free((*A)[i]);
            (*A)[i] = NULL;
        }         /* LIBERA O ESPACO DAS OUTRAS */
        free(*A); /* "PRINCIPAL */
        (*A) = NULL;
    }
}

int Carrega_vetor_1d(int **A)
{
    int i, n;

    scanf("%d", &n);

    (*A) = Aloca_1d(n);
    for (i = 0; i < n; i++)
        scanf("%d", &(*A)[i]);

    return n;
}

int Carrega_vetor_2d(int ***A, int *linhas, int *colunas)
{
    int i, j;

    scanf("%d %d", linhas, colunas);

    if (*linhas > 0 && *colunas > 0)
    {

        (*A) = Aloca_2d(*linhas, *colunas);

        for (i = 0; i < *linhas; ++i)
        {
            for (j = 0; j < *colunas; ++j)
            {
                scanf("%d", &(*A)[i][j]);
            }
        }

        return 1;
    }

    return 0;
}

void Imprime_vetor_1d(int *A, int n)
{
    int i;
    if (n > 0)
    {
        printf("%d", A[0]);
        for (i = 1; i < n; i++)
            printf(" %d", A[i]);
        printf("\n");
    }
}

void Imprime_vetor_2d(int **A, int linhas, int colunas)
{
    int i, j;
    if (linhas > 0 && colunas > 0)
    {
        for (i = 0; i < linhas; ++i)
        {
            printf("%d", A[i][0]);

            for (j = 1; j < colunas; ++j)
                printf(" %d", A[i][j]);

            printf("\n");
        }
    }
}

int main()
{
    int *Vetor, **Matriz;
    int n, linhas, colunas;

    n = Carrega_vetor_1d(&Vetor);
    Carrega_vetor_2d(&Matriz, &linhas, &colunas);

    Imprime_vetor_1d(Vetor, n);
    Imprime_vetor_2d(Matriz, linhas, colunas);

    Libera_vetor_1d(&Vetor);
    Libera_vetor_2d(&Matriz, linhas);

    return 0;
}
