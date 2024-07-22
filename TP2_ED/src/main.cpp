#include "grafo.h"
#include "dijkstra.h"
#include "aestrela.h"
#include <iostream>


bool resolverProblema(Grafo& grafo, float energiaMaxima, int portaisMaximos) {
    // Implementar o algoritmo de Djikstra ou A*
    // Adapte o algoritmo para lidar com a quantidade de energia e portais
    return false; // Retorne verdadeiro se for possível escapar, falso caso contrário
}

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    Grafo grafo(n);

    for (int i = 0; i < n; ++i) {
        float x, y;
        std::cin >> x >> y;
        grafo.adicionarVertice(i, x, y);
    }

    // 
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        float peso = grafo.calcularDistancia(u, v);
        grafo.adicionarAresta(u, v, peso);
    }

    for (int i = 0; i < k; ++i) {
        int u, v;
        std::cin >> u >> v;
        grafo.adicionarPortal(u, v);
    }

    float energiaMaxima;
    int portaisMaximos;
    std::cin >> energiaMaxima >> portaisMaximos;

    std::cout << executarDijkstra(grafo, energiaMaxima, portaisMaximos, 0) << " ";
    std::cout << executarAestrela(grafo, energiaMaxima, portaisMaximos, 0) << std::endl;
    
    return 0;
}
