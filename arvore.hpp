#ifndef ARVORE_HPP
#define ARVORE_HPP

#include <iostream>
struct No{
    int dado;
    No* esquerdo;
    No* direito;
    No (int valor) : dado(valor), esquerdo(nullptr), direito(nullptr) {}
};

class ArvoreBinariaBusca{
private:
    No* raiz;         // mesma ideia da classe anterior
    std::size_t tamanho;   // quantidade de nós guardados

    // auxiliares recursivos: só a classe usa
    No* inserirRecursivo(No* no, int valor);
    bool buscarRecursivo(No* no, int valor);
    void emOrdemRecursivo(No* no);
    void preOrdemRecursivo(No* no);
    void posOrdemRecursivo(No* no);

public:
    ArvoreBinariaBusca();      // cria uma árvore vazia
    bool estaVazia();
    std::size_t getTamanho();
    void inserir(int valor);   // insere seguindo a regra da ordenação
    bool buscar(int valor);    // diz se o valor está na árvore
    void imprimirEmOrdem();    // esquerda, nó, direita
    void imprimirPreOrdem();   // nó, esquerda, direita
    void imprimirPosOrdem();   // esquerda, direita, nó
};


#endif
