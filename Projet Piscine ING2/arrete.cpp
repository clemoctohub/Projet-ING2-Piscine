#include "arrete.h"
#include <iostream>
#include <string>

Arrete::Arrete(Sommet* s1, Sommet* s2, int indice, int poids)
    :m_s1{s1},m_s2{s2},m_indice{indice},m_poids{poids}
{

}

void Arrete::afficher(Svgfile &svgout)  // recoit le fichier svg afin de faire l'affichage dedans
{
    std::cout<<m_indice<<" "<<m_s1->GetIndice()<<" "<<m_s2->GetIndice()<<" "<<m_poids<<std::endl;
    svgout.addLine(m_s1->GetX()*100, m_s1->GetY()*100, m_s2->GetX()*100, m_s2->GetY()*100, "blue");
}

void Arrete::set_poids(int poids)
{
    m_poids = poids;
}

int Arrete::calculdegre(Sommet* sommet, int orientation)
{
    if (orientation == 0)  // si le graphe est orienté ou non, le calcul de degré ne se fait pas de la même manière
    {
        if (m_s1->GetIndice()==sommet->GetIndice() || m_s2->GetIndice()==sommet->GetIndice()) // si le graphe n'est pas orienté, on ajoute un degré a chaque fois que l'un des deux sommets d'une arête est le même que le sommet en question
            return 1;
        else
            return 0;
    }

    if (orientation == 1)
    {
        if (m_s1->GetIndice()==sommet->GetIndice()) // si le graphe est orienté, on ajoute un degrés a chaque fois que le sommet d'arrivé (le deuxième) est le même que le sommet en question
            return 1;
        else
            return 0;
    }
    return 0;
}
