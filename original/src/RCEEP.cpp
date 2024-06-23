#include "RCEEP.h"
#include <algorithm>
#include <iostream>

#include "Roleta.h"

RCEEP::RCEEP(const Grafo& pG):
    G(pG), T(pG.n,pG.m), InBT(G.n, 0), InPontas(G.n, false)
{
    //constructor
    G.nome = "G";
    T.nome = "T";
}

RCEEP::~RCEEP()
{
    //destructor
}

Grafo RCEEP::ObterArvore() const
{
    return T;
}

vector<int> RCEEP::ObterBranches() const
{
    return BT;
}

vector<int> RCEEP::ObterGrauBT() const
{
    vector<int> GrauBT;
    for (int v : BT)
    {
        GrauBT.push_back(T.Grau(v));
    }
    return GrauBT;
}

//Algoritmo Árvore Geradora - Quarta Heurística Randomizada
void RCEEP::Oliveira()
{
    BT.clear();

    for (int i = 0; i < G.n; i++)
    {
        InBT[i] = 0;
        InPontas[i] = false;
        //RemPontas[i] = false;
    }

    //Tratar nova condição para articulações:
    G.DetectarArticulacoesEPontes();

    for(int v : G.ArticulacoesW2)
    {
        T.AdicionarVertice(v); //Adcionar vértices na árvore
        BT.push_back(v); //Considerar que todos são ramificações da árvore
        InBT[v] = 1;
    }

    //Tratar Pontes:
    for(pair<int,int> vu : G.Pontes)
    {
        int v = vu.first;
        int u = vu.second;

        T.AdicionarVertice(v);
        T.AdicionarVertice(u);

        T.AdicionarAresta(v,u);

        if (T.Grau(v) > 2 && InBT[v] == 0)
        {
            BT.push_back(v);
            InBT[v] = 1;
        }

        if (T.Grau(u) > 2 and InBT[u] == 0)
        {
            BT.push_back(u);
            InBT[u] = 1;
        }
    }


    //Tratar vértices marcados como ramificações da árvore:
    for(int v : BT)
    {
        for(int u : G.Adjacentes(v))
        {
            if(T.BuscarVertice(u) == false)
            {
                T.AdicionarVertice(u);
                T.AdicionarAresta(v,u);
            }
            else
            {
                if ((T.Grau(u) == 1 || InBT[u] == 1) && T.CConexa(v) != T.CConexa(u))
                {
                    T.AdicionarAresta(v,u);
                }
            }
        }
    }

    //Verificar quais caminhos pode ser explorados:
    for(int v : T.V)
    {

        if(T.Grau(v) == 1 && G.Grau(v) > 1)
        {
            InPontas[v] = true;
            Pontas.insert(v);
        }
    }

    //Se nenhuma ponta foi identificada, cria uma nova:
    if(Pontas.empty())
    {
        int v = G.VerticeGrauMinimo();
        int u = G.AdjacenteGrauMinimo(v);

        T.AdicionarVertice(v);
        T.AdicionarVertice(u);
        T.AdicionarAresta(v,u);

        InPontas[v] = true;
        Pontas.insert(v);

        InPontas[u] = true;
        Pontas.insert(u);
    }

    //Continuação
    while(T.NumeroArestas() < G.n - 1)
    {
        if(Pontas.empty() == false)
        {
            int v;

            int pesoMax = 0;

            Roleta R = Roleta();

            int somaGraus = 0; //antiga variável peso

            for(int p : Pontas)
            {
                for(int u : G.Adjacentes(p))
                {
                    if(T.BuscarVertice(u) == false || (T.CConexa(u) != T.CConexa(p) && (InBT[u] == 1 || T.Grau(u) == 1)))
                    {
                        somaGraus = G.Grau(p) + G.Grau(u);
                        if(somaGraus > pesoMax)
                        {
                           pesoMax = somaGraus;
                        }
                    }
                }
            }
            pesoMax = pesoMax + 1;

            vector<pair<int, int>> Arestas;

            for(int p : Pontas)
            {
                for(int u : G.Adjacentes(p))
                {
                    if(T.BuscarVertice(u) == false)
                    {
                        somaGraus = G.Grau(p) + G.Grau(u);
                        double peso = pesoMax - somaGraus + 1;
                        Arestas.push_back(make_pair(p, u));
                        int chave = Arestas.size() - 1;
                        R.Adicionar(chave, peso);
                    }
                    else
                    {
                        if(T.CConexa(u) != T.CConexa(p) && (InBT[u] == 1 || T.Grau(u) == 1))
                        {
                            somaGraus = G.Grau(p) + G.Grau(u);
                            double peso = pesoMax - somaGraus;
                            Arestas.push_back(make_pair(p, u));
                            int chave = Arestas.size() - 1;
                            R.Adicionar(chave, peso);
                        }
                    }
                }
            }

            if(somaGraus == 0)
            {
                for(int i : Pontas)
                {
                    InPontas[i] = false;
                }
                Pontas.clear();
            }
            else
            {
                int posAresta = R.Sortear();
                pair<int, int> sorteada = Arestas[posAresta];
                v = sorteada.first;
                int u = sorteada.second;

                if(InBT[v] == 0)
                {
                    Pontas.erase(v);
                    InPontas[v] = false;
                }

                T.AdicionarVertice(u);
                T.AdicionarAresta(v,u);

                if(T.Grau(u) == 1)
                {
                    InPontas[u] = true;
                    Pontas.insert(u);
                }
				else
                {
                    if(InPontas[u] == true && InBT[u] == 0)
                    {
                        Pontas.erase(u);
                        InPontas[u] = false;
                    }
                }
            }
        }
        else
        {
            //Não existe uma nova ponta para ser explorada: necessário converter um vértice da árvore em ramificação.

			int v;
			int nCC = -1;
			vector<int> C;

            for (int i : T.V)
            {
                vector<int> listaC;
                set<int> listaCC;

                for (int u : G.Adjacentes(i))
                {
                    if (T.BuscarVertice(u) == false || (T.CConexa(u) != T.CConexa(i) && (InBT[u] == 1 || T.Grau(u) == 1)))
                    {
                        listaC.push_back(u);
                        listaCC.insert(T.CConexa(u));
                    }
                }

                if ((int)listaCC.size() > nCC)
                {
                    v = i;
                    nCC = listaCC.size();
                    C = listaC;
                }
            }

            if(C.size() > 0)
            {
                //Trasformar v em ramificação permite estabelecer novas conexões:
                BT.push_back(v);
                InBT[v] = 1;

                InPontas[v] = true;
                Pontas.insert(v);
            }
            else
            {
                int v;
                int nCC = -1;
                vector<int> C;

                for (int i : T.V)
                {
                    vector<int> listaC;
                    set<int> listaCC;

                    for (int u : G.Adjacentes(i))
                    {
                        if (T.CConexa(u) != T.CConexa(i))
                        {
                            listaC.push_back(u);
                            listaCC.insert(T.CConexa(u));
                        }
                    }

                    if ((int)listaCC.size() > nCC)
                    {
                        v = i;
                        nCC = listaCC.size();
                        C = listaC;
                    }
                }

                BT.push_back(v);
                InBT[v] = 1;
            }
        }
    }
}

