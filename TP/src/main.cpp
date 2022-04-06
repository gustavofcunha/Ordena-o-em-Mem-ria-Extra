#include <iostream>
#include <string>
#include <fstream>
#include "memlog.h"
#include "Entidade.h"
#include "Fita.h"
#include "Heap.h"
#include "msgassert.h"

/**
* -Descricao: conta e retona numero de linhas de arquivo 
* -Entrada: arquivo
* -Saida: cont
*/
int contaLinhasArquivo(std::ifstream &arquivo){
    int cont = 0;
    std::string buf;
    while(getline(arquivo, buf)){
        cont++;
    }
    return cont;
}

/**
* -Descricao: reconhece e diferencia URL e numero de acessos de 
*  uma string que representa uma entidade e aloca a 
*  entidade com os atributos reconhecios
* -Entrada: buf
* -Saida: entidade
*/
Entidade geraEntidade(std::string buf, int _indiceFitaOrigem){ 
    std::string url, aux;
    int numAcessos;
    Entidade entidade;

    //ponteiro para o espaco na string recebida
    std::size_t pos = buf.find_first_of(" ");

    //corta a string em duas, uma parte representa a 
    //URL e a outra o numero de acessos
    url = buf;
    url.erase(pos);

    aux = buf.substr(pos+1);
    numAcessos = stoi(aux);

    //instanciacao dos atributos de entidade
    entidade.SetUrl(url);
    entidade.SetNumAcessos(numAcessos);
    entidade.SetIndiceFitaOrigem(_indiceFitaOrigem);
    return entidade;
}

/**
* -Descricao: calcula mediana de tres entidades, com base em seu atributo numAcessos
* -Entrada: a, b, c
* -Saida: vet[1] (elemento central do vetor com os tres elementos ordenados)
*/
Entidade mediana(Entidade a, Entidade b, Entidade c){
    //variaveis auxiliares
    Entidade aux;
    Entidade vet[3];
    vet[0] = a;
    vet[1] = b;
    vet[2] = c;

    //comparacoes para ordenacao de vet
    if(vet[0].GetNumAcessos()>vet[1].GetNumAcessos()){
        aux = vet[0];
        vet[0] = vet[1];
        vet[1] = aux;
    }

    if(vet[1].GetNumAcessos()>vet[2].GetNumAcessos()){
        aux = vet[1];
        vet[1] = vet[2];
        vet[2] = aux;
    }

    //retorna o elemento central
    return vet[1];
}

