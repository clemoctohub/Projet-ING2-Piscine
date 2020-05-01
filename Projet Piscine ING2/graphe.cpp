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
    std::ifstream flux(nomFichier); // ouverture du fichier
    if(!flux)
        std::cerr << "Impossible d'ouvrir le fichier"; // message d'erreur si l'ouverture du fichier ne se fait pas correctement

///////////////////  Lecture du fichier et remplissage des differents attributs de la classe graphe/////////////////////////

    flux >> m_orientation >> m_ordre;

    for (int i=0; i<m_ordre; ++i)
    {
        std::string nom;
        int indice, x, y;
        flux>> indice >> nom >> x >> y;
        m_sommet.push_back(new Sommet{indice, nom, x, y});

        m_CP.push_back(0);
    }
    flux>>m_taille;
    //faire le cas pour les graphes orientes
    for (int i=0; i<m_taille; ++i)
    {
        int indice,s1,s2;
        flux >> indice >> s1 >> s2;
        m_arrete.push_back(new Arrete{m_sommet[s1],m_sommet[s2],indice,1});
        //cas graphe non oriente a faire
        m_adjacent[s1].push_back(s2);
        m_adjacent[s2].push_back(s1);
    }
    flux.close();

    for(int i=0; i<100; ++i)
        m_dec[i]=false;
    m_nbr_aretes = 0;

    m_ponderation = false;
    m_compteur = 0;
    m_ppc = 0;

    m_lambda = 0;
}

void Graphe::afficher(int choix)
{
    Svgfile svgout;
    svgout.addGrid();
    std::vector <int> classement;
    int h=0;
    int nomin=180/m_ordre;
    if(m_orientation==0)
        std::cout << "Graphe non oriente"<<std::endl;
    else
        std::cout << "Graphe oriente"<<std::endl;
    std::cout << std::endl<< "      Taille = "<<m_taille<<std::endl;
    for(size_t i=0; i<m_arrete.size(); ++i)
    {
        std::cout << "          arretes :";
        m_arrete[i]->afficher(svgout,m_orientation);
    }
    std::cout << "      Ordre = "<<m_ordre<<std::endl;
    for(size_t i=0; i<m_sommet.size(); ++i)
    {
        for(size_t j=0; j<m_arrete.size(); ++j)
        {
            if(m_arrete[j]->calculdegre(m_sommet[i],0))
                ++h;
        }
        classement.push_back(h);
        h=0;
    }
    for(size_t i=0; i<m_sommet.size(); ++i)
    {
        std::cout << "          sommet :";
        m_sommet[i]->afficher(svgout,classement,nomin);
    }
    system("pause");  // afin de ne pas effacer la console
    /*if (choix==2)
    {
        std::vector <std::vector <double>> ensemble;
        int choix1=0;
        ensemble=indicedecentralite(*this, m_ordre, 3);
        while (choix1!=5)
        {
            system("cls");
            std::cout << "Choisissez l'indice que vous voulez afficher :" << std::endl;
            std::cout << std::endl;
            std::cout << "1: Indice de centralite de degre" << std::endl;
            std::cout << "2: Indice de vecteur propre" << std::endl;
            std::cout << "3: Indice de proximite" << std::endl;
            std::cout << "4: Indice de centralite d'intermediarite" << std::endl;
            std::cout << "5: Retour" << std::endl;
            std::cin >> choix1;


           /* for(size_t i=0; i<ensemble[choix1].size(); i++)
            {
                    std::cout<< ensemble[choix1][i]<<std::endl;
                    svgout.addText(m_sommet[i]->GetX(),m_sommet[i]->GetY(),ensemble[choix1][i],"black");
            }
            system("pause");

            switch(choix1)
            {
            case 1:
                for(size_t i=0; i<ensemble[choix1].size(); i++)
                {
                    svgout.addText(m_sommet[i]->GetX()*100,m_sommet[i]->GetY()*100,ensemble[choix1][i],"black");
                }
                break;

            }
        }
    }*/
}

void Graphe::ajout_ponderation(std::string pondFichier)
{
    std::ifstream ifs(pondFichier);
    if(!ifs)
        std::cerr << "Impossible d'ouvrir le fichier"; // message d'erreur si l'ouverture du fichier ne se fait pas correctement

    int taille,indice,poids;

    ifs >> taille;

    for(int i=0; i<taille; ++i)
    {
        ifs >> indice >> poids;
        m_arrete[indice]->set_poids(poids);
    }

    m_ponderation = true;
}

std::vector <double> Graphe::vecteur_propre()
{
    int n;
    std::vector <double> buffer;
    for(n=0; n<m_ordre; ++n)
        buffer.push_back(1);

    double somme=0,c_Sommet[100],pred=99999;

    for(int k=0; k<m_ordre; ++k)
        c_Sommet[k]=0;

    while(abs(pred-m_lambda)>0.1)
    {
        pred = m_lambda;
        for(int i=0; i<m_ordre; ++i)
            for(size_t j=0; j<m_adjacent[i].size(); ++j)
                c_Sommet[i] += buffer[m_adjacent[i][j]];

        for(int i=0; i<m_ordre; ++i)
            somme += (c_Sommet[i]*c_Sommet[i]);

        m_lambda = sqrt(somme);

        for(int i=0; i<m_ordre; ++i)
            buffer[i]= c_Sommet[i]/m_lambda;

        for(int i=0; i<m_ordre; ++i)
            c_Sommet[i]=0;
        std::cout<<"     "<< m_lambda<<std::endl;
        somme=0;
    }
    m_CVP=buffer;
    buffer.erase(buffer.begin(),buffer.begin()+n);
    return m_CVP;
}

