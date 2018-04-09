#include "MatriceAdjacence.h"
#include <vector>

MatriceAdjacence::MatriceAdjacence() : d_adj(0, std::vector<int>(0)), d_nbsommets(0)
{}

MatriceAdjacence::MatriceAdjacence(std::vector<std::vector<int>> adj, int nbsommets) : d_adj(adj), d_nbsommets(nbsommets)
{}

int MatriceAdjacence::index_get_adj(int i, int j) const
{
    return d_adj[i][j];
}

void MatriceAdjacence::set_adj(int i, int j, int valeur)
{
    d_adj[i][j] = valeur;
}

std::vector<std::vector<int> > MatriceAdjacence::get_adj() const
{
    return d_adj;
}


int MatriceAdjacence::nombreSommets() const
{
    return d_nbsommets;
}


void MatriceAdjacence::afficher(std::ostream& ost) const
{
    for (int ligne = 0; ligne < d_adj.size(); ligne++)
    {
        for (int colonne = 0; colonne < d_adj.size(); colonne++)
        {
            ost << d_adj[ligne][colonne];
        }
        ost << std::endl ;
    }
}

void MatriceAdjacence::redimmension()
{
    d_nbsommets++;
    int nouvelle_taille = d_nbsommets;
    
    
    // redimensionne la matrice d'adjacence
    d_adj.resize(nouvelle_taille);
    for (int i = 0; i < nouvelle_taille; i++) {
        d_adj[i].resize(nouvelle_taille, 0);
    }
}

void MatriceAdjacence::ajouterArc(int i , int j)
{
    if (i>0 && j>0 && i<=nombreSommets() && j<=nombreSommets())
        d_adj[i-1][j-1] = 1;
    else if (i>=nombreSommets() || j>=nombreSommets())
    {
        do{
            redimmension();
        }
        while(i>=nombreSommets() || j>=nombreSommets());
        
        d_adj[i-1][j-1] = 1;
    }
}

void MatriceAdjacence::supprimerArc(int i , int j)
{
    if (i>0 && j>0 && i<=nombreSommets() && j<=nombreSommets())
    {
        d_adj[i-1][j-1] = 0;
    }
}
