#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include "ordenacao_pesquisa.hpp"
using namespace std;

// Troca o conteúdo de a e b. O & faz a função mexer nas variáveis originais
void troca(Atleta& a, Atleta& b) {
    Atleta auxiliar = a;  // guarda o valor de a antes de perder
    a = b;
    b = auxiliar;
}

// Faz a copia do atleta de origem e copia os dados para o atleta destino, não a troca apenas copia
void copiarVetorAtletas(const Atleta origem[], Atleta destino[], int n){
    
    for(int i = 0; i < n; i++){
       destino[i] = origem[i];
    }
}

// Imprime os n elementos de v entre colchetes
void imprimeVetorAtletas_Pont(Atleta v[], int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        cout << v[i].id << " | "<< v[i].nome << " | " << v[i].pontuacao << endl;
    }
    cout << "]" << endl;
}


// Ordena v em ordem descrescente pelo método da seleção (Selection Sort)
void selectionSort(Atleta v[], int n, long long& comparacoes, long long& trocas, bool mostrar) {
    // i é a posição que vai receber o maior do que sobrou
    for (int i = 0; i < n - 1; i++) {
        int indice_maior_pontuacao = i;            // supõe que o maior está em i

        // procura a maior pontuação de v[i + 1] até o fim
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].pontuacao > v[indice_maior_pontuacao].pontuacao) {  // achou alguma pontuação maior: guarda a posição
                indice_maior_pontuacao = j;
            }
        }

        // só troca se o maior não estiver já na posição i
        if (indice_maior_pontuacao != i) {
            troca(v[i], v[indice_maior_pontuacao]);
            trocas++;
        }

        if (mostrar) { // mostra o vetor ao final da passada
            cout << "passada " << i + 1 << ": ";
            imprimeVetorAtletas_Pont(v, n);
        }
    }
}


int buscaSequencial(const Atleta v[], int n, int pontuacaoAtleta, long long& acessos){
    for(int i = 0; i < n; i++){
        acessos++;
       
        if(v[i].pontuacao == pontuacaoAtleta){
            return i;
        }
         
    }
    return -1;
}

int buscaBinaria(const Atleta v[], int n, int pontuacaoAtleta, long long& acessos){

    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        acessos++; 
        
        if (v[meio].pontuacao == pontuacaoAtleta) {
            return meio;  // achou
        }
        if (pontuacaoAtleta > v[meio].pontuacao) {
            fim = meio - 1;  // descarta a direita
        } else {
            inicio = meio + 1;  // descarta a esquerda
        }
    }
    return -1;  // inicio passou de fim
}

int particiona(Atleta v[], int inicio, int fim, long long& comparacoes, long long& trocas) {
    int pivo_pontuacao = v[fim].pontuacao;        // o último é o pivô
    int i = inicio - 1;       // Fim da região dos atletas com MAIOR pontuação
    for (int j = inicio; j < fim; j++) {
        comparacoes++;

        if (v[j].pontuacao > pivo_pontuacao) {   // Entra na região das maiores pontuações (decrescente)
            i++;
            troca(v[i], v[j]);
            trocas++;
        }
    }
    troca(v[i + 1], v[fim]);  // pivô no lugar certo
    trocas++;
    return i + 1;             // posição final do pivô
}


void quickSort(Atleta v[], int inicio, int fim, long long& comparacoes, long long& trocas){

        if (inicio < fim) {  // trecho com 2 ou mais elementos
        int pos_pivo = particiona(v, inicio, fim, comparacoes, trocas);
        quickSort(v, inicio, pos_pivo - 1, comparacoes, trocas);  // esquerda
        quickSort(v, pos_pivo + 1, fim, comparacoes, trocas);     // direita
    }
}

  

