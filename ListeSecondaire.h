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

        /*SET*/
        void successeur_suivant(ListeSecondaire *successeur);

        /*GET*/
        ListeSecondaire* successeur_suivant();

        /*surcharges opérateur*/
        friend std::ostream& operator<<(std::ostream& os, const ListeSecondaire &liste);

    private:
        int d_arc;
        ListeSecondaire *d_successeur_suivant;
        ListePrincipale *d_sommet_pointe;

};


#endif // LISTESECONDAIRE_H
