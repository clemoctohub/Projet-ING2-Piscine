#include <iostream>
#include "graphe.h"
#include <fstream>
#include <string>
#include <vector>

Graphe::Graphe(std::string nomFichier)
{
    std::ifstream flux(nomFichier);
    if(!flux)
        std::cout << "Problème d'ouverture du fichier" << std::endl;
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
        m_arrete.push_back(new Arrete{indice,s1,s2,0});
    }
}

void Graphe::afficher()
{
    if(m_orientation==0)
        std::cout << "Graphe non oriente"<<std::endl;
    else
        std::cout << "Graphe oriente"<<std::endl;
    std::cout << "      Ordre = "<<m_ordre<<std::endl;
    std::cout << "      Liste d'adjacence = "<<std::endl;
    std::cout <<std::endl;
    for(size_t i=0; i<m_sommet.size(); ++i)
    {
        std::cout << "          sommet :";
        m_sommet[i]->afficher();
    }
    system("pause");
}
