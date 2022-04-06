#include "Heap.h"
#include "msgassert.h"
#include <iostream>

/**
* -Descricao: construtor que aloca vetor de entidades de tamanho maxTam
* -Entrada: maxTam
* -Saida: N/A
*/
Heap::Heap(int maxTam){
    vet = new Entidade[maxTam];
    tamVet = 0;
}

/**
* -Descricao: refaz o heap em vet de acordo com os limites Esq e Dir definidos, 
*  de forma a manter a especificacao da estrutura de dados
* -Entrada: Esq, Dir
* -Saida: N/A
*/
void Heap::Refaz(int Esq, int Dir){
    int i,j;
    Entidade x;
    i = Esq;
    j = i*2;
    x = vet[i];

    while(j<=Dir){ //se j ainda eh elemento valido do heap
        if(j<Dir){ //se j tem irmao a direita
            //j recebe indice do maior filho
            if(vet[j].GetNumAcessos() < vet[j+1].GetNumAcessos()) j++;
        }
        if (x.GetNumAcessos() >= vet[j].GetNumAcessos()) break;
        vet[i] = vet[j];
        i = j; 
        j = i *2;   
    }
    vet[i] = x;
}

/**
* -Descricao: adiciona entidade ao heap, 
*  de forma a manter a especificacao da estrutura de dados
* -Entrada: entidade
* -Saida: N/A
*/
void Heap::Add(Entidade entidade){
    //adicao de entidade ao final do vetor vet do heap
    vet[tamVet] = entidade;

    //troca do ultimo elemento com o primeiro
    Entidade aux;
    aux = vet[0];
    vet[0] = vet[tamVet];
    vet[tamVet] = aux;

    tamVet++;

    int Esq;
    //primeira folha
    Esq = (tamVet/2) + 1;

    //refaz o vetor a partir do primeiro no interno
    while(Esq>0){
        Esq--;
        Refaz(Esq, tamVet-1);
    }
}

/**
* -Descricao: retira e retorna o elemento de maior numero de acessos do heap
* -Entrada: N/A
* -Saida: maximo
*/
Entidade Heap::Pop(){
    //retira o maior elemento
    Entidade Maximo;
    erroAssert(tamVet>0, "Erro: heap vazio");
    Maximo = vet[0]; 
    vet[0] = vet[tamVet-1]; 
    tamVet--;
    Refaz(0, tamVet-1);
    return Maximo;
}

/**
* -Descricao: verifica se heap esta vazio ou nao e retorna 
*  valor booleano de acordo com a condicao verificada
* -Entrada: N/A
* -Saida: true (caso esteja vazio) / false(caso nao esteja vazio)
*/
bool Heap::Vazio(){
    if(tamVet>0){
        return false;
    }

    return true;
}

/**
* -Descricao: verifica se heap esta vazio ou nao e retorna 
*  valor booleano de acordo com a condicao verificada
* -Entrada: N/A
* -Saida: true (caso esteja vazio) / false(caso nao esteja vazio)
*/
void Heap::ImprimeHeap(){
    std::cout << std::endl << "Impressao do heap:" << std::endl;
    for(int i=0; i<tamVet; i++){
        vet[i].ImprimeEntidade();
    }
    std::cout << "Fim da impressao do heap." << std::endl;
}

/**
* -Descricao: para cada elemento do vetor vet, verifica
*  se ha empates no numero de acessos com elementos seguintes
*  se houver empates e a ordem alfabetica das urls estiver errada,
*  troca os elementos de lugar desempatando e ordenando 
*  de acordo com a ordem alfabetica
* -Entrada: N/A
* -Saida: N/A
*/
void Heap::Compara(){
    int i,j;
    Entidade aux;

    for(i=0; i<tamVet; i++){
        for(j=i+1; j<tamVet; j++){
            //se elementos empatam na url
            if(vet[i].GetNumAcessos() == vet[j].GetNumAcessos()){
                //se a ordem alfabetica estiver errada
                if(vet[i].GetUrl() > vet[j].GetUrl()){
                    //troca elementos
                    aux = vet[i];
                    vet[i] = vet[j];
                    vet[j] = aux;
                }
            }
        }
    }
}