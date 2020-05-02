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
        Sommet* m_s1;   // sommet d'origine (dans le cas ou le graphe est orient�)
        Sommet* m_s2;   // sommet d'arriv� (dans le cas ou le graphe est orient�)
        int m_indice;   // num�ro de l'ar�te
        int m_poids;    // distance, pond�ration de l'ar�te
    public:
        Arrete(Sommet* s1,Sommet* s2, int indice, int poids);
        Arrete(){}
        ~Arrete(){};
        void afficher(Svgfile &svgout,int orientation);
        void afficher();
        void set_poids(int poids);
        void set_indice(int indice);
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
        bool check_Sommets(Sommet* s1,Sommet* s2,int orientation);
        int calculdegre(Sommet* sommet, int orientation);
        void effacer_adj(std::vector <int> m_adjacent[100]);
        void add_adjacent(std::vector <int> m_adjacent[100],Arrete* aretes);
        void afficherIndice();
};

#endif // ARRETE_H_INCLUDED
