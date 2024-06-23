#include "AndersonV4.h"
#include <algorithm>
#include <iostream>

#include "Roleta.h"


AndersonV4::AndersonV4(const Grafo& pG):
    G(pG), T(pG.n,pG.m), InBT(G.n, 0), InPontas(G.n, false)//, RemPontas(G.n, false)
{
    //constructor
    G.nome = "G";
    T.nome = "T";
}

AndersonV4::~AndersonV4()
{
    //destructor
}

Grafo AndersonV4::ObterArvore() const
{
    return T;

}

vector<int> AndersonV4::ObterBranches() const
{
    return BT;
}

vector<int> AndersonV4::ObterGrauBT() const
{
    vector<int> GrauBT;
    for (int v : BT)
    {
        GrauBT.push_back(T.Grau(v));
    }
    return GrauBT;
}

//Algoritmo Árvore Geradora - V4.3
void AndersonV4::Oliveira()
{
    BT.clear();
    //while (!Pontas.empty()) Pontas.pop();

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
            //Pontas.push(make_pair(-1 * G.Grau(v), v));
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

        //Pontas.push(make_pair(-1 * G.Grau(v), v));
        InPontas[v] = true;
        Pontas.insert(v);

        //Pontas.push(make_pair(-1 * G.Grau(u), u));
        InPontas[u] = true;
        Pontas.insert(u);
    }

    //Continuação
    while(T.NumeroArestas() < G.n - 1)
    {
        if(Pontas.empty() == false)
        {
            int v;
            int grauMax = 0;

            Roleta R = Roleta();

            for(int i : Pontas)
            {
                if(G.Grau(i) > grauMax)
                {
                    grauMax = G.Grau(i);
                }
            }
            grauMax = grauMax + 1;

            for(int p : Pontas)
            {
                //double peso = G.n - G.Grau(p);
                double peso = grauMax - G.Grau(p);
                //cout << p << " - " << peso <<endl;
                R.Adicionar(p, peso);
            }
            v = R.Sortear();

            //cout << v << " ";

            Pontas.erase(v);
            InPontas[v] = false;
            /*
            do
            {
                pair<int,int> topo = Pontas.top();
                int v = topo.second;

                Pontas.pop();
                InPontas[v] = false;

                if (RemPontas[v] == false)
                {
                    break;
                }
                else
                {
                    RemPontas[v] = false;
                    v = -1;
                    continue;
                }
            }
            while(Pontas.empty() == false);

            if (v == -1) continue;*/

            vector<pair<int,pair<int,int>>> Nv;
            for(int u : G.Adjacentes(v))
                if(T.BuscarVertice(u) == false || (T.CConexa(u) != T.CConexa(v) && (InBT[u] == 1 || T.Grau(u) == 1)))
                    Nv.push_back(make_pair(u, make_pair(G.Grau(u), T.Grau(u))));

            if(Nv.empty() == false)
            {
                int du_G;// = G.n + 1;
                int du_T;// = G.n + 1;
                int u;
                int grauMax2 = 0;

                Roleta R = Roleta();

                for(pair<int,pair<int,int>> j : Nv)
                {
                    du_G = j.second.first;
                    if(du_G > grauMax2)
                    {
                        grauMax2 = du_G;
                    }
                }
                grauMax2 = grauMax2 + 1;

                for(pair<int,pair<int,int>> i : Nv)
                {
                    u = i.first;
                    du_G = i.second.first;
                    du_T = i.second.second;

                    if(du_T == 0)
                    {
                        du_G = du_G - 1;
                    }
                    double peso = grauMax2 - du_G;
                    R.Adicionar(u, peso);

                    /*
                    if(i.second.first < du_G)
                    {
                        u = i.first;
                        du_G = i.second.first;
                        du_T = i.second.second;
                    }
                    else
                    {
                        if(i.second.first == du_G)
                        {
                            if (i.second.second < du_T)
                            {
                                u = i.first;
                                du_G = i.second.first;
                                du_T = i.second.second;
                            }
                        }
                    }*/
                }
                u = R.Sortear();

                T.AdicionarVertice(u);
                T.AdicionarAresta(v,u);
				if (T.Grau(u) == 1)
                {
                    //Pontas.push(make_pair(-1 * G.Grau(u), u));
                    InPontas[u] = true;
                    Pontas.insert(u);
                }
				else
                {
                    if(InPontas[u] == true)
                    {
                        //RemPontas[u] = true; //Como pontas é lista de prioridade, não é possível remover diretamente
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

                for(int u : C)
                {
                    if(T.CConexa(u) != T.CConexa(v))
                    {
                        T.AdicionarVertice(u);
                        T.AdicionarAresta(v,u);
						if(T.Grau(u) == 1)
                        {
                            //Pontas.push(make_pair(-1 * G.Grau(u), u));
                            InPontas[u] = true;
                            Pontas.insert(u);
						}
                    }
                }
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

                for(int u : C)
                {
                    if(T.CConexa(u) != T.CConexa(v))
                    {
                        BT.push_back(u);
						InBT[u] = 1;
                        T.AdicionarAresta(v,u);
                    }
                }
            }
        }
    }
}
