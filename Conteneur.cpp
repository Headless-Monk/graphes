#include "Conteneur.h"

Conteneur::Conteneur() :
        d_matrice_adjacence{nullptr},
        d_liste{nullptr},
        d_fs_aps{nullptr}
{}

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
    int m = tmp_fs[0]-n;

    d_matrice_adjacence->set_matrice_1_size(n+1);
    d_matrice_adjacence->set_matrice_2_size(n+1);

    d_matrice_adjacence->set_adj(0,0,n);
    d_matrice_adjacence->set_adj(0,1,m);

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            d_matrice_adjacence->set_adj(i,j,0);
        }
    }

    for(int i = 1; i <= n; i++)
    {
        int j = tmp_aps[i];
        while(tmp_fs[i] != 0)
        {
            d_matrice_adjacence->set_adj(i,tmp_fs[j],1);
            j++;
        }
    }
}

void Conteneur::adj_to_fsasps()
{
    std::vector<int> tmp_fs;
    std::vector<int> tmp_aps;

    std::vector<std::vector<int> > tmp_adj = d_matrice_adjacence->get_adj();

    int n = d_matrice_adjacence->nombreSommets();
    int m = d_matrice_adjacence->nombreArcs();

    tmp_fs.resize(m+n+1);
    tmp_aps.resize(n+1);

    tmp_fs[0] = m+n;
    tmp_aps[0] = n;

    int pos = 0;
    for(int i = 0; i < n; i++)
    {
        tmp_aps[i] = pos;
        for(int j = 0; j < n; ++j)
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

    d_fs_aps = new FsAps(tmp_fs, tmp_aps);
}

void Conteneur::adj_to_liste()
{
    std::vector<std::vector<int> > liste_arcs;

    liste_arcs = d_matrice_adjacence->getArcs();

    d_liste = new Liste(d_matrice_adjacence->nombreSommets(), get_orientation());

    for(unsigned int i = 0; i < liste_arcs.size(); i++)
    {
        d_liste->ajouter_successeur(liste_arcs[i][0], liste_arcs[i][1]);
    }
}

void Conteneur::fsaps_to_liste()
{
    fsaps_to_adj();
    adj_to_liste();
}

void Conteneur::liste_to_adj()
{
    std::vector<std::vector<int> > liste_arcs;

    liste_arcs = d_liste->liste_arcs();

    d_matrice_adjacence = new MatriceAdjacence();
    d_matrice_adjacence->set_nb_sommets(d_liste->nombre_sommets()-1);

    d_matrice_adjacence->redimmension();

    for(unsigned int i = 0; i < liste_arcs.size(); i++)
    {
        d_matrice_adjacence->ajouterArc(liste_arcs[i][0], liste_arcs[i][1]);
    }
}

void Conteneur::liste_to_fsaps()
{
    liste_to_adj();
    adj_to_fsasps();
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
