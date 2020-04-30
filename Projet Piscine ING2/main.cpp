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
    std::cout << "3: Afficher et/ou sauvegarder les indices de centralite" << std::endl;
    std::cout << "4: Afficher les composantes connexes" << std::endl;
    std::cout << "5: Supprimer une arete" << std::endl;
    std::cout << "6: Quitter" << std::endl;
    std::cin >> choix;
    return choix;
}


int main()
{
    int choix=0;
    /*std::string nomFichier;    // on permet � l'utilisateur de choisir le fichier qu'il veut ouvrir
    std::cin>>nomFichier;*/
    Graphe mongraphe("test.txt");
    while(choix!=6)              // switch permettant de choisir l'action voulut en fonction du menu �nonnc� plus haut
    {
        choix=menu();
        switch(choix)
        {
        case 1:
            mongraphe.afficher();// pour chaque action, nous appellons la m�thode ou la fonction qui correspond
            break;
        case 2:
            mongraphe.ajout_ponderation("ponderation.txt");
            mongraphe.afficher();
            break;
        case 3:
            indicedecentralite(mongraphe,mongraphe.get_ordre());
            break;
        case 4:
            mongraphe.connexite();
            break;
        case 5:
            mongraphe.suppr_arete();
            system("cls");
            mongraphe.afficher();
            //mongraphe.difference();
            break;
        }
        system("cls");  // efface la console
    }
    return 0;
}
