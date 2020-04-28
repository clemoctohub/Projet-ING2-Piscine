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

void Arrete::afficher()
{
    std::cout<<m_poids<<std::endl;
}

void Arrete::set_poids(int poids)
{
    m_poids = poids;
}

void Arrete::set_indice(int indice)
{
    m_indice = indice;
}

int Arrete::calculdegre(Sommet* sommet, int orientation)
{
    if (orientation == 0)  // si le graphe est orient� ou non, le calcul de degr� ne se fait pas de la m�me mani�re
    {
        if (m_s1->GetIndice()==sommet->GetIndice() || m_s2->GetIndice()==sommet->GetIndice()) // si le graphe n'est pas orient�, on ajoute un degr� a chaque fois que l'un des deux sommets d'une ar�te est le m�me que le sommet en question
            return 1;
        else
            return 0;
    }

    if (orientation == 1)
    {
        if (m_s1->GetIndice()==sommet->GetIndice()) // si le graphe est orient�, on ajoute un degr�s a chaque fois que le sommet d'arriv� (le deuxi�me) est le m�me que le sommet en question
            return 1;
        else
            return 0;
    } // si la m�thode return 1, on ajoute un degr�, si elle return 0, on n'en ajoute pas
    return 0;
}

bool Arrete::check_Sommets(Sommet* s1,Sommet* s2)
{
    if((s1->GetIndice()==m_s1->GetIndice() && s2->GetIndice()==m_s2->GetIndice())
       || (s1->GetIndice()==m_s2->GetIndice() && s2->GetIndice()==m_s1->GetIndice()))
       return true;
    else return false;
}
