#include <string>
#include <vector>
#include <iostream>
#include "graphe.h"
#include "bibliotheque.h"

int menu(bool ponderation)  ///menu d'affichage principal
{
    int choix=0;
    std::cout << "Choisissez votre action :" << std::endl;
    std::cout << std::endl;
    std::cout << "1: Afficher le graphe" << std::endl;
    if(ponderation==false)///on affiche une phrase diff en fonction de si le fichier de ponderation a ete charge ou non
        std::cout << "2: Prendre en compte un fichier ponderation" << std::endl;
    else
        std::cout << "2: Ne plus prendre en compte le fichier ponderation" << std::endl;
    std::cout << "3: Afficher et/ou sauvegarder les indices de centralite" << std::endl;
    std::cout << "4: Afficher les composantes connexes" << std::endl;
    std::cout << "5: Supprimer une arete (affichage de la difference des indices apres suppression)" << std::endl;
    std::cout << "6: Afficher les indices sur le graphe" << std::endl;
    std::cout << "7: Quitter" << std::endl;
    std::cin >> choix;
    while(choix<1 || choix>7)///tant que la valeur est fausse on redemande
    {
        std::cout << "Veuillez rentrer une des valeurs demandees" << std::endl;
        std::cin >> choix;
    }
    return choix;
}
std::string menu2()  ///menu d'affichage pour le choix du fichier
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
    switch(choix)///en fonction du chiffre entre on charge le fichier correspondant
        {
        case 1:
            fichier="graphe1.txt";
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

std::string menuPonderation()  ///menu d'affichage pour le choix du fichier de ponderation
{
    int choix;
    std::string fichier;
    system("cls");
    std::cout << "Choisissez un des fichiers de ponderation suivants ou rentrer le nom du fichier :" << std::endl;
    std::cout << std::endl;
    std::cout << "1: ponderation_graphe1.txt" << std::endl;
    std::cout << "2: ponderation_graphe2.txt" << std::endl;
    std::cout << "3: ponderation_metro_lyon.txt" << std::endl;
    std::cout << "4: Rentrer le nom du fichier a la main" << std::endl;
    std::cin >> choix;
    while(choix<1 || choix>4)
    {
        std::cout << "Veuillez rentrer une des valeurs demandees" << std::endl;
        std::cin >> choix;
    }
    switch(choix)
        {
        case 1:
            fichier="ponderation_graphe1.txt"; /// pour chaque action, nous appellons la methode ou la fonction qui correspond
            break;
        case 2:
            fichier="ponderation_graphe2.txt";
            break;
        case 3:
            fichier="ponderation_metro_lyon.txt";
            break;
        case 4:
            fichier="rien";
            break;
        }
    return fichier;
}

void boucle(int choix, Graphe mongraphe)
{
        std::vector <std::vector <double>> ensemble;
        while(choix!=7)              /// switch permettant de choisir l'action voulut en fonction du menu enonnce plus haut
    {
        choix=menu(mongraphe.get_ponderation()); /// pour chaque action, nous appellons la methode ou la fonction qui correspond
        switch(choix)
        {
        case 1:
            mongraphe.afficher(-1,ensemble);///permet d'afficher le graphe
            break;
        case 2:
            mongraphe.ajout_ponderation(); ///ajoute la ponderation et affiche a nouveau les donnees du graphe
            mongraphe.afficher(-1,ensemble);
            break;
        case 3:
            indicedecentralite(mongraphe,mongraphe.get_ordre(),1); ///appel la fonction qui calcule tous les indices et les affiche
            break;
        case 4:
            mongraphe.connexite(1);///verifie que le graphe est connexe
            break;
        case 5:///ici on calcule les indices une premiere fois pour etre sur de les avoir
            indicedecentralite(mongraphe,mongraphe.get_ordre(),0);
            mongraphe.suppr_arete(-1);///on supprime l'arrete
            system("cls");
            mongraphe.afficher(-1,ensemble);///on affiche le graphe
            system("cls");
            std::cout<<"Voici les nouveau indices"<<std::endl;
            ensemble=indicedecentralite(mongraphe,mongraphe.get_ordre(),2);///on recalcule les indices et on les affiche
            mongraphe.difference(ensemble);///on calcule la difference et on l'affiche
            break;
        case 6:
            int choix1=0;
            ensemble=indicedecentralite(mongraphe, mongraphe.get_ordre(), 3);///on recupere les indices
            menuAfficherIndiceSVG();///on les affiche sur l'output.svg
            std::cin >> choix1;
            while (choix1!=5)
            {
                mongraphe.afficher(choix1,ensemble);
                menuAfficherIndiceSVG();
                std::cin >> choix1;
            }
            break;
        }
        system("cls");  /// efface la console
    }
}

void menuAfficherIndiceSVG()///menu qui permet de choisir l'indice a afficher
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
