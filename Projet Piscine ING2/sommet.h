#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <string>
#include "svgfile.h"
#include "couleur.h"
#include "util.h"
#include <vector>
#include "graphe.h"

class Sommet
{
private :
    std::string m_nom;
    int m_indice;
    int m_x;  // coordonn�e pour affichage dans fichier svg
    int m_y;  // coordonn�e pour affichage dans fichier svg
public :
    Sommet(int indice, std::string nom, int x, int y);
    ~Sommet(){};
    void afficher(Svgfile &svgout);
    int GetX();
    int GetY();
    int GetIndice();
    void BFS(std::vector <int>& etats,std::vector <int>& predecesseurs,std::vector <int>& file, Graphe* mongraphe);
    void affichernum();
};

#endif // SOMMET_H_INCLUDED
