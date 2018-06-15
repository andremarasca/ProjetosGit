#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

typedef struct pilha Pilha;
typedef struct nodo Nodo;

struct pilha
{
    Nodo *primeiro;
    void (*empilha) (Pilha *p, void *elemento);
    int (*desempilha) (Pilha *p);
    void *(*topo) (Pilha *p);
    int (*vazia) (Pilha *p);
    void (*freeelemento)(void *elemento);
};

Pilha *NewPilha(void (*freeelemento)(void *elemento));
void DestroiPilha(Pilha *p);

#endif // PILHA_H_INCLUDED
