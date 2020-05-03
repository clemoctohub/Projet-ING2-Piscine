#include <iostream>
#include "graphe.h"
#include "arrete.h"
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include "sommet.h"
#include "bibliotheque.h"

Graphe::Graphe(std::string nomFichier)
{
    std::ifstream flux(nomFichier); /// ouverture du fichier
    if(!flux)
        std::cerr << "Impossible d'ouvrir le fichier"; /// message d'erreur si l'ouverture du fichier ne se fait pas correctement

////////////////////////////  Lecture du fichier et remplissage des differents attributs de la classe graphe/////////////////////////////////////

    flux >> m_orientation >> m_ordre;

    for (int i=0; i<m_ordre; ++i)
    {
        std::string nom;
        int indice;
        double x, y;
        flux>> indice >> nom >> x >> y;
        m_sommet.push_back(new Sommet{indice, nom, x, y});
///on cree un nouveau sommet en recuperant les donnees du fichier
        m_CP.push_back(0);
    }
    flux>>m_taille;
    ///faire le cas pour les graphes orientes
    for (int i=0; i<m_taille; ++i)
    {
        int indice,s1,s2;
        flux >> indice >> s1 >> s2;
        m_arrete.push_back(new Arrete{m_sommet[s1],m_sommet[s2],indice,1});
///on cree une nouvelle arete de la meme maniere
        ///permet de recuperer les adjacents d'un sommet, on le remplit dans les deux sens si le graphe n'est pas oriente
        if(m_orientation==0)
        {
            m_adjacent[s1].push_back(s2);
            m_adjacent[s2].push_back(s1);
        }
        else if(m_orientation==1)
        {
            m_adjacent[s1].push_back(s2);
        }

    }

    flux.close();
    ///on initialise les autres attributs du graphe
    for(int i=0; i<100; ++i)
        m_dec[i]=false;
    m_nbr_aretes = 0;

    m_ponderation = false;
    m_compteur = 0;
    m_ppc = 0;

    m_lambda = 0;
}

