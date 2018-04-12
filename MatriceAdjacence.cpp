#include "MatriceAdjacence.h"

MatriceAdjacence::MatriceAdjacence() : d_adj(0, std::vector<int>(0)), d_nbsommets(0), d_tabPrufer(0)
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

std::vector<int> MatriceAdjacence::getTabPrufer() const
{
    return d_tabPrufer;
}


void MatriceAdjacence::afficher(std::ostream& ost) const
{
    ost << "  ";
    for (unsigned int entete = 0; entete < d_adj.size(); entete++)
    {
        ost << entete+1;
    }

    ost << std::endl << "  ";
    for (unsigned int entete = 0; entete < d_adj.size(); entete++)
    {
        ost << "|";
    }

    ost << std::endl;
    for (unsigned int ligne = 0; ligne < d_adj.size(); ligne++)
    {
        ost << ligne+1 << "|";
        for (unsigned int colonne = 0; colonne < d_adj.size(); colonne++)
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
    else if (i>nombreSommets() || j>nombreSommets())
    {
        do{
            redimmension();
        }
        while(i>nombreSommets() || j>nombreSommets());

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

int MatriceAdjacence::plusPetiteFeuille(std::vector<std::vector<int>> adj, std::vector<bool> estPresent) const{

    std::vector<bool> isFeuille(nombreSommets(), false);

    int sommet = INT_MAX;
    for (int i = 0; i < nombreSommets(); i++)
    {
        int feuille = 0;
        for (int j = 0; j < nombreSommets(); j++)
        {
            if(adj[i][j] == 1){
                feuille++;
                if(sommet>j)
                    sommet = j;
            }

            if(adj[j][i] == 1){
                feuille++;
            }
        }

        if(feuille<2)
        {
            isFeuille[i] = true;
        }
    }

    for(unsigned int k = 0; k < isFeuille.size() ; k++)
    {
        if(isFeuille[k] && estPresent[k])
            return k;
    }

    return -1;
}

std::vector<int> MatriceAdjacence::codagePrufer()
{

    std::vector<std::vector<int>> tamp_adj = d_adj;
    std::vector<bool> estPresent(nombreSommets(), true);

    int pptFeuille = 0;

    for (int k = 0; k < nombreSommets()-2; k++) {

        pptFeuille = plusPetiteFeuille(tamp_adj, estPresent);

        if(pptFeuille != -1){

            for (int i = 0; i < nombreSommets(); i++) {

                if(tamp_adj[pptFeuille][i] == 1 || tamp_adj[i][pptFeuille] == 1)
                {
                    d_tabPrufer.push_back(i+1);
                    tamp_adj[pptFeuille][i] = 0;
                    tamp_adj[i][pptFeuille] = 0;
                    estPresent[pptFeuille] = false;
                }
            }
        }
        else{
            std::cout << "Erreur : il n'y a plus de feuille dans l'arbre" << std::endl;
        }
    }

    return d_tabPrufer;
}



