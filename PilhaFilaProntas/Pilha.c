#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int elemento;
    struct nodo *proximo;
}Nodo;

typedef struct pilha
{
    Nodo *primeiro;
}Pilha;

void inicializa(Pilha *p)
{
    p->primeiro = NULL;
}

void empilha (Pilha *p,int elemento)
{
    Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
    novo->elemento = elemento;
    novo->proximo = p->primeiro;
    p->primeiro = novo;
}

int desempilha (Pilha *p)
{
    Nodo *q = p->primeiro;
    int x = q->elemento;
    p->primeiro = q->proximo;
    free(q);
    return x;
}

int pilhavazia(Pilha *p)
{
    if(p->primeiro == NULL) return 1;
    return 0;
}

int main (void)
{
    Pilha pilha;
    inicializa(&pilha);
    int i;
    for(i=0;i<100;i++) empilha(&pilha,i);
    while(!pilhavazia(&pilha)) printf("%d\n",desempilha(&pilha));
    return 0;
}