void Graphe::k_connexite()///verifie la k-connexite
{
    size_t minimun=999999,index=0,k=0,x=0;
    int compteur=0,memoire;
    bool condi = false, condi2 = false;
    bool etat;
    std::vector<int> pred1,pred2;
    std::vector<Arrete*> aretes;
///on recupere le sommet qui a le plus petit nbr d'adjacents et si on a un graphe oriente on calcule la somme des predecesseurs et suivants d'un sommet
    if(m_orientation==0)
        for(int i = 0; i<m_ordre; ++i)
            if(minimun>m_adjacent[i].size() && m_adjacent[i].size()>0)
            {
                minimun = m_adjacent[i].size();
                index = i;
            }
    else if(m_orientation==1)
    {
        for(int index=0;index<m_ordre;++index)
        {
            for(int i = 0;i<m_ordre;++i)
                for(size_t j=0;j<m_adjacent[i].size();++j)
                    if(m_adjacent[i][j]==index)
                    {
                        ++compteur;
                        pred2.push_back(i);
                        pred1.push_back(j);
                    }

            if(minimun>m_adjacent[i].size()+compteur)
            {
                minimun = m_adjacent[i].size()+compteur;
                memoire = compteur;
                index = i;
            }
            else
            {
                for(size_t i=0; i<pred1.size(); ++i)
                {
                    pred1.erase(pred1.begin()+i);
                    pred2.erase(pred2.begin()+i);
                }
            }
            compteur=0;
        }
    }
    ///on va ensuite chercher les aretes respectives du sommet a supprimer et tester la connexite
    if(m_orientation==0)
        while(condi==false)
        {
            ///recherche du sommet
            while(!condi2)
            {
                condi2 = m_arrete[k]->check_Sommets(m_sommet[index],m_sommet[m_adjacent[index][x]],m_orientation);
                if(!condi2)
                    ++k;
            }
            if(condi2==true)
            {
                ///on conserve l'arete qui va etre supprimer
                aretes.push_back(m_arrete[k]);
                condi2=false;
            }

            ///suppr
            m_arrete[k]->effacer_adj(m_adjacent);

            m_arrete.erase(m_arrete.begin()+k);
            m_taille--;
            etat = connexite(0);
            ///on recupere la connexite si c'et tjr connexe on repete l'operation sur une autre arrete du meme sommet sinon on sort de la boucle
            if(etat==false)
            {
                ++x;
            }
            else if(etat==true)
            {
                condi = true;
            }
            k=0;
        }
    else if(m_orientation==1)
    {
        ///ici on connait les aretes a supprimer donc on les fait une par une
        int temp = m_adjacent[index].size();
        for(int i=0; i<temp; ++i)
        {
            while(!condi2)
            {
                condi2 = m_arrete[k]->check_Sommets(m_sommet[index],m_sommet[m_adjacent[index][i]],m_orientation);
                if(!condi2)
                    ++k;
            }
            if(condi2==true)
            {
                aretes.push_back(m_arrete[k]);
                condi2=false;
            }
            m_arrete[k]->effacer_adj(m_adjacent);
            m_arrete.erase(m_arrete.begin()+k);
            m_taille--;
            k=0;
        }
        for(int i=0; i<memoire; ++i)
        {
            while(!condi2)
            {
                condi2 = m_arrete[k]->check_Sommets(m_sommet[pred2[i]],m_sommet[m_adjacent[pred2[i]][pred1[i]]],m_orientation);
                if(!condi2)
                    ++k;
            }
            if(condi2==true)
            {
                aretes.push_back(m_arrete[k]);
                condi2=false;
            }
            m_arrete[k]->effacer_adj(m_adjacent);
            m_arrete.erase(m_arrete.begin()+k);
            m_taille--;
            k=0;
        }
    }
    ///on connait la connexite on affiche la valeur
    std::cout<<"Le composant est "<<aretes.size()<<"-aretes connexes, il faut supprimer les aretes : ";
    ///on reinsere toutes les aretes
    for(size_t i=0; i<aretes.size(); ++i)
    {
        std::cout<<aretes[i]->get_indice()<<" ";
        ++m_taille;
        m_arrete.insert(m_arrete.begin()+aretes[i]->get_indice(),aretes[i]);
        if(m_orientation==0)
        {
            m_adjacent[aretes[i]->get_s1()].push_back(aretes[i]->get_s2());
            m_adjacent[aretes[i]->get_s2()].push_back(aretes[i]->get_s1());
        }
        else if(m_orientation==1)
            m_adjacent[aretes[i]->get_s1()].push_back(aretes[i]->get_s2());
    }
    std::cout<<std::endl;
    system("pause");
    system("cls");
}

bool Graphe::get_ponderation()///retourne la valeur de m_ponderation
{
    return m_ponderation;
}

void Graphe::afficher(int indice, std::vector <std::vector <double>> ensemble)
{
    ///affiche d'abord l'orientation puis appel les fonctions afficher des differents classes et affiche en meme temps dans le fichier .svg
    Svgfile svgout;
    svgout.addGrid();
    int h=0;
    int nomin=0;
    if(ensemble.size()!=0)
        nomin=195/ensemble.size();
    if(m_orientation==0)
        std::cout << "Graphe non oriente"<<std::endl;
    else
        std::cout << "Graphe oriente"<<std::endl;
    std::cout << std::endl<< "      Taille = "<<m_taille<<std::endl;
    ///affiche les aretes
    for(size_t i=0; i<m_arrete.size(); ++i)
    {
        std::cout << "          arretes :";
        m_arrete[i]->afficher(svgout,m_orientation);
    }
    std::cout << "      Ordre = "<<m_ordre<<std::endl;
    ///affich les sommets
    for(size_t i=0; i<m_sommet.size(); ++i)
    {
        std::cout << "          sommet :";
        m_sommet[i]->afficher(svgout,nomin,this,indice,ensemble);
    }
    system("pause");  /// afin de ne pas effacer la console
}

