#include <iostream>
#include "arvore.hpp"

using namespace std;

// --- MÉTODOS RECURSIVOS PRIVADOS ---

// Destrói todos os nós da árvore em pós-ordem para evitar vazamento de memória (Memory Leak)
void ArvoreBinariaBusca::destruirRecursivo(No* no){
    if(no == nullptr){
        return;
    }

    destruirRecursivo(no->esquerdo);
    destruirRecursivo(no->direito);

    delete no; // Libera o nó atual da memória RAM
}

// Calcula recursivamente a altura da árvore
int ArvoreBinariaBusca::alturaRecursivo(No* no){
    if(no == nullptr){
        return -1; // Árvore vazia ou nó folha excedido retorna -1
    }

    int alturaEsquerda = alturaRecursivo(no->esquerdo);
    int alturaDireita = alturaRecursivo(no->direito);

    // Retorna a maior altura entre os ramos, somando 1 do nível atual
    if(alturaEsquerda > alturaDireita){
        return alturaEsquerda + 1;
    } else {
        return alturaDireita + 1;
    }
}

// Insere um novo valor respeitando a regra da ABB (menores à esquerda, maiores à direita)
No* ArvoreBinariaBusca::inserirRecursivo(No* no, int valor){
    if (no == nullptr){
        tamanho++; // Incrementa o contador de nós
        return new No(valor); // Cria e retorna o novo nó alocado dinamicamente
    }

    if(valor < no->dado){
        no->esquerdo = inserirRecursivo(no->esquerdo, valor);
    }else if(valor > no->dado){
        no->direito = inserirRecursivo(no->direito, valor);
    }
    // Se o valor já existe, não insere duplicatas

    return no;
}

// Remove um valor da árvore cobrindo os 3 casos clássicos (folha, 1 filho, 2 filhos)
No* ArvoreBinariaBusca::removerRecursivo(No* no, int valor){
    if(no == nullptr){
        return nullptr;
    }

    // Busca recursiva pelo nó a ser removido
    if(valor < no->dado){
        no->esquerdo = removerRecursivo(no->esquerdo, valor);
    }else if(valor > no->dado){
        no->direito = removerRecursivo(no->direito, valor);
    }else{
        // CASO 1: Nó folha (sem filhos) ou nó com apenas um filho
        if(no->esquerdo == nullptr && no->direito == nullptr){
            delete no;
            tamanho--;
            return nullptr;
        }

        // CASO 2.1: Possui apenas filho à direita
        if(no->esquerdo == nullptr){
            No* temp = no->direito;
            delete no;
            tamanho--;
            return temp;
        }

        // CASO 2.2: Possui apenas filho à esquerda
        if(no->direito == nullptr){
            No* temp = no->esquerdo;
            delete no;
            tamanho--;
            return temp;
        }

        // CASO 3: Possui dois filhos
        // Encontra o menor elemento na sub-árvore da direita (sucessor em ordem)
        No* temp = encontrarMenor(no->direito);
        no->dado = temp->dado; // Substitui o dado do nó atual pelo menor da direita
        no->direito = removerRecursivo(no->direito, temp->dado); // Remove o duplicado à direita
    }

    return no;
}

// Procura recursivamente se um valor está presente na ABB
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

// Percurso em ordem: visita esquerda, imprime o dado, visita direita (retorna elementos ordenados)
void ArvoreBinariaBusca::emOrdemRecursivo(No* no){
    if(no == nullptr){
        return;
    }
    emOrdemRecursivo(no->esquerdo);
    cout << no->dado << " ";
    emOrdemRecursivo(no->direito);
}

// Percurso em pré-ordem: imprime a raiz, visita esquerda, visita direita
void ArvoreBinariaBusca::preOrdemRecursivo(No* no){
    if(no == nullptr){
        return;
    }
    cout << no->dado << " ";
    preOrdemRecursivo(no->esquerdo);
    preOrdemRecursivo(no->direito);
}

// Percurso em pós-ordem: visita esquerda, visita direita, imprime a raiz
void ArvoreBinariaBusca::posOrdemRecursivo(No* no){
    if(no == nullptr){
        return;
    }
    posOrdemRecursivo(no->esquerdo);
    posOrdemRecursivo(no->direito);
    cout << no->dado << " ";
}

// --- MÉTODOS PÚBLICOS ---

ArvoreBinariaBusca::ArvoreBinariaBusca(){
    raiz = nullptr;
    tamanho = 0;
}

ArvoreBinariaBusca::~ArvoreBinariaBusca(){
    destruirRecursivo(raiz); // Aciona a limpeza total da memória ao destruir o objeto
}

// Retorna o nó mais à esquerda de uma sub-árvore
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
        return false; // Se o valor não existe, não faz nada
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