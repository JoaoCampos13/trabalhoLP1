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

        No* raiz;               // raiz da arvore
        std::size_t tamanho;    // quantidade de nós guardados

        // auxiliares recursivos: só a classe usa
        void destruirRecursivo(No* no);             //destruir

        int alturaRecursivo(No* no);        //recebe autura

        No* inserirRecursivo(No* no, int valor);    //inserir
        No* removerRecursivo(No* no, int valor);   //remover
        bool buscarRecursivo(No* no, int valor);    //buscar

        void emOrdemRecursivo(No* no);              //em ordem
        void preOrdemRecursivo(No* no);             //pre ordem
        void posOrdemRecursivo(No* no);             //pos ordem

    public:

        ArvoreBinariaBusca();           // cria uma árvore vazia
        ~ArvoreBinariaBusca();          // libera a memoria e os ponteiros

        bool estaVazia();               // retorna 1 se a arvore estiver vazia e 0 se nao estiver
        std::size_t getTamanho() const;
        int getAltura();
        No* encontrarMenor(No* no);

        void inserir(int valor);        // insere seguindo a regra da ordenação
        bool remover(int valor);        // recebe um valor e esse o valor nao existir retorna -1, se existir remove e retorna o valor
        bool buscar(int valor);         // retorna 1 se o valor esta na arvore e 0 se nao esta
        
        void imprimirEmOrdem();         // imprime na ordem: esquerda, dado, direita
        void imprimirPreOrdem();        // imprime na ordem: r, esquerda, direita
        void imprimirPosOrdem();        // imprime na ordem: esquerda, direita, dado
        
};


#endif