std::vector <std::vector<double>> Graphe::calculdegre()
{
    std::vector <std::vector <double>> ensemble; // vecteur de degrés normalisés et non normalisés
    std::vector <double> degres; // vecteur de degrés
    std::vector <double> degresnormalise; // vecteur de degrés normalisés
    for (int j=0; j<m_ordre; j++) // pour chaque sommet du graphe
    {
        double degre=0;  // on initialise le degré a 0
        if (m_orientation == 0) // si le graphe n'est pas orienté
            for(size_t i=0; i<m_arrete.size(); i++) // pour toutes les arêtes du graphe
                if (m_arrete[i]->calculdegre(m_sommet[j], m_orientation)==1)
                    degre++;  // on ajoute 1 à degré si la méthode calculdegre return 1
        if (m_orientation == 1) // si le graphe est orienté
            for(size_t i=0; i<m_arrete.size(); i++)
                if (m_arrete[i]->calculdegre(m_sommet[j], m_orientation)==1)
                    degre++;
        degres.push_back(degre); // on pushback le degré du sommet calculé dans le vecteur de degrés
        degre=degre/(m_ordre-1); // afin de normaliser le degré, on le divise par le nombre de sommets-1
        degresnormalise.push_back(degre); // on pushback le degré normalisé dans le vecteur de degrés normalisés
    }
    ensemble.push_back(degres);
    ensemble.push_back(degresnormalise);
    return ensemble; // on return le vecteur contenant les degrés normalisés et non-normalisés
}

void Graphe::parcour_DFS_no_ponderation(int numS,int fin,int nbr_aretes)
{
    m_dec[numS] = true;

    if(numS==fin)
        m_nbr_aretes = nbr_aretes;
    else
        ++nbr_aretes;

    for(size_t i=0; i<m_adjacent[numS].size(); ++i)
        if(!m_dec[m_adjacent[numS][i]])
            parcour_DFS_no_ponderation(m_adjacent[numS][i],fin,nbr_aretes);
}

