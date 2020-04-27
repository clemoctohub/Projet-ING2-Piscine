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
    std::vector <Sommet*> m_sommet;
    std::vector <Arrete*> m_arrete;
    std::vector <double> m_CVP;
    std::vector <double> m_adjacent[100];
public:
    Graphe(std::string nomFichier);
    void ajout_ponderation(std::string pondFichier);
    void afficher();
    void vecteur_propre();
};

#endif // GRAPHE_H_INCLUDED
