#include <iostream>
#include "graphe.h"
#include <string>

int menu()
{
    int choix=0;
    std::cout << "Choisissez votre action :" << std::endl;
    std::cout << std::endl;
    std::cout << "1: Afficher le graphe" << std::endl;
    std::cout << "2: Parcourir entier de Dijkstra" << std::endl;
    std::cout << "3: Aller d'un point a un autre par le plus court chemin" << std::endl;
    std::cout << "4: Quitter" << std::endl;
    std::cin >> choix;
    return choix;
}

int main()
{
    int choix=0;
    /*std::string nomFichier;
    std::cin>>nomFichier;*/
    Graphe mongraphe("arrete.txt");
    choix=menu();
    switch(choix)
    {
    case 1:
        mongraphe.afficher();
    }
    return 0;
}
