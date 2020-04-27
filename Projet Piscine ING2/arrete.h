#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED

class Arrete
{
    private:
        int m_s1,m_s2;
        int m_poids;
        int m_indice;
    public:
        Arrete(int s1, int s2, int indice, int poids);
        ~Arrete();
};

#endif // ARRETE_H_INCLUDED
