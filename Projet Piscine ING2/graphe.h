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

    bool m_dec[100]; ///tableau qui verifie si on a deja visite un sommet ou pas
    double m_compteur; ///compte le nbr de fois ou on passe par un sommet pour l'indice de centralite d'intermediarite
    double m_ppc; ///utiliser pour connaitre le nbr de chemin le plus court
    int m_nbr_aretes;///permet de recuperer le nbr d'aretes
    bool m_ponderation; /// O : non pondere ; 1 : pondere

    std::vector <Sommet*> m_sommet; /// vecteur permettant d'avoir acces a tous les sommmets du graphe
    std::vector <Arrete*> m_arrete; /// vecteur permettant d'avoir acces a toutes les aretes du graphe
    std::vector <double> m_CVP; ///utiliser pour l'algorithme de vecteur propre
    std::vector <double> m_CP; ///utiliser pour l'algorithme d'indice de centralite de proximite
    std::vector <int> m_adjacent[100]; /// vecteur permettant d'avoir acces a toutes les adjacences du graphe

public:
    Graphe(std::string nomFichier); /// constructeur
    ~Graphe(){}
    void k_connexite();///verifie la k-arete-connexite du graphe juste apres son chargement
    void ajout_ponderation(); /// ajout du fichier contenant les ponderations
    void suppr_arete(int suppr); ///supprime une arete selectionne en fonction de son indice
    void affichercompo(std::vector <int> predecesseurs,int nb);///affiche la composition de composant connexe
    void afficherBFS(std::vector <int> predecesseur, int start);///affiche le parcour BFS
    void difference(std::vector <std::vector <double>> ensemble);///calcul la difference entre les anciennes donnees et les nouvelles donnees apres suppression d'aretes
    void parcour_DFS_no_ponderation(int numS,int fin,int nbr_aretes); /// parcour DFS sans ponderation
    void recup_pred(std::vector<int> pred[100],int actuel,int autre);/// recupere les predecesseurs de sommet dans un tableau
    void afficher(int choix,std::vector <std::vector <double>> ensemble); /// affichage le graphe
    bool get_ponderation();///recupere la ponderation
    bool connexite(int truc);///verifie la connexite du graphe
    int algo_dijkstra(int debut, int fin);///calcul chemin le plus court en fonction ds poids des aretes
    double algo_dijkstra_intermediarite(int debut, int fin,bool deja_vu[50][50]);///algorithme dijkstra modifie pour les indices de centralite d'intermediarite
    std::vector <int> get_adjacent(int sommet);///retourne les adjacents
    std::vector <int> parcourBFS(int start);///debut du parcours BFS dans le graphe
    std::vector <double> centralite_proximite(); /// calcul de l'indice de centralite de proximite
    std::vector <double> vecteur_propre();  /// calcul de l'indice de vecteur propre
    std::vector <double> centralite_intermediarite(); ///algo pour calculer les indices de centralite d'intermediarite
    std::vector <std::vector<double>> calculdegre(); /// calcul des degres de chaque sommet
    int get_ordre(){
        return m_ordre;
    }
    int get_orientation(){
        return m_orientation;
    }
};

#endif /// GRAPHE_H_INCLUDED
