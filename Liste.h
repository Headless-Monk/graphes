#ifndef LISTE_H
#define LISTE_H

#include "ListePrincipale.h"
#include "ListeSecondaire.h"

class Liste
{
    public:
        Liste();
        Liste(int nombre_sommet);
        Liste(ListePrincipale *racine);
        ~Liste();

        void afficher(std::ostream &os) const;
        void ajouter_sommet();
        void ajouter_successeur(int numero_sommet, int numero_sommet_successeur);

        void supprimer_sommet(int numero_sommet);
        void supprimer_arc(int numero_sommet, int numero_sommet_successeur);

        /*GET*/
        ListePrincipale* sommet_position(int position);

        /*surcharges opérateur*/
        friend std::ostream& operator<<(std::ostream& os, const Liste &liste);

    private:
        void supprimer_arcs_vers(int numero_sommet);
        void supprimer_arcs_de(int numero_sommet);
        bool indice_valide(int position);

        ListePrincipale *d_racine;
        int d_nombre_sommets;
};


#endif // LISTE_H
