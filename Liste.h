#ifndef LISTE_H
#define LISTE_H

#include "ListePrincipale.h"
#include "ListeSecondaire.h"

class Liste
{
    public:
        Liste(ListePrincipale *racine);

        void afficher(std::ostream &os) const;


        /*surcharges op�rateur*/
        friend std::ostream& operator<<(std::ostream& os, const Liste &liste);

    private:
        ListePrincipale *d_racine;
};


#endif // LISTE_H
