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
    int m_orientation;  // booléen -> 1 : orienté ; 0 : non-orienté
    int m_ordre;        // oredre du graphe
    int m_taille;       // taille du graphe
    double m_lambda;    // permettant la fonction "vecteur_propre()"

    bool m_dec[100];
    int m_nbr_aretes;
    bool m_ponderation; // O : non pondéré ; 1 : pondéré

    std::vector <Sommet*> m_sommet; // vecteur permettant d'avoir accès à tous les sommmets du graphe
    std::vector <Arrete*> m_arrete; // vecteur permettant d'avoir accès à toutes les arêtes du graphe
    std::vector <double> m_CVP;
    std::vector <double> m_CP;
    std::vector <int> m_adjacent[100]; // vecteur permettant d'avoir accès à toutes les adjacences du graphe

public:
    Graphe(std::string nomFichier); // constructeur
    void ajout_ponderation(std::string pondFichier); // ajoute du fichier contenant les pondérations
    void vecteur_propre();  // calcul de l'indice de vecteur propre
    void parcour_DFS_no_ponderation(int numS,int fin,int nbr_aretes); // parcour DFS sans pondération
    void parcour_DFS_with_ponderation(int numS,int fin,int nbr_aretes); // parcour DFS avec pondération
    void centralite_proximite(); // calcul de l'indice de centralité de proximité
    std::vector <std::vector<double>> calculdegre(); // calcul des degrés de chaque sommet
    void afficher(); // affichage console du graphe
};

#endif // GRAPHE_H_INCLUDED
