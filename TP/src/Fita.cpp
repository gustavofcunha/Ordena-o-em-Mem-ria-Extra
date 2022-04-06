#include "Fita.h"
#include <iostream>

/**
* -Descricao: construtor padrao
* -Entrada: N/A
* -Saida: N/A
*/
Fita::Fita(){
    numEntidades = 0;
    inicioVet = 0;
}

/**
* -Descricao: construtor que aloca vetor de entidades com numEntidades
* -Entrada: numEntidades
* -Saida: N/A
*/
void Fita::AlocaVetorEntidades (int numEntidades){
    entidades = new Entidade[numEntidades];
}

/**
* -Descricao: getter de numEntidades da classe Fita
* -Entrada: N/A
* -Saida: numEntidades
*/
int Fita::GetNumEntidades(){
    return numEntidades;
}

/**
* -Descricao: getter de entidades da classe Fita
* -Entrada: N/A
* -Saida: entidades
*/
Entidade* Fita::GetEntidades(){
    return entidades;
}

/**
* -Descricao: setter de entidades da classe Entidade
* -Entrada: _entidades
* -Saida: N/A
*/
void Fita::SetEntidades(Entidade *_entidades){
    entidades = _entidades;
}

/**
* -Descricao: setter de numEntidades da classe Entidade
* -Entrada: _numEntidades
* -Saida: N/A
*/
void Fita::IncrementaNumEntidades(){
    numEntidades = numEntidades + 1;
}

/**
* -Descricao: imprime todas as entidades da fita em stdout, linha por linha
* -Entrada: N/A
* -Saida: N/A
*/
void Fita::ImprimeFita(){
    int i;

    std::cout << std::endl;
    for(i=0; i<numEntidades; i++){
        std::cout << entidades[i].GetUrl() << " " 
        << entidades[i].GetNumAcessos() << std::endl;
    }
}

/**
* -Descricao: imprime todas as entidades da fita em arquivo, linha por linha
* -Entrada: arquivo
* -Saida: N/A
*/
void Fita::ImprimeFitaArquivo(std::ofstream &arquivo){
    int i;

    for(i=0; i<numEntidades; i++){
        arquivo << entidades[i].GetUrl() << " " 
        << entidades[i].GetNumAcessos() << std::endl;
    }
}

/**
* -Descricao: remove ultimo elemento do vetor de entidades de Fita
* -Entrada: N/A
* -Saida: ultimo
*/
Entidade Fita::PopFront(){
    Entidade primeiro;
    primeiro = entidades[inicioVet];
    numEntidades--;
    inicioVet++;
    return primeiro;
}

/**
* -Descricao: para cada elemento do vetor de entidades, verifica
*  se ha empates no numero de acessos com elementos seguintes
*  se houver empates e a ordem alfabetica das urls estiver errada,
*  troca os elementos de lugar desempatando e ordenando 
*  de acordo com a ordem alfabetica
* -Entrada: N/A
* -Saida: N/A
*/
void Fita::Compara(){
    int i,j;
    Entidade aux;
 
    for(i=0; i<numEntidades; i++){
        for(j=i+1; j<numEntidades; j++){
            //se elementos empatam na url
            if(entidades[i].GetNumAcessos() == entidades[j].GetNumAcessos()){
                //se a ordem alfabetica estiver errada
                if(entidades[i].GetUrl() > entidades[j].GetUrl()){
                    //troca elementos
                    aux = entidades[i];
                    entidades[i] = entidades[j];
                    entidades[j] = aux;
                }
            }
        }
    }
}

/**
* -Descricao: verifica a fita esta vazia e retorna 
*  valor booleano de acordo com a condicao verificada
*  a definicao de vazia eh nao possuir nenhuma entidade no vetor entidades
*  ou possuir uma entidade 'invalida'
* -Entrada: N/A
* -Saida: true (caso esteja vazio) / false(caso nao esteja vazio)
*/
bool Fita::Vazia(){
    if(numEntidades == 0){
        return true;
    }
    else if(numEntidades == 1 && (entidades[0].GetUrl() == "")){
        return true;
    }
    else{
        return false;
    }
}