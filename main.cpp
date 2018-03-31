#include <iostream>

#include "Liste.h"
#include "ListeSecondaire.h"
#include "ListePrincipale.h"

using std::cout;
using std::endl;


void test_liste_secondaire_2()
{
    Liste l{};

    l.ajouter_sommet();
    l.ajouter_sommet();
    l.ajouter_sommet();
    l.ajouter_sommet();

    l.ajouter_successeur(1,1);
    l.ajouter_successeur(1,2);
    l.ajouter_successeur(2,3);
    l.ajouter_successeur(2,4);
    l.ajouter_successeur(3,2);
    l.ajouter_successeur(4,1);


    cout << l << endl << "--------------" << endl << endl;

    l.supprimer_sommet(2);
    l.supprimer_arc(3, 1);

    cout << l;
}

int main(int argc, char *argv[])
{

    test_liste_secondaire_2();

    return 0;
}
