#include "dijkstra.h"

// Função que executa o algoritmo de Dijkstra utilizando a lista de adjacência do grafo
bool executarDijkstraLista(Grafo& grafo, float energiaMaxima, int portaisMaximos) {
    const int INF = 0x3f3f3f3f; // Define custo infinito
    const int n = grafo.numeroDeVertices;

    // Inicializa o array de distâncias
    float* distancias = new float[n];
    for (int i = 0; i < n; ++i) {
        distancias[i] = INF;
    }
    distancias[0] = 0; // Distância para o vértice inicial é 0

    FilaPrioridade fila;
    fila.inserir(grafo.listaVertices[0], 0, 0); // Insere o vértice inicial na fila


    while (!fila.estaVazia()) {
        Nodo* atual = fila.remover();
        Vertice* vertice = atual->vertice;
        float custoAtual = atual->custo;
        int portaisUsadosAtual = atual->portaisUsados;
        delete atual;

        // Verifica se o vértice atual é o destino
        if (vertice->indice == n - 1) {
            delete[] distancias;
            return custoAtual <= energiaMaxima && portaisUsadosAtual <= portaisMaximos;
        }

        // Verifica se o vértice já foi processado
        if (distancias[vertice->indice] < custoAtual) continue;

        // Processa arestas normais
        Aresta* aresta = grafo.listaAdjacencia[vertice->indice];
        while (aresta) {
            Vertice* vizinho = aresta->destino;
            float custoTotal = custoAtual + aresta->peso;
            if (custoTotal < distancias[vizinho->indice]) {
                distancias[vizinho->indice] = custoTotal;
                fila.inserir(vizinho, custoTotal, portaisUsadosAtual);
            }
            aresta = aresta->proximo;
        }

        // Processa portais
        Aresta* portal = grafo.listaPortais[vertice->indice];
        while (portal) {
            Vertice* vizinho = portal->destino;
            if (portaisUsadosAtual + 1 <= portaisMaximos || vizinho->indice == n - 1) {
                if (distancias[vertice->indice] < distancias[vizinho->indice]) {
                    distancias[vizinho->indice] = distancias[vertice->indice];
                    fila.inserir(vizinho, distancias[vizinho->indice], portaisUsadosAtual + 1);
                }
            }
            portal = portal->proximo;
        }
    }

    delete[] distancias;
    return false;
}

// Função que executa o algoritmo de Dijkstra utilizando a matriz de adjacência do grafo
bool executarDijkstraMatriz(Grafo& grafo, float energiaMaxima, int portaisMaximos) {
    const int INF = 0x3f3f3f3f; // Define custo infinito
    const int n = grafo.numeroDeVertices;

    // Inicializa o array de distâncias
    float* distancias = new float[n];
    for (int i = 0; i < n; ++i) {
        distancias[i] = INF;
    }
    distancias[0] = 0; // Distância para o vértice inicial é 0

    FilaPrioridade fila;
    fila.inserir(grafo.listaVertices[0], 0, 0); // Insere o vértice inicial na fila


    while (!fila.estaVazia()) {
        Nodo* atual = fila.remover();
        Vertice* vertice = atual->vertice;
        float custoAtual = atual->custo;
        int portaisUsadosAtual = atual->portaisUsados;
        delete atual;

        // Verifica se o vértice atual é o destino
        if (vertice->indice == n - 1) {
            delete[] distancias;
            return custoAtual <= energiaMaxima && portaisUsadosAtual <= portaisMaximos;
        }

        // Verifica se o vértice já foi processado
        if (distancias[vertice->indice] < custoAtual) continue;

        // Processa todas as arestas
        for (int j = 0; j < n; j++) {
            if (j == vertice->indice) continue; // Ignora o próprio vértice
            if (grafo.matrizAdjacencia[vertice->indice][j] != -1) { // Verifica se existe uma aresta
                Vertice* vizinho = grafo.listaVertices[j]; // Obtém o vértice vizinho

                if (grafo.matrizAdjacencia[vertice->indice][j] != 0) { // Verifica se a aresta não é um portal
                    float custoTotal = custoAtual + grafo.matrizAdjacencia[vertice->indice][j];
                    if (custoTotal < distancias[j]) {
                        distancias[j] = custoTotal;
                        fila.inserir(vizinho, custoTotal, portaisUsadosAtual);
                    }
                } else { // Se a aresta é um portal
                    if (portaisUsadosAtual + 1 <= portaisMaximos || j == n - 1) {
                        if (distancias[vertice->indice] < distancias[j]) {
                            distancias[j] = distancias[vertice->indice];
                            fila.inserir(vizinho, distancias[j], portaisUsadosAtual + 1);
                        }
                    }
                }
            }
        }
    }

    delete[] distancias;
    return false;
}


