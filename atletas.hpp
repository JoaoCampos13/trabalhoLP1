#ifndef ATLETAS_HPP
#define ATLETAS_HPP

#include<string>
using namespace std;

struct Atleta{//criar o perfil de um atleta. 
    int id;//id que é gerado quando o atleta é criado
    string nome;
    float pontuacao; //pontuacao de acordo com a classificação do atleta.
};

#endif