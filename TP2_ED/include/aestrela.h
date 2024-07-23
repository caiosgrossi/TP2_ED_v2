#ifndef AESTRELA_H
#define ARESTRELA_H

#include "grafo.h"
#include "fila_prioridade.h"

bool executarAestrelaLista(Grafo& grafo, float energiaMaxima, int portaisMaximos);
bool executarAestrelaMatriz(Grafo& grafo, float energiaMaxima, int portaisMaximos);


#endif // AESTRELA_H
