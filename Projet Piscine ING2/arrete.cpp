#include "arrete.h"
#include <iostream>
#include <string>

Arrete::Arrete(int s1, int s2, int indice, int poids)
    :m_s1{s1},m_s2{s2},m_indice{indice},m_poids{poids}
{

}

void Arrete::afficher()
{
    std::cout<<m_s1<<" "<<m_s2<<" "<<m_indice<<" "<<m_poids<<std::endl;
}

void Arrete::set_poids(int poids)
{
    m_poids = poids;
}

int Arrete::calculdegre(int sommet)
{
    if (m_s1==sommet || m_s2==sommet)
    {
        std::cout<<m_s1<<"      "<<m_s2<<std::endl;
        return 1;
    }
    else
    {
        //std::cout<<m_s1<<"      "<<m_s2<<std::endl;
        return 0;
    }
}
