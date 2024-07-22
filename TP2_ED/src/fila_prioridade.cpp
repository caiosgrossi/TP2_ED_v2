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

Nodo* FilaPrioridade::remover() {
    if (estaVazia()) return nullptr;
    Nodo* removido = topo;
    topo = topo->proximo;
    return removido;
}

bool FilaPrioridade::estaVazia() {
    return topo == nullptr;
}

void FilaPrioridade::imprimir() { // Adicione esta função
    Nodo* atual = topo;
    while (atual) {
        std::cout << "Vertice: " << atual->vertice->indice << ", Custo: " << atual->custo << ", Portais Usados: " << atual->portaisUsados << std::endl;
        atual = atual->proximo;
    }
}