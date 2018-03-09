#include <stdio.h>
#include <stdlib.h>
#define TRUE !0
#define FALSE 0
typedef int TDados;
typedef struct nodo {
TDados chave;
struct nodo *esq,*dir;
int bal;
}*TNodo;
// ------------------------------------ Procura_AVL
int Procura_AVL(int x, TNodo *p)
{
TNodo pDeTNodo;
pDeTNodo = (*p);
if (!pDeTNodo)
return(FALSE);
else
if (x<pDeTNodo->chave)
return(Procura_AVL(x, &pDeTNodo->esq));
else
if (x>pDeTNodo->chave)
return(Procura_AVL(x, &pDeTNodo->dir));
else
return(TRUE);
}
// ------------------------------------ Insere_AVL
int Insere_AVL(int x, TNodo *t, int *h)
{
TNodo p, q, pDeTNodo;
pDeTNodo = (*t);
if (!pDeTNodo)
{
pDeTNodo = (TNodo) malloc(sizeof (struct nodo));
if (pDeTNodo == NULL)
abort();
*t = pDeTNodo;
*h = TRUE;
pDeTNodo->chave = x;
pDeTNodo->esq = NULL;
pDeTNodo->dir = NULL;
pDeTNodo->bal = 0;
return(TRUE);
}
else
if (x<pDeTNodo->chave)
{
if (!Insere_AVL(x, &pDeTNodo->esq, h))
return(FALSE);
if (*h)
switch(pDeTNodo->bal)
{
case 1: pDeTNodo->bal = 0;
*h = FALSE;
break;
case 0: pDeTNodo->bal = (-1);
break;
case -1: p = pDeTNodo->esq;
if (p->bal == (-1))
{ // RotaÁ„o Simples
pDeTNodo->esq = p->dir;
p->dir = pDeTNodo;
pDeTNodo->bal = 0;
pDeTNodo = p;
*t = pDeTNodo;
}
else
{ // RotaÁ„o Dupla
q = p->dir;
p->dir = q->esq;
q->esq = p;
pDeTNodo->esq = q->dir;
q->dir = pDeTNodo;
pDeTNodo->bal = (q->bal == (-1)) ? 1 : 0;
p->bal = (q->bal == 1) ? (-1) : 0;
pDeTNodo = q;
*t = pDeTNodo;
}
pDeTNodo->bal = 0;
*h = FALSE;
break;
}
return(TRUE);
}
else
if (x>pDeTNodo->chave)
{
if (!Insere_AVL(x, &pDeTNodo->dir, h))
return(FALSE);
if (*h)
switch(pDeTNodo->bal)
{
case -1: pDeTNodo->bal = 0;
*h = FALSE;
break;
case 0: pDeTNodo->bal = 1;
break;
case 1: p=pDeTNodo->dir;
if (p->bal == 1)
{ // RotaÁ„o Simples
pDeTNodo->dir = p->esq;
p->esq = pDeTNodo;
pDeTNodo->bal = 0;
pDeTNodo = p;
*t = pDeTNodo;
}
else
{ // RotaÁ„o Dupla
q = p->esq;
p->esq = q->dir;
q->dir = p;
pDeTNodo->dir = q->esq;
q->esq = pDeTNodo;
pDeTNodo->bal = (q->bal == 1) ? (-1) : 0;
p->bal = (q->bal == (-1)) ? 1 : 0;
pDeTNodo = q;
*t = pDeTNodo;
}
pDeTNodo->bal = 0;
*h = FALSE;
break;
}
return(TRUE);
}
else
{
*h = FALSE;
return(FALSE);
}
}
// ------------------------------------ Exibe_AVL
void Exibe_AVL(TNodo pt,int indent)
{
int i;
if (pt)
{
Exibe_AVL(pt->dir, indent+1);
for (i = 0;i < indent;i++)
printf(" ");
printf("%d (%d)\n",pt->chave, pt->bal);
Exibe_AVL(pt->esq, indent+1);
}
}
// ------------------------------------ main
int main(void)
{
TNodo raiz;
int chave, dh;
system("cls");
printf("¡rvore AVL (0 - Sair)\n\n");
raiz = NULL;
do {
printf("Chave: ");
scanf("%d", &chave);
if (chave != 0)
{
if (!Insere_AVL(chave, &raiz, &dh))
printf("ERRO: Chave Repetida\n");
if (!Procura_AVL(chave, &raiz))
printf("ERRO: Chave Perdida\n");
}
} while (chave != 0);
printf("\n¡RVORE AVL\n\n");
Exibe_AVL(raiz,0);
printf("\n");
system("pause");
}