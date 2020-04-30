#include "arrete.h"
#include <iostream>
#include <string>
#include "math.h"
#include <cmath>

Arrete::Arrete(Sommet* s1, Sommet* s2, int indice, int poids)
    :m_s1{s1},m_s2{s2},m_indice{indice},m_poids{poids}
{

}

void Arrete::afficher(Svgfile &svgout, int orientation)  // recoit le fichier svg afin de faire l'affichage dedans ainsi que l'orientation
{
    std::cout<<m_indice<<" "<<m_s1->GetIndice()<<" "<<m_s2->GetIndice()<<" "<<m_poids<<std::endl;
    if (orientation==0)   // si le graphe n'est pas orienté
    {
        svgout.addLine(m_s1->GetX()*100, m_s1->GetY()*100, m_s2->GetX()*100, m_s2->GetY()*100, "blue");
    }
    else  // si le graphe est orienté
    {
        svgout.addLine(m_s1->GetX()*100, m_s1->GetY()*100, m_s2->GetX()*100, m_s2->GetY()*100, "blue");
        double x1,x2,y1,y2,angle=0;
        x1=100;
        y1=0;
        x2=(m_s2->GetX()*100)-(m_s1->GetX()*100);
        y2=(m_s2->GetY()*100)-(m_s1->GetY()*100);
        angle=-acos((x1*x2)/(100*sqrt(x2*x2+y2*y2)));
        angle=angle-3.14159265359;
        //angle=angle*(180/3.14159265359);
        std::cout<<angle<< std::endl;
        svgout.addTriangle(m_s2->GetX()*100, m_s2->GetY()*100, (m_s2->GetX()*100)+10*cos(angle-3.14159265359/8), (m_s2->GetY()*100)+10*sin(angle-3.14159265359/8), (m_s2->GetX()*100)+10*cos(angle+3.14159265359/8), (m_s2->GetY()*100)+10*sin(angle+3.14159265359/8), "blue");
    }
}

void Arrete::afficher()
{
    std::cout<<m_poids<<std::endl;
}

void Arrete::afficherIndice()
{
    std::cout<<m_indice<<" : "<<m_s1->GetIndice()<<" "<<m_s2->GetIndice()<<" "<<m_poids<<std::endl;
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
    } // si la méthode return 1, on ajoute un degré, si elle return 0, on n'en ajoute pas
    return 0;
}

bool Arrete::check_Sommets(Sommet* s1,Sommet* s2)
{
    if((s1->GetIndice()==m_s1->GetIndice() && s2->GetIndice()==m_s2->GetIndice())
       || (s1->GetIndice()==m_s2->GetIndice() && s2->GetIndice()==m_s1->GetIndice()))
       return true;
    else return false;
}

void Arrete::effacer_adj(std::vector <int> m_adjacent[100])
{
     for(size_t i=0; i<m_adjacent[m_s1->GetIndice()].size(); ++i)
    {
        if(m_adjacent[m_s1->GetIndice()][i]==m_s2->GetIndice())
        {
            m_adjacent[m_s1->GetIndice()].erase(m_adjacent[m_s1->GetIndice()].begin()+i);
        }
    }
    for(size_t i=0; i<m_adjacent[m_s2->GetIndice()].size(); ++i)
    {
        if(m_adjacent[m_s2->GetIndice()][i]==m_s1->GetIndice())
            m_adjacent[m_s2->GetIndice()].erase(m_adjacent[m_s2->GetIndice()].begin()+i);
    }
}
