#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <vector>
#include "sommet.h"
#include "arrete.h"
#include "svgfile.h"
#include "couleur.h"
#include "util.h"

class Graphe
{
private:
    int m_orientation;
    int m_ordre;
    int m_taille;
    double m_lambda;

    bool m_dec[100];
    int m_nbr_aretes;
    bool m_ponderation;

    std::vector <Sommet*> m_sommet;
    std::vector <Arrete*> m_arrete;
    std::vector <double> m_CVP;
    std::vector <double> m_CP;
    std::vector <int> m_adjacent[100];

public:
    Graphe(std::string nomFichier);
    void ajout_ponderation(std::string pondFichier);
    void vecteur_propre();
    void parcour_DFS_no_ponderation(int numS,int fin,int nbr_aretes);
    int algo_dijkstra(int debut, int fin);
    void centralite_proximite();
    std::vector <std::vector<float>> calculdegre();
    void afficher();
};

#endif // GRAPHE_H_INCLUDED
