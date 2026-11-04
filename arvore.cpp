#include <iostream>
#include "arvore.hpp"

using namespace std;

//Recursivas:
void ArvoreBinariaBusca::destruirRecursivo(No* no){
    if(no == nullptr){
        return;
    }

    destruirRecursivo(no->esquerdo);
    destruirRecursivo(no->direito);

    delete no;
    return;
}

int ArvoreBinariaBusca::alturaRecursivo(No* no){
    if(no == nullptr){
        return -1;
    }

    int alturaEsquerda = alturaRecursivo(no->esquerdo);
    int alturaDireita = alturaRecursivo(no->direito);

    if(alturaEsquerda > alturaDireita){
        return alturaEsquerda + 1;
    }else{
        return alturaDireita + 1;
    }
}

No* ArvoreBinariaBusca::inserirRecursivo(No* no, int valor){
    if (no == nullptr){
        tamanho ++;
        return new No(valor);
    }

    if(valor < no->dado){
        no->esquerdo = inserirRecursivo(no->esquerdo, valor);
    }else if(valor > no->dado){
        no->direito = inserirRecursivo(no->direito, valor);
    }

    return no;
}

No* ArvoreBinariaBusca::removerRecursivo(No* no, int valor){
    if(no == nullptr){
        return nullptr;
    }

    if(valor < no->dado){
        no->esquerdo = removerRecursivo(no->esquerdo, valor);
    }else if(valor > no->dado){
        no->direito = removerRecursivo(no->direito, valor);
    }else{
        if(no->esquerdo == nullptr && no->direito == nullptr){
            delete no;
            tamanho--;
            return nullptr;
        }

        if(no->esquerdo == nullptr){
            No* temp = no->direito;
            delete no;
            tamanho--;
            return temp;
        }

        if(no->direito == nullptr){
            No* temp = no->esquerdo;
            delete no;
            tamanho--;
            return temp;
        }

        No* temp = encontrarMenor(no->direito);
        no->dado = temp->dado;
        no->direito = removerRecursivo(no->direito, temp->dado);
    }

    return no;
}

bool ArvoreBinariaBusca::buscarRecursivo(No* no, int valor) {
    if (no == nullptr) {
        return false;
    }

    if (no->dado == valor) {
        return true;
    }

    if (valor < no->dado) {
        return buscarRecursivo(no->esquerdo, valor);
    } else {
        return buscarRecursivo(no->direito, valor);
    }
}

void ArvoreBinariaBusca::emOrdemRecursivo(No* no){
    if(no == nullptr){
        return;
    }
    emOrdemRecursivo(no->esquerdo);
    cout<< no->dado << " ";
    emOrdemRecursivo(no->direito);
}

void ArvoreBinariaBusca::preOrdemRecursivo(No* no){
    if(no == nullptr){
        return;
    }
    cout<< no->dado << " ";
    preOrdemRecursivo(no->esquerdo);
    preOrdemRecursivo(no->direito);
}

void ArvoreBinariaBusca::posOrdemRecursivo(No* no){
    if(no == nullptr){
        return;
    }
    posOrdemRecursivo(no->esquerdo);
    posOrdemRecursivo(no->direito);
    cout<< no->dado << " ";
}

//Normais:

ArvoreBinariaBusca::ArvoreBinariaBusca(){
    raiz = nullptr;
    tamanho = 0;
}

ArvoreBinariaBusca::~ArvoreBinariaBusca(){
    destruirRecursivo(raiz);
}

No* ArvoreBinariaBusca::encontrarMenor(No* no){
    while(no->esquerdo != nullptr){
        no = no->esquerdo;
    }

    return no;
}

bool ArvoreBinariaBusca::estaVazia(){
    return tamanho == 0;
}

std::size_t ArvoreBinariaBusca::getTamanho() const{
    return tamanho;
}

int ArvoreBinariaBusca::getAltura() {
    return alturaRecursivo(raiz);
}

void ArvoreBinariaBusca::inserir(int valor){
    raiz = inserirRecursivo(raiz, valor);
}

bool ArvoreBinariaBusca::remover(int valor){
    if(!buscar(valor)){
        return false;
    }

    raiz = removerRecursivo(raiz, valor);
    return true;
}

bool ArvoreBinariaBusca::buscar(int valor) {
    return buscarRecursivo(raiz, valor);
}

void ArvoreBinariaBusca::imprimirEmOrdem(){
    emOrdemRecursivo(raiz);
}

void ArvoreBinariaBusca::imprimirPreOrdem(){
    preOrdemRecursivo(raiz);
}

void ArvoreBinariaBusca::imprimirPosOrdem(){
    posOrdemRecursivo(raiz);
}
