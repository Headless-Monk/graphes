#include "ListeSecondaire.h"

ListeSecondaire::ListeSecondaire() :
    d_arc{0},
    d_successeur_suivant{nullptr},
    d_sommet_pointe{nullptr}
{}

ListeSecondaire::ListeSecondaire(ListePrincipale *sommet) :
    d_arc{0},
    d_successeur_suivant{nullptr},
    d_sommet_pointe{sommet}
{}

void ListeSecondaire::afficher(std::ostream &os) const
{
    os << d_sommet_pointe->sommet();
}

void ListeSecondaire::successeur_suivant(ListeSecondaire *successeur)
{
    d_successeur_suivant = successeur;
}

ListeSecondaire* ListeSecondaire::successeur_suivant()
{
    return d_successeur_suivant;
}

std::ostream& operator<<(std::ostream &os, const ListeSecondaire &liste)
{
    liste.afficher(os);
    return os;
}
