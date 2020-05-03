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
    Sommet* m_s1;   /// sommet d'origine (dans le cas ou le graphe est oriente)
    Sommet* m_s2;   /// sommet d'arrive (dans le cas ou le graphe est oriente)
    int m_indice;   /// num�ro de l'arete
    int m_poids;    /// distance, ponderation de l'arete
public:
    Arrete(Sommet* s1,Sommet* s2, int indice, int poids);///dans le constructeur on a deux sommets aces un poids et un indice
    Arrete(){}
    ~Arrete(){}
    void afficher(); /// affiche le poids de l'arete
    void afficherIndice(); /// affiche les indices des sommets de l'arete
    void set_poids(int poids);///change le poids
    void set_indice(int indice);///change l'indice
    void afficher(Svgfile &svgout,int orientation); /// affiche l'arete en svg et dans la console
    void effacer_adj(std::vector <int> m_adjacent[100]); /// efface les adjacents d'une arete
    void add_adjacent(std::vector <int> m_adjacent[100],Arrete* aretes); /// ajoute les adjacents lorsqu'on rajoute une arete
    bool check_Sommets(Sommet* s1,Sommet* s2,int orientation); /// permet de verifier l'existance d'une arete entre deux sommets
    int calculdegre(Sommet* sommet, int orientation); /// booleen verifiant l'existance d'une arete sur un sommet
    int get_s1()///retourne le sommet 1
    {
        return m_s1->GetIndice();
    }
    int get_s2()///retourne le sommet 2
    {
        return m_s2->GetIndice();
    }
    int get_poids()///retourne le poids
    {
        return m_poids;
    }
    int get_indice()///retourne l'indice
    {
        return m_indice;
    }
};

#endif /// ARRETE_H_INCLUDED
