#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "grafo.h"
#include "fila_prioridade.h"
#include "fila_heap.h"

bool executarDijkstraLista(Grafo& grafo, float energiaMaxima, int portaisMaximos);
bool executarDijkstraMatriz(Grafo& grafo, float energiaMaxima, int portaisMaximos);

bool executarDijkstraListaHeap(Grafo& grafo, float energiaMaxima, int portaisMaximos);
bool executarDijkstraMatrizHeap(Grafo& grafo, float energiaMaxima, int portaisMaximos);

#endif // DIJKSTRA_H