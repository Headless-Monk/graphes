#include "Liste.h"

Liste::Liste(ListePrincipale *racine) : d_racine{racine}
{}

void Liste::afficher(std::ostream &os) const
{
    ListePrincipale *liste = d_racine;

    while(liste)
    {
        os << *liste << std::endl;
        liste = liste->sommet_suivant();
    }
}


std::ostream& operator<<(std::ostream &os, const Liste &liste)
{
    liste.afficher(os);
    return os;
}