void Graphe::ajout_ponderation()
{
    if(m_ponderation==false)///si la ponderation n'est pas active alors on demande le fichier de ponderation a charger et on le charge
    {
        std::string pondFichier;
        pondFichier=menuPonderation();
        if(pondFichier=="rien") /// on permet a l'utilisateur de choisir le fichier qu'il veut ouvrir
        {
            std::cout << "Rentrez le nom du fichier" << std::endl;
            std::cin>>pondFichier;
        }
        std::ifstream ifs(pondFichier);
        if(!ifs)
            std::cerr << "Impossible d'ouvrir le fichier"; /// message d'erreur si l'ouverture du fichier ne se fait pas correctement

        int taille,indice,poids;

        ifs >> taille;

        for(int i=0; i<taille && i<m_taille; ++i)
        {
            ifs >> indice >> poids;
            m_arrete[indice]->set_poids(poids); ///on modifie la valeur
        }
        ifs.close();
        m_ponderation = true;
    }
    else if(m_ponderation==true) ///si on veut retirer le fichier on remet le poids des aretes a 1
    {
        for(int i=0; i<m_taille; ++i)
        {
            m_arrete[i]->set_poids(1);
        }
        m_ponderation = false;
    }
}

std::vector <double> Graphe::vecteur_propre() ///permet de calculer les indices de vecteur propre
{
    int n;
    std::vector <double> buffer;
    bool condi = false;
    for(n=0; n<m_ordre; ++n)
        buffer.push_back(1);

    double somme=0,c_Sommet[100],pred=99999;
///on initialise
    for(int k=0; k<m_ordre; ++k)
        c_Sommet[k]=0;
///tant que la valeur de lambda varie trop
    while(abs(pred-m_lambda)>0.1 && condi==false)
    {
        pred = m_lambda;///on recupere ancienne valeur pour faire la difference
        ///somme des indices des voisins de chaque sommet
        for(int i=0; i<m_ordre; ++i)
        {
            if(m_adjacent[i].size()>0)
                for(size_t j=0; j<m_adjacent[i].size(); ++j)
                    c_Sommet[i] += buffer[m_adjacent[i][j]];
            else
            {
                c_Sommet[i] = 0;
            }
        }
        ///calcule de lambda
        for(int i=0; i<m_ordre; ++i)
            somme += (c_Sommet[i]*c_Sommet[i]);

        m_lambda = sqrt(somme);
        if(m_lambda == 0)
        {
            condi=true;
            m_lambda = pred;
        }
        ///recalcule des indices en fonction de lambda
        for(int i=0; i<m_ordre; ++i)
        {
            buffer[i]= c_Sommet[i]/m_lambda;
            c_Sommet[i]=0;
        }
        somme=0;
    }
    m_CVP=buffer;
    buffer.erase(buffer.begin(),buffer.begin()+n);
    return m_CVP;
}

std::vector <std::vector<double>> Graphe::calculdegre()
{
    std::vector <std::vector <double>> ensemble; /// vecteur de degrés normalisés et non normalisés
    std::vector <double> degres; /// vecteur de degrés
    std::vector <double> degresnormalise; /// vecteur de degrés normalisés
    for (int j=0; j<m_ordre; j++) /// pour chaque sommet du graphe
    {
        double degre=0;  /// on initialise le degré a 0
        for(size_t i=0; i<m_arrete.size(); i++)
            if (m_arrete[i]->calculdegre(m_sommet[j], m_orientation)==1)
                degre++;
        degres.push_back(degre); /// on pushback le degré du sommet calculé dans le vecteur de degrés
        degre=degre/(m_ordre-1); /// afin de normaliser le degré, on le divise par le nombre de sommets-1
        degresnormalise.push_back(degre); /// on pushback le degré normalisé dans le vecteur de degrés normalisés
    }
    ensemble.push_back(degres);
    ensemble.push_back(degresnormalise);
    return ensemble; /// on return le vecteur contenant les degrés normalisés et non-normalisés
}

void Graphe::parcour_DFS_no_ponderation(int numS,int fin,int nbr_aretes)
{
    m_dec[numS] = true;
    ///on marque le sommet comme decouvert
    if(numS==fin)
        m_nbr_aretes = nbr_aretes;
    else
        ++nbr_aretes;
    ///on rajoute une arrete des qu'on rappelle la fonction et qu'on va pas plus loin et qu'on a pas fini car on s'enfonce plus profond avec un parcours DFS
    for(size_t i=0; i<m_adjacent[numS].size(); ++i)
        if(!m_dec[m_adjacent[numS][i]])
            parcour_DFS_no_ponderation(m_adjacent[numS][i],fin,nbr_aretes);
}

