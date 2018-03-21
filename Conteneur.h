#ifndef CONTENEUR_H
#define CONTENEUR_H

#include "Graphe.h"

class Conteneur
{
public:
    Conteneur();
    //~Conteneur();
    
    // méthodes de conversion
    
    void adj_to_fsasps();
    void fsaps_to_adj();
    //void adj_to_liste();
    //void liste_to_adj();
    //void fsaps_to_liste();
    //void liste_to_fsaps();
    
    
    
    

private:
    MatriceAdjacence *d_matrice_adjacence;
    Liste *d_liste;
    FsAps *d_fs_aps;
};


#endif // CONTENEUR_H
