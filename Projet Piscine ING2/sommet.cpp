#include "sommet.h"
#include <iostream>
#include <string>

Sommet::Sommet(int indice, std::string nom, double x, double y) /// constructeur
    :m_nom{nom},m_indice{indice},m_x{x},m_y{y}
{

}

void Sommet::afficher(Svgfile &svgout, std::vector <int> classement, int nomin, Graphe* mongraphe,int indice, std::vector <std::vector <double>> ensemble)
{
    int compteur=0;
    for(size_t i=0; i<classement.size(); ++i)
    {
        if(classement[i]>classement[m_indice])
            ++compteur;
    }
    std::cout<<m_indice<<" :    nom : "<< m_nom <<", X : "<<m_x<<", Y : "<<m_y<< std::endl; /// affichage en console
    svgout.addDisk(m_x*100, m_y*100, 4, svgout.makeRGB(255,75+(nomin*compteur),75+(nomin*compteur))); /// affiche le cercle du sommet
    svgout.addText(m_x*100+10, m_y*100+15, m_nom, "black"); /// affiche le nom
    svgout.addText(m_x*100-15, m_y*100-10, m_indice, "green"); /// affiche l'indice du sommet

    if (indice>-1)
    {
        svgout.addText((m_x)*100+10,m_y*100-10,ensemble[indice][m_indice],"orange"); /// affiche l'indice de centralité
    }
}

double Sommet::GetX()
{
    return m_x;
}

double Sommet::GetY()
{
    return m_y;
}

int Sommet::GetIndice()
{
    return m_indice;
}

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

void Sommet::affichernum()
{
    std::cout << m_indice << "<--";
}
