#include "grafo.h"
#include "dijkstra.h"
#include "aestrela.h"
#include <iostream>

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    Grafo grafo(n);

    // Adicionando vértices
    for (int i = 0; i < n; ++i) {
        float x, y;
        std::cin >> x >> y;
        grafo.adicionarVertice(i, x, y);
    }

    // Adicionando arestas
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        float peso = grafo.calcularDistancia(u, v);
        grafo.adicionarAresta(u, v, peso);
    }

    // Adicionando portais
    for (int i = 0; i < k; ++i) {
        int u, v;
        std::cin >> u >> v;
        grafo.adicionarPortal(u, v);
    }

    float energiaMaxima;
    int portaisMaximos;
    std::cin >> energiaMaxima >> portaisMaximos;

    std::cout << executarDijkstraMatrizHeap(grafo, energiaMaxima, portaisMaximos) << " ";
    std::cout << executarAestrelaMatrizHeap(grafo, energiaMaxima, portaisMaximos) << std::endl;
    std::cout << executarDijkstraListaHeap(grafo, energiaMaxima, portaisMaximos) << " ";
    std::cout << executarAestrelaListaHeap(grafo, energiaMaxima, portaisMaximos) << std::endl;
    return 0;
}
