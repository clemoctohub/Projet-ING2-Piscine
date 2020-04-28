#include <iostream>
#include "graphe.h"
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

Graphe::Graphe(std::string nomFichier)
{
    std::ifstream flux(nomFichier); // ouverture du fichier
    if(!flux)
        std::cerr << "Impossible d'ouvrir le fichier"; // message d'erreur si l'ouverture du fichier ne se fait pas correctement


///////////////////  Lecture du fichier et remplissage des differents attributs de la classe graphe/////////////////////////

    flux >> m_orientation >> m_ordre;

    for (int i=0; i<m_ordre; ++i)
    {
        std::string nom;
        int indice, x, y;
        flux>> indice >> nom >> x >> y;
        m_sommet.push_back(new Sommet{indice, nom, x, y});

        m_CP.push_back(0);
    }
    flux>>m_taille;
    for (int i=0; i<m_taille; ++i)
    {
        int indice,s1,s2;
        flux >> indice >> s1 >> s2;
        m_arrete.push_back(new Arrete{m_sommet[s1],m_sommet[s2],indice,0});
        //graphe non oriente
        m_adjacent[s1].push_back(s2);
        m_adjacent[s2].push_back(s1);
    }

    for(int i=0; i<100; ++i)
        m_dec[i]=false;
    m_nbr_aretes = 0;

    m_ponderation = false;
}

void Graphe::afficher()
{
    Svgfile svgout;
    svgout.addGrid();
    if(m_orientation==0)
        std::cout << "Graphe non oriente"<<std::endl;
    else
        std::cout << "Graphe oriente"<<std::endl;
    std::cout << "      Ordre = "<<m_ordre<<std::endl;
    for(size_t i=0; i<m_sommet.size(); ++i)
    {
        std::cout << "          sommet :";
        m_sommet[i]->afficher(svgout);
    }
    std::cout << std::endl<< "      Taille = "<<m_taille<<std::endl;
    for(size_t i=0; i<m_arrete.size(); ++i)
    {
        std::cout << "          arretes :";
        m_arrete[i]->afficher(svgout);
    }


    system("pause");  // afin de ne pas effacer la console
}

void Graphe::ajout_ponderation(std::string pondFichier)
{
    std::ifstream ifs(pondFichier);
    if(!ifs)
        std::cerr << "Impossible d'ouvrir le fichier"; // message d'erreur si l'ouverture du fichier ne se fait pas correctement

    int taille,indice,poids;

    ifs >> taille;

    for(int i=0; i<taille; ++i)
    {
        ifs >> indice >> poids;
        m_arrete[indice]->set_poids(poids);
    }

    m_ponderation = true;
}

std::vector <double> Graphe::vecteur_propre()
{
    int n;
    std::vector <double> buffer;
    for(n=0; n<m_ordre; ++n)
    {
        m_CVP.push_back(1);
    }

    double somme=0,c_Sommet[100],index=0;

    for(int k=0; k<m_ordre; ++k)
    {
        c_Sommet[k]=0;
    }

    while(index<50)
    {
        for(int i=0; i<m_ordre; ++i)
        {
            for(size_t j=0; j<m_adjacent[i].size(); ++j)
            {
                int temp = m_adjacent[i][j];
                c_Sommet[i] += m_CVP[temp];
            }
        }
        for(int i=0; i<m_ordre; ++i)
        {
            somme += c_Sommet[i]*c_Sommet[i];
        }
        m_lambda = sqrt(somme);

        for(int i=0; i<m_ordre; ++i)
        {
            m_CVP[i]= c_Sommet[i]/m_lambda;
        }
        ++index;
    }
    buffer=m_CVP;
    m_CVP.erase(m_CVP.begin(),m_CVP.begin()+n);
    return buffer;
}

std::vector <std::vector<double>> Graphe::calculdegre()
{
    std::vector <std::vector <double>> ensemble; // vecteur de degrés normalisés et non normalisés
    std::vector <double> degres; // vecteur de degrés
    std::vector <double> degresnormalise; // vecteur de degrés normalisés
    for (int j=0; j<m_ordre; j++) // pour chaque sommet du graphe
    {
        double degre=0;  // on initialise le degré a 0
        if (m_orientation == 0) // si le graphe n'est pas orienté
            for(size_t i=0; i<m_arrete.size(); i++) // pour toutes les arêtes du graphe
                if (m_arrete[i]->calculdegre(m_sommet[j], m_orientation)==1)
                    degre++;  // on ajoute 1 à degré si la méthode calculdegre return 1
        if (m_orientation == 1) // si le graphe est orienté
            for(size_t i=0; i<m_arrete.size(); i++)
                if (m_arrete[i]->calculdegre(m_sommet[j], m_orientation)==1)
                    degre++;
        degres.push_back(degre); // on pushback le degré du sommet calculé dans le vecteur de degrés
        degre=degre/(m_ordre-1); // afin de normaliser le degré, on le divise par le nombre de sommets-1
        degresnormalise.push_back(degre); // on pushback le degré normalisé dans le vecteur de degrés normalisés
    }
    ensemble.push_back(degres);
    ensemble.push_back(degresnormalise);
    return ensemble; // on return le vecteur contenant les degrés normalisés et non-normalisés
}

void Graphe::parcour_DFS_no_ponderation(int numS,int fin,int nbr_aretes)
{
    m_dec[numS] = true;

    if(numS==fin)
        m_nbr_aretes = nbr_aretes;
    else
        ++nbr_aretes;

    for(size_t i=0; i<m_adjacent[numS].size(); ++i)
        if(!m_dec[m_adjacent[numS][i]])
            parcour_DFS_no_ponderation(m_adjacent[numS][i],fin,nbr_aretes);
}

std::vector <double> Graphe::centralite_proximite()
{
    //faire le cas si il y a les ponderations + cas normalise et non normalise
    std::vector<double> somme;
    for(int i=0; i<m_ordre; ++i)
    {
        somme.push_back(0);
        for(int j=0; j<m_ordre; ++j)
            if(j!=i)
            {
                if(m_ponderation = true)
                {
                    parcour_DFS_no_ponderation(i,j,0);
                    somme[i] += m_nbr_aretes;
                    m_nbr_aretes = 0;
                    for(int i=0; i<100; ++i)
                        m_dec[i]=false;

                }
                else
                {

                }
            }
    }
    for(size_t i=0; i<somme.size(); ++i)
    {
        m_CP[i] = (m_ordre-1)/somme[i];
    }
    somme.erase(somme.begin(),somme.begin()+m_ordre);
    return m_CP;
}
