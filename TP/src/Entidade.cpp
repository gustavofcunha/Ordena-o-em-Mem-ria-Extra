#include "Entidade.h"
#include <iostream>
#include<fstream>

/**
* -Descricao: construtor padrao
* -Entrada: N/A
* -Saida: N/A
*/
Entidade::Entidade(){
    //estado da entidade considerado 'invalido'
    numAcessos = 0;
    url = "";
}

/**
* -Descricao: getter de numAcessos da classe Entidade
* -Entrada: N/A
* -Saida: numAcessos
*/
int Entidade::GetNumAcessos(){
    return numAcessos;
}

/**
* -Descricao: getter de url da classe Entidade
* -Entrada: N/A
* -Saida: url
*/
std::string Entidade::GetUrl(){
    return url;
}

/**
* -Descricao: setter de numAcessos da classe Entidade
* -Entrada: _numAcessos
* -Saida: N/A
*/
void Entidade::SetNumAcessos(int _numAcessos){
    numAcessos = _numAcessos;
}

/**
* -Descricao: setter de url da classe Entidade
* -Entrada: _url
* -Saida: N/A
*/
void Entidade::SetUrl(std::string _url){
    url = _url;
}

/**
* -Descricao: getter de indiceFitaOrigem da classe Entidade
* -Entrada: N/A
* -Saida: indiceFitaOrigem
*/
int Entidade::GetIndiceFitaOrigem(){
    return indiceFitaOrigem;
}

/**
* -Descricao: setter de indiceFitaOrigem da classe Entidade
* -Entrada: _indiceFitaOrigem
* -Saida: N/A
*/
void Entidade::SetIndiceFitaOrigem(int _indiceFitaOrigem){
    indiceFitaOrigem = _indiceFitaOrigem;
}

/**
* -Descricao: imprime a entidade em arquivo
* -Entrada: arquivo
* -Saida: N/A
*/
void Entidade::ImprimeEntidade(){
    std::cout << url << " " << numAcessos << std::endl;
}

/**
* -Descricao: imprime a entidade em arquivo
* -Entrada: arquivo
* -Saida: N/A
*/
void Entidade::ImprimeArquivo(std::ofstream &arquivo){
    arquivo << url << " " << numAcessos << std::endl;
}