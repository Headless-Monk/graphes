#ifndef CONTENEUR_H
#define CONTENEUR_H

#include "Graphe.h"

class Conteneur
{
public:
    Conteneur();
    Conteneur(MatriceAdjacence* matrice);
    Conteneur(FsAps* fsaps);
    Conteneur(Liste* liste);
    //~Conteneur();

    // méthodes de conversion

    void adj_to_fsasps();
    void fsaps_to_adj();
    //void adj_to_liste();
    //void liste_to_adj();
    //void fsaps_to_liste();
    //void liste_to_fsaps();

    void liste(Liste *li);
    Liste* liste();
    MatriceAdjacence* matrice();
    FsAps* fs_aps();

private:
    MatriceAdjacence *d_matrice_adjacence;
    Liste *d_liste;
    FsAps *d_fs_aps;
};


#endif // CONTENEUR_H
