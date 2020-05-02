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
    double m_x;  // coordonnee pour affichage dans fichier svg
    double m_y;  // coordonnee pour affichage dans fichier svg
public :
    Sommet(int indice, std::string nom, double x, double y);
    ~Sommet(){};
    void afficher(Svgfile &svgout, std::vector <int> classement, int nomin, Graphe* mongraphe,int indice, std::vector <std::vector <double>> ensemble);
    double GetX();
    double GetY();
    int GetIndice();
    void BFS(std::vector <int>& etats,std::vector <int>& predecesseurs,std::vector <int>& file, Graphe* mongraphe);
    void affichernum();
};

#endif // SOMMET_H_INCLUDED
