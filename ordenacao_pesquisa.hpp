#ifndef ORDENACAO_PESQUISA_HPP
#define ORDENACAO_PESQUISA_HPP

#include <string>
#include "atletas.hpp" // <-- Importa a struct oficial do projeto
using namespace std;

// Funções de ordenação recebem o vetor de Atleta (usando o float pontuacao corretamente)
void quickSort(Atleta v[], int inicio, int fim, long long& comparacoes, long long& trocas);
int particiona(Atleta v[], int inicio, int fim, long long& comparacoes, long long& trocas);

// Função auxiliar de troca, cópia de atletas e impressão
void troca(Atleta& a, Atleta& b);
void copiarVetorAtletas(const Atleta origem[], Atleta destino[], int n);

void imprimeVetorAtletas_Pont(Atleta v[], int n);
void selectionSort(Atleta v[], int n, long long& comparacoes, long long& trocas, bool mostrar); 
void insertionSort(Atleta v[], int n, long long& comparacoes, long long& trocas, bool mostrar);

// Funções de buscas (ajustadas para buscar por pontuação se necessário, ou ID)
int buscaSequencial(const Atleta v[], int n, float pontuacaoAtleta, long long& acessos);
int buscaBinaria(const Atleta v[], int n, float pontuacaoAtleta, long long& acessos);

// Função para teste
void executarModoTeste();

#endif