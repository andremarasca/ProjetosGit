#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

struct nodo
{
    void *elemento;
    Nodo *proximo;
};

//Cabecalhos estaticos das funcoes da fila
// static pra evitar que sejam chamados
// sem ser por "orientacao objeto"

static void enfila (Fila *p, void *elemento);
static int desenfila (Fila *p);
static void *topo (Fila *p);
static int vazia(Fila *p);

// A funcao enfila abaixo recebe um elemento
// coloca num bloco novo, manda esse bloco
// apontar pro vazio, pois ele vai ser o ultimo.
// Em seguida, se o novo nodo eh o primeiro
// ele se torna o primeiro e ultimo ao mesmo tempo
// caso contrario, o proximo do atual ultimo
// aponta pra ele e ele se torna o ultimo
static void enfila (Fila *f, void *elemento)
{
    Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
    novo->elemento = elemento;
    novo->proximo = NULL;
    if(f->primeiro == NULL)
        f->primeiro = novo;
    else
        f->ultimo->proximo = novo;
    f->ultimo = novo;
}

// O desenfila recebe a fila, retorna 0
// se nao tem mais nada pra desenfilar
// e retorna 1 se desenfilou com sucesso.
// Salva o ponteiro do primeiro pois sera
// removido. Se for o unico elemento da fila
// o primeiro e o ultimo se tornam NULL.
// caso contraio, o segundo vira o primeiro
static int desenfila (Fila *f)
{
    if(f->primeiro == NULL)
        return 0;
    Nodo *tmp = f->primeiro;
    if(f->primeiro == f->ultimo)
        f->primeiro = f->ultimo = NULL;
    else
        f->primeiro = tmp->proximo;
    free(tmp);
    return 1;
}

// essa funcao verifica se a fila esta vazia,
// se estiver vazia, entao retorna NULL,
// caso contrario, retorna o ponteiro para
// o elemento do nodo do topo da fila.
static void *topo (Fila *f)
{
    if(vazia(f))
        return NULL;
    return f->primeiro->elemento;
}

// a funcao abaixo retorna 1 se a fila esta vazia
// caso contrario retorna 0
static int vazia(Fila *f)
{
    if(f->primeiro == NULL)
        return 1;
    return 0;
}

// A funcao abaixo recebe a funcao que limpa elemento
// como calback, aloca uma fila nova, ajusta os ponteiros
// de funcao e retorna o ponteiro para a fila alocada
Fila *NewFila(void (*freeelemento)(void *elemento))
{
    Fila *f = (Fila *) malloc(sizeof(Fila));
    f->primeiro=NULL;
    f->ultimo=NULL;
    f->enfila = enfila;
    f->desenfila = desenfila;
    f->topo = topo;
    f->vazia = vazia;
    f->freeelemento = freeelemento;
    return f;
}

// Desaloca o objeto Fila
// enquanto nao estiver vazia
// vai desenfilando
void DestroiFila(Fila *f)
{
    while(!f->vazia(f))
        f->desenfila(f);
    free(f);
}