/**
* -Descricao: funcao auxiliar de QuickSort, 
*  responsavel por gerar particoes
* -Entrada: Esq, Dir, i, j, A
* -Saida: N/A
*/
void Particao(int Esq, int Dir, int *i, int *j, Entidade *A){ 
    Entidade x, w;
    *i = Esq; *j = Dir;
    x = mediana(A[Esq], A[Dir/2], A[Dir]); //pivo mediana de tres
    do{ 
        while (x.GetNumAcessos() < A[*i].GetNumAcessos()) (*i)++;
        while (x.GetNumAcessos() > A[*j].GetNumAcessos()) (*j)--;
        if (*i <= *j){ 
            //troca de elementos
            w = A[*i]; A[*i] = A[*j]; A[*j] = w;
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

/**
* -Descricao: funcao recursiva auxiliar de QuickSort, 
*  responsavel por ordenar as particoes
* -Entrada: Esq, Dir, A
* -Saida: N/A
*/
void Ordena(int Esq, int Dir, Entidade *A){
    int i,j;
    Particao(Esq, Dir, &i, &j, A);
    if (Esq < j) Ordena(Esq, j, A);
    if (i < Dir) Ordena(i, Dir, A);
}

/**
* -Descricao: ordenacao do vetor de Entidade A, 
*  de acordo com a Chave de seus itens
* -Entrada: A (referencia), n(tamanho do vetor)
* -Saida: N/A
*/
void QuickSort(Entidade *A, int n){ 
    Ordena(0, n-1, A); 
}


/**
* -Descricao: ordena vetor de Entidade da fita de forma crescente 
*  de acordo com o numero de acessos,
*  utilizando algoritmo de ordenacao Quicksort
* -Entrada: fita (referencia)
* -Saida: N/A
*/
void ordenaFita(Fita &fita){
    QuickSort(fita.GetEntidades(), fita.GetNumEntidades());
}

/**
* -Descricao: transcreve fita para um arquivo de 
*  nome "rodada-n.txt”, localizado no diretorio fitas do TP
   onde n eh substituido por indiceFita
* -Entrada: fita, indiceFita
* -Saida: N/A
*/
void transcreveFita(Fita fita, int indiceFita){
    //variaveis auxiliares
    std::ofstream arquivoRodada;
    std::string nomeArquivoRodada;
    nomeArquivoRodada = "rodada-" + std::to_string(indiceFita+1);
    nomeArquivoRodada.append(".txt");

    //abertura do arquivo de rodada referente a Fita
    arquivoRodada.open(nomeArquivoRodada);
    erroAssert(arquivoRodada.is_open(), 
        "ERRO: Nao foi possivel abrir os arquivos de rodadas (fitas)");

    for(int i=0; i<fita.GetNumEntidades(); i++){
        if(fita.GetEntidades()[i].GetUrl() != ""){
            arquivoRodada << fita.GetEntidades()[i].GetUrl() 
            << " " << fita.GetEntidades()[i].GetNumAcessos() << std::endl;
        }
    }

    //fechamento do arquivo de rodada referente a Fita
    arquivoRodada.close();
}

/**
* -Descricao: gera os numFitas arquivos (chamados rodadas)
*  referente as Fitas com numEntidades Entidades internas ja ordenadas;
*  ordena as entidades nas fitas; transcreve cada fita para um arquivo
* -Entrada: arquivoEntrada, numEntidades, numFitas
* -Saida: N/A
*/
void geraRodadas(Fita *fitas, std::ifstream &arquivoEntrada,
                 int numEntidades, int numLinhas, int &numFitas){
    //variaveis auxiliares
    int i,j;
    std::string buf;

    //leitura das numFitas Fitas com numEntidades cada
    //as fitas serao colocadas no vetor de Fitas fitas
    for(i=0; i<numFitas; i++){
        for(j=0; j<numEntidades; j++){
            if(numLinhas>0){
                getline(arquivoEntrada, buf);
                fitas[i].GetEntidades()[j] = geraEntidade(buf, i);
                fitas[i].IncrementaNumEntidades();
                numLinhas--;
            }
        }
    }
    
    //ordenacao e transcricao em arquivo de cada Fita em fitas
    for(i=0; i<numFitas; i++){
        //se a fota tiver mais de uma entidade, ela sera ordenada usando QuickSort
        if(fitas[i].GetNumEntidades() > 1){
            ordenaFita(fitas[i]);
        }
        //funcao que mitiga possiveis empates, 
        //desempatando com a ordem alfabetica das urls
        fitas[i].Compara();
        //transcreve a fita gerada para um arquivo, caso a fita nao esteja vazia
        if(!fitas[i].Vazia()){
            transcreveFita(fitas[i], i);
        }
        //se a fita estiver vazia, ela sera desconsiderada no escopo global do algoritmo
        //(numFitas eh referencia, nessa funcao)
        else{
            numFitas--;
        }
    }
}

/**
* -Descricao: intercala as entidades nas fitas geradas em geraRodadas 
*  através de um heap
* -Entrada: fitas, numFitas, heap, arquivoSaida
* -Saida: N/A
*/
void intercalaRodadas(Fita *fitas, int numFitas, Heap *heap, 
                      std::ofstream &arquivoSaida){
    int i;
    Entidade aux, aux2, aux3;
    int indiceOrigem;

    //adiciona as ultimas entidades de cada fita ao heap
    for(i=0; i<numFitas; i++){
        //aux recebe a ultima (com maior numero de acessos) 
        //entidade da Fita fitas[i]
        aux = fitas[i].PopFront();
        heap->Add(aux);
    }
    
    //impressao para verificacao na saida padrao (opcional)
    /*std::cout << std::endl << "Primeira Impressao: ";
    heap->ImprimeHeap();*/
    
    while(!heap->Vazio()){
        //funcao que mitiga possiveis empates, desempatando com a ordem alfabetica das urls
        heap->Compara();

        aux2 = heap->Pop();
        indiceOrigem = aux2.GetIndiceFitaOrigem();
        aux2.ImprimeArquivo(arquivoSaida);

        if(fitas[indiceOrigem].GetNumEntidades()>0){
            aux3 = fitas[indiceOrigem].PopFront();
            heap->Add(aux3);
        }

        //impressao para verificacao na saida padrao (opcional)
        //heap->ImprimeHeap();
    }
}

/**
* -Descricao: funcao principal, faz a captacao e incializacao
*  dos parametros de entrada para execucao do programa e chama
*  metodos definidos na especificacao do programa
* -Entrada: argc, argv
* -Saida: 0
*/
int main(int argc, char* argv[]){
    //ARGUMENTOS DE argv:
    //(obrigatorio) primeiro argumento: nome do arquivo de entrada
    //(obrigatorio) segundo argumento: nome do arquivo de saida
    //(obrigatorio) terceiro argumento: numero de entidades suportadas pela memoria primaria
    //(opcional) quarto argumento: caminho/nome do arquivo para registro de log
    //(a principio, registra apenas o tempo do programa)
    //(opcional) quinto argumento: ativa registro de acesso (tempo e enderecos)

    //variaveis auxiliares
    std::ifstream arquivoEntrada;
    std::ofstream arquivoSaida;
    std::string nomeArquivoEntrada, nomeArquivoSaida;
    int numEntidades, numFitas, numLinhas, i;
    bool regmem = false;

    //caso os quatro argumentos obrigatorios para execucao do programa nao tenham 
    //sido informados, gera excecao
    erroAssert(argc >= 4, "ERRO: Argumentos faltantes para execucao do arquivo");

    nomeArquivoEntrada = argv[1];
    nomeArquivoSaida = argv[2];
    numEntidades = atoi(argv[3]);

    //verifica se o parametro numEntidades recebido eh valido
    erroAssert(numEntidades>0, "ERRO: O parametro de execucao passado eh invalido");

    //inicia registro de acesso, se solicitado
    if(argc >= 5){
        iniciaMemLog(argv[4]);
        regmem = true;
    }

    //ativar registro de acesso ou nao, se solicitado
    if(argc == 6){
        ativaMemLog();
    }

    else{
        desativaMemLog();
    }

    //abertura do arquivo de entrada para contagem de linhas
    arquivoEntrada.open(nomeArquivoEntrada);
    erroAssert(arquivoEntrada.is_open(), 
               "ERRO: Nao foi possivel abrir o arquivo de entrada");
    
    numLinhas = contaLinhasArquivo(arquivoEntrada);
    numFitas = ((numLinhas/numEntidades)+1);

    //fecha arquivo de entrada
    arquivoEntrada.close();

    //abertura do arquivo de entrada para leitura de linhas
    arquivoEntrada.open(nomeArquivoEntrada);
    erroAssert(arquivoEntrada.is_open(), 
               "ERRO: Nao foi possivel abrir o arquivo de entrada");
    
    //abertura do arquivo de saida para escrita
    arquivoSaida.open(nomeArquivoSaida);
    erroAssert(arquivoSaida.is_open(), 
               "ERRO: Nao foi possivel abrir o arquivo de saida");

    //vetor com as fitas a serem geradas
    Fita *fitas = new Fita[numFitas];

    //alocacao do vetor de entidades de cada fita em fitas para contar ATE numEntidades
    for(i=0; i<numFitas; i++){
        fitas[i].AlocaVetorEntidades(numEntidades);
    }

    //fase de geracao e ordenacao (pelo QuickSort) de rodadas
    if(argc == 6){
        defineFaseMemLog(1);
    }

    //gera numFitas rodadas (fitas) com numEntidades entidades cada,
    //conforme especificacao
    geraRodadas(fitas, arquivoEntrada, numEntidades, numLinhas, numFitas);
    //fase de intercalação de rodadas
    if(argc == 6){
        defineFaseMemLog(2);
    }

    //heap a ser utilizado na intercalacao de rodadas
    Heap *heap;
    heap = new Heap(numFitas);

    //intercalacao das rodadas geradas anteriormente utilizando o Heap heap
    //apenas se mais de uma fita foi gerada
    if(numLinhas>numEntidades){
        intercalaRodadas(fitas, numFitas, heap, arquivoSaida);
    }
    //caso nao haja intercalacao, a primeira fita gerada eh transcrita para a saida
    else{
        fitas[0].ImprimeFitaArquivo(arquivoSaida);
    }
    
    //desalocacao do vetor de fitas
    delete(fitas);

    //desalocacao do heap
    delete(heap);

    //fechamento arquivo entrada
    arquivoEntrada.close();

    //fechamento arquivo saida
    arquivoSaida.close();

    // conclui registro de acesso, se incializado
    if(regmem){
        finalizaMemLog();
    }
    
    return 0;
} 