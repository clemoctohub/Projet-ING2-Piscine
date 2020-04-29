#include <iostream>
#include <fstream>
#include "graphe.h"
#include <string>

void afficher_indice (std::vector <std::vector <double>> v1,int ordre) // affichage dans la console
{
    int h=0; // booleen evitant que "Indice de centralite normalise" s'affiche 2 fois
    std::cout<<"Indice de centralite non normalise"<<std::endl;
    for (size_t j=0; j<v1.size(); j++)
    {
        for (size_t i=0; i<v1[1].size(); i++)
        {
            std::cout<<i<<"   "<<v1[j][i]<<std::endl;
        }
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
    std::cout<<std::endl<<"Indice de centralité de proximite non normalise"<<std::endl;
    for (size_t i=0; i<v1[1].size(); i++)
        std::cout<<i<<"   "<<v1[2][i]/(ordre-1)<<std::endl;
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
        if(h==1)
            monFlux <<"\n"<< "Indice de vecteur propre\n";
        if(h==2)
            monFlux <<"\n"<< "Indice de centralite d'intermediarite\n";
        if(h==3)
            monFlux <<"\n"<< "Indice de centralite de proximite\n";
        h++;
    }
}

void indicedecentralite(Graphe mongraphe,int ordre)
{
    int sauv=0;
    std::vector <std::vector <double>> ensemble;
    ensemble=mongraphe.calculdegre();
    ensemble.push_back(mongraphe.vecteur_propre());
    ensemble.push_back(mongraphe.centralite_intermediarite());
    ensemble.push_back(mongraphe.centralite_proximite());
    afficher_indice(ensemble,ordre);
    std::cout<<std::endl<<"Voulez-vous sauvegarder ?"<<std::endl;
    std::cout<<"1:Oui   2:Non"<<std::endl;
    std::cin>>sauv;
    if(sauv==1)
    {
        sauvegarder(ensemble);
    }
}
