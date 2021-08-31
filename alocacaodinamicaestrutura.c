/*
Questão 02 - Alocação Dinâmica (Estrutura)
Descrição
Neste código, deve ser criado um vetor, a ser alocado dinamicamente. Cada elemento do vetor deve ser uma estrutura de nome TItem. Deve ser lido um conjunto de informações com diferentes tipos de dados como segue:

Entrada
int n: o tamanho do vetor a ser alocado. Deve ser verificada a validade do tamanho.

int chave_int

float chave_float

char * chave_char

Saída
Após alocado o vetor, o código irá ler os dados de entrada, inserí-los no final vetor, e finalizar imprimindo o vetor do início para o fim.

Exemplo
Entrada

aluno@ubuntu:~$ ./questao02
2
13540 27119.5098 WCUDL
3300 28993.1250 VWYbqR
Saída esperada

13540 27119.5098 WCUDL 3300 28993.1250 VWYbqR
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *chave_char;
    int chave_int;
    float chave_float;
} TItem;

TItem *Aloca_1d(int n)
{
    return ((n > 0) ? ((TItem *)malloc(n * sizeof(TItem))) : (NULL));
}

// Le um arquivo (ou entrada do teclado) e aloca a string dinamicamente.
char *inputString(FILE *fp, size_t size)
{

    char *str;
    int ch = 0;
    size_t len = 0;
    str = realloc(NULL, sizeof(char) * size); //size is start size
    if (!str)
        return str;

    ch = fgetc(fp);
    do
    {
        if (ch != ' ')
        { // Espaco
            str[len++] = ch;
            if (len == size)
            {
                str = realloc(str, sizeof(char) * (size += 5));
                if (!str)
                    return str;
            }
        }
        ch = fgetc(fp);
    } while (ch != '\n' && ch != ' '); // Espaco ou \n
    str[len++] = '\0';

    return realloc(str, sizeof(char) * (len)); // Por fim, aloca o tamanho correto da string
}

int Carrega_vetor(TItem **A)
{
    int i;
    int n;
    scanf("%d", &n);
    (*A) = Aloca_1d(n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &(*A)[i].chave_int);
        scanf("%f", &(*A)[i].chave_float);
        (*A)[i].chave_char = inputString(stdin, 5);
    }
    return n;
}

void Libera_vetor(TItem **A)
{
    if ((*A) != NULL)
    {
        free(*A);
        (*A) = NULL;
    }
}

void Imprime_vetor(TItem *A, int n)
{
    int i;
    if (n > 0)
    {
        printf("%d", A[0].chave_int);
        printf(" %.4f", A[0].chave_float);
        printf(" %s", A[0].chave_char);

        for (i = 1; i < n; i++)
        {
            printf(" %d", A[i].chave_int);
            printf(" %.4f", A[i].chave_float);
            printf(" %s", A[i].chave_char);
        }
        printf("\n");
    }
}

int main()
{
    TItem *A;
    int n;

    n = Carrega_vetor(&A);
    Imprime_vetor(A, n);
    Libera_vetor(&A);

    return 0;
}
