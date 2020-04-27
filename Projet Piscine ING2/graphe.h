#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <vector>

class Graphe
{
private:
    int m_orientation;
    int m_ordre;
    int m_taille;
    std::vector <Sommet*> m_sommet;
    std::vector <Liaison*> m_liaison;
public:
    Graphe::Graphe(std::string fichier);

};

#endif // GRAPHE_H_INCLUDED
