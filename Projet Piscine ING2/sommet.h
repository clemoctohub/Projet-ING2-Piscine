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
    int m_x;  // coordonnée pour affichage dans fichier svg
    int m_y;  // coordonnée pour affichage dans fichier svg
public :
    Sommet(int indice, std::string nom, int x, int y); // constructeur
    void afficher(Svgfile &svgout);  // affichage dans svg
    int GetX();
    int GetY();
    int GetIndice();
    void BFS(std::vector <int>& etats,std::vector <int>& predecesseurs,std::vector <int>& file, Graphe* mongraphe);
    void affichernum();
};

#endif // SOMMET_H_INCLUDED
