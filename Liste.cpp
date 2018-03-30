#include "Liste.h"

Liste::Liste() : d_racine{nullptr}
{}

Liste::Liste(ListePrincipale *racine) : d_racine{racine}
{}

Liste::~Liste()
{
    delete d_racine;
}

void Liste::afficher(std::ostream &os) const
{
    ListePrincipale *liste = d_racine;

    while(liste)
    {
        os << *liste << std::endl;
        liste = liste->sommet_suivant();
    }
}

void Liste::ajouter_sommet()
{
    int nombre_sommet = 0;
    ListePrincipale *liste = d_racine;
    ListePrincipale *precedent = d_racine;

    while(liste)
    {
        nombre_sommet++;
        precedent = liste;
        liste = liste->sommet_suivant();
    }

    ListePrincipale *nouveau_sommet = new ListePrincipale{nombre_sommet+1};
    if(precedent != nullptr)
    {
        precedent->sommet_suivant(nouveau_sommet);
    }
    else
    {
        d_racine = nouveau_sommet;
    }
}

void Liste::ajouter_successeur(int numero_sommet, int numero_sommet_successeur)
{
    int sommet_courant = 1, sommet_successeur_courant = 1;
    ListePrincipale *sommet = d_racine, *sommet_successeur = d_racine;

    while(sommet_courant != numero_sommet)
    {
        sommet_courant++;
        sommet = sommet->sommet_suivant();
    }

    while(sommet_successeur_courant != numero_sommet_successeur)
    {
        sommet_successeur_courant++;
        sommet_successeur = sommet_successeur->sommet_suivant();
    }

    sommet->ajouter_successeur(sommet_successeur);
}


/*surcharges opérateur*/

std::ostream& operator<<(std::ostream &os, const Liste &liste)
{
    liste.afficher(os);
    return os;
}
