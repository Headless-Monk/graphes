#include <iostream>

#include "Liste.h"
#include "ListeSecondaire.h"
#include "ListePrincipale.h"

using std::cout;
using std::endl;

void test_liste_secondaire()
{
    ListePrincipale p1{1};
    ListePrincipale p2{2};
    ListePrincipale p3{3};
    ListePrincipale p4{4};

    p1.sommet_suivant(&p2);
    p2.sommet_suivant(&p3);
    p3.sommet_suivant(&p4);
    p4.sommet_suivant(nullptr);

    ListeSecondaire s1(&p1);
    ListeSecondaire s2(&p2);
    ListeSecondaire s3(&p3);
    ListeSecondaire s4(&p4);
    ListeSecondaire s5(&p2);
    ListeSecondaire s6(&p1);

    s1.successeur_suivant(&s2);
    s2.successeur_suivant(nullptr);
    s3.successeur_suivant(&s4);
    s4.successeur_suivant(nullptr);
    s5.successeur_suivant(nullptr);
    s6.successeur_suivant(nullptr);

    p1.successeur_suivant(&s1);
    p2.successeur_suivant(&s3);
    p3.successeur_suivant(&s5);
    p4.successeur_suivant(&s6);

    Liste l{&p1};

    cout << l;
}

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

    l.supprimer_sommet(4);

    cout << l;

}

int main(int argc, char *argv[])
{
    //test_liste_secondaire();
    //cout << endl << "---------------------" << endl << endl;
    test_liste_secondaire_2();

    return 0;
}
