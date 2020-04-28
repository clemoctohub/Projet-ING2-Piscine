#include <iostream>
#include <fstream>
#include "graphe.h"
#include <string>

void afficher_indice (std::vector <std::vector <double>> v1) // affichage dans la console
{
    int h=0; // bool�en �vitant que "Indice de centralite normalise" s'affiche 2 fois
    std::cout<<"Indice de centralite non normalise"<<std::endl;
    for (size_t j=0; j<v1.size(); j++)
    {
        for (size_t i=0; i<v1[1].size(); i++)
        {
            std::cout<<i<<"   "<<v1[j][i]<<std::endl;
        }
        if(h==0)
            std::cout<<std::endl<<"Indice de centralite normalise"<<std::endl;
        h=1;
    }
    system ("pause");
}

void sauvegarder (std::vector <std::vector <double>> v1)
{
    std::string const nomFichier("C:Sauvegarde.txt");
    std::ofstream monFlux(nomFichier.c_str());
    int h=0;
    if(!monFlux)
    {
        std::cerr << "Error : Can't open the file" << std::endl;
    }
    monFlux << "Indice de centralite non normalise\n";
    for (size_t j=0; j<v1.size(); j++)
    {
        for (size_t i=0; i<v1[1].size(); i++)
        {
            monFlux<<v1[j][i]<<"  ";
        }
        if(h==0)
            monFlux <<"\n"<< "Indice de centralite normalise\n";
        h=1;
    }
}

void indicedecentralite(Graphe mongraphe)
{
    std::vector <std::vector <double>> ensemble;
    ensemble=mongraphe.calculdegre();
    afficher_indice(ensemble);
    sauvegarder(ensemble);
    mongraphe.vecteur_propre();
    mongraphe.centralite_proximite();
}
