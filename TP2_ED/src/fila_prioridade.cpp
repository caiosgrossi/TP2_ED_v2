#include "fila_prioridade.h"
#include "grafo.h"
#include "vertice.h"

FilaPrioridade::FilaPrioridade(){
    topo = nullptr;
}

FilaPrioridade::~FilaPrioridade() {
    while (topo) {
        Nodo* temp = topo;
        topo = topo->proximo;
        delete temp;
    }
}

// Insere um novo nó na fila de prioridade
void FilaPrioridade::inserir(Vertice* vertice, float custo, int portaisUsados) {
    // Insere o novo nodo na posição correta
    Nodo* novoNodo = new Nodo{vertice, custo, portaisUsados, nullptr};
    Nodo* atual;

    if (!topo || topo->custo > custo) {
        novoNodo->proximo = topo;
        topo = novoNodo;
    } else {
        atual = topo;
        while (atual->proximo && atual->proximo->custo <= custo) {
            atual = atual->proximo;
        }
        novoNodo->proximo = atual->proximo;
        atual->proximo = novoNodo;
    }
}

// Remove o nó com menor custo da fila de prioridade
Nodo* FilaPrioridade::remover() {
    if (estaVazia()) return nullptr;
    Nodo* removido = topo;
    topo = topo->proximo;
    return removido;
}

// Verifica se a fila de prioridade está vazia
bool FilaPrioridade::estaVazia() {
    return topo == nullptr;
}