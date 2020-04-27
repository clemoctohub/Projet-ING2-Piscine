#include <iostream>
#include "graphe.h"
#include <string>

int main()
{
    /*std::string nomFichier;
    std::cin>>nomFichier;*/
    Graphe mongraphe("arrete.txt");
    mongraphe.afficher();
    return 0;
}
