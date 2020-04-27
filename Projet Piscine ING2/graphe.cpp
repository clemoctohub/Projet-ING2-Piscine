#include <iostream>
#include "graphe.h"
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

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

    for(int i=0;i<taille;++i){
        ifs >> indice >> poids;
        m_arrete[indice]->set_poids(poids);
    }
}

void Graphe::vecteur_propre()
{
    int n;
    for(n=0;n<m_ordre;++n)
    {
        m_CVP.push_back(1);
    }

    double somme=0,c_Sommet[100],index=0;
    int temp;

    while(index<1000)
    {
        for(int i=0;i<m_ordre;++i)
        {
            for(int j=0;j<m_adjacent[i].size();++j)
            {
                int temp = m_adjacent[i][j];
                c_Sommet[i] += m_CVP[temp];
            }
        }
        for(int i=0;i<m_ordre;++i)
        {
            somme += c_Sommet[i]*c_Sommet[i];
        }
        m_lambda = sqrt(somme);

        for(int i=0;i<m_ordre;++i)
        {
            m_CVP[i]= c_Sommet[i]/m_lambda;
        }
        ++index;
    }

    m_CVP.erase(m_CVP.begin(),m_CVP.begin()+n);
    system("pause");

int Graphe::calculdegre(int sommet)
{
    int degre=0;
    if (m_orientation == 0)
    {
        for(size_t i=0; i<m_arrete.size(); i++)
        {
            if (m_arrete[i]->calculdegre(sommet, m_orientation)==1)
            {
                degre++;
            }
        }
    }

    if (m_orientation == 1)
    {
        for(size_t i=0; i<m_arrete.size(); i++)
        {
            if (m_arrete[i]->calculdegre(sommet, m_orientation)==1)
            {
                degre++;
            }
        }
    }
    return degre;
}
