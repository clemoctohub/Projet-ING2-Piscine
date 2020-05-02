#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED
#include "svgfile.h"
#include "couleur.h"
#include "util.h"
#include "sommet.h"
#include "graphe.h"

class Arrete
{
private:
    int m_indice;   // num�ro de l'arete
    int m_poids;    // distance, ponderation de l'arete
    Sommet* m_s1;   // sommet d'origine (dans le cas ou le graphe est oriente)
    Sommet* m_s2;   // sommet d'arrive (dans le cas ou le graphe est oriente)
public:
    Arrete(Sommet* s1,Sommet* s2, int indice, int poids);
    Arrete(){}
    ~Arrete(){}
    void afficher();
    void afficherIndice();
    void set_poids(int poids);
    void set_indice(int indice);
    void afficher(Svgfile &svgout,int orientation);
    void effacer_adj(std::vector <int> m_adjacent[100]);
    void add_adjacent(std::vector <int> m_adjacent[100],Arrete* aretes);
    bool check_Sommets(Sommet* s1,Sommet* s2,int orientation);
    int calculdegre(Sommet* sommet, int orientation);
    int get_s1()
    {
        return m_s1->GetIndice();
    }
    int get_s2()
    {
        return m_s2->GetIndice();
    }
    int get_poids()
    {
        return m_poids;
    }
    int get_indice()
    {
        return m_indice;
    }
};

#endif // ARRETE_H_INCLUDED
