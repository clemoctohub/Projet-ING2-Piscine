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
        Arrete(Sommet* s1,Sommet* s2, int indice, int poids);
        Arrete(){}
        void afficher(Svgfile &svgout);
        void afficher();
        void set_poids(int poids);
        void set_indice(int indice);
        int get_poids()
        {
            return m_poids;
        }
        int get_indice()
        {
            return m_indice;
        }
        bool check_Sommets(Sommet* s1,Sommet* s2);
        int calculdegre(Sommet* sommet, int orientation);
};

#endif // ARRETE_H_INCLUDED