int Graphe::algo_dijkstra(int debut, int fin) ///algorithme de dijkstra qui retourne la distance la plus petite enter deux sommets
{
    std::queue<Arrete> que;
    Arrete actuel,initial;
    int temp,k=0;
    int dist[100];

    initial.set_indice(debut);
    initial.set_poids(0);

    que.push(initial);
///on initialise les distances et les conditions
    for(int i=0; i<m_ordre; ++i)
        dist[i]=999999;

    bool condi = false,condi2=false;
    dist[debut]=0;

    while(!que.empty() && condi!=true)
    {

        actuel = que.front();
        que.pop();
        temp = actuel.get_indice();

        if(temp == fin)
            condi = true;
        if(m_dec[temp])
            continue;
        m_dec[temp] = true;///on marque le sommet comme decouvert

        for(size_t i = 0; i < m_adjacent[temp].size(); ++i)
        { ///pour chaque adjacent
            if(!m_dec[m_adjacent[temp][i]]) ///si il n'a pas ete decouvert
            {
                Arrete nouveau;
                nouveau.set_indice(m_adjacent[temp][i]);
                ///on cherche l'arete correspondante aux deux sommets
                while(!condi2)
                {
                    condi2 = m_arrete[k]->check_Sommets(m_sommet[temp],m_sommet[m_adjacent[temp][i]],m_orientation);
                    if(!condi2)
                        ++k;
                }
                if(condi2==true)
                    condi2 = false;
                ///si la nouvelle distance pour aller a un sommet adjacent est plus petite on actualise la nouvelle distance
                if(dist[nouveau.get_indice()] > dist[temp] + m_arrete[k]->get_poids())
                {
                    dist[nouveau.get_indice()] = dist[temp] + m_arrete[k]->get_poids();
                }
                k=0;
                que.push(nouveau);
            }
        }
    }

    return dist[temp];
}

std::vector <double> Graphe::centralite_proximite()
{
    std::vector<double> somme;
    ///pour chaque chemin allant d'un sommet a un autre on calcule les distances minimales
    for(int i=0; i<m_ordre; ++i)
    {
        somme.push_back(0);
        for(int j=0; j<m_ordre; ++j)
            if(j!=i)
            {
                if(m_ponderation == false) ///On adapte le cose en fonction de la ponderation
                {
                    parcour_DFS_no_ponderation(i,j,0); ///On utilise le DFS pour cet indice, on parcourt tous les chemins
                    somme[i] += m_nbr_aretes;   ///on fait la somme du nbr d'aretes si on a pas les ponderations car la distance se calcul en nbr d'arc
                    m_nbr_aretes = 0;
                }
                else if(m_ponderation == true) ///si la ponderation a ete charge on calcule la plus petite distance entre deux points avec dijkstra
                {
                    if(m_adjacent[i].size()!=0)
                        somme[i] += algo_dijkstra(i,j);///retourne la plus petite distance entre les points i et j
                    else
                    {
                        somme[i]=0;
                    }
                }
                for(int i=0; i<100; ++i)
                    m_dec[i]=false;
            }
    }
    ///calcule de l'indice normalise
    for(size_t i=0; i<somme.size(); ++i)
    {
        if(somme[i]!=0)
            m_CP[i] = (m_ordre-1)/somme[i];
        else
            m_CP[i] = 0;
    }
    somme.erase(somme.begin(),somme.begin()+m_ordre);
    return m_CP;
}


