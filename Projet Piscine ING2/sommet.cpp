#include "sommet.h"
#include <iostream>
#include <string>

Sommet::Sommet(int indice, std::string nom, int x, int y)
    :m_nom{nom},m_indice{indice},m_x{x},m_y{y}
{

}

void Sommet::afficher()
{
    std::cout<<m_indice<<" "<< m_nom <<" "<<m_x<<" "<<m_y<< std::endl;
}
