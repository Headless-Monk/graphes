#ifndef LISTESECONDAIRE_H
#define LISTESECONDAIRE_H

#include <iostream>

#include "ListePrincipale.h"

class ListePrincipale;
class ListeSecondaire
{
    public:
        ListeSecondaire();
        ListeSecondaire(ListePrincipale *sommet);

        void afficher(std::ostream &os) const;

        /*GET*/
        int arc();
        ListeSecondaire* successeur_suivant();
        ListePrincipale* sommet_pointe();

        /*SET*/
        void arc(int arc);
        void successeur_suivant(ListeSecondaire *successeur);
        void sommet_pointe(ListePrincipale *sommet);

        /*surcharges opérateur*/
        friend std::ostream& operator<<(std::ostream& os, const ListeSecondaire &liste);

    private:
        int d_arc;
        ListeSecondaire *d_successeur_suivant;
        ListePrincipale *d_sommet_pointe;

};


#endif // LISTESECONDAIRE_H