void Graphe::recup_pred(std::vector<int> pred[100],int actuel,int autre) ///Recuperer les predecesseurs d'un sommet
{
    ///on part d'un sommet on remonte tous ces predecesseurs avec un appelle recurssif
    if(pred[actuel].size()>0)
    {
        for(size_t i=0; i<pred[actuel].size(); ++i)
        {
            ///si on a pas finit de parcourir alors on continue de parcourir
            if(pred[actuel][i]!=-1)
                recup_pred(pred,pred[actuel][i],autre);
            ///si on est sur le sommet qu'on cherche on rajoute +1 au comtpeur ou la taille de ces predecesseurs car il y a plusieurs plus court chemin si on continue (il y en a n*le nombre de precedent direct a actuel)
            if(actuel==autre)
            {
                if(m_orientation==0)
                    m_compteur += pred[actuel].size();
                else if(m_orientation==1)
                    ++m_compteur;
            }
            ///si on a atteint le fond alors on a trouve un chemin
            if(pred[actuel][i]==-1)
                ++m_ppc;
        }
    }
    else if(pred[actuel].size()==0)
    {
        m_ppc=1;
        m_compteur = 0;
    }
}

double Graphe::algo_dijkstra_intermediarite(int debut, int fin,bool deja_vu[50][50]) ///Algoritme de dijkstra adapter pour l'indice d'intermediarite
{
    std::queue<Arrete> que;
    Arrete actuel,initial;
    int temp,k=0;
    int dist[100];
    std::vector<int> pred[100];
    double somme=0;
    ///on met en place une arete initiale
    initial.set_indice(debut);
    initial.set_poids(0);

    que.push(initial);
    pred[debut].push_back(-1);
/// on initialise les conditions et les distances a infini
    for(int i=0; i<m_ordre; ++i)
        dist[i]=999999;

    bool condi2=false;
    dist[debut]=0;
///tant que la file n'est pas vide
    while(!que.empty())
    {
        actuel = que.front();
        que.pop();
        temp = actuel.get_indice();

        if(m_dec[temp])
            continue;
        m_dec[temp] = true;///on marque le sommet comme decouvert
///pour chaque adjcent on regarde si il n'a pas ete decouvert on met a jour sa distance et on l'ajoute a la file
        for(size_t i = 0; i < m_adjacent[temp].size(); ++i)
        {
            if(!m_dec[m_adjacent[temp][i]])
            {
                Arrete nouveau;
                nouveau.set_indice(m_adjacent[temp][i]);
                ///on cherche l'arete correspondante aux sommets
                while(!condi2)
                {
                    condi2 = m_arrete[k]->check_Sommets(m_sommet[temp],m_sommet[m_adjacent[temp][i]],m_orientation);
                    if(!condi2)
                        ++k;
                }
                if(condi2==true)
                    condi2 = false;
///si la distance est plus petite que celle deja sur le sommet on actualise/ si les distances sont egales on ajoute le sommet dans un tableau de precedent
                if(dist[nouveau.get_indice()] > dist[temp] + m_arrete[k]->get_poids())
                {
                    dist[nouveau.get_indice()] = dist[temp] + m_arrete[k]->get_poids();
                    pred[nouveau.get_indice()].push_back(temp);
                }
                else if(dist[nouveau.get_indice()] == dist[temp] + m_arrete[k]->get_poids())
                    pred[nouveau.get_indice()].push_back(temp);
                k=0;
                que.push(nouveau);
            }
        }
    }
    ///on a un taableau de sommet qui nous permet de connaitre toutes les plus petites distances en partant du sommet "debut"
    ///on remonte le tableau en partant de chaque sommet de pred jusqu'a qu'on arrive au sommet de depart et on compte le nbr de chemin le plus court et le nbr de fois qu'on passe par un sommet
    for(int i=0; i<m_ordre; ++i)
        if(i!=fin && i!=debut)
        {
            if(m_orientation==0)
            {
                if(deja_vu[debut][i]==false && deja_vu[i][debut]==false)///double condition a verifier car l'arete va dans les deux sens
                {
                    deja_vu[debut][i]=true;
                    recup_pred(pred,i,fin);///fonction qui permet de remonter le tableau pred depuis un sommet jusqu'au sommet de depart
                    somme += (m_compteur*1.0)/(m_ppc*1.0); ///on ajoute a la somme le rapport de
                    m_compteur=0;
                    m_ppc=0;
                }
            }
            else if(m_orientation==1)
            {
                if(deja_vu[debut][i]==false)
                {
                    deja_vu[debut][i]=true;
                    recup_pred(pred,i,fin);
                    somme += (m_compteur*1.0)/(m_ppc*1.0);
                    m_compteur=0;
                    m_ppc=0;
                }
            }
        }

    return somme;
}

