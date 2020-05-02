#include "arrete.h"
#include <iostream>
#include <string>
#include "math.h"
#include <cmath>
#include <vector>

Arrete::Arrete(Sommet* s1, Sommet* s2, int indice, int poids)
    :m_s1{s1},m_s2{s2},m_indice{indice},m_poids{poids}
{

}

void Arrete::afficher(Svgfile &svgout, int orientation)  // recoit le fichier svg afin de faire l'affichage dedans ainsi que l'orientation
{
    std::cout<<m_indice<<"/ sommet 1 :"<<m_s1->GetIndice()<<" / sommet 2 : "<<m_s2->GetIndice()<<" / poids : "<<m_poids<<std::endl;
    if (orientation==0)   // si le graphe n'est pas orient�
    {
        svgout.addLine(m_s1->GetX()*100, m_s1->GetY()*100, m_s2->GetX()*100, m_s2->GetY()*100, "blue");
    }
    else  // si le graphe est orient�
    {
        svgout.addLine(m_s1->GetX()*100, m_s1->GetY()*100, m_s2->GetX()*100, m_s2->GetY()*100, "blue");
        double x1,x2,y2,angle=0;
        x1=100;
        x2=(m_s2->GetX()*100)-(m_s1->GetX()*100);
        y2=(m_s2->GetY()*100)-(m_s1->GetY()*100);
        angle=acos((x1*x2)/(100*sqrt(x2*x2+y2*y2)));
        angle=angle-3.14159265359;
        if (y2<0)
        {
            angle=-angle;
        }
        svgout.addTriangle(m_s2->GetX()*100, m_s2->GetY()*100, (m_s2->GetX()*100)+12*cos(angle-3.14159265359/8), (m_s2->GetY()*100)+12*sin(angle-3.14159265359/8), (m_s2->GetX()*100)+12*cos(angle+3.14159265359/8), (m_s2->GetY()*100)+12*sin(angle+3.14159265359/8), "blue");
    }
}

void Arrete::afficher()
{
    std::cout<<m_poids<<std::endl;
}

void Arrete::afficherIndice()
{
    std::cout<<m_indice<<"/ sommet 1 :"<<m_s1->GetIndice()<<" / sommet 2 : "<<m_s2->GetIndice()<<" / poids : "<<m_poids<<std::endl;
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

bool Arrete::check_Sommets(Sommet* s1,Sommet* s2,int orientation)
{
    if(orientation==0)
    {
        if((s1->GetIndice()==m_s1->GetIndice() && s2->GetIndice()==m_s2->GetIndice())
        || (s1->GetIndice()==m_s2->GetIndice() && s2->GetIndice()==m_s1->GetIndice()))
            return true;
        else return false;
    }
    else if(orientation==1)
    {
        if(s1->GetIndice()==m_s1->GetIndice() && s2->GetIndice()==m_s2->GetIndice())
            return true;
        else return false;
    }
    return true;
}

void Arrete::effacer_adj(std::vector <int> m_adjacent[100])
{
    for(size_t i=0; i<m_adjacent[m_s1->GetIndice()].size(); ++i)
        if(m_adjacent[m_s1->GetIndice()][i]==m_s2->GetIndice())
            m_adjacent[m_s1->GetIndice()].erase(m_adjacent[m_s1->GetIndice()].begin()+i);

    for(size_t i=0; i<m_adjacent[m_s2->GetIndice()].size(); ++i)
        if(m_adjacent[m_s2->GetIndice()][i]==m_s1->GetIndice())
            m_adjacent[m_s2->GetIndice()].erase(m_adjacent[m_s2->GetIndice()].begin()+i);
}

void Arrete::add_adjacent(std::vector <int> m_adjacent[100],Arrete* aretes)
{
    for(size_t i=0; i<m_adjacent[m_s1->GetIndice()].size(); ++i)
        if(m_adjacent[m_s1->GetIndice()][i]==m_s2->GetIndice())
            m_adjacent[m_s1->GetIndice()].insert(m_adjacent[m_s1->GetIndice()].begin()+i,aretes->get_indice());

    for(size_t i=0; i<m_adjacent[m_s2->GetIndice()].size(); ++i)
        if(m_adjacent[m_s2->GetIndice()][i]==m_s1->GetIndice())
            m_adjacent[m_s2->GetIndice()].insert(m_adjacent[m_s2->GetIndice()].begin()+i,aretes->get_indice());
}
