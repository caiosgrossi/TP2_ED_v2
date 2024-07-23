#ifndef GRAFO_H
#define GRAFO_H

#include <cmath>
#include <iostream>
#include "vertice.h"

struct Aresta {
    Vertice* destino;
    float peso;
    Aresta* proximo;
};

struct Grafo { 
    int numeroDeVertices;
    float** matrizAdjacencia;
    Aresta** listaAdjacencia;
    Aresta** listaPortais;
    Vertice** listaVertices;

    Grafo(int n);
    ~Grafo();

    void adicionarVertice(int indice, float x, float y);
    void adicionarAresta(int u, int v, float peso);
    void adicionarPortal(int u, int v);
    float calcularDistancia(int vertice1, int vertice2);
    void imprimir();
};

#endif // GRAFO_H