std::vector<double> Graphe::centralite_intermediarite()
{
    std::vector<double> somme;
    bool deja_vu[50][50];
    for(int i=0; i<m_ordre; ++i)
        somme.push_back(0);

    for(int i=0; i<50; ++i)
        for(int j=0; j<50; ++j)
            deja_vu[i][j]=false;
///l'algorithme est le suivant : pour chaque sommet on prend un autre sommet considere comme le sommet de depart et on compte le nombre de fois que notre premier sommet passe entre les deux autres sommets sur les distances les plus courtes
    for(int x=0; x<m_ordre; ++x)
    {
        if(m_adjacent[x].size()>0)
        {
            for(int y=0; y<m_ordre; ++y)
                if(y!=x)
                {
                    if(m_adjacent[y].size()>0)
                    {
                        somme[x] += algo_dijkstra_intermediarite(y,x,deja_vu);///on recupere le nombre de fois qu'on passe par le sommet x sur le nombre de chemin le plus court
                        for(int i=0; i<100; ++i)
                            m_dec[i]=false;
                    }
                    else if(m_adjacent[y].size()==0)
                    {
                        somme[x] += 0;
                    }
                }
            for(int i=0; i<50; ++i)
                for(int j=0; j<50; ++j)
                    deja_vu[i][j]=false; ///On remet les cases du tableau a false pour la prochaine boucle
        }
        else if(m_adjacent[x].size()==0)
        {
            somme[x] += 0;
        }
    }
    ///calcule de l'indice normalise
    for(int i=0; i<m_ordre; ++i)
        somme[i] = (somme[i]*2)/(m_ordre*m_ordre - 3*m_ordre + 2);

    return somme;
}


