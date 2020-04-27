#include <iostream>
#include "graphe.h"
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

Graphe::Graphe(std::string nomFichier)
{
    std::ifstream flux(nomFichier);
    if(!flux)
        std::cout << "Probl�me d'ouverture du fichier" << std::endl;
    if(!flux)
        std::cerr << "Impossible d'ouvrir le fichier";

    flux >> m_orientation >> m_ordre;

    for (int i=0; i<m_ordre; ++i)
    {
        std::string nom;
        int indice, x, y;
        flux>> indice >> nom >> x >> y;
        m_sommet.push_back(new Sommet{indice, nom, x, y});
    }
    flux>>m_taille;
    for (int i=0; i<m_taille; ++i)
    {
        int indice,s1,s2;
        flux >> indice >> s1 >> s2;
        m_arrete.push_back(new Arrete{m_sommet[s1],m_sommet[s2],indice,0});
        //graphe non oriente
        m_adjacent[s1].push_back(s2);
        m_adjacent[s2].push_back(s1);
    }
}

void Graphe::afficher()
{
    Svgfile svgout;
    svgout.addGrid();
    if(m_orientation==0)
        std::cout << "Graphe non oriente"<<std::endl;
    else
        std::cout << "Graphe oriente"<<std::endl;
    std::cout << "      Ordre = "<<m_ordre<<std::endl;
    for(size_t i=0; i<m_sommet.size(); ++i)
    {
        std::cout << "          sommet :";
        m_sommet[i]->afficher(svgout);
    }
    std::cout << std::endl<< "      Taille = "<<m_taille<<std::endl;
    for(size_t i=0; i<m_arrete.size(); ++i)
    {
        std::cout << "          arretes :";
        m_arrete[i]->afficher(svgout);
    }


    system("pause");
}

void Graphe::ajout_ponderation(std::string pondFichier)
{
    std::ifstream ifs(pondFichier);
    if(!ifs)
        std::cout << "Probl�me d'ouverture du fichier" << std::endl;
    if(!ifs)
        std::cerr << "Impossible d'ouvrir le fichier";

    int taille,indice,poids;

    ifs >> taille;

    for(int i=0; i<taille; ++i)
    {
        ifs >> indice >> poids;
        m_arrete[indice]->set_poids(poids);
    }
}

void Graphe::vecteur_propre()
{
    int n;
    for(n=0; n<m_ordre; ++n)
    {
        m_CVP.push_back(1);
    }

    double somme=0,c_Sommet[100],index=0;

    while(index<1000)
    {
        for(int i=0; i<m_ordre; ++i)
        {
            for(size_t j=0; j<m_adjacent[i].size(); ++j)
            {
                int temp = m_adjacent[i][j];
                c_Sommet[i] += m_CVP[temp];
            }
        }
        for(int i=0; i<m_ordre; ++i)
        {
            somme += c_Sommet[i]*c_Sommet[i];
        }
        m_lambda = sqrt(somme);

        for(int i=0; i<m_ordre; ++i)
        {
            m_CVP[i]= c_Sommet[i]/m_lambda;
        }
        ++index;
    }

    m_CVP.erase(m_CVP.begin(),m_CVP.begin()+n);
    system("pause");
}

std::vector <std::vector<float>> Graphe::calculdegre()
{
    std::vector <std::vector <float>> ensemble;
    std::vector <float> degres;
    std::vector <float> degresnormalise;
    for (int j=0; j<m_ordre; j++)
    {
        float degre=0;
        if (m_orientation == 0)
            for(size_t i=0; i<m_arrete.size(); i++)
                if (m_arrete[i]->calculdegre(m_sommet[j], m_orientation)==1)
                    degre++;
        if (m_orientation == 1)
            for(size_t i=0; i<m_arrete.size(); i++)
                if (m_arrete[i]->calculdegre(m_sommet[j], m_orientation)==1)
                    degre++;
        std::cout<<degre<<std::endl;



        degres.push_back(degre);
        degre=degre/m_ordre;
        degresnormalise.push_back(degre);
    }
    ensemble.push_back(degres);
    ensemble.push_back(degresnormalise);
    return ensemble;
}


int Graphe::algo_dijkstra(int debut, int fin)
{
    std::queue<int> que;
    int actuel;
    int nbr_aretes=0,pred[100];

    pred[debut] =-1;
    que.push(debut);

    bool check[100];
    bool condi = false;

    while(!que.empty() && !condi){

        actuel = que.front();
        que.pop();

        if(actuel == fin){
            condi = true;
        }

        if(check[actuel])
            continue;

        check[actuel] = true;
        std::cout<<actuel;
        for(int i = 0; i < m_adjacent[i].size(); ++i){
            if(!check[m_adjacent[actuel][i]]) {
                int nouveau;
                nouveau = m_adjacent[actuel][i];
                que.push(nouveau);
                pred[nouveau] = actuel;
            }
        }
    }

    while(pred[actuel]!=-1)
    {
        actuel=pred[actuel];
        ++nbr_aretes;
    }
    std::cout<<std::endl;
    return nbr_aretes;
}

void Graphe::centralite_proximite()
{//faire le cas si il y a les ponderations

    for(int i=0;i<m_ordre;++i)
    {
        m_CP.push_back(0);
        for(int j=0;j<m_ordre;++j)
        {
            if(j!=i){
                m_CP[i] += algo_dijkstra(i,j);
                std::cout<<"i ="<<i<<" j = "<<j<<std::endl;
            }
                //std::cout<<" i = "<<i<<" "<<m_CP[i]<<"  ";
        }

    }

//    for(int i=0;i<m_CP.size();++i)
//    {
//        std::cout<<"nombre arete du sommet "<<i<<" : "<<m_CP[i]<<std::endl;
//    }
    system("pause");
}