// Ordena v em ordem decrescente pelo método da Inserção (Insertion Sort)
void insertionSort(Atleta v[], int n, long long& comparacoes, long long& trocas, bool mostrar) {
    for (int i = 1; i < n; i++) {
        Atleta chave = v[i];  // O atleta da vez
        int j = i - 1;   // último da parte já ordenada
        
        // Desloca os elementos menores que a chave para a direita
        while (j >= 0) {
            comparacoes++;
            if (v[j].pontuacao < chave.pontuacao) { // Ordem decrescente
                v[j + 1] = v[j];
                trocas++; // Conta cada deslocamento de elemento
                j--;
            } else {
                break; // Achou a posição correta da chave
            }
        }
        v[j + 1] = chave;
        
        if (mostrar) { // Exibe o vetor ao final de cada passada
            cout << "passada " << i << ": ";
            imprimeVetorAtletas_Pont(v, n);
        }
    }
}

void executarModoTeste() {
    // Tamanhos de vetores definidos pelas especificações do trabalho (50, 500 e 5000)
    int tamanhos[] = {50, 500, 5000};
    
    cout << "\n=========================================================================\n";
    cout << " MODO DE TESTE AUTOMATIZADO - MÓDULO C \n";
    cout << "=========================================================================\n";
    
    for (int t = 0; t < 3; t++) {
        int n = tamanhos[t];
        
        // 1. Alocação dinâmica dos vetores de teste
        Atleta* original = new Atleta[n];
        Atleta* copia = new Atleta[n];
        
        // 2. Preenchimento do vetor original com registros aleatórios de atletas
        for (int i = 0; i < n; i++) {
            original[i].id = i + 1;
            original[i].nome = "Atleta_" + to_string(i + 1);
            original[i].pontuacao = rand() % 10000; // Pontuações de 0 a 9999
        }
        
        cout << "\n-------------------------------------------------------------------------\n";
        cout << " TESTES COM " << n << " REGISTROS \n";
        cout << "-------------------------------------------------------------------------\n";
        
        // --- TESTE 1: QUICKSORT ---
        long long compQ = 0, trocasQ = 0;
        copiarVetorAtletas(original, copia, n);
        quickSort(copia, 0, n - 1, compQ, trocasQ);
        
        // --- TESTE 2: SELECTION SORT ---
        long long compS = 0, trocasS = 0;
        copiarVetorAtletas(original, copia, n);
        selectionSort(copia, n, compS, trocasS, false); // mostrar = false para não poluir o terminal
        
        // --- TESTE 3: INSERTION SORT ---
        long long compI = 0, trocasI = 0;
        copiarVetorAtletas(original, copia, n);
        insertionSort(copia, n, compI, trocasI, false);
        
        // Exibição formatada das métricas de Ordenação
        cout << left << setw(18) << "Algoritmo" << setw(22) << "Comparacoes" << setw(22) << "Trocas/Deslocamentos" << "\n";
        cout << "-------------------------------------------------------------------------\n";
        cout << left << setw(18) << "Quicksort" << setw(22) << compQ << setw(22) << trocasQ << "\n";
        cout << left << setw(18) << "Selection Sort" << setw(22) << compS << setw(22) << trocasS << "\n";
        cout << left << setw(18) << "Insertion Sort" << setw(22) << compI << setw(22) << trocasI << "\n";
        
        // --- TESTES DE PESQUISA ---
        // Seleciona a chave de um elemento central para testar a busca
        int chaveAlvo = original[n / 2].pontuacao;
        
        long long acessosSeq = 0;
        buscaSequencial(original, n, chaveAlvo, acessosSeq);
        
        long long acessosBin = 0;
        // A busca binária deve ser realizada no vetor ordenado (copia)
        buscaBinaria(copia, n, chaveAlvo, acessosBin);
        
        cout << "\n>>> COMPARATIVO DE BUSCA (Chave Procurada: " << chaveAlvo << " pts) <<<\n";
        cout << left << setw(25) << "Metodo de Busca" << setw(22) << "Acessos a Memoria" << "\n";
        cout << "-------------------------------------------------------------------------\n";
        cout << left << setw(25) << "Busca Sequencial" << setw(22) << acessosSeq << "\n";
        cout << left << setw(25) << "Busca Binaria" << setw(22) << acessosBin << "\n";
        
        // 3. Desalocação correta de memória
        delete[] original;
        delete[] copia;
    }
    
    cout << "=========================================================================\n\n";
}


