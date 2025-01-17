#include "sommet.h"
#include <iostream>
#include <string>

Sommet::Sommet(int indice, std::string nom, double x, double y) /// constructeur
    :m_indice{indice},m_nom{nom},m_x{x},m_y{y}
{

}
///affiche tous les sommets sur le output.svg et en console
void Sommet::afficher(Svgfile &svgout, int nomin, Graphe* mongraphe,int indice, std::vector <std::vector <double>> ensemble)
{
    int compteur=0;
    if(indice==-1)
    {
        std::cout<<m_indice<<" :    nom : "<< m_nom <<", X : "<<m_x<<", Y : "<<m_y<< std::endl; /// affichage en console
        svgout.addDisk(m_x*100, m_y*100, 4, svgout.makeRGB(255,0,0)); /// affiche le cercle du sommet
        svgout.addText(m_x*100+10, m_y*100+15, m_nom, "black"); /// affiche le nom
        svgout.addText(m_x*100-15, m_y*100-10, m_indice, "green"); /// affiche l'indice du sommet
    }
    if (indice>-1)
    {
        int compteur=0;
        for(size_t i=0; i<ensemble[indice].size(); ++i)
        {
            if(ensemble[indice][i]>ensemble[indice][m_indice])
                ++compteur;
        }
        std::cout<<m_indice<<" :    nom : "<< m_nom <<", X : "<<m_x<<", Y : "<<m_y<< std::endl; /// affichage en console
        svgout.addDisk(m_x*100, m_y*100, 4, svgout.makeRGB(255,60+(nomin*compteur),60+(nomin*compteur))); /// affiche le cercle du sommet
        svgout.addCircle(m_x*100, m_y*100,4,1,"black");
        svgout.addText(m_x*100+10, m_y*100+15, m_nom, "black"); /// affiche le nom
        svgout.addText(m_x*100-15, m_y*100-10, m_indice, "green"); /// affiche l'indice du sommet
        svgout.addText((m_x)*100+10,m_y*100-10,ensemble[indice][m_indice],"orange"); /// affiche l'indice de centralit�
    }
}

double Sommet::GetX()///retourne la coordonee x
{
    return m_x;
}

double Sommet::GetY()///retourne la coordonee y
{
    return m_y;
}

int Sommet::GetIndice()///retourne l'indice
{
    return m_indice;
}
///parcour BFS des sommets
void Sommet::BFS(std::vector <int>& etats,std::vector <int>& predecesseurs,std::vector <int>& file, Graphe* mongraphe)
{
    std::vector <int> buffer;
    for(size_t i=0; i<mongraphe->get_adjacent(m_indice).size(); ++i) /// pour tous les adjacents du sommet en question
    {
        if(etats[mongraphe->get_adjacent(m_indice)[i]]==0) ///si le sommet n'a pas encore ete decouvert
        {
            etats[mongraphe->get_adjacent(m_indice)[i]]=1; /// on change l'etat du sommet en le mettant en "decouvert"
            predecesseurs[mongraphe->get_adjacent(m_indice)[i]]=m_indice; /// on note son predeceseur
            buffer.push_back(mongraphe->get_adjacent(m_indice)[i]);
        }
    }
    file.insert(file.begin()+file.size(), buffer.begin(), buffer.end()); /// on ajoute les prochains sommets a la file
    file.erase(file.begin()); /// on supprime le sommet de la file
}

void Sommet::affichernum()///affiche les indices
{
    std::cout << m_indice << "<--";
}
