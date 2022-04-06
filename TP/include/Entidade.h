#ifndef ENTIDADE_H
#define ENTIDADE_H

#include <string>

class Entidade{
    public:
        Entidade();
        int GetNumAcessos();
        int GetIndiceFitaOrigem();
        std::string GetUrl();
        void SetNumAcessos(int _numAcessos);
        void SetUrl(std::string _url);
        void SetIndiceFitaOrigem(int _indiceFitaOrigem);
        void ImprimeEntidade();
        void ImprimeArquivo(std::ofstream &arquivo);

    private:
        std::string url;
        int numAcessos;
        int indiceFitaOrigem;
    friend class Fita;
};

#endif