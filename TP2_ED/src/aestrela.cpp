#include "aestrela.h"


bool executarAestrelaLista(Grafo& grafo, float energiaMaxima, int portaisMaximos) {
    const int INF = 0x3f3f3f3f; //Determina custo infinito
    const int n = grafo.numeroDeVertices;

    // Inicializa estruturas de dados
    float* distancias = new float[n];
    for (int i = 0; i < n; ++i) {
        distancias[i] = INF;
    }
    distancias[0] = 0;

    FilaPrioridade fila;
    fila.inserir(grafo.listaVertices[0], 0, 0); // Começa no vértice 0, custo 0, portais usados 0


    while (!fila.estaVazia()) {
        Nodo* atual = fila.remover();
        Vertice* vertice = atual->vertice;
        float custoAtual = distancias[vertice->indice];
        int portaisUsadosAtual = atual->portaisUsados;
        delete atual;

        // Verifica se o nó removido é o destino
        if (vertice->indice == n - 1) {
            // Chegou ao destino
            delete[] distancias;
            return custoAtual <= energiaMaxima && portaisUsadosAtual <= portaisMaximos;
        }

        //Verifica se o nó já foi processado
        if(distancias[vertice->indice] < custoAtual) continue;

        // Processa as arestas normais
        Aresta* aresta = grafo.listaAdjacencia[vertice->indice];
        while (aresta) {
            Vertice* vizinho = aresta->destino;
            float custoTotal = custoAtual + aresta->peso;
            if (custoTotal < distancias[vizinho->indice]) {
                distancias[vizinho->indice] = custoTotal;
                float prioridade = custoTotal + grafo.calcularDistancia(vizinho->indice, n-1);
                fila.inserir(vizinho, prioridade, portaisUsadosAtual);
            }
            aresta = aresta->proximo;
        }

        // Processa os portais
        Aresta* portal = grafo.listaPortais[vertice->indice];
        while (portal) {
            Vertice* vizinho = portal->destino;
            if (portaisUsadosAtual + 1 <= portaisMaximos || vizinho->indice == n - 1) {
                if (distancias[vertice->indice] < distancias[vizinho->indice]) {
                    distancias[vizinho->indice] = distancias[vertice->indice];
                    float prioridade = distancias[vertice->indice] + grafo.calcularDistancia(vizinho->indice, n-1);
                    fila.inserir(vizinho, prioridade, portaisUsadosAtual + 1);
                }
            }
            portal = portal->proximo;
        }
    }

    delete[] distancias;
    return false;
}

bool executarAestrelaMatriz(Grafo& grafo, float energiaMaxima, int portaisMaximos) {
    const int INF = 0x3f3f3f3f; //Determina custo infinito
    const int n = grafo.numeroDeVertices;

    // Inicializa estruturas de dados
    float* distancias = new float[n];
    for (int i = 0; i < n; ++i) {
        distancias[i] = INF;
    }
    distancias[0] = 0;

    FilaPrioridade fila;
    fila.inserir(grafo.listaVertices[0], 0, 0); // Começa no vértice 0, custo 0, portais usados 0


    while (!fila.estaVazia()) {
        Nodo* atual = fila.remover();
        Vertice* vertice = atual->vertice;
        float custoAtual = distancias[vertice->indice];
        int portaisUsadosAtual = atual->portaisUsados;
        delete atual;

        // Verifica se o nó removido é o destino
        if (vertice->indice == n - 1) {
            // Chegou ao destino
            delete[] distancias;
            return custoAtual <= energiaMaxima && portaisUsadosAtual <= portaisMaximos;
        }

        //Verifica se o nó já foi processado
        if(distancias[vertice->indice] < custoAtual) continue;

        // Processa TODAS as arestas
        for(int j = 0; j < n; j++){
            if(j == vertice->indice) continue; //Ignora a si mesmo
            if(grafo.matrizAdjacencia[vertice->indice][j] != -1){ //Se existe aresta
                Vertice* vizinho = grafo.listaVertices[j]; //Vizinho é o vértice adjacente

                if(grafo.matrizAdjacencia[vertice->indice][j] != 0){ //Se a aresta não é um portal
                    float custoTotal = custoAtual + grafo.matrizAdjacencia[vertice->indice][j];
                    if (custoTotal < distancias[vizinho->indice]) {
                        distancias[vizinho->indice] = custoTotal;
                        float prioridade = custoTotal + grafo.calcularDistancia(vizinho->indice, n-1);
                        fila.inserir(vizinho, prioridade, portaisUsadosAtual);
                    }
                }
                else{ //Se a aresta é um portal
                    if (distancias[vertice->indice] < distancias[vizinho->indice] || j == n - 1) {
                        distancias[vizinho->indice] = distancias[vertice->indice];
                        float prioridade = distancias[vertice->indice] + grafo.calcularDistancia(vizinho->indice, n-1);
                        fila.inserir(vizinho, prioridade, portaisUsadosAtual + 1);
                    }
                }

            }
        }
    }

    delete[] distancias;
    return false;
}
