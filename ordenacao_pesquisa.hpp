#ifndef ORDENACAO_PESQUISA_HPP
#define ORDENACAO_PESQUISA_HPP
#include <string>
#include <vector>
using namespace std;

// Struct que representa o registro do atleta no torneio
struct Atleta
{
    int pontuacao;
    int id;
    string nome;

};

//Uso do long long& e para evitaro estouro de Memória (Integer Overflow)
void QuickSort(Atleta v[], int inicio, int fim, long long& comparacoes, long long& trocas);
int parcionar();

//função auxiliar de troca, cópia de atletas e imprimir atletas
void troca(Atleta& a, Atleta& b);
void copiarVetorAtletas(const Atleta origem[], Atleta destino[], int n);

void imprimeVetorAtletas_Pont(Atleta v[], int n);
void selectionSort(Atleta v[], int n, long long& comparacoes, long long& trocas, bool mostrar); 
void insertSort(Atleta v[], int n, long long& comparacoes, long long& trocas, bool mostrar);

// funções de buscas
int buscaSequencial(const Atleta v[], int n, int pontuacaoAtleta, long long& acessos);
int buscaBinaria(const Atleta v[], int n, int pontuacaoAtleta, long long& acessos);

// função para teste
void executarModoTeste();


#endif
