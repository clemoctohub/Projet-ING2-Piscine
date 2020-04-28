#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <vector>
#include "sommet.h"
#include "arrete.h"
#include "svgfile.h"
#include "couleur.h"
#include "util.h"

class Graphe
{
private:
    int m_orientation;  // bool�en -> 1 : orient� ; 0 : non-orient�
    int m_ordre;        // oredre du graphe
    int m_taille;       // taille du graphe
    double m_lambda;    // permettant la fonction "vecteur_propre()"

    bool m_dec[100];
    int m_nbr_aretes;
    bool m_ponderation; // O : non pond�r� ; 1 : pond�r�

    std::vector <Sommet*> m_sommet; // vecteur permettant d'avoir acc�s � tous les sommmets du graphe
    std::vector <Arrete*> m_arrete; // vecteur permettant d'avoir acc�s � toutes les ar�tes du graphe
    std::vector <double> m_CVP;
    std::vector <double> m_CP;
    std::vector <int> m_adjacent[100]; // vecteur permettant d'avoir acc�s � toutes les adjacences du graphe

public:
    Graphe(std::string nomFichier); // constructeur
    void ajout_ponderation(std::string pondFichier); // ajoute du fichier contenant les pond�rations
    std::vector <double> vecteur_propre();  // calcul de l'indice de vecteur propre
    void parcour_DFS_no_ponderation(int numS,int fin,int nbr_aretes); // parcour DFS sans pond�ration
    void parcour_DFS_with_ponderation(int numS,int fin,int nbr_aretes); // parcour DFS avec pond�ration
    std::vector <double> centralite_proximite(); // calcul de l'indice de centralit� de proximit�
    std::vector <std::vector<double>> calculdegre(); // calcul des degr�s de chaque sommet
    void afficher(); // affichage console du graphe
};

#endif // GRAPHE_H_INCLUDED
