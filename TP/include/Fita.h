#ifndef FITA_H
#define FITA_H

#include "Entidade.h"
#include <fstream>
#include <iostream>

class Fita{
    public:
        Fita();
        void AlocaVetorEntidades(int _numEntidades);
        int GetNumEntidades();
        Entidade* GetEntidades();
        void SetEntidades(Entidade *_entidades);
        void IncrementaNumEntidades();
        void ImprimeFita();
        void ImprimeFitaArquivo(std::ofstream &arquivo);
        Entidade PopFront();
        void Compara();
        bool Vazia();
        
    private:
        int inicioVet;
        int numEntidades;
        Entidade *entidades;
};

#endif