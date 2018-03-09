#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// ------------------------------------ defines
#define SUCESSO 0
#define FALTA_DE_MEMORIA 1
#define INFO_NAO_EXISTE 2
// ------------------------------------ Definição de Tipos
typedef int TDados;
typedef struct Nodo
{
    struct Nodo *ptesq;
    TDados info;
    struct Nodo *ptdir;
} TNodo;
typedef struct
{
    TNodo *raiz;
} TArvore;
// ------------------------------------ Prototypes
int Inclui(TArvore *a, TDados info);
int Inclui_Recursivo(TNodo **ptnodo, TDados info);
int Exclui(TArvore *a, int info);
int Exclui_Recursivo(TNodo **ptnodo, int info);
TNodo **Procura_Maior(TNodo **ptnodo);
void Cria_Arvore(TArvore *a);
void Pre_Ordem(TArvore a);
void Pre_Ordem_Recursivo (TNodo *ptnodo);
void Em_Ordem(TArvore a);
void Em_Ordem_Recursivo (TNodo *ptnodo);
void Pos_Ordem(TArvore a);
void Pos_Ordem_Recursivo (TNodo *ptnodo);
// ------------------------------------ Programa Principal
int main(void)
{
    TArvore a;
    TDados info;
    char tecla, op;
    system("cls");
    Cria_Arvore(&a);
    do
    {
        printf("[I]ncluir\n");
        printf("[E]xcluir\n");
        printf("[C]aminha\n");
        printf("[F]im\n");
        printf("\nQual a sua Opção? ");
        do
        {
            tecla = getchar();
        }
        while (!strchr("IiEeCcFf", tecla));
        printf("%c\n", tecla);
        switch (tecla)
        {
        case 'I':
        case 'i':
            printf("\nInformação: ");
            scanf("%d", &info);
            Inclui (&a, info);
            break;
        case 'E':
        case 'e':
            printf("\nInformação: ");
            scanf("%d", &info);
            if (Exclui (&a, info) == INFO_NAO_EXISTE)
                printf("ERRO: Informação Inexistente\n");
            break;
        case 'C':
        case 'c':
            printf("[1] Pré-fixado\n");
            printf("[2] In-fixado\n");
            printf("[3] Pós-fixado\n");
            printf("\nQual o Caminhamento? ");
            do
            {
                op = getchar();
            }
            while (!strchr("123", op));
            printf("%c\n", tecla);
            switch (op)
            {
            case '1':
                printf("\nCaminhamento Pré-Ordem: ");
                Pre_Ordem(a);
                printf("\n\n");
                break;
            case '2':
                printf("\nCaminhamento Em-Ordem: ");
                Em_Ordem(a);
                printf("\n\n");
                break;
            case '3':
                printf("\nCaminhamento Pós-Ordem: ");
                Pos_Ordem(a);
                printf("\n\n");
                break;
            }
            break;
        }
    }
    while (!strchr("Ff", tecla));
}
// ------------------------------------ Cria_Arvore
void Cria_Arvore (TArvore *a)
{
    a->raiz = NULL;
}
// ------------------------------------ Inclui
int Inclui(TArvore *a, TDados info)
{
    return(Inclui_Recursivo(&(a->raiz), info));
}
// ------------------------------------ Inclui_Recursivo
int Inclui_Recursivo (TNodo **ptnodo, TDados info)
{
    TNodo *p;
    if (*ptnodo == NULL)
    {
        p = (TNodo *) malloc (sizeof(TNodo));
        if (p == NULL)
            return(FALTA_DE_MEMORIA);
        else
        {
            p->ptesq = NULL;
            p->ptdir = NULL;
            p->info = info;
            *ptnodo = p;
            return SUCESSO;
        }
    }
    else if (info < (*ptnodo)->info)
        return(Inclui_Recursivo(&((*ptnodo)->ptesq), info));
    else
        return(Inclui_Recursivo(&((*ptnodo)->ptdir), info));
}
// ------------------------------------ Exclui
int Exclui(TArvore *a, int info)
{
    return(Exclui_Recursivo( &(a->raiz), info));
}
// ------------------------------------ Exclui_Recursivo
int Exclui_Recursivo (TNodo **ptnodo, TDados info)
{
    TNodo *p, **aux;
    if (*ptnodo == NULL)
        return(INFO_NAO_EXISTE);
    else if ( info < (*ptnodo)->info)
        return(Exclui_Recursivo (&((*ptnodo)->ptesq), info));
    else if (info > (*ptnodo)->info)
        return(Exclui_Recursivo (&((*ptnodo)->ptdir), info));
    else
    {
        if ((*ptnodo)->ptesq == NULL)
            if ((*ptnodo)->ptdir == NULL)
            {
                free ( *ptnodo);
                *ptnodo = NULL;
            }
            else
            {
                p = *ptnodo;
                *ptnodo = (*ptnodo)->ptdir;
                free(p);
            }
        else if ((*ptnodo)->ptdir == NULL)
        {
            p = *ptnodo;
            *ptnodo = (*ptnodo)->ptesq;
            free(p);
        }
        else
        {
            aux = Procura_Maior( &(*ptnodo)->ptesq);
            (*ptnodo)->info = (*aux)->info;
            return(Exclui_Recursivo(aux, (*aux)->info));
        }
        return SUCESSO;
    }
}
// ------------------------------------ Procura_Maior
TNodo **Procura_Maior(TNodo **ptnodo)
{
    if ((*ptnodo)->ptdir == NULL)
        return(ptnodo);
    else
        return(Procura_Maior(&(*ptnodo)->ptdir));
}
// ------------------------------------ Pre_Ordem
void Pre_Ordem(TArvore a)
{
    Pre_Ordem_Recursivo(a.raiz);
}
// ------------------------------------ Pre_Ordem_Recursivo
void Pre_Ordem_Recursivo (TNodo *ptnodo)
{
    if (ptnodo != NULL)
    {
        printf("%d ", ptnodo->info);
        Pre_Ordem_Recursivo(ptnodo->ptesq);
        Pre_Ordem_Recursivo(ptnodo->ptdir);
    }
}
// ------------------------------------ Em_Ordem
void Em_Ordem(TArvore a)
{
    Em_Ordem_Recursivo(a.raiz);
}
// ------------------------------------ Em_Ordem_Recursivo
void Em_Ordem_Recursivo(TNodo *ptnodo)
{
    if (ptnodo != NULL)
    {
        Em_Ordem_Recursivo(ptnodo->ptesq);
        printf("%d ", ptnodo->info);
        Em_Ordem_Recursivo(ptnodo->ptdir);
    }
}
// ------------------------------------ Pos_Ordem
void Pos_Ordem(TArvore a)
{
    Pos_Ordem_Recursivo(a.raiz);
}
// ------------------------------------ Pos_Ordem_Recursivo
void Pos_Ordem_Recursivo (TNodo *ptnodo)
{
    if (ptnodo != NULL)
    {
        Pos_Ordem_Recursivo(ptnodo->ptesq);
        Pos_Ordem_Recursivo(ptnodo->ptdir);
        printf("%d ", ptnodo->info);
    }
}
