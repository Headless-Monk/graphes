#include "Liste.h"

Liste::Liste() : d_racine{nullptr}, d_nombre_sommets{0}
{}

Liste::Liste(ListePrincipale *racine) : d_racine{racine}, d_nombre_sommets{1}
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
    ListePrincipale *sommet = sommet_position(numero_sommet);
    ListePrincipale *sommet_successeur = sommet_position(numero_sommet_successeur);

    sommet->ajouter_successeur(sommet_successeur);
}

void Liste::supprimer_arcs_vers(int numero_sommet)
{
    ListePrincipale *sommet = sommet_position(numero_sommet);
    ListePrincipale *sommet_courant = d_racine;

    while(sommet_courant)
    {
        if(sommet_courant != sommet)
        {
            sommet_courant->supprimer_arcs_vers(sommet);
        }
        sommet_courant = sommet_courant->sommet_suivant();
    }
}

void Liste::supprimer_arcs(int numero_sommet)
{
    ListePrincipale *sommet = sommet_position(numero_sommet);
    sommet->supprimer_arcs();
}

void Liste::supprimer_sommet(int numero_sommet)
{
    //suppression des arcs
    supprimer_arcs_vers(numero_sommet);
    supprimer_arcs(numero_sommet);

    //suppression des sommets
    ListePrincipale *sommet = sommet_position(numero_sommet);
    ListePrincipale *sommet_courant = d_racine, *precedent = d_racine;

    while(sommet_courant != sommet)
    {
        precedent = sommet_courant;
        sommet_courant = sommet_courant->sommet_suivant();
    }

    if(sommet_courant == d_racine)
    {
        d_racine = d_racine->sommet_suivant();
    }
    else
    {
        precedent->sommet_suivant(sommet_courant->sommet_suivant());
    }

    delete sommet_courant;

    //mise à jour des cles sommets
    if(d_racine->cle_sommet() != 1)
    {
        d_racine->cle_sommet(1);
        sommet_courant = d_racine->sommet_suivant();
    }
    else
    {
        sommet_courant = precedent->sommet_suivant();
    }

    while(sommet_courant)
    {
        sommet_courant->cle_sommet(precedent->cle_sommet()+1);
        precedent = sommet_courant;
        sommet_courant = sommet_courant->sommet_suivant();
    }
}

/*
void ListePrincipale::supprimer_arc(int numero_sommet, int numero_sommet_successeur)
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
}*/


/*GET*/
ListePrincipale* Liste::sommet_position(int position)
{
    int sommet_courant = 1;
    ListePrincipale *sommet = d_racine;

    while(sommet_courant != position)
    {
        sommet_courant++;
        sommet = sommet->sommet_suivant();
    }

    return sommet;
}

/*surcharges opérateur*/

std::ostream& operator<<(std::ostream &os, const Liste &liste)
{
    liste.afficher(os);
    return os;
}
