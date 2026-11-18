#include <iostream>
#include "arvore.hpp"

using namespace std;

//Recursivas:
void ArvoreBinariaBusca::destruirRecursivo(No* no){
    if(no == nullptr){ // condicao de parada
        return;
    }

    destruirRecursivo(no->esquerdo); // chama parte da esquerda
    destruirRecursivo(no->direito); //chama parte da direita

    delete no; //deleta o no
    return;
}

int ArvoreBinariaBusca::alturaRecursivo(No* no){
    if(no == nullptr){ //condicao de parada
        return -1;
    }

    int alturaEsquerda = alturaRecursivo(no->esquerdo); //calcula altura da esquerda
    int alturaDireita = alturaRecursivo(no->direito); //calcula altura da direita

    if(alturaEsquerda > alturaDireita){ // verifica qualm é maior
        return alturaEsquerda + 1; 
    }else{
        return alturaDireita + 1;
    }
}

No* ArvoreBinariaBusca::inserirRecursivo(No* no, int valor){
    if (no == nullptr){ //condicao de parada
        tamanho ++;
        return new No(valor);
    }

    if(valor < no->dado){
        no->esquerdo = inserirRecursivo(no->esquerdo, valor); //insere na esqueda se for menor
    }else if(valor > no->dado){
        no->direito = inserirRecursivo(no->direito, valor); //insere na direita se for maior
    }

    return no;
}

No* ArvoreBinariaBusca::removerRecursivo(No* no, int valor){
    if(no == nullptr){ //condicao de parada
        return nullptr;
    }

    if(valor < no->dado){ //se o valor procurado for menor que o atual
        no->esquerdo = removerRecursivo(no->esquerdo, valor); //procura valor na esquerda
    }else if(valor > no->dado){
        no->direito = removerRecursivo(no->direito, valor); //senao procura na direita
    }else{ //se nao for menor nem maior o no foi encontrado
        //Caso 1: no folha
        //Basta liberar a memoria e decrementar o tamanho
        if(no->esquerdo == nullptr && no->direito == nullptr){ 
            delete no;
            tamanho--;
            return nullptr;
        }
        //Caso 2: no nao tem o filho esquerdo na esquerda
        //filho na direita assume o lugar na arvore
        if(no->esquerdo == nullptr){
            No* temp = no->direito;
            delete no;
            tamanho--;
            return temp;
        }
        //Caso 3: no nao possui filho direito
        //filho na esquerda assume lugar na arvore        
        if(no->direito == nullptr){
            No* temp = no->esquerdo;
            delete no;
            tamanho--;
            return temp;
        }
        //Caso 4: possui dois filhos
        No* temp = encontrarMenor(no->direito); //encontra o menor elemento da subarvore da direita
        no->dado = temp->dado; //substitui o valor do no atual pelo sucessor
        no->direito = removerRecursivo(no->direito, temp->dado); //tamanho decrementado dentro da chamada recursiva
    }

    return no;
}

bool ArvoreBinariaBusca::buscarRecursivo(No* no, int valor) {
    if (no == nullptr) { //condicao de parada
        return false;
    }

    if (no->dado == valor) { //retorna true se achar o valor
        return true;
    }

    if (valor < no->dado) {
        return buscarRecursivo(no->esquerdo, valor); //busca na esquerda se for menor
    } else {
        return buscarRecursivo(no->direito, valor); //busca na direita se for maioir
    }
}

void ArvoreBinariaBusca::emOrdemRecursivo(No* no){
    if(no == nullptr){ // condicao de parada
        return;
    }
    emOrdemRecursivo(no->esquerdo); //imprime lado esquedo primeiro
    cout<< no->dado << " "; //imprime dado no meio
    emOrdemRecursivo(no->direito); //imprime lado direito por ultimo
}

void ArvoreBinariaBusca::preOrdemRecursivo(No* no){
    if(no == nullptr){ // condicao de parada
        return;
    }
    cout<< no->dado << " "; //imprime dado primeiro
    preOrdemRecursivo(no->esquerdo); //imprime esquerda em segundo
    preOrdemRecursivo(no->direito); //imprime direita por ultimo
}

void ArvoreBinariaBusca::posOrdemRecursivo(No* no){
    if(no == nullptr){ // condicao de parada
        return;
    }
    posOrdemRecursivo(no->esquerdo); //imprime lado esquedo primeiro
    posOrdemRecursivo(no->direito);  //imprime lado direito em segundo lugar
    cout<< no->dado << " ";  //imprime dado por ultimo
}

//Normais:

ArvoreBinariaBusca::ArvoreBinariaBusca(){ //contrutor
    raiz = nullptr;
    tamanho = 0;
}

ArvoreBinariaBusca::~ArvoreBinariaBusca(){ //destrutor
    destruirRecursivo(raiz); //Chama o destruir
}

No* ArvoreBinariaBusca::encontrarMenor(No* no){ 
    while(no->esquerdo != nullptr){ //avança ate o menor dado
        no = no->esquerdo;
    }

    return no;
}

bool ArvoreBinariaBusca::estaVazia(){ // retorna true se no esta vazio
    return tamanho == 0;
}

std::size_t ArvoreBinariaBusca::getTamanho() const{ //retorna tamanho
    return tamanho;
}

int ArvoreBinariaBusca::getAltura() { //retorna altura da arvore
    return alturaRecursivo(raiz);
}

void ArvoreBinariaBusca::inserir(int valor){ //chama inserir recursivo
    raiz = inserirRecursivo(raiz, valor);
}

bool ArvoreBinariaBusca::remover(int valor){ //chama remover se aarvore nao estiver vazia
    if(!buscar(valor)){
        return false;
    }

    raiz = removerRecursivo(raiz, valor);
    return true;
}

bool ArvoreBinariaBusca::buscar(int valor) { //chama buscar Recursivo
    return buscarRecursivo(raiz, valor);
}

void ArvoreBinariaBusca::imprimirEmOrdem(){ // imprime em ordem
    emOrdemRecursivo(raiz);
}

void ArvoreBinariaBusca::imprimirPreOrdem(){ //imprime pre ordem
    preOrdemRecursivo(raiz);
}

void ArvoreBinariaBusca::imprimirPosOrdem(){ //imnprime pos ordem
    posOrdemRecursivo(raiz);
}
