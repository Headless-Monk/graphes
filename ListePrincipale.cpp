#include "ListePrincipale.h"

ListePrincipale::ListePrincipale() :
    d_sommet{0},
    d_sommet_suivant{nullptr},
    d_successeur_suivant{nullptr}
{}

ListePrincipale::ListePrincipale(int sommet) :
    d_sommet{sommet},
    d_sommet_suivant{nullptr},
    d_successeur_suivant{nullptr}
{}

void ListePrincipale::afficher(std::ostream &os) const
{
    os << d_sommet;

    ListeSecondaire *successeur = d_successeur_suivant;
    while(successeur)
    {
        os << " --> " << *successeur;
        successeur = successeur->successeur_suivant();
    }
}

/*GET*/

int ListePrincipale::sommet()
{
    return d_sommet;
}

ListePrincipale* ListePrincipale::sommet_suivant()
{
    return d_sommet_suivant;
}

ListeSecondaire* ListePrincipale::successeur_suivant()
{
    return d_successeur_suivant;
}

/*SET*/

void ListePrincipale::sommet(int sommet)
{
    d_sommet = sommet;
}

void ListePrincipale::sommet_suivant(ListePrincipale *sommet)
{
    d_sommet_suivant = sommet;
}

void ListePrincipale::successeur_suivant(ListeSecondaire *successeur)
{
    d_successeur_suivant = successeur;
}

/*surcharges op�rateur*/

std::ostream& operator<<(std::ostream &os, const ListePrincipale &liste)
{
    liste.afficher(os);
    return os;
}
