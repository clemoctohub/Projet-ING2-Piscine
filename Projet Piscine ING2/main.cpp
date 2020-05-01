#include <iostream>
#include "graphe.h"
#include <string>
#include "bibliotheque.h"

int main()
{
    int choix=0;
    std::string nomFichier;
    nomFichier=menu2();
    if(nomFichier=="rien") // on permet a l'utilisateur de choisir le fichier qu'il veut ouvrir
    {
        std::cout << "Rentrez le nom du fichier" << std::endl;
        std::cin>>nomFichier;
    }
    system("cls");
    Graphe mongraphe(nomFichier);
    mongraphe.k_connexite();
    boucle(choix, mongraphe);
    return 0;
}
