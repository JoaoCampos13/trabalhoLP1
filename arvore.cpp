#include <iostream>
#include "ABB.hpp"

using namespace std;

//Recursivas:

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

No* ArvoreBinariaBusca::buscarRecursivo(No* no, int valor){
    if (no->dado == valor){
        return no;
    }

    if (no->dado < valor){
        return buscarRecursivo(no->esquerdo, valor);
    }else if (no->dado > valor){
        return buscarRecursivo(no->direito, valor);
    }

    return nullptr;
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
    emOrdemRecursivo(no->esquerdo);
    emOrdemRecursivo(no->direito);
}

void ArvoreBinariaBusca::ArvoreBinariaBusca:: posOrdemRecursivo(No* no){
    if(no == nullptr){
        return;
    }
    emOrdemRecursivo(no->esquerdo);
    emOrdemRecursivo(no->direito);
    cout<< no->dado << " ";
}

//Normais:

ArvoreBinariaBusca::ArvoreBinariaBusca(){
    raiz = nullptr;
    tamanho = 0;
}

bool ArvoreBinariaBusca::estaVazia(){
    return tamanho == 0;
}

std::size_t ArvoreBinariaBusca::getTamanho(){
    return tamanho;
}

void ArvoreBinariaBusca::inserir(int valor){
    raiz = inserirRecursivo(raiz, valor);
}

bool* ArvoreBinariaBusca::buscar(int valor){
    if(buscarRecursivo (raiz, valor) != nullptr){
        return true;
    }else{
        return false;
    }
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
