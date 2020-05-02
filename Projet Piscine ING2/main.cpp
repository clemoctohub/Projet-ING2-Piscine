#include <iostream>
#include "graphe.h"
#include <string>
#include "bibliotheque.h"

int main()
{
    int choix=0;
    std::string nomFichier;
    nomFichier=menu2(); /// menu compose des differents fichiers propose a l'utilisateur
    if(nomFichier=="rien") /// si le fichier que l'utilisateur veut utiliser n'est pas dans la liste proposee on permet a l'utilisateur de choisir le fichier qu'il veut ouvrir
    {
        std::cout << "Rentrez le nom du fichier" << std::endl;
        std::cin>>nomFichier;
    }
    system("cls");
    Graphe mongraphe(nomFichier); /// on ouvre de fichier choisit par l'utilisateur
    mongraphe.k_connexite(); ///des l'ouverture du fichier on test la connexite du fichier
    boucle(choix, mongraphe); /// boucle appellant le menu principal et les menus segondaires
    return 0;
}
