#ifndef ARVORE_HPP
#define ARVORE_HPP

#include <iostream>

// Estrutura que representa cada nó da Árvore Binária de Busca (ABB)
struct No{
    int dado;          // Valor armazenado no nó (chave de ordenação da árvore, ex: ID)
    No* esquerdo;      // Ponteiro para o filho à esquerda (valores menores)
    No* direito;       // Ponteiro para o filho à direita (valores maiores)
    
    // Construtor para inicializar o nó com um valor e ponteiros nulos
    No (int valor) : dado(valor), esquerdo(nullptr), direito(nullptr) {}
};

// Classe principal que gerencia a Árvore Binária de Busca
class ArvoreBinariaBusca {

    private:
        No* raiz;               // Ponteiro para o nó raiz da árvore
        std::size_t tamanho;    // Contador da quantidade de nós guardados na árvore

        // Métodos auxiliares recursivos (privados, acessíveis apenas internamente pela classe)
        void destruirRecursivo(No* no);             // Libera a memória de todos os nós recursivamente
        int alturaRecursivo(No* no);                // Calcula a altura da árvore recursivamente

        No* inserirRecursivo(No* no, int valor);    // Insere um valor mantendo a propriedade da ABB
        No* removerRecursivo(No* no, int valor);    // Remove um valor tratando os 3 casos possíveis
        bool buscarRecursivo(No* no, int valor);    // Procura um valor recursivamente na árvore

        void emOrdemRecursivo(No* no);              // Percurso em ordem (Esquerda, Raiz, Direita)
        void preOrdemRecursivo(No* no);             // Percurso em pré-ordem (Raiz, Esquerda, Direita)
        void posOrdemRecursivo(No* no);             // Percurso em pós-ordem (Esquerda, Direita, Raiz)

    public:
        ArvoreBinariaBusca();           // Construtor: cria uma árvore vazia
        ~ArvoreBinariaBusca();          // Destrutor: libera toda a memória alocada

        bool estaVazia();               // Retorna true se a árvore estiver vazia e false caso contrário
        std::size_t getTamanho() const; // Retorna o número total de nós
        int getAltura();                // Retorna a altura atual da árvore
        No* encontrarMenor(No* no);     // Encontra o nó com o menor valor (usado na remoção)

        void inserir(int valor);        // Método público para inserir um novo valor
        bool remover(int valor);        // Método público para remover um valor da árvore
        bool buscar(int valor);         // Método público para verificar se um valor existe
        
        void imprimirEmOrdem();         // Imprime os elementos em ordem crescente
        void imprimirPreOrdem();        // Imprime os elementos em pré-ordem
        void imprimirPosOrdem();        // Imprime os elementos em pós-ordem
};

#endif