#include "Liste.h"

Liste::Liste() : d_racine{nullptr}, d_nombre_sommets{0}
{}

Liste::Liste(int nombre_sommet, bool oriente) :
    d_racine{nullptr},
    d_nombre_sommets{0},
    d_oriente{oriente}
{
    for(int i=0; i<nombre_sommet; i++)
    {
        ajouter_sommet();
    }
}

Liste::Liste(ListePrincipale *racine) : d_racine{racine}, d_nombre_sommets{1}
{}

Liste::~Liste()
{
    ListePrincipale *liste = d_racine;

    while(liste)
    {
        d_racine = liste;
        liste = liste->sommet_suivant();
        delete d_racine;
    }
}

void Liste::afficher(std::ostream &os) const
{
    ListePrincipale *liste = d_racine;

    std::string oriente;
    if(d_oriente)
        oriente = "oriente";
    else
        oriente = "non oriente";

    os << "Graphe " << oriente << " :" << std::endl;
    while(liste)
    {
        os << *liste << std::endl;
        liste = liste->sommet_suivant();
    }


    /* TEST */

    os << "Liste olivier :" << std::endl;
    std::vector<std::vector<int>> l = liste_arcs();

    for(int i=0; i<l.size(); i++)
    {
        for(int j=0; j<l[i].size(); j++)
        {
            os << l[i][j] << " --> ";
        }
        os << std::endl;
    }
    os << std::endl;


}

void Liste::ajouter_sommet()
{
    d_nombre_sommets++;

    ListePrincipale *liste = d_racine;
    ListePrincipale *precedent = d_racine;

    while(liste)
    {
        precedent = liste;
        liste = liste->sommet_suivant();
    }

    ListePrincipale *nouveau_sommet = new ListePrincipale{d_nombre_sommets};
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
    if(indice_valide(numero_sommet) && indice_valide(numero_sommet_successeur))
    {
        if(!arc_existant(numero_sommet, numero_sommet_successeur))
        {
            ListePrincipale *sommet = sommet_position(numero_sommet);
            ListePrincipale *sommet_successeur = sommet_position(numero_sommet_successeur);

            sommet->ajouter_successeur(sommet_successeur);
        }
    }
}

void Liste::supprimer_sommet(int numero_sommet)
{
    if(indice_valide(numero_sommet))
    {
        //suppression des arcs
        supprimer_arcs_vers(numero_sommet);
        supprimer_arcs_de(numero_sommet);

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
        d_nombre_sommets--;

        //mise à jour des cles sommets
        if(d_nombre_sommets > 0)
        {
            if(d_racine->cle_sommet() != 1)
            {
                d_racine->cle_sommet(1);
                sommet_courant = d_racine->sommet_suivant();
                precedent = d_racine;
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
    }
}

void Liste::supprimer_arc(int numero_sommet, int numero_sommet_successeur)
{
    if(indice_valide(numero_sommet) && indice_valide(numero_sommet_successeur))
    {
        ListePrincipale *sommet = sommet_position(numero_sommet);
        ListePrincipale *sommet_successeur = sommet_position(numero_sommet_successeur);

        sommet->supprimer_arc_vers(sommet_successeur);
    }
}


/*GET*/
ListePrincipale* Liste::sommet_position(int position)
{
    if(indice_valide(position))
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
    return nullptr;
}

bool Liste::oriente()
{
    return d_oriente;
}

std::vector<std::vector<int>> Liste::liste_arcs()
{
    std::vector<std::vector<int>> tabArcs(0, std::vector<int> (2));

    ListePrincipale *liste = d_racine;

    while(liste)
    {
        std::vector<int> liste_successeur = liste->liste_successeurs();

        for(unsigned int i=0; i<liste_successeur.size(); i++)
        {
            std::vector<int> succ{liste->cle_sommet(), liste_successeur[i]};
            tabArcs.push_back(succ);
        }

        liste = liste->sommet_suivant();
    }

    return tabArcs;
}

/*surcharges operateur*/

std::ostream& operator<<(std::ostream &os, const Liste &liste)
{
    liste.afficher(os);
    return os;
}

/*méthodes privées*/

void Liste::supprimer_arcs_vers(int numero_sommet)
{
    ListePrincipale *sommet = sommet_position(numero_sommet);
    ListePrincipale *sommet_courant = d_racine;

    while(sommet_courant)
    {
        if(sommet_courant != sommet)
        {
            sommet_courant->supprimer_arc_vers(sommet);
        }
        sommet_courant = sommet_courant->sommet_suivant();
    }
}

void Liste::supprimer_arcs_de(int numero_sommet)
{
    ListePrincipale *sommet = sommet_position(numero_sommet);
    sommet->supprimer_arcs();
}

bool Liste::indice_valide(int position)
{
    return ((position >= 1) && (position <= d_nombre_sommets))?true:false;
}

bool Liste::arc_existant(int numero_sommet, int numero_sommet_successeur)
{
    if(indice_valide(numero_sommet) && indice_valide(numero_sommet_successeur))
    {
        ListePrincipale *sommet = sommet_position(numero_sommet);
        ListePrincipale *sommet_successeur = sommet_position(numero_sommet_successeur);

        return sommet->possede_successeur(sommet_successeur);
    }

    return false;
}
