#ifndef MATRICEADJACENCE_H
#define MATRICEADJACENCE_H

#include <iostream>
#include <vector>

class MatriceAdjacence
{
    public:
        MatriceAdjacence();
        MatriceAdjacence(std::vector<std::vector<int>> adj, int nbsommets);
    
        // accesseurs 
        int index_get_adj(int i, int j) const;
        void set_adj(int i, int j, int valeur);
        int nombreSommets() const;
        std::vector<std::vector<int> > get_adj() const;
        std::vector<int> getTabPrufer() const;
    
    
        // affichage
        void afficher(std::ostream& ost) const;
    
        // gestion structure
        void redimmension();
        void ajouterArc(int i , int j);
        void supprimerArc(int i , int j);
    
        //méthode
        int plusPetiteFeuille(std::vector<std::vector<int>> adj, std::vector<bool> estPresent) const;
        std::vector<int> codagePrufer();

    private:
        std::vector<std::vector<int> > d_adj;
        int d_nbsommets;
        std::vector<int> d_tabPrufer;

};

#endif // MATRICEADJACENCE_H
