#include "sommet.h"
#include <iostream>
#include <string>

Sommet::Sommet(int indice, std::string nom, int x, int y)
    :m_nom{nom},m_indice{indice},m_x{x},m_y{y}
{

}

void Sommet::afficher(Svgfile &svgout)
{
    std::cout<<m_indice<<" "<< m_nom <<" "<<m_x<<" "<<m_y<< std::endl;
    svgout.addDisk(m_x*100, m_y*100, 5, "red");
    svgout.addText(m_x*100+10, m_y*100+15, m_nom, "black");
    svgout.addText(m_x*100-15, m_y*100-10, m_indice, "green");
}

int Sommet::GetX()
{
    return m_x;
}

int Sommet::GetY()
{
    return m_y;
}

int Sommet::GetIndice()
{
    return m_indice;
}
