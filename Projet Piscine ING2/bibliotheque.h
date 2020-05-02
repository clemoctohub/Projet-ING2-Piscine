#ifndef BIBLIOTHEQUE_H_INCLUDED
#define BIBLIOTHEQUE_H_INCLUDED

void boucle(int choix, Graphe mongraphe);
void afficher (std::vector <float> v1);
std::vector <float> calculdegrenorma(std::vector <float> degresnorma);
std::vector <std::vector <double>> indicedecentralite(Graphe mongraphe,int ordre, int suppr);
void afficher_indice(std::vector <std::vector <double>> v1,int ordre);
void afficher_indice_svg(Graphe mongraphe);
int menu(bool m_ponderation);
std::string menu2();
std::string menuPonderation();
void menuAfficherIndiceSVG();

#endif // BIBLIOTHEQUE_H_INCLUDED
