#ifndef MATRICEADJACENCE_H
#define MATRICEADJACENCE_H

#include <iostream>
#include <vector>

class MatriceAdjacence
{
    public:
        MatriceAdjacence();
        MatriceAdjacence(std::vector<std::vector<int>> adj, int nbsommets);
    
        int index_get_adj(int i, int j) const;
        void set_adj(int i, int j, int valeur);
        int nombreSommets() const;

        std::vector<std::vector<int> > get_adj() const;
    
        void afficher(std::ostream& ost) const;
        void redimmension();
        void ajouterArc(int i , int j);
        void supprimerArc(int i , int j);

    private:
        std::vector<std::vector<int> > d_adj;
        int d_nbsommets;

};

#endif // MATRICEADJACENCE_H
