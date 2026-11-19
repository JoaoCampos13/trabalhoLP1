#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include "ordenacao_pesquisa.hpp"

using namespace std;

// Realiza a troca física de dois atletas no vetor
void troca(Atleta& a, Atleta& b) {
    Atleta auxiliar = a;  
    a = b;
    b = auxiliar;
}

// Copia os dados de um vetor de atletas para outro vetor destino
void copiarVetorAtletas(const Atleta origem[], Atleta destino[], int n){
    for(int i = 0; i < n; i++){
       destino[i] = origem[i];
    }
}

// Imprime os dados essenciais dos atletas no console
void imprimeVetorAtletas_Pont(Atleta v[], int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        cout << v[i].id << " | " << v[i].nome << " | " << v[i].pontuacao << endl;
    }
    cout << "]" << endl;
}

// Ordena o vetor em ordem decrescente utilizando o algoritmo Selection Sort
void selectionSort(Atleta v[], int n, long long& comparacoes, long long& trocas, bool mostrar) {
    for (int i = 0; i < n - 1; i++) {
        int indice_maior_pontuacao = i;            

        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].pontuacao > v[indice_maior_pontuacao].pontuacao) {  
                indice_maior_pontuacao = j;
            }
        }

        if (indice_maior_pontuacao != i) {
            troca(v[i], v[indice_maior_pontuacao]);
            trocas++;
        }

        if (mostrar) { 
            cout << "passada " << i + 1 << ": ";
            imprimeVetorAtletas_Pont(v, n);
        }
    }
}

// Procura um elemento de forma sequencial (linear) num vetor desordenado
int buscaSequencial(const Atleta v[], int n, int pontuacaoAtleta, long long& acessos){
    for(int i = 0; i < n; i++){
        acessos++; // Conta cada verificação de memória feita
       
        if(v[i].pontuacao == pontuacaoAtleta){
            return i; // Retorna o índice onde encontrou
        }
    }
    return -1; // Não encontrado
}

// Procura um elemento de forma binária em um vetor ordenado
int buscaBinaria(const Atleta v[], int n, int pontuacaoAtleta, long long& acessos){
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        acessos++; // Conta o acesso ao elemento do meio
        
        if (v[meio].pontuacao == pontuacaoAtleta) {
            return meio;  
        }
        if (pontuacaoAtleta > v[meio].pontuacao) { 
            fim = meio - 1;  
        } else {
            inicio = meio + 1;  
        }
    }
    return -1;  
}

// Função de partição auxiliar para o QuickSort (organiza em ordem decrescente)
int particiona(Atleta v[], int inicio, int fim, long long& comparacoes, long long& trocas) {
    int pivo_pontuacao = v[fim].pontuacao;        
    int i = inicio - 1;       

    for (int j = inicio; j < fim; j++) {
        comparacoes++;
        if (v[j].pontuacao > pivo_pontuacao) {   
            i++;
            troca(v[i], v[j]);
            trocas++;
        }
    }
    troca(v[i + 1], v[fim]);  
    trocas++;
    return i + 1;             
}

// Algoritmo de ordenação rápida QuickSort
void quickSort(Atleta v[], int inicio, int fim, long long& comparacoes, long long& trocas){
    if (inicio < fim) {  
        int pos_pivo = particiona(v, inicio, fim, comparacoes, trocas);
        quickSort(v, inicio, pos_pivo - 1, comparacoes, trocas);  
        quickSort(v, pos_pivo + 1, fim, comparacoes, trocas);     
    }
}

// Ordena o vetor em ordem decrescente utilizando o Insertion Sort
void insertionSort(Atleta v[], int n, long long& comparacoes, long long& trocas, bool mostrar) {
    for (int i = 1; i < n; i++) {
        Atleta chave = v[i];  
        int j = i - 1;   
        
        while (j >= 0) {
            comparacoes++;
            if (v[j].pontuacao < chave.pontuacao) { 
                v[j + 1] = v[j];
                trocas++; 
                j--;
            } else {
                break; 
            }
        }
        v[j + 1] = chave;
        
        if (mostrar) { 
            cout << "passada " << i << ": ";
            imprimeVetorAtletas_Pont(v, n);
        }
    }
}

// Executa testes automatizados exigidos para o relatório (com tamanhos 50, 500 e 5000)
void executarModoTeste() {
    int tamanhos[] = {50, 500, 5000};

    for(int t = 0; t < 3; t++){
        int n = tamanhos[t];

        Atleta* original = new Atleta[n];
        Atleta* copia = new Atleta[n];

        for(int i = 0; i < n; i++){
            original[i].id = i + 1;
            original[i].nome = "Atleta_" + to_string(i + 1);
            original[i].pontuacao = rand() % 10000; 
        }

        // Teste QuickSort
        long long compQ = 0, trocasQ = 0;
        copiarVetorAtletas(original, copia, n);
        quickSort(copia, 0 , n - 1, compQ, trocasQ);

        // Teste Selection Sort
        long long compS = 0, trocasS = 0;
        copiarVetorAtletas(original, copia, n);
        selectionSort(copia, n, compS, trocasS, false); 

        // Teste Insertion Sort
        long long compI = 0, trocasI = 0;
        copiarVetorAtletas(original, copia, n);
        insertionSort(copia, n, compI, trocasI, false);

        // Exibição dos resultados estatísticos
        cout << "\n--- Relatorio para N = " << n << " ---" << endl;
        cout << left << setw(18) << "Algoritmo" << setw(22) << "Comparacoes" << setw(22) << "Trocas/Deslocamentos" << endl;
        cout << left << setw(18) << "Quicksort" << setw(22) << compQ << setw(22) << trocasQ << endl;
        cout << left << setw(18) << "Selection Sort" << setw(22) << compS << setw(22) << trocasS << endl;
        cout << left << setw(18) << "Insertion Sort" << setw(22) << compI << setw(22) << trocasI << endl;

        int chaveAlvo = original[n / 2].pontuacao;

        long long acessosSeq = 0;
        buscaSequencial(original, n, chaveAlvo, acessosSeq);

        long long acessosBin = 0; 
        buscaBinaria(copia, n, chaveAlvo, acessosBin);

        cout << "[ Pesquisa (Chave: " << chaveAlvo << " pts) ]" << endl;
        cout << left << setw(25) << "Metodo de busca" << setw(22) << "Acessos a Memoria" << endl;
        cout << left << setw(25) << "Busca Sequencial" << setw(22) << acessosSeq << endl;
        cout << left << setw(25) << "Busca Binaria" << setw(22) << acessosBin << endl;

        delete [] original;
        delete[] copia;
    }
}