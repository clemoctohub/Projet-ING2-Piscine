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
        int indice;
        double x, y;
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
    for(int i=0; i<100; ++i)
        m_dec[i]=false;
    m_nbr_aretes = 0;

    m_ponderation = false;
    m_compteur = 0;
    m_ppc = 0;

    m_lambda = 0;
}

void Graphe::k_connexite()
{
    size_t minimun=999999,index=0,k=0,x=0;
    int compteur=0,memoire;
    bool condi = false, condi2 = false;
    bool etat;
    std::vector<int> pred1,pred2;
    std::vector<Arrete*> aretes;

    if(m_orientation==0)
        for(int i = 0;i<m_ordre;++i)
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
                for(size_t i=0;i<pred1.size();++i)
                {
                    pred1.erase(pred1.begin()+i);
                    pred2.erase(pred2.begin()+i);
                }
            }
            compteur=0;
        }
    }
    if(m_orientation==0)
        while(condi==false)
        {
            while(!condi2)
            {
                condi2 = m_arrete[k]->check_Sommets(m_sommet[index],m_sommet[m_adjacent[index][x]],m_orientation);
                if(!condi2)
                    ++k;
            }
            if(condi2==true)
            {
                aretes.push_back(m_arrete[k]);
                condi2=false;
            }

            //suppr
            m_arrete[k]->effacer_adj(m_adjacent);

            m_arrete.erase(m_arrete.begin()+k);
            m_taille--;
            etat = connexite(0);
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
        int temp = m_adjacent[index].size();
        for(int i=0;i<temp;++i)
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
        for(int i=0;i<memoire;++i)
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

    std::cout<<"Le composant est "<<aretes.size()<<"-aretes connexes, il faut supprimer les aretes : ";
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

bool Graphe::get_ponderation()
{
    return m_ponderation;
}

void Graphe::afficher(int indice, std::vector <std::vector <double>> ensemble)
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
        m_sommet[i]->afficher(svgout,classement,nomin,this,indice,ensemble);
    }
    system("pause");  // afin de ne pas effacer la console
}

void Graphe::ajout_ponderation()
{
    std::string pondFichier;
    pondFichier=menuPonderation();
    if(pondFichier=="rien") // on permet a l'utilisateur de choisir le fichier qu'il veut ouvrir
    {
        std::cout << "Rentrez le nom du fichier" << std::endl;
        std::cin>>pondFichier;
    }
    if(m_ponderation==false)
    {
        std::ifstream ifs(pondFichier);
        if(!ifs)
            std::cerr << "Impossible d'ouvrir le fichier"; // message d'erreur si l'ouverture du fichier ne se fait pas correctement

        int taille,indice,poids;

        ifs >> taille;

        for(int i=0; i<taille && i<m_taille; ++i)
        {
            ifs >> indice >> poids;
            m_arrete[indice]->set_poids(poids);
        }
        ifs.close();
        m_ponderation = true;
    }
    else if(m_ponderation==true)
    {
        for(int i=0; i<m_taille; ++i)
        {
            m_arrete[i]->set_poids(1);
        }
        m_ponderation = false;
    }
}

std::vector <double> Graphe::vecteur_propre()
{
    int n;
    std::vector <double> buffer;
    bool condi = false;
    for(n=0; n<m_ordre; ++n)
        buffer.push_back(1);

    double somme=0,c_Sommet[100],pred=99999;

    for(int k=0; k<m_ordre; ++k)
        c_Sommet[k]=0;

    while(abs(pred-m_lambda)>0.1 && condi==false)
    {
        pred = m_lambda;
        for(int i=0; i<m_ordre; ++i)
        {
            if(m_adjacent[i].size()>0)
                for(size_t j=0; j<m_adjacent[i].size(); ++j)
                    c_Sommet[i] += buffer[m_adjacent[i][j]];
            else{
                c_Sommet[i] = 0;
            }
        }

        for(int i=0; i<m_ordre; ++i)
            somme += (c_Sommet[i]*c_Sommet[i]);

        m_lambda = sqrt(somme);
        if(m_lambda == 0)
        {
            condi=true;
            m_lambda = pred;
        }
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
    std::vector <std::vector <double>> ensemble; // vecteur de degrés normalisés et non normalisés
    std::vector <double> degres; // vecteur de degrés
    std::vector <double> degresnormalise; // vecteur de degrés normalisés
    for (int j=0; j<m_ordre; j++) // pour chaque sommet du graphe
    {
        double degre=0;  // on initialise le degré a 0
        //if (m_orientation == 0) // si le graphe n'est pas orienté
           // for(size_t i=0; i<m_arrete.size(); i++) // pour toutes les arêtes du graphe
               // if (m_arrete[i]->calculdegre(m_sommet[j], m_orientation)==1)
                //    degre++;  // on ajoute 1 à degré si la méthode calculdegre return 1
        //if (m_orientation == 1) // si le graphe est orienté
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
                    condi2 = m_arrete[k]->check_Sommets(m_sommet[temp],m_sommet[m_adjacent[temp][i]],m_orientation);
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
                else if(m_ponderation == true)
                {
                    if(m_adjacent[i].size()!=0)
                        somme[i] += algo_dijkstra(i,j);
                    else{somme[i]=0;}
                }
                for(int i=0; i<100; ++i)
                    m_dec[i]=false;
            }
    }
    for(size_t i=0; i<somme.size(); ++i)
    {
        if(somme[i]!=0)
            m_CP[i] = (m_ordre-1)/somme[i];
        else m_CP[i] = 0;
    }
    somme.erase(somme.begin(),somme.begin()+m_ordre);
    return m_CP;
}