void Graphe::affichercompo(std::vector <int> predecesseurs,int nb) ///Fonction affichage des composantes connexes
{
    std::cout << "Composante connexe " << nb << ": ";
    for(size_t i=0; i<predecesseurs.size(); ++i)
    {
        if(predecesseurs[i]!=-1)
        {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}


std::vector <int> Graphe::parcourBFS(int start) ///parcour le graphe en largeur
{
    std::vector <int> etats;
    std::vector <int> predecesseurs;
    std::vector <int> file;
    for(int i=0; i<m_ordre; ++i)
    {
        etats.push_back(0);
        predecesseurs.push_back(-1);
    }

    etats[start]=1;
    file.push_back(start);

    while(file.size()) /// tant que la file n'est pas vide
    {
        m_sommet[file[0]]->BFS(etats,predecesseurs,file,this);
    }
    return predecesseurs;
}


bool Graphe::connexite(int truc) ///Calcul des composantes connexes
{
    int nb=0;
    int parcours=0;
    std::vector <int> etats;
    bool condi = false;
    std::vector <int> predecesseurs;
    for(int i=0; i<m_ordre; ++i)
    {
        etats.push_back(0);
    }
    ///tant qu'on a pas visite tous les sommets
    while(parcours!=-1)
    {
        nb++;
        ///on parcour le graphe et on affiche
        predecesseurs=this->parcourBFS(parcours);
        predecesseurs[parcours]=parcours;
        if(truc==1)
            this->affichercompo(predecesseurs,nb);
        ///on  verifie les sommmets visites
        for(size_t i=0; i<predecesseurs.size(); ++i)
        {
            if(predecesseurs[i]!=-1)
            {
                etats[i]=1;
            }
        }
        parcours=-1;
        ///si un sommet n'a pas ete decouvert on se place dessus et on relance le BFS
        for(size_t i=0; i<etats.size(); ++i)
        {
            if(etats[i]==0 && parcours==-1)
            {
                condi = true;
                parcours=i;
            }
        }
    }
    if(truc==1)
        system("pause");
    return condi;
}

std::vector <int> Graphe::get_adjacent(int sommet)///retourne le tableau d'adjacent
{
    return (m_adjacent[sommet]);
}


void Graphe::afficherBFS(std::vector <int> predecesseur, int start) ///Fonction d'affichage du BFS
{
    for(size_t i=0; i<m_sommet.size(); ++i)
    {
        int j=i;
        while(predecesseur[j]!=-1)
        {
            m_sommet[j]->affichernum();
            j=predecesseur[m_sommet[j]->GetIndice()];
            if(predecesseur[j]==-1)
                std::cout << start << std::endl;
        }
    }
    system("pause");
}

void Graphe::suppr_arete(int suppr) ///Recois en parametre l'arete a effacer
{
    if (suppr==-1) ///Condition pour utiliser cette mathode de plusieurs manieres
    {
        size_t i=0,maximun=0;
        size_t choix=0;
        std::cout<<"Saisir l'indice de l'arete que vous souhaitez supprimer"<<std::endl;
        ///affiche les differents indices
        for(size_t i=0; i<m_arrete.size(); ++i)
        {
            std::cout << "    arretes ";
            m_arrete[i]->afficherIndice();
        }
        for(size_t i=0;i<m_arrete.size();++i)///permet de connaitre l'indice max car la taille du tableau diminue on ne peut pas la comparer à l'indice choisi pour le blindage
        {
            if(maximun < m_arrete[i]->get_indice())
                maximun = m_arrete[i]->get_indice();
        }
        std::cin>>choix;
        while(choix<0 || choix>maximun) ///Blindage
        {
            std::cout << "Veuillez choisir une arete existante" << std::endl;
            std::cin >> choix;
        }
        while(m_arrete[i]->get_indice()!=choix)
        {
            i++;
        }
        m_arrete[i]->effacer_adj(m_adjacent);///on efface son adjacent (ou ses)
        m_arrete.erase(m_arrete.begin()+i);///on efface l'arrete
        m_taille--;
    }
    else ///autre condition cree pour supprimer un sommet mais nous n'avions pas fini de coder suppr_sommet
    {
        int i=0;
        while(m_arrete[i]->get_indice()!=suppr)
        {
            i++;
        }
        m_arrete[i]->effacer_adj(m_adjacent);
        m_arrete.erase(m_arrete.begin()+i);
        m_taille--;
    }
}
///ce ssprg permet de faire la difference entre les anciennes donnees du graphe (avant suppression) et celle apres suppression
void Graphe::difference(std::vector <std::vector <double>> ensemble)
{
    std::ifstream flux("Sauvegarde.txt"); /// ouverture du fichier
    if(!flux)
        std::cerr << "Impossible d'ouvrir le fichier";

    int ordre;
    double temp;
    std::vector<double> degre,vecteur,intermediaire,proximite;

    flux >> ordre;
    ///on reouvre le fichier ou toutes les anciennes donnees sont ecrits et on les met dans des vecteurs
    for(int i=0; i<ordre; ++i)
    {
        flux >> temp;
        degre.push_back(temp);
        flux >> temp;
        vecteur.push_back(temp);
        flux >> temp;
        intermediaire.push_back(temp);
        flux >> temp;
        proximite.push_back(temp);
    }
    ///on affiche la difference en utilisant les donnees du fichier et celles recalculees et contenu dans le vecteur ensemble
    system("pause");
    system("cls");
    std::cout<<"DIFFERENCE ENTRE LE INDICES PRECEDENTS ET LES ACTUELS : "<<std::endl<<std::endl;
    for(size_t i = 1; i<ensemble.size(); ++i)
    {
        if(i==1)
            std::cout<<"CENTRALITE DE DEGRE : ";
        if(i==2)
            std::cout<<"CENTRALITE DE VECTEUR PROPRE : ";
        if(i==3)
            std::cout<<"CENTRALITE D'INTERMEDIARITE : ";
        if(i==4)
            std::cout<<"CENTRALITE DE PROXIMITE : ";

        for(size_t j = 0; j<ensemble[i].size(); ++j)
        {
            if(i==1)
                printf("%.2f",degre[j]-ensemble[i][j]);
            if(i==2)
                printf("%.2f",vecteur[j]-ensemble[i][j]);
            if(i==3)
                printf("%.2f",intermediaire[j]-ensemble[i][j]);
            if(i==4)
                printf("%.2f",proximite[j]-ensemble[i][j]);
            printf(" ");
        }
        std::cout<<std::endl;
    }
    system("pause");
}
