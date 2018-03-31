#include "MatriceAdjacence.h"

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
