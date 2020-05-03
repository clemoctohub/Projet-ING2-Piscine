#ifndef BIBLIOTHEQUE_H_INCLUDED
#define BIBLIOTHEQUE_H_INCLUDED

void menuAfficherIndiceSVG(); ///menu qui affiche la selection des indices a afficher sur le fichier .svg
void afficher (std::vector <float> v1); ///affiche un vecteur de reels
void boucle(int choix, Graphe mongraphe); ///boucle du menu
void afficher_indice(std::vector <std::vector <double>> v1,int ordre); /// affichage dans la console
int menu(bool m_ponderation); ///menu  d'affichage principal
std::vector <float> calculdegrenorma(std::vector <float> degresnorma); /// calcul les degres normalisé
std::vector <std::vector <double>> indicedecentralite(Graphe mongraphe,int ordre, int suppr);
std::string menu2(); ///menu choix fichier
std::string menuPonderation(); ///menu choix fichier ponderation

#endif // BIBLIOTHEQUE_H_INCLUDED
