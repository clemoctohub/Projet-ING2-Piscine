#include <string>
#include <vector>
#include <iostream>

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
    std::cout << "6: Rentrer le nom du fichier a la main" << std::endl;
    std::cin >> choix;
    while(choix<1 || choix>6)
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
            fichier="rien";
            break;
        }
        return fichier;
}
