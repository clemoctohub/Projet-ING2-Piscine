#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED
#include "svgfile.h"
#include "couleur.h"
#include "util.h"
#include "sommet.h"

class Arrete
{
    private:
        Sommet* m_s1;   // sommet d'origine (dans le cas ou le graphe est orienté)
        Sommet* m_s2;   // sommet d'arrivé (dans le cas ou le graphe est orienté)
        int m_indice;   // numéro de l'arête
        int m_poids;    // distance, pondération de l'arête
    public:
        Arrete(Sommet* s1,Sommet* s2, int indice, int poids);  //constructeur
        void afficher(Svgfile &svgout);         // affichage de l'arete dans fichier svg
        void set_poids(int poids);              // étant donné que le poids peut être ajouté dans un second temps, un set_poids était nécessaire
        int calculdegre(Sommet* sommet, int orientation); // calcul le degré d'un sommet
};

#endif // ARRETE_H_INCLUDED
