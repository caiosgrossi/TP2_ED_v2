#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H
#include "vertice.h"

struct Nodo {
    Vertice* vertice;
    float custo;
    int portaisUsados;
    Nodo* proximo;
};

struct FilaPrioridade {
    Nodo* topo;
    FilaPrioridade();
    ~FilaPrioridade();

    void inserir(Vertice* vertice, float custo, int portaisUsados);
    Nodo* remover();
    bool estaVazia();
    void imprimir();
};

#endif // FILA_PRIORIDADE_H
