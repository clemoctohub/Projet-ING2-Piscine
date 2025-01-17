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

void Arrete::afficher(Svgfile &svgout, int orientation)  /// recoit le fichier svg afin de faire l'affichage dedans ainsi que l'orientation
{
    std::cout<<m_indice<<"/ sommet 1 :"<<m_s1->GetIndice()<<" / sommet 2 : "<<m_s2->GetIndice()<<" / poids : "<<m_poids<<std::endl;
    if (orientation==0)   /// si le graphe n'est pas oriente
    {
        svgout.addLine(m_s1->GetX()*100, m_s1->GetY()*100, m_s2->GetX()*100, m_s2->GetY()*100, "blue"); /// on dessine l'arete
    }
    else  /// si le graphe est oriente
    {
        svgout.addLine(m_s1->GetX()*100, m_s1->GetY()*100, m_s2->GetX()*100, m_s2->GetY()*100, "blue"); /// on dessine l'arete
        double x2,y2,angle=0;
        x2=(m_s2->GetX()*100)-(m_s1->GetX()*100); /// on "deplace" le vecteur de l'arete pour le mettre a 0
        y2=(m_s2->GetY()*100)-(m_s1->GetY()*100);
        angle=acos((100*x2)/(100*sqrt(x2*x2+y2*y2))); /// on calcule l'angle entre le vecteur et l'axe des abcisses
        angle=angle-3.14159265359; /// on enleve pi afin de calculer l'angle complementaire de ce dernier
        if (y2<0) /// si l'arete est orientee vers le haut
        {
            angle=-angle; /// on prend l'inverse de son angle
        }
        ///pour les valeurs des 2 points manquant du triangle pour dessiner la fleche, on enleve/rajoute un peut de valeur a l'angle afin d'avoir l'ecart entre les 2 points
        svgout.addTriangle(m_s2->GetX()*100, m_s2->GetY()*100, (m_s2->GetX()*100)+12*cos(angle-3.14159265359/8), (m_s2->GetY()*100)+12*sin(angle-3.14159265359/8), (m_s2->GetX()*100)+12*cos(angle+3.14159265359/8), (m_s2->GetY()*100)+12*sin(angle+3.14159265359/8), "blue");
    }
}

void Arrete::afficher() ///affiche seulement le poids
{
    std::cout<<m_poids<<std::endl;
}

void Arrete::afficherIndice() ///affiche l'ensemble des indices d'une arete
{
    std::cout<<m_indice<<"/ sommet 1 :"<<m_s1->GetIndice()<<" / sommet 2 : "<<m_s2->GetIndice()<<" / poids : "<<m_poids<<std::endl;
}

void Arrete::set_poids(int poids) ///change le poids
{
    m_poids = poids;
}

void Arrete::set_indice(int indice)///modifie l'indice d'une arete
{
    m_indice = indice;
}

int Arrete::calculdegre(Sommet* sommet, int orientation)
{
    if (orientation == 0)  /// si le graphe est oriente ou non, le calcul de degre ne se fait pas de la meme maniere
    {
        if (m_s1->GetIndice()==sommet->GetIndice() || m_s2->GetIndice()==sommet->GetIndice()) /// si le graphe n'est pas oriente, on ajoute un degre a chaque fois que l'un des deux sommets d'une arete est le meme que le sommet en question
            return 1;
        else
            return 0;
    }
    if (orientation == 1)
    {
        if (m_s1->GetIndice()==sommet->GetIndice()) /// si le graphe est oriente, on ajoute un degres a chaque fois que le sommet d'arrive (le deuxieme) est le meme que le sommet en question
            return 1;
        else
            return 0;
    } /// si la methode return 1, on ajoute un degre, si elle return 0, on n'en ajoute pas
    return 0;
}

bool Arrete::check_Sommets(Sommet* s1,Sommet* s2,int orientation) /// permet de verifier l'existance d'une arete
{
    if(orientation==0) /// si le graphe n'est pas oriente
    { ///on verifie si l'arete qui appelle ce ssprg relie bien les deux sommets envoye. Dans ce cas on verifie le tableau d'adjacence dans les deux sens
        if((s1->GetIndice()==m_s1->GetIndice() && s2->GetIndice()==m_s2->GetIndice())
        || (s1->GetIndice()==m_s2->GetIndice() && s2->GetIndice()==m_s1->GetIndice()))
            return true;
        else return false;
    }
    else if(orientation==1) /// si le graphe est oriente
    {///on fait la meme chose mais on verifie dans un seul sens car l'arete ne va que dans un sens
        if(s1->GetIndice()==m_s1->GetIndice() && s2->GetIndice()==m_s2->GetIndice())
            return true;
        else return false;
    }
    return true;
}

void Arrete::effacer_adj(std::vector <int> m_adjacent[100]) /// efface les adjacents d'une arete
{
    for(size_t i=0; i<m_adjacent[m_s1->GetIndice()].size(); ++i)
        if(m_adjacent[m_s1->GetIndice()][i]==m_s2->GetIndice())
            m_adjacent[m_s1->GetIndice()].erase(m_adjacent[m_s1->GetIndice()].begin()+i);

    for(size_t i=0; i<m_adjacent[m_s2->GetIndice()].size(); ++i)
        if(m_adjacent[m_s2->GetIndice()][i]==m_s1->GetIndice())
            m_adjacent[m_s2->GetIndice()].erase(m_adjacent[m_s2->GetIndice()].begin()+i);
}

void Arrete::add_adjacent(std::vector <int> m_adjacent[100],Arrete* aretes) /// ajoute les adjacents lorsqu'il y a une arete
{
    for(size_t i=0; i<m_adjacent[m_s1->GetIndice()].size(); ++i)
        if(m_adjacent[m_s1->GetIndice()][i]==m_s2->GetIndice())
            m_adjacent[m_s1->GetIndice()].insert(m_adjacent[m_s1->GetIndice()].begin()+i,aretes->get_indice());

    for(size_t i=0; i<m_adjacent[m_s2->GetIndice()].size(); ++i)
        if(m_adjacent[m_s2->GetIndice()][i]==m_s1->GetIndice())
            m_adjacent[m_s2->GetIndice()].insert(m_adjacent[m_s2->GetIndice()].begin()+i,aretes->get_indice());
}
