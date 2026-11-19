#include <iostream>
#include <string>
#include <list>
#include <queue>
#include "arvore.hpp"
#include "atletas.hpp"
#include "ordenacao_pesquisa.hpp"
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Função auxiliar para inicializar o vetor base de atletas com IDs sequenciais e pontuação zerada
void carregarRegistros(Atleta vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i].id = i + 1;
        vetor[i].nome = "atleta " + to_string(i + 1);
        vetor[i].pontuacao = 0.0; 
    }
}

int main() {
    srand(time(0)); // Inicializa a semente de números aleatórios

    Atleta* atletas = nullptr; // Ponteiro para armazenar o vetor de atletas alocado dinamicamente
    int opcao = 0;             // Armazena a opção escolhida pelo usuário no menu principal
    int tamanho = 0;           // Armazena a quantidade de registros do torneio (50, 500 ou 5000)
    
    queue<Atleta> filaEspera;        // Fila padrão do C++ para gerenciar a ordem de largada da prova
    list<Atleta> listaAtletas;        // Lista duplamente encadeada padrão para navegação e desclassificação
    ArvoreBinariaBusca arvoreAtletas; // Instância da Árvore Binária de Busca organizada por ID

    // Loop principal do menu interativo
    do {
        cout << "\n==============================================" << endl;
        cout << "           Gerenciamento do Torneio";
        cout << "\n==============================================" << endl;
        cout << "1. Registrar atletas (50, 500 ou 5.000)." << endl;
        cout << "2. Realizar prova do primeiro atleta na fila." << endl;
        cout << "3. Inserir um atleta na lista." << endl;
        cout << "4. Remover um atleta na lista (Desclassificar)." << endl;
        cout << "5. Navegar na lista (proximo, anterior)." << endl;
        cout << "6. Gerenciar ABB (Inserir ID, Buscar, Remover 3 Casos, Listar, Altura)." << endl;
        cout << "7. Ordenar Atletas por Pontuacao (QuickSort, Selection, Insertion)." << endl;
        cout << "8. Executar Modo de Teste Automatizado (Relatorio completo)." << endl;
        cout << "0. Encerrar programa." << endl;
        cout << "==============================================" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch(opcao) {
            case 0: 
                break; // Encerra o loop do menu

            case 1: { // Opção 1: Criação e carregamento da massa de dados inicial
                cout << "Quantos atletas quer registrar? 50, 500 ou 5.000: ";
                cin >> tamanho;

                if (tamanho != 50 && tamanho != 500 && tamanho != 5000) {
                    cout << "Quantidade invalida." << endl;
                    break;
                }
                if (atletas != nullptr) {
                    delete[] atletas; // Libera vetor anterior se já existia
                }
                    
                atletas = new Atleta[tamanho];
                carregarRegistros(atletas, tamanho);
                cout << tamanho << " registros foram criados!" << endl;

                while (!filaEspera.empty()) { 
                    filaEspera.pop(); // Esvazia a fila antiga
                }
                listaAtletas.clear(); // Esvazia a lista antiga

                // Passa os registros para a Fila e para a Lista Dupla
                for (int i = 0; i < tamanho; i++) {
                    filaEspera.push(atletas[i]);
                    listaAtletas.push_back(atletas[i]);
                }
                break;
            }

            case 2: { // Opção 2: Tira o primeiro atleta da fila, gera nota e insere o ID na ABB
                if (filaEspera.empty()) {
                    cout << "Erro: fila vazia" << endl;
                    break;
                }

                Atleta atual = filaEspera.front(); // Pega o primeiro da fila
                filaEspera.pop();                  // Remove ele da fila

                double pontuacaoGerada = (rand() % 501 + 500) / 10.0; // Gera nota aleatória entre 50.0 e 100.0

                if (atletas != nullptr && (atual.id - 1) < tamanho) {
                    atletas[atual.id - 1].pontuacao = pontuacaoGerada;
                }

                // Atualiza a pontuação também na lista duplamente encadeada
                for (auto& a : listaAtletas) {
                    if (a.id == atual.id) {
                        a.pontuacao = pontuacaoGerada; 
                        break;
                    }
                }

                // Insere automaticamente o ID na ABB após o término da prova
                arvoreAtletas.inserir(atual.id);

                cout << "Prova realizada e ID inserido na ABB!" << endl;
                cout << "Atleta: ID " << atual.id << " | Nome: " << atual.nome << " | Nota: " << pontuacaoGerada << endl;

                if (!filaEspera.empty()) {
                    cout << "Proximo na fila: " << filaEspera.front().nome << endl;
                } else {
                    cout << "Este foi o ultimo atleta da fila." << endl;
                }
                cout << "Atletas ainda esperando na fila: " << filaEspera.size() << endl;
                break;
            }

            case 3: { // Opção 3: Inserção manual de um novo atleta
                Atleta novoAtleta;
                tamanho++;
                novoAtleta.id = tamanho;
                novoAtleta.nome = "atleta " + to_string(tamanho);
                novoAtleta.pontuacao = 0.0;

                listaAtletas.push_back(novoAtleta);
                filaEspera.push(novoAtleta);

                cout << novoAtleta.nome << " inserido na lista e fila. ID: " << novoAtleta.id << endl;
                break;
            }

            case 4: { // Opção 4: Desclassificação / Remoção de um atleta da lista por ID
                if (listaAtletas.empty()) {
                    cout << "Erro: lista vazia." << endl;
                    break;
                }

                int idBusca;
                cout << "Digite o ID do atleta a ser desclassificado: ";
                cin >> idBusca;

                bool encontrado = false;
                for (auto atual = listaAtletas.begin(); atual != listaAtletas.end(); atual++) {
                    if (atual->id == idBusca) {
                        listaAtletas.erase(atual); // Remove da lista encadeada
                        encontrado = true;
                        cout << "Atleta com ID " << idBusca << " desclassificado do torneio." << endl;
                        break;
                    }
                }

                if (!encontrado) {
                    cout << "O ID " << idBusca << " nao foi encontrado nos registros." << endl;
                }
                break;
            }

            case 5: { // Opção 5: Navegação interativa bidirecional na lista duplamente encadeada
                if (listaAtletas.empty()) {
                    cout << "Erro: lista vazia." << endl;
                    break;
                }

                auto atual = listaAtletas.begin(); 
                char comando = ' ';

                cout << "\n==== Navegacao com lista dupla ====" << endl;  
                cout << "ID: " << atual->id << " | Nome: " << atual->nome << " | Pontuacao: " << atual->pontuacao << endl;

                while (true) {
                    cout << "Comandos: [d] = proximo, [e] = anterior. Outra tecla = sair: ";
                    cin >> comando;

                    if (comando == 'd') {
                        auto proximo = atual;
                        ++proximo;
                        if (proximo != listaAtletas.end()) {
                            atual = proximo;
                            cout << "ID: " << atual->id << " | Nome: " << atual->nome << " | Pontuacao: " << atual->pontuacao << endl;
                        } else {
                            cout << "Voce ja esta no ultimo atleta!" << endl;
                        }
                    } else if (comando == 'e') {
                        if (atual != listaAtletas.begin()) {
                            --atual;
                            cout << "ID: " << atual->id << " | Nome: " << atual->nome << " | Pontuacao: " << atual->pontuacao << endl;
                        } else {
                            cout << "Voce ja esta no primeiro atleta!" << endl;
                        }
                    } else {
                        cout << "Saindo da navegacao." << endl;
                        break;
                    }
                }
                break;
            }

            case 6: { // Opção 6: Sub-menu interativo exclusivo para a Árvore Binária de Busca (ABB)
                int opArvore;
                do {
                    cout << "\n--- MODULO ARVORE BINARIA DE BUSCA (ABB) ---\n";
                    cout << "1. Inserir ID na ABB\n";
                    cout << "2. Buscar ID na ABB\n";
                    cout << "3. Remover ID na ABB (3 Casos)\n";
                    cout << "4. Listar IDs em Ordem (In-Order)\n";
                    cout << "5. Mostrar Altura e Quantidade de Nos\n";
                    cout << "0. Voltar ao Menu Principal\n";
                    cout << "Escolha: ";
                    cin >> opArvore;

                    if (opArvore == 1) {
                        int idVal;
                        cout << "Digite o ID para inserir na ABB: "; cin >> idVal;
                        arvoreAtletas.inserir(idVal);
                        cout << ">>> ID inserido na ABB!\n";
                    } else if (opArvore == 2) {
                        int idVal;
                        cout << "Digite o ID para buscar: "; cin >> idVal;
                        if (arvoreAtletas.buscar(idVal)) cout << ">>> ID encontrado na ABB!\n";
                        else cout << ">>> ID NAO encontrado.\n";
                    } else if (opArvore == 3) {
                        int idVal;
                        cout << "Digite o ID para remover (3 Casos): "; cin >> idVal;
                        if (arvoreAtletas.remover(idVal)) cout << ">>> Removido com sucesso!\n";
                        else cout << ">>> ID nao encontrado.\n";
                    } else if (opArvore == 4) {
                        cout << "\n--- LISTAGEM EM ORDEM (ABB) ---\n";
                        if (arvoreAtletas.estaVazia()) cout << "ABB vazia.\n";
                        else arvoreAtletas.imprimirEmOrdem();
                        cout << "\n";
                    } else if (opArvore == 5) {
                        cout << "Quantidade de Nos: " << arvoreAtletas.getTamanho() << "\n";
                        cout << "Altura da ABB: " << arvoreAtletas.getAltura() << "\n";
                    }
                } while (opArvore != 0);
                break;
            }

            case 7: { // Opção 7: Módulo de Ordenação por Pontuação
                if (tamanho == 0 || atletas == nullptr) {
                    cout << "Erro: Nenhum registro criado. Use a opcao 1 primeiro." << endl;
                    break;
                }
                
                Atleta* copiaOrdenacao = new Atleta[tamanho];
                copiarVetorAtletas(atletas, copiaOrdenacao, tamanho);

                long long comp = 0, trocas = 0;
                cout << "\nEscolha o metodo de ordenacao:\n";
                cout << "1. QuickSort\n2. Selection Sort\n3. Insertion Sort\nOpcao: ";
                int opOrd; cin >> opOrd;

                if (opOrd == 1) quickSort(copiaOrdenacao, 0, tamanho - 1, comp, trocas);
                else if (opOrd == 2) selectionSort(copiaOrdenacao, tamanho, comp, trocas, false);
                else if (opOrd == 3) insertionSort(copiaOrdenacao, tamanho, comp, trocas, false);
                else { cout << "Opcao invalida!\n"; delete[] copiaOrdenacao; break; }

                cout << "\nOrdenacao concluida!\n";
                cout << "Comparacoes: " << comp << " | Trocas/Deslocamentos: " << trocas << endl;
                
                cout << "Deseja imprimir os primeiros 10 atletas ordenados? (1-Sim / 0-Nao): ";
                int imp; cin >> imp;
                if (imp == 1) imprimeVetorAtletas_Pont(copiaOrdenacao, (tamanho < 10 ? tamanho : 10));

                delete[] copiaOrdenacao; // Libera a cópia temporária
                break;
            }

            case 8: { // Opção 8: Execução dos testes automatizados exigidos no relatório
                executarModoTeste();
                break;
            }

            default: {
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
            }
        }
    } while (opcao != 0);

    cout << "\nSaindo..." << endl;
    if (atletas != nullptr) {
        delete[] atletas; // Libera o vetor principal ao fechar o programa
    }
    return 0;
}