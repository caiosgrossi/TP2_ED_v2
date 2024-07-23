#include "grafo.h"

Grafo::Grafo(int n) {
    numeroDeVertices = n; //Inicializando variáveis
    matrizAdjacencia = new float*[n];
    listaAdjacencia = new Aresta*[n];
    listaPortais = new Aresta*[n];
    listaVertices = new Vertice*[n];

    for (int i = 0; i < n; ++i) { 
        matrizAdjacencia[i] = new float[n]; //Inicializando matriz de adjacência com -1
        for (int j = 0; j < n; ++j) {
            matrizAdjacencia[i][j] = -1;
        }
        listaAdjacencia[i] = nullptr; //Inicializando listas de adjacência com nullptr
        listaPortais[i] = nullptr; //Inicializando listas de portais com nullptr
        listaVertices[i] = nullptr; //Inicializando lista de vértices com nullptr
    }
}

Grafo::~Grafo() {
    for (int i = 0; i < numeroDeVertices; ++i) {
        delete[] matrizAdjacencia[i]; //Deletando matriz de adjacência

        Aresta* atual = listaAdjacencia[i]; //Deletando listas de adjacência
        while (atual) { //
            Aresta* temp = atual;
            atual = atual->proximo;
            delete temp;
        }

        atual = listaPortais[i]; //Deletando listas de portais
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

// Adiciona um vértice ao grafo
void Grafo::adicionarVertice(int indice, float x, float y) {

    Vertice *novoVertice = new Vertice{indice, x, y}; //Adicionando vértice à lista de vértices
    listaVertices[indice] = novoVertice;
}

// Adiciona uma aresta ao grafo
void Grafo::adicionarAresta(int u, int v, float peso) {
    matrizAdjacencia[u][v] = peso; //Adicionando aresta à matriz de adjacência

    Vertice* origem = listaVertices[u]; //Adicionando aresta à lista de adjacência
    Vertice* destino = listaVertices[v];

    Aresta* novaAresta = new Aresta{destino, peso, listaAdjacencia[origem->indice]};
    listaAdjacencia[origem->indice] = novaAresta;
}

// Adiciona um portal ao grafo
void Grafo::adicionarPortal(int u, int v) {
    matrizAdjacencia[u][v] = 0; //Adicionando portal à matriz de adjacência

    Vertice* origem = listaVertices[u]; //Adicionando portal à lista de portais
    Vertice* destino = listaVertices[v];

    Aresta* novoPortal = new Aresta{destino, 0.0f, listaPortais[origem->indice]};
    listaPortais[origem->indice] = novoPortal;
}

// Calcula a distância entre dois vértices
float Grafo::calcularDistancia(int vertice1, int vertice2) {
    Vertice *v1 = listaVertices[vertice1];
    Vertice *v2 = listaVertices[vertice2];
    return sqrt(pow(v1->x - v2->x, 2) + pow(v1->y - v2->y, 2)); //Distância euclidiana
}
