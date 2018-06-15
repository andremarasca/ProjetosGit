#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int elemento;
    struct nodo *proximo;
} Nodo;

typedef struct fila
{
    Nodo *primeiro;
    Nodo *ultimo;
} Fila;

void inicializa (Fila *f)
{
    f->primeiro=NULL;
    f->ultimo=NULL;
}

void enfila (Fila *f, int elemento)
{
    Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
    novo->elemento = elemento;
    novo->proximo = NULL;
    if(f->primeiro == NULL)
    {
        f->primeiro = novo;
        f->ultimo = novo;
    }
    else
    {
        f->ultimo->proximo = novo;
        f->ultimo = novo;
    }
}

int desenfila (Fila *f)
{
    if(f->primeiro == NULL) return -1;
    Nodo *tmp = f->primeiro;
    int x = tmp->elemento;
    if(f->primeiro == f->ultimo) f->primeiro = f->ultimo = NULL;
    else
    {
        f->primeiro = tmp->proximo;
    }
    free(tmp);
    return x;
}

int filavazia (Fila *f)
{
    if(f->primeiro == NULL) return 1;
    return 0;
}

int main (void)
{
    Fila fila;
    inicializa (&fila);
    int i;
    for (i = 0; i < 100; i++) enfila (&fila, i);
    while (!filavazia (&fila)) printf("%d\n", desenfila (&fila));
    return 0;
}
