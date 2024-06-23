#ifndef GRAFO_H
#define GRAFO_H

#include <set>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

class Grafo
{
    public:
        Grafo();
        Grafo(int n, int m = 0);
        Grafo(const Grafo& G);

        static Grafo LerArquivo(string nomeArquivo);

        virtual ~Grafo();

        int n;
        int m;

        vector<bool> InV;
        vector<int> V;

        vector<pair<int,int>> E;
        vector<vector<int>> listaAdj;

        vector<int> ArticulacoesW2;
        vector<pair<int,int>> Pontes;

        void DetectarArticulacoesEPontes();
        void AtualizarCConexas(int v, int u);

        vector<int> Adjacentes(int v) const;

        int Grau(int v) const;
        bool BuscarVertice(int v) const;

        void AdicionarVertice(int v);
        void AdicionarAresta(int v, int u);
        void RemoverAresta(int v, int u);

        int CConexa(int v) const;

        int VerticeGrauMinimo() const;
        int AdjacenteGrauMinimo(int v) const;

        int NumeroArestas() const;

        bool ValidarArvore() const;

        void ImprimirListaAdj() const;
        void ImprimirArvoreGraphviz() const;


        string nome;

    protected:
        int raiz;
        int t;
        vector<int> PE;
        vector<int> PS;
        vector<int> BACK;
        vector<int> pai;
        vector<int> ListaCT;

        void DFS(int v);
        vector<int> listaCConexa;
        vector<vector<int>> mapaCConexa;


    private:
};

#endif // GRAFO_H
