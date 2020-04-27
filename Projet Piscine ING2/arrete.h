#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED

class Arrete
{
    private:
        int m_s1,m_s2;
        int m_indice;
        int m_poids;
    public:
        Arrete(int s1, int s2, int indice, int poids);
        void afficher();
        ~Arrete();
};

#endif // ARRETE_H_INCLUDED
