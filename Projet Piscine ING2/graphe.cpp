#include <iostream>
#include "graphe.h"
#include "arrete.h"
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

        m_CP.push_back(0);
    }
    flux>>m_taille;
    //faire le cas pour les graphes orientes
    for (int i=0; i<m_taille; ++i)
    {
        int indice,s1,s2;
        flux >> indice >> s1 >> s2;
        m_arrete.push_back(new Arrete{m_sommet[s1],m_sommet[s2],indice,0});
        //cas graphe non oriente a faire
        m_adjacent[s1].push_back(s2);
        m_adjacent[s2].push_back(s1);
    }

    for(int i=0;i<100;++i)
        m_dec[i]=false;
    m_nbr_aretes = 0;

    m_ponderation = false;
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
        std::cout << "Probleme d'ouverture du fichier" << std::endl;
    if(!ifs)
        std::cerr << "Impossible d'ouvrir le fichier";

    int taille,indice,poids;

    ifs >> taille;

    for(int i=0; i<taille; ++i)
    {
        ifs >> indice >> poids;
        m_arrete[indice]->set_poids(poids);
    }

    m_ponderation = true;
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
        degres.push_back(degre);
        degre=degre/(m_ordre-1);
        degresnormalise.push_back(degre);
    }
    ensemble.push_back(degres);
    ensemble.push_back(degresnormalise);
    return ensemble;
}

void Graphe::parcour_DFS_no_ponderation(int numS,int fin,int nbr_aretes)
{
    m_dec[numS] = true;

    if(numS==fin)
        m_nbr_aretes = nbr_aretes;
    else
        ++nbr_aretes;

    for(size_t i=0;i<m_adjacent[numS].size();++i)
        if(!m_dec[m_adjacent[numS][i]])
            parcour_DFS_no_ponderation(m_adjacent[numS][i],fin,nbr_aretes);
}

int Graphe::algo_dijkstra(int debut, int fin)
{
    std::queue<Arrete> que;
    Arrete actuel,initial;
    int temp,k=0;
    int dist[100];

    initial.set_indice(debut);
    initial.set_poids(0);

    que.push(initial);

    for(int i=0;i<m_ordre;++i)
    {
        dist[i]=999999;
    }

    bool condi = false,condi2=false;
    dist[debut]=0;

    while(!que.empty() && condi!=true){

        actuel = que.front();
        que.pop();
        temp = actuel.get_indice();

        if(temp == fin)
            condi = true;
        if(m_dec[temp])
            continue;
        m_dec[temp] = true;
        for(size_t i = 0; i < m_adjacent[temp].size(); ++i){
            if(!m_dec[m_adjacent[temp][i]]){
                Arrete nouveau;
                nouveau.set_indice(m_adjacent[temp][i]);
                while(!condi2)
                {
                    condi2 = m_arrete[k]->check_Sommets(m_sommet[temp],m_sommet[m_adjacent[temp][i]]);
                    if(!condi2)
                        ++k;
                }
                if(condi2==true)
                    condi2 = false;

                if(dist[nouveau.get_indice()] > dist[temp] + m_arrete[k]->get_poids()){
                    dist[nouveau.get_indice()] = dist[temp] + m_arrete[k]->get_poids();
                }
                k=0;
                que.push(nouveau);
            }
        }
    }


    return dist[temp];
}

void Graphe::centralite_proximite()
{//faire le cas si il y a les ponderations + cas normalise et non normalise
    std::vector<double> somme;
    for(int i=0;i<m_ordre;++i)
    {
        somme.push_back(0);
        for(int j=0;j<m_ordre;++j)
            if(j!=i){
                if(m_ponderation == false){
                    parcour_DFS_no_ponderation(i,j,0);
                    somme[i] += m_nbr_aretes;
                }
                else if(m_ponderation==true){
                    somme[i] += algo_dijkstra(i,j);
                }
                for(int i=0;i<100;++i)
                    m_dec[i]=false;
            }
    }

    for(size_t i=0;i<somme.size();++i){
        m_CP[i] = (m_ordre-1)/somme[i];
        std::cout<<"CP["<<i<<"] = "<<m_CP[i]<<std::endl;
    }
    somme.erase(somme.begin(),somme.begin()+m_ordre);
    system("pause");
}
