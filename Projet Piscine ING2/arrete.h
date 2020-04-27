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
        void afficher(Svgfile &svgout);
        void set_poids(int poids);
        ~Arrete();
};

#endif // ARRETE_H_INCLUDED
