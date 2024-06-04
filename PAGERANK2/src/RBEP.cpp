#include "RBEP.h"
#include <algorithm>
#include <iostream>

#include "Roleta.h"

RBEP::RBEP(const Grafo& pG):
    G(pG), T(pG.n,pG.m), InBT(G.n, 0), InPontas(G.n, false)//, RemPontas(G.n, false)
{
    //constructor
    G.nome = "G";
    T.nome = "T";
}

RBEP::~RBEP()
{
    //destructor
}

Grafo RBEP::ObterArvore() const
{
    return T;

}

vector<int> RBEP::ObterBranches() const
{
    return BT;
}

vector<int> RBEP::ObterGrauBT() const
{
    vector<int> GrauBT;
    for (int v : BT)
    {
        GrauBT.push_back(T.Grau(v));
    }
    return GrauBT;
}

//Algoritmo Árvore Geradora - V4.3 - Primeira Heurística Randomizada
void RBEP::Oliveira(int seed)
{

    BT.clear();

    for (int i = 0; i < G.n; i++)
    {
        InBT[i] = 0;
        InPontas[i] = false;
    }

    //Detectar articulações e pontes com DFS.
    G.DetectarArticulacoesEPontes();

    for(int v : G.ArticulacoesW2)
    {   
        T.AdicionarVertice(v); //Adicionar vértices na Árvore.
        BT.push_back(v); //Considera que todos são ramificações da árvore.
        InBT[v] = 1; //Marca o vértice como uma ramificação.
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
        // int v = G.VerticeGrauMinimo();
        // int u = G.AdjacenteGrauMinimo(v);

        int v = G.VerticePageRankMinimo();
        int u = G.AdjacentePageRankMinimo(v);

        T.AdicionarVertice(v);
        T.AdicionarVertice(u);
        T.AdicionarAresta(v,u);

        InPontas[v] = true;
        Pontas.insert(v);

        InPontas[u] = true;
        Pontas.insert(u);
        
    }

    while(T.NumeroArestas() < G.n - 1)
    {
        if(Pontas.empty() == false)
        {
            int v;
            // int grauMax = 0;
            float pgMax = 0;

            Roleta R = Roleta();

            // for(int i : Pontas)
            // {
            //     // if(G.Grau(i) > grauMax)
            //     if(G.PG[i] > pgMax)
            //     {
            //         // grauMax = G.Grau(i);
            //         pgMax = G.PG[i];
            //     }
            // }
            // // grauMax = grauMax + 1;
            // pgMax = pgMax + 1;

            for(int p : Pontas)
            {
                double peso = 1 / G.PG[p];
                R.Adicionar(p, peso);
            }
            v = R.Sortear(seed);

            Pontas.erase(v);
            InPontas[v] = false;

            /*
                Salvando todos os adjacentes do Vértice V
                que foi sorteado no vector.
            */
            vector<tuple<int,pair<int,int>, double>> Nv;
            for(int u : G.Adjacentes(v))
                if(T.BuscarVertice(u) == false || (T.CConexa(u) != T.CConexa(v) && 
                (InBT[u] == 1 || T.Grau(u) == 1))){
                    Nv.push_back(make_tuple(u, make_pair(G.Grau(u), T.Grau(u)), G.PG[u]));
            }

            if(Nv.empty() == false)
            {
                int du_G;// = G.n + 1;
                int du_T;// = G.n + 1;
                int u;
                // int grauMax2 = 0;

                Roleta R = Roleta();

                // for(pair<int,pair<int,int>> j : Nv)
                // {
                //     du_G = j.second.first;
                //     if(du_G > grauMax2)
                //     {
                //         grauMax2 = du_G;
                //     }
                // }
                // grauMax2 = grauMax2 + 1;

                for(const auto & i : Nv)
                {
                    u = get<0>(i);
                    // du_G = get<1>(i).first;
                    // du_T = get<1>(i).second;

                    if(du_T == 0)
                    {
                        du_G = du_G - 1;
                    }
                    // double peso = grauMax2 - du_G;
                    double peso = 1 / get<2>(i);
                    R.Adicionar(u, peso);

                }
                u = R.Sortear(seed);

                T.AdicionarVertice(u);
                T.AdicionarAresta(v,u);
                
				if (T.Grau(u) == 1)
                {
                    InPontas[u] = true;
                    Pontas.insert(u);
                }
				else
                {
                    if(InPontas[u] == true)
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


            for (int i : T.V) // Todos os vértices da arvore atual.
            {   
                vector<int> listaC;
                set<int> listaCC;

                for (int u : G.Adjacentes(i)) 
                {
                    /*
                    Salvar todos os vértices adjacentes de 
                    i que se adequam nesses critérios.
                    */
                    if (T.BuscarVertice(u) == false || 
                        (T.CConexa(u) != T.CConexa(i) && 
                        (InBT[u] == 1 || T.Grau(u) == 1)))
                    {
                        listaC.push_back(u);
                        listaCC.insert(T.CConexa(u));
                    }
                }

                //Salvar o vértice com a maior quantidade de opções.
                if ((int)listaCC.size() > nCC)
                {
                    v = i;
                    nCC = listaCC.size();
                    C = listaC;
                }
            }

            if(C.size() > 0) //Se existir vértice que tenha opções que possa ser escolhida
            {   
                //Trasformar v em ramificação permite estabelecer novas conexões:
                BT.push_back(v);
                InBT[v] = 1;
                for(int u : C)
                {
                    if(T.CConexa(u) != T.CConexa(v)) //Expansão desse novo vértice
                    {
                        T.AdicionarVertice(u);
                        T.AdicionarAresta(v,u);

						if(T.Grau(u) == 1)
                        {
                            InPontas[u] = true;
                            Pontas.insert(u); //Atualização de Pontas
						}
                    }
                }

            }
            else
            {   
                int v;
                int nCC = -1;
                vector<int> C;

                for (int i : T.V) // Todos os vértices de V
                {
                    vector<int> listaC;
                    set<int> listaCC;

                    for (int u : G.Adjacentes(i)) //Adjacentes de V no grafo.
                    {
                        if (T.CConexa(u) != T.CConexa(i)) // Ainda não estão conectados
                        {
                            listaC.push_back(u);
                            listaCC.insert(T.CConexa(u));
                        }
                    }

                    if ((int)listaCC.size() > nCC) //Seleciona o maior
                    {
                        v = i;
                        nCC = listaCC.size();
                        C = listaC;
                    }
                }
                //Torna esse novo vetor uma ramificação.
                BT.push_back(v);
                InBT[v] = 1;
            }
        }
    }
}

