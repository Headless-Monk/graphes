#ifndef MATRICEADJACENCE_H
#define MATRICEADJACENCE_H

#include <iostream>
#include <vector>

class MatriceAdjacence
{
    public:
        int index_get_adj(int i, int j) const;
        void set_adj(int i, int j, int valeur);

        std::vector<std::vector<int> > get_adj() const;

    private:
        std::vector<std::vector<int> > d_adj;

};

#endif // MATRICEADJACENCE_H
