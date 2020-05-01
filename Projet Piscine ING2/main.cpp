#include <iostream>
#include "graphe.h"
#include <string>
#include "bibliotheque.h"

int main()
{
    int choix=0;
    std::vector <std::vector <double>> ensemble;
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
    while(choix!=7)              // switch permettant de choisir l'action voulut en fonction du menu enonnce plus haut
    {
        choix=menu(mongraphe.get_ponderation());
        switch(choix)
        {
        case 1:
            mongraphe.afficher(1);// pour chaque action, nous appellons la methode ou la fonction qui correspond
            break;
        case 2:
            mongraphe.ajout_ponderation("ponderation.txt");
            mongraphe.afficher(1);
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
            mongraphe.afficher(1);
            system("cls");
            std::cout<<"Voici les nouveau indices"<<std::endl;
            ensemble=indicedecentralite(mongraphe,mongraphe.get_ordre(),2);
            mongraphe.difference(ensemble);
            break;
        case 6:
            mongraphe.afficher(2);
            break;
        }
        system("cls");  // efface la console
    }
    return 0;
}
