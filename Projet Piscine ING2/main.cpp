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
    std::cout << "6: Afficher les indices sur le graphe" << std::endl;
    std::cout << "7: Quitter" << std::endl;
    std::cin >> choix;
    while(choix<1 || choix>7)
    {
        std::cout << "Veuillez rentrer une des valeurs demandees" << std::endl;
        std::cin >> choix;
    }
    return choix;
}

int main()
{
    int choix=0;
    std::vector <std::vector <double>> ensemble;
    std::string nomFichier;    // on permet a l'utilisateur de choisir le fichier qu'il veut ouvrir
    std::cout << "Rentrez le nom du fichier" << std::endl;
    std::cin>>nomFichier;
    Graphe mongraphe(nomFichier);
    mongraphe.k_connexite();
    while(choix!=7)              // switch permettant de choisir l'action voulut en fonction du menu �nonnc� plus haut
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
            indicedecentralite(mongraphe,mongraphe.get_ordre(),1);
            break;
        case 4:
            mongraphe.connexite(1);
            break;
        case 5:
            indicedecentralite(mongraphe,mongraphe.get_ordre(),0);
            mongraphe.suppr_arete();
            system("cls");
            mongraphe.afficher();
            system("cls");
            std::cout<<"Voici les nouveau indices"<<std::endl;
            ensemble=indicedecentralite(mongraphe,mongraphe.get_ordre(),2);
            mongraphe.difference(ensemble);
            break;
        case 6:
            afficher_indice_svg(mongraphe);
            break;
        }
        system("cls");  // efface la console
    }
    return 0;
}
