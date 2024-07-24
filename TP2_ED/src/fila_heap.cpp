#include "fila_heap.h"

Heap::Heap(int capacidade) {
    this->vetorHeap = new NodoHeap*[capacidade];
    this->capacidade = capacidade;
    this->tamanho = 0;
}

Heap::~Heap() {
    delete[] this->vetorHeap;
}

void Heap::subir(int indice) {
    int pai = (indice - 1) / 2;
    if (this->vetorHeap[pai]->custo > this->vetorHeap[indice]->custo) {
        this->trocar(pai, indice);
        this->subir(pai);
    }
}

void Heap::descer(int indice) {
    int esquerda = 2 * indice + 1;
    int direita = 2 * indice + 2;
    int menor = indice;

    if (esquerda < this->tamanho && this->vetorHeap[esquerda]->custo < this->vetorHeap[menor]->custo) {
        menor = esquerda;
    }

    if (direita < this->tamanho && this->vetorHeap[direita]->custo < this->vetorHeap[menor]->custo) {
        menor = direita;
    }

    if (menor != indice) {
        this->trocar(indice, menor);
        this->descer(menor);
    }
}

void Heap::trocar(int i, int j) {
    NodoHeap* aux = this->vetorHeap[i];
    this->vetorHeap[i] = this->vetorHeap[j];
    this->vetorHeap[j] = aux;
}

void Heap::inserir(Vertice* vertice, float custo, int portaisUsados) {
    if (this->tamanho == this->capacidade) {
        return;
    }

    NodoHeap* novoNodo = new NodoHeap;
    novoNodo->vertice = vertice;
    novoNodo->custo = custo;
    novoNodo->portaisUsados = portaisUsados;

    this->vetorHeap[this->tamanho] = novoNodo;
    this->subir(this->tamanho);
    this->tamanho++;
}

NodoHeap* Heap::remover() {
    if (this->tamanho == 0) {
        return nullptr;
    }

    NodoHeap* removido = this->vetorHeap[0];
    this->vetorHeap[0] = this->vetorHeap[this->tamanho - 1];
    this->tamanho--;
    this->descer(0);

    return removido;
}

bool Heap::estaVazia() {
    return this->tamanho == 0;
}