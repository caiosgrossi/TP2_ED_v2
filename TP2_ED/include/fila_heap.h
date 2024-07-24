#ifndef FILA_HEAP_H
#define FILA_HEAP_H
#include "vertice.h"

struct NodoHeap {
    Vertice* vertice;
    float custo;
    int portaisUsados;
};

struct Heap {
    NodoHeap** vetorHeap;
    int capacidade;
    int tamanho;

    Heap(int capacidade);
    ~Heap();

    void subir(int indice);
    void descer(int indice);
    void trocar(int i, int j);

    void inserir(Vertice* vertice, float custo, int portaisUsados);
    NodoHeap* remover();
    bool estaVazia();
};

#endif // FILA_HEAP_H