// Função que executa o algoritmo de Dijkstra utilizando a lista de adjacência do grafo
bool executarDijkstraListaHeap(Grafo& grafo, float energiaMaxima, int portaisMaximos) {
    const int INF = 0x3f3f3f3f; // Define custo infinito
    const int n = grafo.numeroDeVertices;

    // Inicializa o array de distâncias
    float* distancias = new float[n];
    for (int i = 0; i < n; ++i) {
        distancias[i] = INF;
    }
    distancias[0] = 0; // Distância para o vértice inicial é 0

    Heap fila_heap(n);
    fila_heap.inserir(grafo.listaVertices[0], 0, 0); // Insere o vértice inicial na fila


    while (!fila_heap.estaVazia()) {
        NodoHeap* atual = fila_heap.remover();
        Vertice* vertice = atual->vertice;
        float custoAtual = atual->custo;
        int portaisUsadosAtual = atual->portaisUsados;
        delete atual;

        // Verifica se o vértice atual é o destino
        if (vertice->indice == n - 1) {
            delete[] distancias;
            return custoAtual <= energiaMaxima && portaisUsadosAtual <= portaisMaximos;
        }

        // Verifica se o vértice já foi processado
        if (distancias[vertice->indice] < custoAtual) continue;

        // Processa arestas normais
        Aresta* aresta = grafo.listaAdjacencia[vertice->indice];
        while (aresta) {
            Vertice* vizinho = aresta->destino;
            float custoTotal = custoAtual + aresta->peso;
            if (custoTotal < distancias[vizinho->indice]) {
                distancias[vizinho->indice] = custoTotal;
                fila_heap.inserir(vizinho, custoTotal, portaisUsadosAtual);
            }
            aresta = aresta->proximo;
        }

        // Processa portais
        Aresta* portal = grafo.listaPortais[vertice->indice];
        while (portal) {
            Vertice* vizinho = portal->destino;
            if (portaisUsadosAtual + 1 <= portaisMaximos || vizinho->indice == n - 1) {
                if (distancias[vertice->indice] < distancias[vizinho->indice]) {
                    distancias[vizinho->indice] = distancias[vertice->indice];
                    fila_heap.inserir(vizinho, distancias[vizinho->indice], portaisUsadosAtual + 1);
                }
            }
            portal = portal->proximo;
        }
    }

    delete[] distancias;
    return false;
}

// Função que executa o algoritmo de Dijkstra utilizando a matriz de adjacência do grafo
bool executarDijkstraMatrizHeap(Grafo& grafo, float energiaMaxima, int portaisMaximos) {
    const int INF = 0x3f3f3f3f; // Define custo infinito
    const int n = grafo.numeroDeVertices;

    // Inicializa o array de distâncias
    float* distancias = new float[n];
    for (int i = 0; i < n; ++i) {
        distancias[i] = INF;
    }
    distancias[0] = 0; // Distância para o vértice inicial é 0

    Heap fila_heap(n);
    fila_heap.inserir(grafo.listaVertices[0], 0, 0); // Insere o vértice inicial na fila


    while (!fila_heap.estaVazia()) {
        NodoHeap* atual = fila_heap.remover();
        Vertice* vertice = atual->vertice;
        float custoAtual = atual->custo;
        int portaisUsadosAtual = atual->portaisUsados;
        delete atual;

        // Verifica se o vértice atual é o destino
        if (vertice->indice == n - 1) {
            delete[] distancias;
            return custoAtual <= energiaMaxima && portaisUsadosAtual <= portaisMaximos;
        }

        // Verifica se o vértice já foi processado
        if (distancias[vertice->indice] < custoAtual) continue;

        // Processa todas as arestas
        for (int j = 0; j < n; j++) {
            if (j == vertice->indice) continue; // Ignora o próprio vértice
            if (grafo.matrizAdjacencia[vertice->indice][j] != -1) { // Verifica se existe uma aresta
                Vertice* vizinho = grafo.listaVertices[j]; // Obtém o vértice vizinho

                if (grafo.matrizAdjacencia[vertice->indice][j] != 0) { // Verifica se a aresta não é um portal
                    float custoTotal = custoAtual + grafo.matrizAdjacencia[vertice->indice][j];
                    if (custoTotal < distancias[j]) {
                        distancias[j] = custoTotal;
                        fila_heap.inserir(vizinho, custoTotal, portaisUsadosAtual);
                    }
                } else { // Se a aresta é um portal
                    if (portaisUsadosAtual + 1 <= portaisMaximos || j == n - 1) {
                        if (distancias[vertice->indice] < distancias[j]) {
                            distancias[j] = distancias[vertice->indice];
                            fila_heap.inserir(vizinho, distancias[j], portaisUsadosAtual + 1);
                        }
                    }
                }
            }
        }
    }

    delete[] distancias;
    return false;
}
