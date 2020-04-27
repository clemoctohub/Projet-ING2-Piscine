#include <iostream>
#include "graphe.h"
#include <string>

int main()
{
    std::string nomFichier;
    std::cin>>nomFichier;
    Graphe mongraphe(nomFichier);
    mongraphe.afficher();
    return 0;
}
