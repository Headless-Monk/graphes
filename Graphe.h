#ifndef GRAPHE_H
#define GRAPHE_H

#include "Liste.h"
#include "MatriceAdjacence.h"
#include "FsAps.h"

class Graphe
{
public:
    Graphe();

    virtual void afficher(std::ostream &os) const =0;

    virtual void distance(FsAps* fsaps, int s, int* &d) =0;
    virtual void calcul_rang(FsAps* fs_aps, int* &rang, int* &pilch, int* &prem) =0;

private:

};


#endif // GRAPHE_H
