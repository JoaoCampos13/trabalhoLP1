#ifndef ARVORE_HPP
#define ARVORE_HPP

#include <iostream>

struct No{
    int dado;                                                          //guarda o valor do no
    No* direito;                                                       //ponteiro que aponta para o filho da direita
    No* esquerdo;                                                      //ponteiro que aponta para o filho da esquerda
    No(int valor): dado(valor), direito(nullptr), esquerdo(nullptr) {} //guarda valor e inicia os ponteiros em null
};

class ArvoreBinariaBusca{
private:
    No* raiz;         // mesma ideia da classe anterior
    std::size_t tamanho;   // quantidade de nos guardados

    // auxiliares recursivos: so a classe usa
    No* inserirRecursivo(No* no, int valor);
    No* buscarRecursivo(No* no, int valor);
    void emOrdemRecursivo(No* no);
    void preOrdemRecursivo(No* no);
    void posOrdemRecursivo(No* no);

public:
    ArvoreBinariaBusca();      // cria uma arvore vazia
    bool estaVazia();
    std::size_t getTamanho();
    void inserir(int valor);   // insere seguindo a regra da ordenacao
    bool buscar(int valor);    // diz se o valor esta na arvore
    void imprimirEmOrdem();    // esquerda, no, direita
    void imprimirPreOrdem();   // no, esquerda, direita
    void imprimirPosOrdem();   // esquerda, direita, no
    void remover(int valor);   // remove o no
};


#endif
