#include "Conteneur.h"

/*Conteneur::Conteneur() :
        d_matrice_adjacence{nullptr},
        d_liste{nullptr},
        d_fs_aps{nullptr}
{}*/

Conteneur::Conteneur(bool orientation) :
        d_matrice_adjacence{nullptr},
        d_liste{nullptr},
        d_fs_aps{nullptr},
        d_orientation{orientation}
{}

Conteneur::Conteneur(MatriceAdjacence* matrice, bool orientation)
{
    d_matrice_adjacence = matrice;
    d_orientation = orientation;
    adj_to_fsasps();
    adj_to_liste();
}

Conteneur::Conteneur(FsAps* fsaps, bool orientation)
{
    d_fs_aps = fsaps;
    d_orientation = orientation;
    fsaps_to_adj();
    adj_to_liste();
}

Conteneur::Conteneur(Liste* liste, bool orientation)
{
    d_liste = liste;
    d_orientation = orientation;
}

void Conteneur::fsaps_to_adj()
{
    std::vector<int> tmp_fs = d_fs_aps->getFs();
    std::vector<int> tmp_aps = d_fs_aps->getAps();

    int n = tmp_aps[0];
    int m = tmp_fs[0];

    d_matrice_adjacence->set_adj(0,0,n);
    d_matrice_adjacence->set_adj(0,1,m);

    for(int i = 1; i < n; i++)
    {
        int nbs = tmp_aps[i+1] - tmp_aps[i]-1;
        d_matrice_adjacence->set_adj(i,0,nbs);
        for(int j = 1; tmp_fs[tmp_aps[i]+j-1] != 0; j++)
        {
            d_matrice_adjacence->set_adj(i,j,tmp_fs[tmp_aps[i]+j-1]);
        }
    }
    int nbs = tmp_fs[0] - tmp_aps[n];
    d_matrice_adjacence->set_adj(n,0,nbs);
    for(int j = 1; tmp_fs[tmp_aps[n]+j-1] != 0; j++)
    {
        d_matrice_adjacence->set_adj(n,j,tmp_fs[tmp_aps[n]+j-1]);
    }
}

void Conteneur::adj_to_fsasps()
{
    std::vector<int> tmp_fs;
    std::vector<int> tmp_aps;

    std::vector<std::vector<int> > tmp_adj = d_matrice_adjacence->get_adj();

    int n = tmp_adj[0][0];
    int m = tmp_adj[0][1];

    tmp_fs[0] = m+n;
    tmp_aps[0] = n;

    int pos = 1;
    for(int i = 1; i <= n; i++)
    {
        tmp_aps[i] = pos;
        for(int j = 1; j <= n; ++j)
        {
            if(tmp_adj[i][j] == 1)
            {
                tmp_fs[pos] = j;
                ++pos;
            }
        }
        tmp_fs[pos] = 0;
        ++pos;
    }
}

void Conteneur::adj_to_liste()
{
    std::vector<std::vector<int> > liste_arcs;

    liste_arcs = d_matrice_adjacence->getArcs();

    d_liste = new Liste(d_matrice_adjacence->nombreSommets(), get_orientation());

    for(unsigned int i = 0; i < liste_arcs.size(); i++)
    {
        d_liste->ajouter_successeur(liste_arcs[0][i], liste_arcs[1][i]);
    }
}

bool Conteneur::get_orientation() const
{
    return d_orientation;
}

void Conteneur::set_orientation(bool orientation)
{
    d_orientation = orientation;
}

void Conteneur::liste(Liste *li)
{
    d_liste = li;
}

void Conteneur::fsaps(FsAps *fa)
{
    d_fs_aps = fa;
}

void Conteneur::matrice(MatriceAdjacence *adj)
{
    d_matrice_adjacence = adj;
}


Liste* Conteneur::liste()
{
    return d_liste;
}

MatriceAdjacence* Conteneur::matrice()
{
    return d_matrice_adjacence;
}

FsAps* Conteneur::fs_aps()
{
    return d_fs_aps;
}
