#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

typedef struct item Item;

// Estrutura com o item desejado
struct item {
    int x, y;
};

// Funcao necessaria para dar free nos itens alocados
// Note que a estrutura poderia ter conter uma matriz dinamica
// Em que a desalocacao eh mais complicada que apenas chamar free
void freePilhaItem(void *item)
{
    Item *x = (Item *) item;
    free(x);
}

// Funcao necessaria para alocar o elemento a ser empilhado
// Note que isso torna a pilha generica, uma vez que a alocacao
// eh dinamica, dessa forma, qualquer tipo de dado pode ser usado
// dentro da estrutura Item
Item *NewItem(int x, int y)
{
    Item *item = (Item *) malloc(sizeof(Item));
    item->x = x;
    item->y = y;
    return item;
}

// Para pegar um item deve-se chamar o topo
// Ao fazer isso deve-se atribuir o retorno
// para um ponteiro de Item, pra evitar ser
// um processo tedioso eu fiz uma funcao
Item *topoPilhaItem(Pilha *p)
{
    Item *item = (Item *) p->topo(p);
    return item;
}

// Funcao principal contendo um exemplo de uso da pilha
// Todas as funcoes foram utilizada eh um exemplo completo
int main(void)
{
    // A pilha foi implementada com ponteiros de funcao
    // em uma struct, sendo assim, todas as funcoes
    // necessarias para seu funcionamento estao encapsuladas
    Pilha *p = NewPilha(freePilhaItem);
    int i;
    for(i = 0; i < 100; i++)
    {
        // ao inserir um item na pilha eh necessario
        // fazer a tipagem para ponteiro de void
        p->empilha(p, (void *) NewItem(i, 100 - i));
    }
    FILE *arq = fopen("Saida.txt", "w+");
    while(!p->vazia(p))
    {
        Item *item = topoPilhaItem(p);
        fprintf(arq, "%d %d\n", item->x, item->y);
        p->desempilha(p);
    }
    fclose(arq);
    DestroiPilha(p);
    return 0;
}
