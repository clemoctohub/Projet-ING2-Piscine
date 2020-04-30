#include <iostream>
#include <fstream>
#include "graphe.h"
#include "bibliotheque.h"
#include <string>

void afficher_indice (std::vector <std::vector <double>> v1,int ordre,int normal) // affichage dans la console
{
    int h=0; // booleen evitant que "Indice de centralite normalise" s'affiche 2 fois
    if(normal==0)
        std::cout<<"Indice de centralite non normalise"<<std::endl;
    else{
        std::cout<<std::endl<<"Indice de centralite normalise"<<std::endl;
        ++h;
    }
    for (size_t j=normal; j<v1.size(); j++)
    {
        for (size_t i=0; i<v1[1].size(); i++)
            std::cout<<i<<"   "<<v1[j][i]<<std::endl;
        if(h==0)
            std::cout<<std::endl<<"Indice de centralite normalise"<<std::endl;
        if(h==1)
            std::cout<<std::endl<<"Indice de vecteur propre"<<std::endl;
        if(h==2)
            std::cout<<std::endl<<"Indice de centralite d'intermediarite normalise"<<std::endl;
        if(h==3)
            std::cout<<std::endl<<"Indice de centralite de proximite normalise"<<std::endl;
        h++;
    }
    if(normal == 0)
    {
        std::cout<<std::endl<<"Indice de centralité de proximite non normalise"<<std::endl;
        for (size_t i=0; i<v1[1].size(); i++)
            std::cout<<i<<"   "<<v1[4][i]/(ordre-1)<<std::endl;
    }
}


void sauvegarder (std::vector <std::vector <double>> v1)
{
    std::string const nomFichier("C:Sauvegarde.txt");
    std::ofstream monFlux(nomFichier.c_str());
    if(!monFlux)
        std::cerr << "Error : Can't open the file" << std::endl;

    monFlux << v1[1].size()<<"\n";
    for (size_t j=1; j<v1.size(); j++)
    {
        for (size_t i=0; i<v1[1].size(); i++)
            monFlux<<v1[j][i]<<"  ";
        monFlux << "\n";
    }
    monFlux.close();
}

std::vector <std::vector <double>> indicedecentralite(Graphe mongraphe,int ordre, int suppr)
{
    int sauv=0;
    std::vector <std::vector <double>> ensemble;
    ensemble=mongraphe.calculdegre();
    ensemble.push_back(mongraphe.vecteur_propre());
    ensemble.push_back(mongraphe.centralite_intermediarite());
    ensemble.push_back(mongraphe.centralite_proximite());
    if(suppr==1)
    {
        afficher_indice(ensemble,ordre,0);
        std::cout<<std::endl<<"Voulez-vous sauvegarder ?"<<std::endl;
        std::cout<<"1:Oui   2:Non"<<std::endl;
        std::cin>>sauv;
        while(sauv<1 || sauv>2)
        {
            std::cout << "Veuillez rentrer une des valeurs demandees" << std::endl;
            std::cin >> sauv;
        }
        if(sauv==1)
            sauvegarder(ensemble);
    }
    else if(suppr==0)
    {
         sauvegarder(ensemble);
    }
    else if(suppr==2)
    {
         afficher_indice(ensemble,ordre,1);
    }

    return ensemble;
}

void afficher_indice_svg(Graphe mongraphe)
{
    Svgfile svgout;
    int choix1=0;
    while (choix1!=5)
    {
        system("cls");
        std::cout << "Choisissez l'indice que vous voulez afficher :" << std::endl;
        std::cout << std::endl;
        std::cout << "1: Indice de centralite de degre" << std::endl;
        std::cout << "2: Indice de vecteur propre" << std::endl;
        std::cout << "3: Indice de proximite" << std::endl;
        std::cout << "4: Indice de centralite d'intermediarite" << std::endl;
        std::cout << "5: Retour" << std::endl;
        std::cin >> choix1;
    }
    switch(choix1)
        {
        case 1:
            //afficher_centralite();
            break;
        }
}
