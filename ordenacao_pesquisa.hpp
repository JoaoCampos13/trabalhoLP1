#ifndef ORDENACAO_PESQUISA_HPP
#define ORDENACAO_PESQUISA_HPP

#include <string>
#include "atletas.hpp" // Importa a struct oficial de Atleta do projeto

using namespace std;

// Funções de ordenação utilizando a pontuação do atleta como chave (organizadas em ordem decrescente)
void quickSort(Atleta v[], int inicio, int fim, long long& comparacoes, long long& trocas);
int particiona(Atleta v[], int inicio, int fim, long long& comparacoes, long long& trocas);

// Funções utilitárias auxiliares para manipulação de vetores
void troca(Atleta& a, Atleta& b);
void copiarVetorAtletas(const Atleta origem[], Atleta destino[], int n);
void imprimeVetorAtletas_Pont(Atleta v[], int n);

// Algoritmos de ordenação alternativos pedidos no trabalho
void selectionSort(Atleta v[], int n, long long& comparacoes, long long& trocas, bool mostrar); 
void insertionSort(Atleta v[], int n, long long& comparacoes, long long& trocas, bool mostrar);

// Funções de busca com contagem de acessos à memória
int buscaSequencial(const Atleta v[], int n, int pontuacaoAtleta, long long& acessos);
int buscaBinaria(const Atleta v[], int n, int pontuacaoAtleta, long long& acessos);

// Função para testes automatizados com massas de dados de 50, 500 e 5000 registros
void executarModoTeste();

#endif