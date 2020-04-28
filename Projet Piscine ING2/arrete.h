#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED
#include "svgfile.h"
#include "couleur.h"
#include "util.h"
#include "sommet.h"

class Arrete
{
    private:
        Sommet* m_s1;
        Sommet* m_s2;
        int m_indice;
        int m_poids;
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
