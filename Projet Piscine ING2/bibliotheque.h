#ifndef BIBLIOTHEQUE_H_INCLUDED
#define BIBLIOTHEQUE_H_INCLUDED

void menuAfficherIndiceSVG();
void afficher (std::vector <float> v1);
void boucle(int choix, Graphe mongraphe);
void afficher_indice_svg(Graphe mongraphe);
void afficher_indice(std::vector <std::vector <double>> v1,int ordre);
int menu(bool m_ponderation);
std::vector <float> calculdegrenorma(std::vector <float> degresnorma);
std::vector <std::vector <double>> indicedecentralite(Graphe mongraphe,int ordre, int suppr);
std::string menu2();
std::string menuPonderation();

#endif // BIBLIOTHEQUE_H_INCLUDED
