#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <vector>
#include "svgfile.h"
#include "couleur.h"
#include "util.h"

class Sommet;
class Arrete;

class Graphe
{
private:
    int m_orientation;  // booleen -> 1 : oriente ; 0 : non-oriente
    int m_ordre;        // oredre du graphe
    int m_taille;       // taille du graphe
    double m_lambda;    // permettant la fonction "vecteur_propre()"

    bool m_dec[100];
    int m_nbr_aretes;
    bool m_ponderation; // O : non pondere ; 1 : pondere

    std::vector <Sommet*> m_sommet; // vecteur permettant d'avoir acces a tous les sommmets du graphe
    std::vector <Arrete*> m_arrete; // vecteur permettant d'avoir acces a toutes les aretes du graphe
    std::vector <double> m_CVP;
    std::vector <double> m_CP;
    std::vector <int> m_adjacent[100]; // vecteur permettant d'avoir acces a toutes les adjacences du graphe

public:
    Graphe(std::string nomFichier); // constructeur
    void ajout_ponderation(std::string pondFichier); // ajoute du fichier contenant les ponderations
    std::vector <double> vecteur_propre();  // calcul de l'indice de vecteur propre
    void parcour_DFS_no_ponderation(int numS,int fin,int nbr_aretes); // parcour DFS sans ponderation
    void parcour_DFS_with_ponderation(int numS,int fin,int nbr_aretes); // parcour DFS avec ponderation
    std::vector <double> centralite_proximite(); // calcul de l'indice de centralite de proximite
    std::vector <std::vector<double>> calculdegre(); // calcul des degres de chaque sommet
    void afficher(); // affichage console du graphe
    void affichercompo(std::vector <int> predecesseurs,int nb);
    void connexite();
    void afficherBFS(std::vector <int> predecesseur, int start);
    std::vector <int> get_adjacent(int sommet);
    std::vector <int> parcourBFS(int start);
};

#endif // GRAPHE_H_INCLUDED
