#include "arrete.h"
#include <iostream>
#include <string>

Arrete::Arrete(Sommet* s1, Sommet* s2, int indice, int poids)
    :m_s1{s1},m_s2{s2},m_indice{indice},m_poids{poids}
{
//    m_s1=s1;
//    m_s2=s2;
}

void Arrete::afficher(Svgfile &svgout)
{
    std::cout<<m_indice<<" "<<m_s1->GetIndice()<<" "<<m_s2->GetIndice()<<" "<<m_poids<<std::endl;
    svgout.addLine(m_s1->GetX()*100, m_s1->GetY()*100, m_s2->GetX()*100, m_s2->GetY()*100, "blue");
}

void Arrete::set_poids(int poids)
{
    m_poids = poids;
}