int Graphe::algo_dijkstra(int debut, int fin)
{
    std::queue<Arrete> que;
    Arrete actuel,initial;
    int temp,k=0;
    int dist[100];

    initial.set_indice(debut);
    initial.set_poids(0);

    que.push(initial);

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
        m_dec[temp] = true;

        for(size_t i = 0; i < m_adjacent[temp].size(); ++i)
        {
            if(!m_dec[m_adjacent[temp][i]])
            {
                Arrete nouveau;
                nouveau.set_indice(m_adjacent[temp][i]);
                while(!condi2)
                {
                    condi2 = m_arrete[k]->check_Sommets(m_sommet[temp],m_sommet[m_adjacent[temp][i]]);
                    if(!condi2)
                        ++k;
                }
                if(condi2==true)
                    condi2 = false;

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
    //faire le cas si il y a les ponderations + cas normalise et non normalise
    std::vector<double> somme;
    for(int i=0; i<m_ordre; ++i)
    {
        somme.push_back(0);
        for(int j=0; j<m_ordre; ++j)
            if(j!=i)
            {
                if(m_ponderation == false)
                {
                    parcour_DFS_no_ponderation(i,j,0);
                    somme[i] += m_nbr_aretes;
                    m_nbr_aretes = 0;
                }
                else if(m_ponderation==true)
                {
                    somme[i] += algo_dijkstra(i,j);
                }
                for(int i=0; i<100; ++i)
                    m_dec[i]=false;
            }
    }
    for(size_t i=0; i<somme.size(); ++i)
        m_CP[i] = (m_ordre-1)/somme[i];
    somme.erase(somme.begin(),somme.begin()+m_ordre);
    return m_CP;
}


void Graphe::recup_pred(std::vector<int> pred[100],int actuel,int autre)
{
    for(size_t i=0; i<pred[actuel].size(); ++i)
    {
        if(pred[actuel][i]!=-1)
            recup_pred(pred,pred[actuel][i],autre);
        if(actuel==autre)
            m_compteur += pred[actuel].size();
        if(pred[actuel][i]==-1)
            ++m_ppc;
    }
}

double Graphe::algo_dijkstra_intermediarite(int debut, int fin,bool deja_vu[50][50])
{
    std::queue<Arrete> que;
    Arrete actuel,initial;
    int temp,k=0;
    int dist[100];
    std::vector<int> pred[100];
    double somme=0;

    initial.set_indice(debut);
    initial.set_poids(0);

    que.push(initial);
    pred[debut].push_back(-1);

    for(int i=0; i<m_ordre; ++i)
        dist[i]=999999;

    bool condi2=false;
    dist[debut]=0;

    while(!que.empty())
    {
        actuel = que.front();
        que.pop();
        temp = actuel.get_indice();

        if(m_dec[temp])
            continue;
        m_dec[temp] = true;

        for(size_t i = 0; i < m_adjacent[temp].size(); ++i)
        {
            if(!m_dec[m_adjacent[temp][i]])
            {
                Arrete nouveau;
                nouveau.set_indice(m_adjacent[temp][i]);
                while(!condi2)
                {
                    condi2 = m_arrete[k]->check_Sommets(m_sommet[temp],m_sommet[m_adjacent[temp][i]]);
                    if(!condi2)
                        ++k;
                }
                if(condi2==true)
                    condi2 = false;

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

    for(int i=0; i<m_ordre; ++i)
        if(i!=fin && i!=debut)
            if(deja_vu[debut][i]==false && deja_vu[i][debut]==false)
            {
                deja_vu[debut][i]=true;
                recup_pred(pred,i,fin);
                somme += (m_compteur*1.0)/(m_ppc*1.0);
                m_compteur=0;
                m_ppc=0;
            }

    return somme;
}

std::vector<double> Graphe::centralite_intermediarite()
{
    //tablo somet deja fait + tableau sommet
    std::vector<double> somme;
    bool deja_vu[50][50];
    for(int i=0; i<m_ordre; ++i)
        somme.push_back(0);
    for(int i=0; i<50; ++i)
        for(int j=0; j<50; ++j)
            deja_vu[i][j]=false;

    for(int x=0; x<m_ordre; ++x)
    {

        for(int y=0; y<m_ordre; ++y)
            if(y!=x)
            {
                somme[x] += algo_dijkstra_intermediarite(y,x,deja_vu);
                for(int i=0; i<100; ++i)
                    m_dec[i]=false;
            }
        for(int i=0; i<50; ++i)
            for(int j=0; j<50; ++j)
                deja_vu[i][j]=false;
    }

    for(int i=0; i<m_ordre; ++i)
        somme[i] = (somme[i]*2)/(m_ordre*m_ordre - 3*m_ordre + 2);

    return somme;
}


void Graphe::affichercompo(std::vector <int> predecesseurs,int nb)
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


std::vector <int> Graphe::parcourBFS(int start)
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

    while(file.size())
    {
        m_sommet[file[0]]->BFS(etats,predecesseurs,file,this);
    }
    return predecesseurs;
}


void Graphe::connexite()
{
    int nb=0;
    int parcours=0;
    std::vector <int> etats;
    std::vector <int> predecesseurs;
    for(int i=0; i<m_ordre; ++i)
    {
        etats.push_back(0);
    }
    while(parcours!=-1)
    {
        nb++;
        predecesseurs=this->parcourBFS(parcours);
        predecesseurs[parcours]=parcours;
        this->affichercompo(predecesseurs,nb);
        for(size_t i=0; i<predecesseurs.size(); ++i)
        {
            if(predecesseurs[i]!=-1)
            {
                etats[i]=1;
            }
        }
        parcours=-1;
        for(size_t i=0; i<etats.size(); ++i)
        {
            if(etats[i]==0 && parcours==-1)
            {
                parcours=i;
            }
        }
    }
    system("pause");
}

std::vector <int> Graphe::get_adjacent(int sommet)
{
    return (m_adjacent[sommet]);
}


void Graphe::afficherBFS(std::vector <int> predecesseur, int start)
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

void Graphe::suppr_arete()
{
    int i=0;
    int choix=0;
    std::cout<<"Saisir l'indice de l'arete que vous souhaitez supprimer"<<std::endl;
    for(size_t i=0; i<m_arrete.size(); ++i)
    {
        std::cout << "    arretes ";
        m_arrete[i]->afficherIndice();
    }
    std::cin>>choix;
    while(choix<0 || choix>m_arrete.size())
    {
        std::cout << "Veuillez choisir une arete existante" << std::endl;
        std::cin >> choix;
    }
    while(m_arrete[i]->get_indice()!=choix)
    {
        i++;
    }
    m_arrete[i]->effacer_adj(m_adjacent);
    m_arrete.erase(m_arrete.begin()+i);
    m_taille--;
}

void Graphe::difference(std::vector <std::vector <double>> ensemble)
{
    std::ifstream flux("Sauvegarde.txt"); // ouverture du fichier
    if(!flux)
        std::cerr << "Impossible d'ouvrir le fichier";

    int ordre;
    double temp;
    std::vector<double> degre,vecteur,intermediaire,proximite;

    flux >> ordre;

    for(int i=0; i<ordre; ++i)
    {
        flux >> temp;
        degre.push_back(temp);
    }
    for(int i=0; i<ordre; ++i)
    {
        flux >> temp;
        vecteur.push_back(temp);
    }
    for(int i=0; i<ordre; ++i)
    {
        flux >> temp;
        intermediaire.push_back(temp);
    }
    for(int i=0; i<ordre; ++i)
    {
        flux >> temp;
        proximite.push_back(temp);
    }

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
