#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include "Entidade.h"

class Heap{
    public:
        Heap(int maxTam);
        void Refaz(int Esq, int Dir);
        void Add(Entidade entidade);
        Entidade Pop();
        bool Vazio();
        void ImprimeHeap();
        void Compara();
    private:
        Entidade *vet;
        int tamVet;
};

#endif