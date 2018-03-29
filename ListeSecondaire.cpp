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

/*GET*/

int ListeSecondaire::arc()
{
    return d_arc;
}

ListeSecondaire* ListeSecondaire::successeur_suivant()
{
    return d_successeur_suivant;
}

ListePrincipale* ListeSecondaire::sommet_pointe()
{
    return d_sommet_pointe;
}

/*SET*/

void ListeSecondaire::arc(int arc)
{
    d_arc = arc;
}

void ListeSecondaire::successeur_suivant(ListeSecondaire *successeur)
{
    d_successeur_suivant = successeur;
}

void ListeSecondaire::sommet_pointe(ListePrincipale *sommet)
{
    d_sommet_pointe = sommet;
}

/*surcharges opérateur*/

std::ostream& operator<<(std::ostream &os, const ListeSecondaire &liste)
{
    liste.afficher(os);
    return os;
}
