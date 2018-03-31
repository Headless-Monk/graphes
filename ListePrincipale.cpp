#include "ListePrincipale.h"

/*GET*/

int ListePrincipale::cle_sommet()
{
    return d_cle_sommet;
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

void ListePrincipale::cle_sommet(int cle_sommet)
{
    d_cle_sommet = cle_sommet;
}

void ListePrincipale::sommet_suivant(ListePrincipale *sommet)
{
    d_sommet_suivant = sommet;
}

void ListePrincipale::successeur_suivant(ListeSecondaire *successeur)
{
    d_successeur_suivant = successeur;
}

/*surcharges operateur*/

std::ostream& operator<<(std::ostream &os, const ListePrincipale &liste)
{
    liste.afficher(os);
    return os;
}

/*methodes privees*/

ListePrincipale::ListePrincipale(int cle_sommet) :
    d_cle_sommet{cle_sommet},
    d_sommet{},
    d_sommet_suivant{nullptr},
    d_successeur_suivant{nullptr}
{}

ListePrincipale::~ListePrincipale()
{
    ListeSecondaire *liste = d_successeur_suivant;

    while(liste)
    {
        d_successeur_suivant = liste;
        liste = liste->successeur_suivant();
        delete d_successeur_suivant;
    }
}

void ListePrincipale::afficher(std::ostream &os) const
{
    os << d_cle_sommet;

    ListeSecondaire *successeur = d_successeur_suivant;
    while(successeur)
    {
        os << " --> " << *successeur;
        successeur = successeur->successeur_suivant();
    }
}

void ListePrincipale::ajouter_successeur(ListePrincipale *sommet)
{
    ListeSecondaire *successeur = d_successeur_suivant;
    ListeSecondaire *precedent = d_successeur_suivant;

    while(successeur)
    {
        precedent = successeur;
        successeur = successeur->successeur_suivant();
    }

    ListeSecondaire *nouveau_successeur = new ListeSecondaire{sommet};
    if(precedent != nullptr)
    {
        precedent->successeur_suivant(nouveau_successeur);
    }
    else
    {
        d_successeur_suivant = nouveau_successeur;
    }
}

void ListePrincipale::supprimer_arc_vers(ListePrincipale *sommet)
{
    ListeSecondaire *successeur = d_successeur_suivant;
    ListeSecondaire *precedent = d_successeur_suivant;

    while( (successeur != nullptr) && (successeur->sommet_pointe() != sommet))
    {
        precedent = successeur;
        successeur = successeur->successeur_suivant();
    }

    if(successeur != nullptr)
    {
        if(d_successeur_suivant->sommet_pointe() == sommet)
        {
            d_successeur_suivant = successeur->successeur_suivant();
        }
        else
        {
            precedent->successeur_suivant(successeur->successeur_suivant());
        }

        delete successeur;
    }
}

void ListePrincipale::supprimer_arcs()
{
    ListeSecondaire *successeur = d_successeur_suivant;
    ListeSecondaire *precedent = d_successeur_suivant;

    while(successeur)
    {
        precedent = successeur;
        successeur = successeur->successeur_suivant();
        delete precedent;
    }

    d_successeur_suivant = nullptr;
}
