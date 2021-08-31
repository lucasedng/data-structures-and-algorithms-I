/*
Questão 03 - E/S em arquivos
Descrição
Neste código, deve ser criado um vetor, a ser alocado dinamicamente. Cada elemento do vetor deve ser uma estrutura de nome TItem.

Neste código, devem ser implementados:

1) a função que retorna um vetor de tamanho n, a ser alocado dinamicamente. Inclusive o cabeçalho dela, não somente o corpo.

Deve ser lido um conjunto de informações com diferentes tipos de dados como segue:

Entrada
int n: o tamanho do vetor a ser alocado. Deve ser verificada a validade do tamanho.

int chave_int

float chave_float

char * chave_char

Saída
Após alocado o vetor, o código irá ler os dados de entrada, inserí-los no final vetor, gravar o conteúdo do vetor em um arquivo, ler esse arquivo em outro vetor, e finalizar imprimindo o vetor do início para o fim. Limite o numero de casas decimais para 4, com o %.4f, quando for tratar valores de ponto flutuante

Exemplo
Entrada

aluno@ubuntu:~$ ./questao03
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
    int chave_int;
    float chave_float;
    char *chave_char;
} TItem;

TItem *Aloca_1d(int n)
{
    TItem *aloc;
    if (n > 0)
    {
        aloc = (TItem *)malloc(sizeof(TItem) * n);
        return (aloc);
    }
    return (NULL);
}

// Le um arquivo (ou entrada do teclado: stdin) e aloca a string dinamicamente.
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
    int i, n;

    scanf("%d", &n);

    (*A) = Aloca_1d(n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &(*A)[i].chave_int);
        scanf("%f", &(*A)[i].chave_float);
        (*A)[i].chave_char = inputString(stdin, 21);
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

void Imprimir_vetor(TItem *A, int n)
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

int Importa_vetor(TItem **A, FILE *arq_in)
{
    int i;
    int n;
    fscanf(arq_in, "%d", &n);
    (*A) = Aloca_1d(n);
    for (i = 0; i < n; i++)
    {
        fscanf(arq_in, "%d", &(*A)[i].chave_int);
        fscanf(arq_in, "%f", &(*A)[i].chave_float);
        (*A)[i].chave_char = inputString(arq_in, 21);
    }
    return (n);
}

void Exporta_vetor(TItem *A, int n, FILE *arq_out)
{
    int i;
    if (n > 0)
    {
        fprintf(arq_out, "%d\n", n);
        fprintf(arq_out, "%d", A[0].chave_int);
        fprintf(arq_out, " %.4f", A[0].chave_float);
        fprintf(arq_out, " %s", A[0].chave_char);
        for (i = 1; i < n; i++)
        {
            fprintf(arq_out, " %d", A[i].chave_int);
            fprintf(arq_out, " %.4f", A[i].chave_float);
            fprintf(arq_out, " %s", A[i].chave_char);
        }
        fprintf(arq_out, "\n");
    }
}

int main()
{
    TItem *A;
    int n;

    FILE *arq_out = fopen("/dev/shm/output.txt", "w");
    n = Carrega_vetor(&A); // Carrega vetor na struct

    // Exportando os dados para o arquivo de saida
    // O arquivo de saida deve conter o numero de elementos do vetor na primeira linha,
    // e os dados da struct devem ser dispostos na segunda linha, separados por espacos.
    // Limite o numero de casas decimais para 4, com o %.4f, quando for tratar valores de ponto flutuante
    Exporta_vetor(A, n, arq_out);
    Libera_vetor(&A);
    fclose(arq_out);

    FILE *arq_in = fopen("/dev/shm/output.txt", "r");
    n = Importa_vetor(&A, arq_in); // Importa vetor do arquivo de saida, da mesma forma que o Carrega_vetor, mas agora a partir de um arquivo.
    Imprimir_vetor(A, n);          // imprimir vetor
    Libera_vetor(&A);
    fclose(arq_in);

    return 0;
}
