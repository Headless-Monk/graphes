#ifndef GRAPHE_H
#define GRAPHE_H

#include "Liste.h"
#include "MatriceAdjacence.h"
#include "FsAps.h"

class Graphe
{
public:
    Graphe();
    virtual void distance(FsAps* fsaps, int s, int* &d) = 0;
    virtual void calcul_rang(FsAps* fs_aps, int* &rang, int* &pilch, int* &prem);
    

private:
        
};


#endif // GRAPHE_H
