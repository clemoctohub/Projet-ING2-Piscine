#include <iostream>
#include "graphe.h"
#include <string>

int main()
{
    std::string nomFichier;


    std::cin>>nomFichier;
    Graphe mongraphe(nomFichier);

    std::cout << "Salut";
    return 0;
}
