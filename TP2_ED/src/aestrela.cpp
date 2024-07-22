#include "aestrela.h"


bool executarAestrela(Grafo& grafo, float energiaMaxima, int portaisMaximos, bool print) {
    const int INF = 0x3f3f3f3f; //Determina custo infinito
    const int n = grafo.numeroDeVertices;

    // Inicializa estruturas de dados
    float* distancias = new float[n];
    int* portaisUsados = new int[n];
    for (int i = 0; i < n; ++i) {
        distancias[i] = INF;
        portaisUsados[i] = INF;
    }
    distancias[0] = 0;
    portaisUsados[0] = 0;

    FilaPrioridade fila;
    fila.inserir(grafo.listaVertices[0], 0, 0); // Começa no vértice 0, custo 0, portais usados 0
    if(print){
        fila.imprimir();
        std::cout << "numero de vertices: " << grafo.numeroDeVertices << std::endl;
    }

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
            delete[] portaisUsados;
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
                portaisUsados[vizinho->indice] = portaisUsadosAtual;
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
                    portaisUsados[vizinho->indice] = portaisUsadosAtual + 1;
                    float prioridade = distancias[vertice->indice] + grafo.calcularDistancia(vizinho->indice, n-1);
                    fila.inserir(vizinho, prioridade, portaisUsados[vizinho->indice]);
                }
            }
            portal = portal->proximo;
        }

        if (print){
            for (int i = 0; i < n; ++i) {
                std::cout << std::endl << "distancia " << i << ": " << distancias[i] << " ";
            }
            std::cout << std::endl;
            fila.imprimir();
            std::cout << std::endl;
        }
    }

    delete[] distancias;
    delete[] portaisUsados;
    return false;
}
