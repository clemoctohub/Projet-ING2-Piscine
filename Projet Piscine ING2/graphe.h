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
    int m_orientation;  /// booleen -> 1 : oriente ; 0 : non-oriente
    int m_ordre;        /// oredre du graphe
    int m_taille;       /// taille du graphe
    double m_lambda;    /// permettant la fonction "vecteur_propre()"

    bool m_dec[100];
    double m_compteur;
    double m_ppc;
    int m_nbr_aretes;
    bool m_ponderation; /// O : non pondere ; 1 : pondere

    std::vector <Sommet*> m_sommet; /// vecteur permettant d'avoir acces a tous les sommmets du graphe
    std::vector <Arrete*> m_arrete; /// vecteur permettant d'avoir acces a toutes les aretes du graphe
    std::vector <double> m_CVP;
    std::vector <double> m_CP;
    std::vector <int> m_adjacent[100]; /// vecteur permettant d'avoir acces a toutes les adjacences du graphe

public:
    Graphe(std::string nomFichier); // constructeur
    ~Graphe(){}
    void tarjan();
    void k_connexite();
    void suppr_sommet();
    void ajout_ponderation(); // ajoute du fichier contenant les ponderations
    void suppr_arete(int suppr);
    void affichercompo(std::vector <int> predecesseurs,int nb);
    void afficherBFS(std::vector <int> predecesseur, int start);
    void difference(std::vector <std::vector <double>> ensemble);
    void parcour_DFS_no_ponderation(int numS,int fin,int nbr_aretes); // parcour DFS sans pond�ration
    void recup_pred(std::vector<int> pred[100],int actuel,int autre);
    void afficher(int choix,std::vector <std::vector <double>> ensemble); // affichage le graphe
    bool get_ponderation();
    bool connexite(int truc);
    int algo_dijkstra(int debut, int fin);//calcul chemin le plus court en fonction ds poids des aretes
    double algo_dijkstra_intermediarite(int debut, int fin,bool deja_vu[50][50]);
    std::vector <int> get_adjacent(int sommet);
    std::vector <int> parcourBFS(int start);
    std::vector <double> centralite_proximite(); // calcul de l'indice de centralite de proximite
    std::vector <double> vecteur_propre();  // calcul de l'indice de vecteur propre
    std::vector <double> centralite_intermediarite();
    std::vector <std::vector<double>> calculdegre(); // calcul des degres de chaque sommet
    int get_ordre(){
        return m_ordre;
    }
    int get_orientation(){
        return m_orientation;
    }
};

#endif /// GRAPHE_H_INCLUDED
