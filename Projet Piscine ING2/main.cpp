#include <iostream>
#include "graphe.h"
#include <string>
#include "bibliotheque.h"

int menu()
{
    int choix=0;
    std::cout << "Choisissez votre action :" << std::endl;
    std::cout << std::endl;
    std::cout << "1: Afficher le graphe" << std::endl;
    std::cout << "2: Prendre en compte un fichier ponderation" << std::endl;
    std::cout << "3: Afficher les indices de centralite" << std::endl;
    std::cout << "5: Quitter" << std::endl;
    std::cin >> choix;
    return choix;
}

int main()
{
    int choix=0;
    /*std::string nomFichier;
    std::cin>>nomFichier;*/
    Graphe mongraphe("arrete.txt");
    while(choix!=5)
    {
        choix=menu();
        switch(choix)
        {
        case 1:
            mongraphe.afficher();
            break;
        case 2:
            mongraphe.ajout_ponderation("ponderation.txt");
            mongraphe.afficher();
            break;
        case 3:
            indicedecentralite(mongraphe);
            break;
        case 4:
            mongraphe.vecteur_propre();
            mongraphe.centralite_proximite();
            break;
        }
        system("cls");
    }
    return 0;
}
