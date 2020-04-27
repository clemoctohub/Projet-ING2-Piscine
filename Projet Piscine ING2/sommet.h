#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <string>

class Sommet
{
private :
    std::string m_nom;
    int m_indice;
    int m_x;
    int m_y;
public :
    Sommet(int indice, std::string nom, int x, int y);
};

#endif // SOMMET_H_INCLUDED
