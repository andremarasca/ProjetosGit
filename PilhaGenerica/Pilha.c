#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

struct nodo
{
    void *elemento;
    Nodo *proximo;
};

//Cabecalhos estaticos das funcoes da pilha
// static pra evitar que sejam chamados
// sem ser por "orientacao objeto"

static void empilha (Pilha *p, void *elemento);
static int desempilha (Pilha *p);
static void *topo (Pilha *p);
static int vazia(Pilha *p);

// A funcao abaixo coloca um novo elemento
// no inicio da pilha, pra isso o novo
// elemento deve apontar pro inicio da pilha
// e o topo da pilha eh atualizado para esse
// novo elemento
static void empilha (Pilha *p, void *elemento)
{
    Nodo *novo = (Nodo *) malloc(sizeof(Nodo));
    novo->elemento = elemento;
    novo->proximo = p->primeiro;
    p->primeiro = novo;
}

// O desempilha verifica se a pilha esta vazia.
// Se estiver vazia nao tem mais como desempilhar.
// Se nao estiver vazia, salva o topo atual da pilha,
// muda a topo da pilha para o proximo Nodo,
// desaloca o elemento do nodo que vai ser desempilhado,
// e por fim desaloca o ponteiro para o nodo
// que vai ser desempilhado
static int desempilha (Pilha *p)
{
    if(vazia(p))
        return 0;
    Nodo *q = p->primeiro;
    p->freeelemento(q->elemento);
    p->primeiro = q->proximo;
    free(q);
    return 1;
}

// essa funcao verifica se a pilha esta vazia,
// se estiver vazia, entao retorna NULL,
// caso contrario, retorna o ponteiro para
// o elemento do nodo do topo da pilha.
static void *topo (Pilha *p)
{
    if(vazia(p))
        return NULL;
    return p->primeiro->elemento;
}

// a funcao abaixo retorna 1 se a pilha esta vazia
// caso contrario retorna 0
static int vazia(Pilha *p)
{
    if(p->primeiro == NULL)
        return 1;
    return 0;
}

// A funcao abaixo recebe a funcao que limpa elemento
// como calback, aloca uma pilha nova, ajusta os ponteiros
// de funcao e retorna o ponteiro para a pilha alocada
Pilha *NewPilha(void (*freeelemento)(void *elemento))
{
    Pilha *p = (Pilha *) malloc(sizeof(Pilha));
    p->primeiro = NULL;
    p->empilha = empilha;
    p->desempilha = desempilha;
    p->topo = topo;
    p->vazia = vazia;
    p->freeelemento = freeelemento;
    return p;
}

// Desaloca o objeto Pilha
// enquanto nao estiver vazia
// vai desempilhando
void DestroiPilha(Pilha *p)
{
    while(!p->vazia(p))
        p->desempilha(p);
    free(p);
}
