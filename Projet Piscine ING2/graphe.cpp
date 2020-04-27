#include "graphe"

Graphe::Graphe(std::string fichier)
{
    std::ifstream flux(fichier);
    if(!flux)
        std::cout << "Problème d'ouverture du fichier" << std::endl;
    if(!flux)
        std::cerr << "Impossible d'ouvrir le fichier";

    flux >> m_orientation>>m_ordre>>m_taille;

    for (int i=0; i<m_ordre; ++i)
        m_sommet.push_back(new Sommet(i));

    for (int i=0; i<m_taille; ++i)
        m_liaison.push_back(new Liaison());

    int s1,s2,poids;

    for (int j=0; j<m_taille; ++j)
    {
        flux >> s1 >> s2 >> poids;
        m_sommet[s1]->SetAdjacents(m_sommet[s2]);
        m_liaison[j]->Set_liaison(m_sommet[s1],m_sommet[s2],poids);
        m_sommet[s1]->Add_liaison(m_liaison[j]);
        if(m_orientation==0)
        {
            m_sommet[s2]->Add_liaison(m_liaison[j]);
            m_sommet[s2]->SetAdjacents(m_sommet[s1]);
        }
    }
}
