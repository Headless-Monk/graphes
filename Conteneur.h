#ifndef CONTENEUR_H
#define CONTENEUR_H

#include "Graphe.h"

class Conteneur
{
public:
    Conteneur();
    Conteneur(bool orientation);
    Conteneur(MatriceAdjacence* matrice, bool orientation);
    Conteneur(FsAps* fsaps, bool orientation);
    Conteneur(Liste* liste, bool orientation);
    //~Conteneur();

    // méthodes de conversion
    void adj_to_fsasps();
    void fsaps_to_adj();
    void adj_to_liste();
    void fsaps_to_liste();
    void liste_to_adj();
    void liste_to_fsaps();

    void liste(Liste *li);
    void fsaps(FsAps *fa) ;
    void matrice(MatriceAdjacence *adj) ;

    bool get_orientation() const;
    void set_orientation(bool orientation);

    Liste* liste();
    MatriceAdjacence* matrice();
    FsAps* fs_aps();

private:
    MatriceAdjacence *d_matrice_adjacence;
    Liste *d_liste;
    FsAps *d_fs_aps;
    bool d_orientation;
};


#endif // CONTENEUR_H
