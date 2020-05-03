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
    int m_indice; /// indice du sommet
    std::string m_nom; /// nom du sommet
    double m_x;  /// coordonnee pour affichage dans fichier svg
    double m_y;  /// coordonnee pour affichage dans fichier svg

public :
    Sommet(int indice, std::string nom, double x, double y);///constructeur qui recoit un indice, un nom et deux coordonnees
    ~Sommet(){};
    void affichernum(); /// affiche l'indice sur la console
    void BFS(std::vector <int>& etats,std::vector <int>& predecesseurs,std::vector <int>& file, Graphe* mongraphe); /// parcour BFS
    void afficher(Svgfile &svgout, int nomin, Graphe* mongraphe,int indice, std::vector <std::vector <double>> ensemble); /// affiche le sommet dans le fichier svg et en console
    int GetIndice(); /// renvoi l'indice du sommet
    double GetX(); /// renvoi la coordonnee x du sommet
    double GetY(); /// renvoi la coordonnee y du sommet
};

#endif // SOMMET_H_INCLUDED
