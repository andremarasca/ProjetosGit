#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

typedef struct fila Fila;
typedef struct nodo Nodo;

struct fila
{
    Nodo *primeiro;
    Nodo *ultimo;
    void (*enfila) (Fila *p, void *elemento);
    int (*desenfila) (Fila *p);
    void *(*topo) (Fila *p);
    int (*vazia) (Fila *p);
    void (*freeelemento)(void *elemento);
};

Fila *NewFila(void (*freeelemento)(void *elemento));
void DestroiFila(Fila *p);

#endif // PILHA_H_INCLUDED
