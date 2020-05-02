#include "sommet.h"
#include <iostream>
#include <string>

Sommet::Sommet(int indice, std::string nom, double x, double y) // constructeur
    :m_nom{nom},m_indice{indice},m_x{x},m_y{y}
{

}

void Sommet::afficher(Svgfile &svgout, std::vector <int> classement, int nomin)
{
    int compteur=0;
    for(size_t i=0; i<classement.size(); ++i)
    {
        if(classement[i]>classement[m_indice])
            ++compteur;
    }
    std::cout<<m_indice<<" :    nom : "<< m_nom <<", X : "<<m_x<<", Y : "<<m_y<< std::endl;
    svgout.addDisk(m_x*100, m_y*100, 4, svgout.makeRGB(255,75+(nomin*compteur),75+(nomin*compteur)));
    svgout.addText(m_x*100+10, m_y*100+15, m_nom, "black");
    svgout.addText(m_x*100-15, m_y*100-10, m_indice, "green");
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
    for(size_t i=0; i<mongraphe->get_adjacent(m_indice).size(); ++i)
    {
        if(etats[mongraphe->get_adjacent(m_indice)[i]]==0)
        {
            etats[mongraphe->get_adjacent(m_indice)[i]]=1;
            predecesseurs[mongraphe->get_adjacent(m_indice)[i]]=m_indice;
            buffer.push_back(mongraphe->get_adjacent(m_indice)[i]);
        }
    }
    file.insert(file.begin()+file.size(), buffer.begin(), buffer.end());
    file.erase(file.begin());
}

void Sommet::affichernum()
{
    std::cout << m_indice << "<--";
}
