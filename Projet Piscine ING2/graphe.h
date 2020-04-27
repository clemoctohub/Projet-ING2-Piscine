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
    std::vector <Sommet*> m_sommet;
    std::vector <Arrete*> m_arrete;
public:
    Graphe(std::string nomFichier);
    void ajout_ponderation(std::string pondFichier);
    void afficher();
};

#endif // GRAPHE_H_INCLUDED
