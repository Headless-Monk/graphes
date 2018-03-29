#ifndef LISTEPRINCIPALE_H
#define LISTEPRINCIPALE_H

#include <iostream>

#include "ListeSecondaire.h"

class ListeSecondaire;
class ListePrincipale
{
    public:
        ListePrincipale();
        ListePrincipale(int sommet);

        void afficher(std::ostream &os) const;

        /*GET*/
        int sommet();
        ListePrincipale* sommet_suivant();

        /*SET*/
        void sommet_suivant(ListePrincipale *sommet);
        void successeur_suivant(ListeSecondaire *successeur);

        /*surcharges opérateur*/
        friend std::ostream& operator<<(std::ostream& os, const ListePrincipale &liste);

    private:
        int d_sommet;
        ListePrincipale *d_sommet_suivant;
        ListeSecondaire *d_successeur_suivant;

};


#endif // LISTEPRINCIPALE_H
