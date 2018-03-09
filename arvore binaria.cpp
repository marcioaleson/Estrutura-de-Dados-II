#include <stdio.h>
#include<stdlib.h>
typedef char TDados;
typedef struct Nodo
{
    struct Nodo *esq;
    TDados info;
    struct Nodo *dir;
} TNodo;
typedef TNodo TArvore;
// --------------------------------------------- Cria
TArvore *Cria(TArvore *esq, TDados info, TArvore* dir)
{
    TArvore *p;
    p = (TArvore*) malloc(sizeof(TArvore));
    if (p == NULL)
    {
        printf("ERRO FATAL: Falta de Memória\n");
        getchar();
        exit(0);
    }
    else
    {
        p->info = info;
        p->esq = esq;
        p->dir = dir;
    }
    return p;
}
// --------------------------------------------- Vazia
int Vazia(TArvore *a)
{
    if (a == NULL)
        return(1);
    else
        return(0);
}
// --------------------------------------------- Caminhamento_Pre_Ordem

void Caminhamento_Pre_Ordem(TArvore *a)
{
    if (!Vazia(a))
    {
        printf("%c ", a->info); // mostra raiz
        Caminhamento_Pre_Ordem(a->esq); // mostra sub_esq
        Caminhamento_Pre_Ordem(a->dir); // mostra sub_dir
    }
}
// --------------------------------------------- Caminhamento_In_Fixado
void Caminhamento_In_Fixado(TArvore *a)
{
    if (!Vazia(a))
    {
        Caminhamento_In_Fixado(a->esq); // mostra sub_esq
        printf("%c ", a->info); // mostra raiz
        Caminhamento_In_Fixado(a->dir); // mostra sub_dir
    }
}
// --------------------------------------------- Caminhamento_Pos_Fixado
void Caminhamento_Pos_Fixado(TArvore *a)
{
    if (!Vazia(a))
    {
        Caminhamento_Pos_Fixado(a->esq); // mostra sub_esq
        Caminhamento_Pos_Fixado(a->dir); // mostra sub_dir
        printf("%c ", a->info); // mostra raiz
    }
}
// --------------------------------------------- Destroi
TArvore *Destroi(TArvore *a)
{
    if (!Vazia(a))
    {
        Destroi(a->esq); // libera sub_esq
        Destroi(a->dir); // libera sub_dir
        free(a); // libera raiz
    }
    return(NULL);
}
// --------------------------------------------- Programa Principal
int main(void)
{

    TArvore *a, *a1, *a2, *a3, *a4, *a5, *a6;
    a1 = Cria(NULL, 'd', NULL);
    a2 = Cria(NULL, 'e', NULL);
    a3 = Cria(a1, 'b', a2);
    a4 = Cria(NULL, 'g', NULL);
    a5 = Cria(a4, 'f', NULL);
    a6 = Cria(NULL, 'c', a5);
    a = Cria(a3, 'a', a6);
    printf("Caminhamentos na Árvore\n\n Pré-Ordem: ");
    Caminhamento_Pre_Ordem(a);
    printf("\n In-Fixado: ");
    Caminhamento_In_Fixado(a);
    printf("\nPós-Fixado: ");
    Caminhamento_Pos_Fixado(a);
    return(0);
}
