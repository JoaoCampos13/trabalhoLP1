#include <iostream>
#include <string>
#include <list>//biblioteca da lista
#include <queue>//biblioteca da fila
#include "arvore.hpp"//incluir arquivo da arvore binária
#include "atletas.hpp"//incluir arquivo com a struct Atleta
#include "ordenacao.hpp"//incluir arquivo de ordenação
#include <cstdlib>//para poder usar o rand() para sortear a pontuação dos atletas.
#include <ctime>//para poder usar o rand() para sortear a pontuação dos atletas.
using namespace std;

void carregarRegistros(Atleta vetor[],int tamanho){//Registra os atletas, 50, 500 ou 5.000.
    for(int i=0;i<tamanho;i++){
        vetor[i].id = i + 1;//inicia cada atleta com um id em ordem crescente.
        vetor[i].nome = "atleta " + to_string(i+1);//serve para inserir um nome na string. Sugestao de IA.
        vetor[i].pontuacao = 0.0;//inicia a pontuação com 0. 
    }
}

int main(){
    srand(time(0));

    Atleta* atletas = nullptr;//inicializar o vetor de atletas com nullptr;
    int opcao; //opcao do menu. 
    int tamanho = 0;//saber quantos atletas farão registro.
    
    queue<Atleta> filaEspera;//Cria uma fila com os atletas registrados.
    list<Atleta> listaAtletas;//Cria uma lista dupla com os atletas registrados. 

    //Menu.
    do{
        cout<<"\n=============================================="<<endl;
        cout<<"           Gerenciamento do Torneio";
        cout<<"\n=============================================="<<endl;
        cout<<"1. Registrar atletas."<<endl;//registro inicial de 50,500 ou 5.000 atletas.
        cout<<"2. Realizar prova do primeiro atleta na fila."<<endl;//realizar prova usando fila.
        cout<<"3. Inserir um atleta na lista."<<endl;//inserir usando lista dupla.
        cout<<"4. Remover um atleta na lista."<<endl;//Remover usando lista dupla.
        cout<<"5. Navegar na lista (proximo, anterior)."<<endl;//navegar usando lista dupla.
        cout<<"0. Encerrar programa."<<endl;//opcao de saída.
        cout<<"=============================================="<<endl;
        cin>>opcao;


        switch(opcao){
            case 0: break;

            case 1: {//registrar atletas.
                cout<<"Quantos atletas quer registrar? 50, 500 ou 5.000"<<endl;
                cin>> tamanho;

                if(tamanho != 50 && tamanho != 500 && tamanho != 5000){//ver se é um dos valores aceitos.
                    cout<<"Quantidade invalida."<<endl;
                    break;
                }
                if(atletas != nullptr){
                    delete[] atletas;//caso já exista um vetor alocado.
                }

                    
                atletas = new Atleta[tamanho];//Alocar vetor dessa quantidade de atletas.
                carregarRegistros(atletas, tamanho);//carregar o registro.
                cout<< tamanho <<" registros foram criados!"<<endl;

                while(!filaEspera.empty()){//esvaziar a fila antiga se ainda tiver alguma coisa.
                    filaEspera.pop();
                }

                listaAtletas.clear();//esvaziar a lista caso ja exista.

                for(int i=0;i<tamanho;i++){
                    filaEspera.push(atletas[i]);//passa todos os atletas do vetor para a fila. 
                    listaAtletas.push_back(atletas[i]);//passa todos os atletas para a lista.
                }
                
                break;
            }

            case 2:{
                if(filaEspera.empty()){//verificar se tem alguma coisa na fila
                    cout<<"Erro: fila vazia"<<endl;
                    break;
                }

                Atleta atual = filaEspera.front();//pega o primeiro atleta da fila e "coloca ele pra correr"
                filaEspera.pop();//retira esse atleta da fila.

                double pontuacaoGerada = (rand() % 501 + 500)/10.0;//gera nota aleatória entre 50 e 100

                if(atletas != nullptr && (atual.id - 1) < tamanho){
                    atletas[atual.id - 1].pontuacao = pontuacaoGerada;
                }

                for(auto& a : listaAtletas){//procura dentro da lista alguem com o ID igual a do atual. 
                    if(a.id == atual.id){
                        a.pontuacao = pontuacaoGerada;//se achar dá a pontuacao. 
                        break;
                    }
                }
                cout<<"Prova realizada!"<<endl;
                cout<<"Atleta que realizou: ID "<<atual.id<<" | Nome: "<<atual.nome<<" | Nota: "<<pontuacaoGerada<<endl;

                //Mostrar o proximo na fila e quantos restam.
                if(!filaEspera.empty()){
                    cout<<"O nome do proximo atleta e: "<<filaEspera.front().nome<<endl;
                }else{
                    cout<<"Este foi o ultimo atleta da fila."<<endl;
                }

                cout<<"Atletas ainda esperando na fila: "<<filaEspera.size()<<endl;

                break;
            }

            case 3:{
                Atleta novoAtleta;//cria um novo atleta.
                tamanho++;//o id do atleta vai ser o tamanho atual mais um.
                novoAtleta.id = tamanho;
                novoAtleta.nome = "atleta " + to_string(tamanho);//nome do atleta.
                novoAtleta.pontuacao = 0.0;

                listaAtletas.push_back(novoAtleta);//o atleta é inserido no final para seguir a ordem do ID.
                filaEspera.push(novoAtleta);//adicionar a fila de espera.

                cout<<novoAtleta.nome<<" inserido na lista. ID: "<<novoAtleta.id<<endl;
                
                break;
            }

            case 4:{
                if(listaAtletas.empty()){
                    cout<<"Erro: lista vazia."<<endl;
                    break;
                }

                int idBusca;
                cout<<"Digite o ID do atleta a ser desclassificado."<<endl;
                cin>>idBusca;

                bool encontrado = false;//inicia encontrado com falso.
                //serve para procurar dentro da lista se existe um atleta com o indice digitado.
                for(auto atual = listaAtletas.begin(); atual != listaAtletas.end();atual++){
                    if(atual->id == idBusca){
                        listaAtletas.erase(atual);
                        encontrado = true;
                        cout<< "atleta com ID "<<idBusca<<" desclassificado do torneio."<<endl;
                        break;
                    }
                }

                //caso o id não seja encontrado.
                if(!encontrado){
                    cout<<"O id "<< idBusca<<" nao foi encontrado nos registros do torneio."<<endl;
                }
                break;
            }

            case 5: {
                // 1. Validação inicial: verifica se a lista está vazia antes de iniciar a navegação
                if(listaAtletas.empty()){
                    cout<<"Erro: lista vazia."<<endl;
                    break;
                }

                // 2. Cria um iterador (cursor) posicionado no início da lista e uma variável para os comandos do usuário
                auto atual = listaAtletas.begin(); // Começa pelo primeiro elemento da lista dupla
                char comando = ' ';

                // 3. Exibe o cabeçalho da navegação e os dados do primeiro atleta atual
                cout<<"\n====Navegacao com lista dupla===="<<endl;  
                cout<<"Atleta atual:"<<endl;
                cout<<"ID: "<<atual->id<<" | Nome: "<<atual->nome<<" Pontuacao: "<<atual->pontuacao<<endl;

                // 4. Loop de navegação interativa (permite avançar ou voltar repetidamente)
                while(true){
                    cout<<"Comandos(Minusculo): [d] = proximo, [e] = anterior. Use qualquer digito para sair."<<endl;
                    cout<<"Escolha: ";
                    cin>>comando;

                    // 5. Opção para avançar para o próximo elemento da lista dupla
                    if(comando == 'd'){
                        auto proximo = atual; // Cria uma cópia temporária do iterador atual
                        ++proximo; // Move a cópia para a frente
                        
                        // Verifica se a cópia não ultrapassou o fim da lista
                        if(proximo != listaAtletas.end()){
                            atual = proximo; // Atualiza o iterador oficial para a nova posição
                            cout<<"\nIndo para o proximo."<<endl;
                            cout << "ID: " << atual->id << " | Nome: " << atual->nome << " | Pontuacao: " << atual->pontuacao << endl;
                        }else{
                            cout<<"Voce ja esta no ultimo atleta da lista!"<<endl;
                        }
                    }
                    // 6. Opção para voltar para o elemento anterior (aproveitando o encadeamento duplo)
                    else if(comando == 'e'){
                        // Verifica se o iterador não está no início absoluto da lista
                        if(atual != listaAtletas.begin()){
                            --atual; // Recua o iterador diretamente para o elemento anterior
                            cout<<"\nIndo para o anterior."<<endl;
                            cout << "ID: " << atual->id << " | Nome: " << atual->nome << " | Pontuacao: " << atual->pontuacao << endl;
                        }else{
                            cout<<"Voce ja esta no primeiro atleta da lista.!"<<endl;
                        }
                    }
                    // 7. Qualquer outra tecla encerra o loop de navegação e retorna ao menu principal
                    else{
                        cout<<"Saindo da navegacao."<<endl;
                        break;
                    }
                }

                break;
            }

            default: {
                cout<<"opcao invalida. Tente novamente."<<endl;
                break;
            }

        }
    }while(opcao!=0);//encerrando o programa. 
    cout<<"\nSaindo..."<<endl;

    if(atletas != nullptr){//liberar o vetor de atletas caso exista alguma coisa
        delete[] atletas;
    }
    return 0;
}