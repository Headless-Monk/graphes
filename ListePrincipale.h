#ifndef LISTEPRINCIPALE_H
#define LISTEPRINCIPALE_H

#include <iostream>

#include "ListeSecondaire.h"
#include "Sommet.h"

class ListeSecondaire;
class ListePrincipale
{
    public:
        ListePrincipale();
        ListePrincipale(int cle_sommet);

        void afficher(std::ostream &os) const;
        void ajouter_successeur(ListePrincipale *sommet);

        /*GET*/
        int cle_sommet();
        //Sommet sommet();
        ListePrincipale* sommet_suivant();
        ListeSecondaire* successeur_suivant();

        /*SET*/
        void cle_sommet(int cle_sommet);
        //void Sommet(Sommet &sommet);
        void sommet_suivant(ListePrincipale *sommet);
        void successeur_suivant(ListeSecondaire *successeur);

        /*surcharges opérateur*/
        friend std::ostream& operator<<(std::ostream& os, const ListePrincipale &liste);

    private:
        int d_cle_sommet;
        Sommet d_sommet;
        ListePrincipale *d_sommet_suivant;
        ListeSecondaire *d_successeur_suivant;

};


#endif // LISTEPRINCIPALE_H
