#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <string>
#include "svgfile.h"
#include "couleur.h"
#include "util.h"

class Sommet
{
private :
    std::string m_nom;
    int m_indice;
    int m_x;
    int m_y;
public :
    Sommet(int indice, std::string nom, int x, int y);
    void afficher(Svgfile &svgout);
    int GetX();
    int GetY();
    int GetIndice();
};

#endif // SOMMET_H_INCLUDED
