#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED
#include "svgfile.h"
#include "couleur.h"
#include "util.h"
#include "sommet.h"

class Arrete
{
    private:
        Sommet* m_s1;   // sommet d'origine (dans le cas ou le graphe est orient�)
        Sommet* m_s2;   // sommet d'arriv� (dans le cas ou le graphe est orient�)
        int m_indice;   // num�ro de l'ar�te
        int m_poids;    // distance, pond�ration de l'ar�te
    public:
        Arrete(Sommet* s1,Sommet* s2, int indice, int poids);  //constructeur
        void afficher(Svgfile &svgout);         // affichage de l'arete dans fichier svg
        void set_poids(int poids);              // �tant donn� que le poids peut �tre ajout� dans un second temps, un set_poids �tait n�cessaire
        int calculdegre(Sommet* sommet, int orientation); // calcul le degr� d'un sommet
};

#endif // ARRETE_H_INCLUDED
