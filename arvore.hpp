#ifndef ARVORE_HPP
#define ARVORE_HPP

#include <iostream>

// Estrutura que representa um nó individual dentro da Árvore Binária de Busca (ABB)
struct No {
    int dado;       // Valor inteiro armazenado no nó (utilizado como chave, ex: ID do atleta)
    No* esquerdo;   // Ponteiro que aponta para o filho à esquerda (valores menores)
    No* direito;    // Ponteiro que aponta para o filho à direita (valores maiores)
    
    // Construtor do nó: inicializa o dado com o valor recebido e define os ponteiros como nulos
    No(int valor) : dado(valor), esquerdo(nullptr), direito(nullptr) {}
};

// Classe que gerencia a Árvore Binária de Busca e suas operações
class ArvoreBinariaBusca {
private:
    No* raiz;            // Ponteiro para o nó raiz (topo) da árvore
    std::size_t tamanho; // Contador do número total de nós presentes na árvore

    // Métodos auxiliares recursivos privados (utilizados internamente pela classe)
    void destruirRecursivo(No* no);            // Libera da memória RAM todos os nós de forma recursiva
    int alturaRecursivo(No* no);               // Calcula recursivamente a altura total da árvore

    No* inserirRecursivo(No* no, int valor);   // Insere um valor mantendo as regras da ABB
    No* removerRecursivo(No* no, int valor);   // Remete e cobre os 3 casos estruturais da ABB
    bool buscarRecursivo(No* no, int valor);   // Pesquisa recursivamente se um valor existe na árvore

    void emOrdemRecursivo(No* no);             // Percurso em ordem (Esquerda -> Raiz -> Direita)
    void preOrdemRecursivo(No* no);            // Percurso em pré-ordem (Raiz -> Esquerda -> Direita)
    void posOrdemRecursivo(No* no);            // Percurso em pós-ordem (Esquerda -> Direita -> Raiz)

public:
    ArvoreBinariaBusca();   // Construtor padrão: inicializa uma árvore vazia
    ~ArvoreBinariaBusca();  // Destrutor: chama a limpeza de memória ao destruir o objeto

    bool estaVazia();             // Verifica se a árvore está vazia
    std::size_t getTamanho() const; // Retorna a quantidade total de nós armazenados
    int getAltura();              // Retorna a altura atual da árvore
    No* encontrarMenor(No* no);   // Encontra o nó com o menor valor em uma sub-árvore

    void inserir(int valor);      // Método público para inserir uma nova chave
    bool remover(int valor);      // Método público para remover uma chave
    bool buscar(int valor);       // Método público para checar se uma chave está presente
    
    void imprimirEmOrdem();       // Imprime os elementos em ordem crescente
    void imprimirPreOrdem();      // Imprime os elementos em pré-ordem
    void imprimirPosOrdem();      // Imprime os elementos em pós-ordem
};

#endif