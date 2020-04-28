#include <iostream>
#include "graphe.h"
#include <string>
#include "bibliotheque.h"

int menu()  //menu d'affichage
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

void calcul_centralite(Graphe mongraphe){    // appel de toutes les fonctions relatives aux indices de centralité
    indicedecentralite(mongraphe);
    mongraphe.vecteur_propre();
    mongraphe.centralite_proximite();
}

int main()
{
    int choix=0;
    /*std::string nomFichier;    // on permet à l'utilisateur de choisir le fichier qu'il veut ouvrir
    std::cin>>nomFichier;*/
    Graphe mongraphe("arrete.txt");
    while(choix!=5)              // switch permettant de choisir l'action voulut en fonction du menu énonncé plus haut
    {
        choix=menu();
        switch(choix)
        {
        case 1:
            mongraphe.afficher();// pour chaque action, nous appellons la méthode ou la fonction qui correspond
            break;
        case 2:
            mongraphe.ajout_ponderation("ponderation.txt");
            mongraphe.afficher();
            break;
        case 3:
            calcul_centralite(mongraphe);
            break;
        }
        system("cls");  // efface la console
    }
    return 0;
}
