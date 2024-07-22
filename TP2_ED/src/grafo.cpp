#include "grafo.h"

Grafo::Grafo(int n) {
    numeroDeVertices = n;
    listaAdjacencia = new Aresta*[n];
    listaPortais = new Aresta*[n];
    listaVertices = new Vertice*[n];

    for (int i = 0; i < n; ++i) {
        listaAdjacencia[i] = nullptr;
        listaPortais[i] = nullptr;
        listaVertices[i] = nullptr;
    }
}

Grafo::~Grafo() {
    for (int i = 0; i < numeroDeVertices; ++i) {
        Aresta* atual = listaAdjacencia[i];
        while (atual) {
            Aresta* temp = atual;
            atual = atual->proximo;
            delete temp;
        }
        atual = listaPortais[i];
        while (atual) {
            Aresta* temp = atual;
            atual = atual->proximo;
            delete temp;
        }
    }
    delete[] listaVertices;
    delete[] listaAdjacencia;
    delete[] listaPortais;
}

void Grafo::adicionarVertice(int indice, float x, float y) {
    Vertice *novoVertice = new Vertice{indice, x, y};
    listaVertices[indice] = novoVertice;
}

void Grafo::adicionarAresta(int u, int v, float peso) {
    Vertice* origem = listaVertices[u];
    Vertice* destino = listaVertices[v];

    Aresta* novaAresta = new Aresta{destino, peso, listaAdjacencia[origem->indice]};
    listaAdjacencia[origem->indice] = novaAresta;
}

void Grafo::adicionarPortal(int u, int v) {
    Vertice* origem = listaVertices[u];
    Vertice* destino = listaVertices[v];

    Aresta* novoPortal = new Aresta{destino, 0.0f, listaPortais[origem->indice]};
    listaPortais[origem->indice] = novoPortal;
}

float Grafo::calcularDistancia(int vertice1, int vertice2) {
    Vertice *v1 = listaVertices[vertice1];
    Vertice *v2 = listaVertices[vertice2];
    return sqrt(pow(v1->x - v2->x, 2) + pow(v1->y - v2->y, 2));
}

void Grafo::imprimir() {
    for (int i = 0; i < numeroDeVertices; ++i) {
        std::cout << "Clareira " << i << ":";
        Aresta* atual = listaAdjacencia[i];
        while (atual) {
            std::cout << " -> " << atual->destino->indice << " (peso: " << atual->peso << ")";
            atual = atual->proximo;
        }
        std::cout << std::endl;
    }
}
