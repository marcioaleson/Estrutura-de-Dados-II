#include <stdio.h>
#include<stdlib.h>
#define ESC 27
typedef char TDados;
typedef struct Nodo {
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
// --------------------------------------------- Caminhamento_In_Fixado
void Caminhamento_In_Fixado(TArvore *a)
{
if (!Vazia(a))
{
Caminhamento_In_Fixado(a->esq);
printf("\nEndereço: %p - Info: %c", a, a->info);
Caminhamento_In_Fixado(a->dir);
}
}
// --------------------------------------------- Destroi
TArvore *Destroi(TArvore *a)
{
if (!Vazia(a))
{
Destroi(a->esq);
Destroi(a->dir);
free(a);
}
return(NULL);
}
// --------------------------------------------- Busca
TArvore *Busca(TArvore *raiz, TDados chave)
{
TArvore *a1;
if (raiz == NULL)
return(NULL);
else
if (raiz->info == chave) // busca na raiz
return(raiz);
else
{
a1 = Busca(raiz->esq,chave); // busca na sub-árvore esquerda
if (a1 == NULL)
a1 = Busca(raiz->dir,chave); // busca na sub-árvore direita
return(a1);
}
}
// --------------------------------------------- Programa Principal
int main(void)
{
TArvore *a,*a1,*a2,*a3,*a4,*a5,*a6,*arv;
TDados info;
system("cls");
a1 = Cria(NULL,'a',NULL);
a2 = Cria(NULL,'c',NULL);
a3 = Cria(a1,'b',a2);
a4 = Cria(NULL,'e',NULL);
a5 = Cria(NULL,'g',NULL);
a6 = Cria(a4,'f',a5);
a = Cria(a3,'d',a6);
printf("\nCaminhamento In-Fixado: ");
Caminhamento_In_Fixado(a);
printf("\nESC - Abandona");
do {
printf("\nInfo: ");
do {
info = getchar();
} while (!(info >= 'a' && info <= 'z') && info != ESC);
if (info != ESC)
{
arv = Busca(a,info);
printf("\nEndereço do Nodo [%c]: %p", info, arv);
}
} while (info != ESC);
return(0);
}