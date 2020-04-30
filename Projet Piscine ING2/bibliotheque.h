#ifndef BIBLIOTHEQUE_H_INCLUDED
#define BIBLIOTHEQUE_H_INCLUDED

void afficher (std::vector <float> v1);
std::vector <float> calculdegrenorma(std::vector <float> degresnorma);
void indicedecentralite(Graphe mongraphe,int ordre, int suppr);
void afficher_indice (std::vector <std::vector <double>> v1,int ordre);
void afficher_indice_svg(Graphe mongraphe, Svgfile &svgout);

#endif // BIBLIOTHEQUE_H_INCLUDED
