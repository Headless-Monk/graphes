#include "Conteneur.h"

Conteneur::Conteneur() :
        d_matrice_adjacence{nullptr},
        d_liste{nullptr},
        d_fs_aps{nullptr}
{}

Conteneur::Conteneur(MatriceAdjacence* matrice)
{
    d_matrice_adjacence = matrice;
}

Conteneur::Conteneur(FsAps* fsaps)
{
    d_fs_aps = fsaps;
}

Conteneur::Conteneur(Liste* liste)
{
    d_liste = liste;
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

void Conteneur::liste(Liste *li)
{
    d_liste = li;
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
