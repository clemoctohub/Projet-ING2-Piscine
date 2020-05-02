#include <string>
#include <vector>
#include <iostream>
#include "graphe.h"
#include "bibliotheque.h"

int menu(bool ponderation)  //menu d'affichage
{
    int choix=0;
    std::cout << "Choisissez votre action :" << std::endl;
    std::cout << std::endl;
    std::cout << "1: Afficher le graphe" << std::endl;
    if(ponderation==false)
        std::cout << "2: Prendre en compte un fichier ponderation" << std::endl;
    else
        std::cout << "2: Ne plus prendre en compte le fichier ponderation" << std::endl;
    std::cout << "3: Afficher et/ou sauvegarder les indices de centralite" << std::endl;
    std::cout << "4: Afficher les composantes connexes" << std::endl;
    std::cout << "5: Supprimer une arete (affichage de la difference des indices apres suppression)" << std::endl;
    std::cout << "6: Supprimer un sommet" << std::endl;
    std::cout << "7: Afficher les indices sur le graphe" << std::endl;
    std::cout << "8: Quitter" << std::endl;
    std::cin >> choix;
    while(choix<1 || choix>8)
    {
        std::cout << "Veuillez rentrer une des valeurs demandees" << std::endl;
        std::cin >> choix;
    }
    return choix;
}
std::string menu2()  //menu d'affichage
{
    int choix;
    std::string fichier;
    std::cout << "Choisissez un des fichiers suivants ou rentrer le nom du fichier :" << std::endl;
    std::cout << std::endl;
    std::cout << "1: graphe1.txt" << std::endl;
    std::cout << "2: graphe2.txt" << std::endl;
    std::cout << "3: graphe3.txt" << std::endl;
    std::cout << "4: graphe4.txt" << std::endl;
    std::cout << "5: reseau_ile_reunion.txt" << std::endl;
    std::cout << "6: metro_lyon.txt" << std::endl;
    std::cout << "7: Rentrer le nom du fichier a la main" << std::endl;
    std::cin >> choix;
    while(choix<1 || choix>7)
    {
        std::cout << "Veuillez rentrer une des valeurs demandees" << std::endl;
        std::cin >> choix;
    }
    switch(choix)
        {
        case 1:
            fichier="graphe1.txt";// pour chaque action, nous appellons la methode ou la fonction qui correspond
            break;
        case 2:
            fichier="graphe2.txt";
            break;
        case 3:
            fichier="graphe3.txt";
            break;
        case 4:
            fichier="graphe4.txt";
            break;
        case 5:
            fichier="reseau_ile_reunion.txt";
            break;
        case 6:
            fichier="metro_lyon.txt";
            break;
        case 7:
            fichier="rien";
            break;
        }
        return fichier;
}

void boucle(int choix, Graphe mongraphe)
{
        std::vector <std::vector <double>> ensemble;
        while(choix!=8)              // switch permettant de choisir l'action voulut en fonction du menu enonnce plus haut
    {
        choix=menu(mongraphe.get_ponderation());
        switch(choix)
        {
        case 1:
            mongraphe.afficher(-1,ensemble);// pour chaque action, nous appellons la methode ou la fonction qui correspond
            break;
        case 2:
            mongraphe.ajout_ponderation("ponderation.txt");
            mongraphe.afficher(-1,ensemble);
            break;
        case 3:
            indicedecentralite(mongraphe,mongraphe.get_ordre(),1);
            break;
        case 4:
            mongraphe.connexite(-1);
            break;
        case 5:
            indicedecentralite(mongraphe,mongraphe.get_ordre(),0);
            mongraphe.suppr_arete(-1);
            system("cls");
            mongraphe.afficher(-1,ensemble);
            system("cls");
            std::cout<<"Voici les nouveau indices"<<std::endl;
            ensemble=indicedecentralite(mongraphe,mongraphe.get_ordre(),2);
            mongraphe.difference(ensemble);
            break;
        case 6:
            indicedecentralite(mongraphe,mongraphe.get_ordre(),0);
            mongraphe.suppr_sommet();
            system("cls");
            mongraphe.afficher(-1,ensemble);
            system("cls");
            std::cout<<"Voici les nouveau indices"<<std::endl;
            ensemble=indicedecentralite(mongraphe,mongraphe.get_ordre(),2);
            mongraphe.difference(ensemble);
            break;
        case 7:
            int choix1=0;
            ensemble=indicedecentralite(mongraphe, mongraphe.get_ordre(), 3);
            menuAfficherIndiceSVG();
            std::cin >> choix1;
            while (choix1!=5)
            {
                mongraphe.afficher(choix1,ensemble);
                menuAfficherIndiceSVG();
                std::cin >> choix1;
            }
            break;
        }
        system("cls");  // efface la console
    }
}

void menuAfficherIndiceSVG()
{
    system("cls");
    std::cout << "Choisissez l'indice que vous voulez afficher :" << std::endl;
    std::cout << std::endl;
    std::cout << "1: Indice de centralite de degre" << std::endl;
    std::cout << "2: Indice de vecteur propre" << std::endl;
    std::cout << "3: Indice de proximite" << std::endl;
    std::cout << "4: Indice de centralite d'intermediarite" << std::endl;
    std::cout << "5: Retour" << std::endl;
}