void Graphe::recup_pred(std::vector<int> pred[100],int actuel,int autre)
{
    if(pred[actuel].size()>0)
    {
        for(size_t i=0; i<pred[actuel].size(); ++i)
        {
            if(pred[actuel][i]!=-1)
                recup_pred(pred,pred[actuel][i],autre);
            if(actuel==autre)
            {
                if(m_orientation==0)
                    m_compteur += pred[actuel].size();
                else if(m_orientation==1)
                    ++m_compteur;
            }
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
                    condi2 = m_arrete[k]->check_Sommets(m_sommet[temp],m_sommet[m_adjacent[temp][i]],m_orientation);
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
        {
            if(m_orientation==0)
            {
                if(deja_vu[debut][i]==false && deja_vu[i][debut]==false)
                {
                    deja_vu[debut][i]=true;
                    recup_pred(pred,i,fin);
                    somme += (m_compteur*1.0)/(m_ppc*1.0);
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

    for(int x=0; x<m_ordre; ++x)
    {
        if(m_adjacent[x].size()>0)
        {
            for(int y=0; y<m_ordre; ++y)
                if(y!=x)
                {
                    if(m_adjacent[y].size()>0)
                    {
                        somme[x] += algo_dijkstra_intermediarite(y,x,deja_vu);
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
                    deja_vu[i][j]=false;
        }
        else if(m_adjacent[x].size()==0)
        {
            somme[x] += 0;
        }
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


bool Graphe::connexite(int truc)
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
    while(parcours!=-1)
    {
        nb++;
        predecesseurs=this->parcourBFS(parcours);
        predecesseurs[parcours]=parcours;
        if(truc==1)
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
                condi = true;
                parcours=i;
            }
        }
    }
    if(truc==1)
        system("pause");
    return condi;
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

void Graphe::suppr_arete(int suppr)
{
    if (suppr==-1)
    {
        size_t i=0,maximun=0;
        size_t choix=0;
        std::cout<<"Saisir l'indice de l'arete que vous souhaitez supprimer"<<std::endl;
        for(size_t i=0; i<m_arrete.size(); ++i)
        {
            std::cout << "    arretes ";
            m_arrete[i]->afficherIndice();
        }
        for(size_t i=0;i<m_arrete.size();++i)
        {
            if(maximun < m_arrete[i]->get_indice())
                maximun = m_arrete[i]->get_indice();
        }
        std::cin>>choix;
        while(choix<0 || choix>maximun)
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
    else
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

void Graphe::suppr_sommet()
{
    size_t choix=0,maximun=0;
    int k=0;
    std::cout<<"Saisir l'indice du sommet que vous souhaitez supprimer"<<std::endl;
    for(size_t i=0; i<m_sommet.size(); ++i)
    {
        std::cout << "    sommet ";
        m_sommet[i]->affichernum();
        std::cout<<std::endl;
    }
    for(size_t i=0;i<m_arrete.size();++i)
    {
        if(maximun < m_arrete[i]->get_indice())
            maximun = m_arrete[i]->get_indice();
    }
    std::cin>>choix;
    while(choix<0 || choix>maximun)
    {
        std::cout << "Veuillez choisir une arete existante" << std::endl;
        std::cin >> choix;
    }
    while(m_sommet[k]->GetIndice()!=choix)
    {
        k++;
    }
    int taille_arete = m_arrete.size();
    for (int i=0; i<taille_arete; i++)
    {
        if (m_arrete[i]->calculdegre(m_sommet[k],0))
        {
            suppr_arete(i);
        }
        for (int i=0; i<taille_arete; i++)
    {
        }
    }
    for (int i=0; i<taille_arete; i++)
    {
        if (m_arrete[i]->calculdegre(m_sommet[k],0))
        {
            suppr_arete(i);
        }
    }
    if(m_orientation==1)
    {

    }
    m_sommet.erase(m_sommet.begin()+k);
    m_ordre--;
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
        flux >> temp;
        vecteur.push_back(temp);
        flux >> temp;
        intermediaire.push_back(temp);
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

void Graphe::tarjan()
{

}
