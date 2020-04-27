#include <iostream>
#include "graphe.h"
#include <string>
#include "bibliothèque.h"

void afficher (std::vector <float> v1)
{
    for (size_t i=0; i<v1.size(); i++)
    {
        std::cout<<i<<"   "<<v1[i]<<std::endl;
    }
    system ("pause");
}

std::vector <float> calculdegrenorma(std::vector <float> degresnorma)
{
    int a=0;
    for (size_t i=0; i<degresnorma.size(); i++)
    {
        if (degresnorma[i]>a)
        {
            a=degresnorma[i];
        }
    }
    a=a-1;
    for (size_t i=0; i<degresnorma.size(); i++)
    {
        degresnorma[i]=degresnorma[i]/a;
    }
    return degresnorma;
}

void indicedecentralite(Graphe mongraphe)
{
    std::vector <float> degres;
    std::vector <float> degresnorma;
    degres=mongraphe.calculdegre();
    degresnorma=calculdegrenorma(degres);
    afficher(degres);
    afficher(degresnorma);
}
