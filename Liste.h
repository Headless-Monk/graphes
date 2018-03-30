#ifndef LISTE_H
#define LISTE_H

#include "ListePrincipale.h"
#include "ListeSecondaire.h"

class Liste
{
    public:
        Liste();
        Liste(ListePrincipale *racine);
        ~Liste();

        void afficher(std::ostream &os) const;
        void ajouter_sommet();
        void ajouter_successeur(int numero_sommet, int numero_sommet_successeur);

        /*surcharges opérateur*/
        friend std::ostream& operator<<(std::ostream& os, const Liste &liste);

    private:
        ListePrincipale *d_racine;
};


#endif // LISTE_H
