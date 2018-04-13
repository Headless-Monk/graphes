#ifndef LISTEPRINCIPALE_H
#define LISTEPRINCIPALE_H

#include <iostream>

#include "ListeSecondaire.h"
#include "Sommet.h"

class ListeSecondaire;
class Liste;
class ListePrincipale
{
    friend Liste;


    public:
        /*GET*/
        int cle_sommet();
        //Sommet sommet();
        ListePrincipale* sommet_suivant();
        ListeSecondaire* successeur_suivant();
        std::vector<int> liste_successeurs();

        /*SET*/
        void cle_sommet(int cle_sommet);
        //void Sommet(Sommet &sommet);
        void sommet_suivant(ListePrincipale *sommet);
        void successeur_suivant(ListeSecondaire *successeur);

        /*surcharges opérateur*/
        friend std::ostream& operator<<(std::ostream& os, const ListePrincipale &liste);

    private:
        ListePrincipale() =delete;
        ListePrincipale(int cle_sommet);
        ~ListePrincipale();

        void afficher(std::ostream &os) const;
        void ajouter_successeur(ListePrincipale *sommet);

        void supprimer_arc_vers(ListePrincipale *sommet);
        void supprimer_arcs();

        bool possede_successeur(ListePrincipale *successeur);


        int d_cle_sommet;
        Sommet d_sommet;
        ListePrincipale *d_sommet_suivant;
        ListeSecondaire *d_successeur_suivant;

};


#endif // LISTEPRINCIPALE_H
