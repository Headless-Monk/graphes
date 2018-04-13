#include "Interface.h"
#include <cstdlib>

Interface::Interface() : d_graphe_courant{0}, d_type_courant{0}, d_liste_graphes{}
{
    graphe_pour_tests();
}

void Interface::graphe_pour_tests()
{
    /*graphe 1, non oriente*/
    d_liste_graphes.push_back(new Conteneur{0});

    Liste *l1 = new Liste{4, 0};

    l1->ajouter_successeur(1,1);
    l1->ajouter_successeur(1,2);
    l1->ajouter_successeur(1,3);
    l1->ajouter_successeur(1,4);
    l1->ajouter_successeur(2,3);
    l1->ajouter_successeur(2,4);
    l1->ajouter_successeur(3,2);
    l1->ajouter_successeur(4,1);

    l1->ajouter_successeur(2,1);
    l1->ajouter_successeur(3,2);
    l1->ajouter_successeur(4,2);
    l1->ajouter_successeur(2,3);
    l1->ajouter_successeur(1,4);

    d_liste_graphes[0]->liste(l1);

    d_liste_graphes[0]->liste_to_adj();
    d_liste_graphes[0]->liste_to_fsaps();

    /*graphe 2, oriente*/
    d_liste_graphes.push_back(new Conteneur{1});

    MatriceAdjacence* mat = new MatriceAdjacence{};
s
    mat->ajouterArc(1, 1);
    mat->ajouterArc(1, 2);
    mat->ajouterArc(1, 3);
    mat->ajouterArc(5, 3);
    mat->ajouterArc(3, 4);
    mat->ajouterArc(1, 5);
    mat->ajouterArc(5, 6);
    mat->ajouterArc(8, 7);
    mat->ajouterArc(2, 8);

    d_liste_graphes[1]->matrice(mat);

    d_liste_graphes[1]->adj_to_liste();
    d_liste_graphes[1]->adj_to_fsasps();
}

void Interface::clear_console()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Interface::afficher_graphe(std::ostream &os)
{
    afficher_graphe(os, d_graphe_courant);
}

void Interface::afficher_graphe(std::ostream &os, int numero)
{
    switch(d_type_courant)
    {
    case 0 :
        if(d_liste_graphes[numero]->liste())
            os << *d_liste_graphes[numero]->liste();
        else
            os << "Graphe liste indisponible" << endl;
        break;
    case 1 :
        /*matrice*/
        if(d_liste_graphes[numero]->matrice())
            d_liste_graphes[numero]->matrice()->afficher(os);
        else
            os << "Graphe matrice indisponible" << endl;
        break;
    case 2 :
        /*fs_aps*/
        if(d_liste_graphes[numero]->fs_aps())
            os << *d_liste_graphes[numero]->fs_aps();
        else
            os << "Graphe Fs Aps indisponible" << endl;
        break;
    default :
        break;
    }

    os << endl;
}

void Interface::menu_principal(std::ostream &os, std::istream &is)
{
    int graphe = 0;
    int type = 0;
    int choix = 0;
    while(choix != 5)
    {
        clear_console();

        afficher_graphe(os);

        os << "(1) Changer de graphe courant" << endl;
        os << "(2) Changer le mode d'affichage du graphe" << endl;
        os << "(3) Actions sur le graphe courant" << endl;
        os << "(4) Action sur les graphes" << endl;
        os << "(5) Quitter" << endl << endl;


        is >> choix;

        switch (choix)
        {
            case 1:
                for(unsigned int i=0; i<d_liste_graphes.size(); i++)
                {
                    os << "(" << i+1 << ") --------------------" << endl;
                    afficher_graphe(os, i);
                    os << endl;
                }
                os << "Saisir le numero du graphe a selectionner : ";
                do
                {
                    is >> graphe;
                }while((graphe<1) || (graphe>(int)d_liste_graphes.size()));
                d_graphe_courant = graphe-1;
                break;
            case 2:
                os << "0 : Liste" << endl;
                os << "1 : Matrice" << endl;
                os << "2 : fs aps" << endl;
                os << "Saisir le type : ";
                do
                {
                    is >> type;
                }while((type<0) || (type>2));
                d_type_courant = type;
                break;
            case 3:
                if(d_type_courant == 0)
                    menu_liste(os, is);
                if(d_type_courant == 1)
                    menu_matrice(os, is);
                if(d_type_courant == 2)
                    menu_fs_aps(os, is);
                break;

            case 4:
                clear_console();
                afficher_graphe(os, d_graphe_courant);

                os << "(1) Ajouter un graphe" << endl;
                os << "(2) Modifier un graphe" << endl;
                os << "(3) Supprimer un graphe" << endl;
                os << "(4) Retour" << endl;
                is >> choix;
                clear_console();
                switch (choix)
                {
                    case 1:
                        menu_creer_graphe(os, is);
                    break;
                    case 2:
                        menu_modifier_graphe(os, is);
                    break;
                    case 3:
                        menu_supprimer_graphe(os, is);
                    break;
                }
                break;
            default:
                break;
        }
    }
}


void Interface::menu_liste(std::ostream &os, std::istream &is)
{
    int sommet1=0, sommet2=0;
    int choix = 0;
    while(choix != 5)
    {
        clear_console();

        afficher_graphe(os);

        os << "(1) Ajouter sommet" << endl;
        os << "(2) Ajouter successeur" << endl;
        os << "(3) Supprimer sommet" << endl;
        os << "(4) Supprimer arc" << endl;
        os << "(5) Retour" << endl << endl;

        is >> choix;

        switch (choix)
        {
            case 1:
                d_liste_graphes[d_graphe_courant]->liste()->ajouter_sommet();
                break;
            case 2:
                os << "Saisir le numero du sommet de depart : ";
                is >> sommet1;
                os << "Saisir le numero du sommet d'arrivee : ";
                is >> sommet2;
                d_liste_graphes[d_graphe_courant]->liste()->ajouter_successeur(sommet1, sommet2);
                if(!d_liste_graphes[d_graphe_courant]->liste()->oriente())
                    if(sommet1 != sommet2)
                        d_liste_graphes[d_graphe_courant]->liste()->ajouter_successeur(sommet2, sommet1);
                break;
            case 3:
                os << "Saisir le numero du sommet a supprimer : ";
                is >> sommet1;
                d_liste_graphes[d_graphe_courant]->liste()->supprimer_sommet(sommet1);
                break;
            case 4:
                os << "Saisir le numero du sommet de depart : ";
                is >> sommet1;
                os << "Saisir le numero du sommet d'arrivee : ";
                is >> sommet2;
                d_liste_graphes[d_graphe_courant]->liste()->supprimer_arc(sommet1, sommet2);
                if(!d_liste_graphes[d_graphe_courant]->liste()->oriente())
                    d_liste_graphes[d_graphe_courant]->liste()->supprimer_arc(sommet2, sommet1);
                break;
            default:
                break;
        }
    }
}

void Interface::menu_matrice(std::ostream &os, std::istream &is)
{
    int sommet1=0, sommet2=0;
    std::vector<int> prufer;
    int choix = 0;
    while(choix != 4)
    {
        clear_console();

        afficher_graphe(os);

        os << "(1) Ajouter arc" << endl;
        os << "(2) Supprimer arc" << endl;
        os << "(3) Codage de Prufer" << endl;
        os << "(4) Retour" << endl << endl;

        is >> choix;

        switch (choix)
        {
            case 1:
                os << "Saisir le numero du sommet de depart : ";
                is >> sommet1;
                os << "Saisir le numero du sommet d'arrivee : ";
                is >> sommet2;

                d_liste_graphes[d_graphe_courant]->matrice()->ajouterArc(sommet1, sommet2);
                break;
            case 2:
                os << "Saisir le numero du sommet de depart : ";
                is >> sommet1;
                os << "Saisir le numero du sommet d'arrivee : ";
                is >> sommet2;
                d_liste_graphes[d_graphe_courant]->matrice()->supprimerArc(sommet1, sommet2);
                break;
            case 3:
                prufer = d_liste_graphes[d_graphe_courant]->matrice()->codagePrufer();
                os << "{";
                for(unsigned int i = 0; i < prufer.size() ; i++)
                {
                    if(i==prufer.size()-1)
                        os << prufer[i];
                    else
                        os << prufer[i] << "," ;
                }

                os << "}" << endl;
                break;
            default:
                break;
        }
    }

}

void Interface::menu_fs_aps(std::ostream &os, std::istream &is)
{
    int sommet1=0, sommet2=0, test , maxi;
    int ** tableau_distance ;
    int *lc_ordo, *fpc_ordo,* appc_ordo;
    int *d_ordo = new int[6];
    d_ordo[0]=0;d_ordo[1]=2 ;d_ordo[2]=3 ;d_ordo[3]=1;d_ordo[4]=2 ;d_ordo[5]=3 ;
    vector <int> cfc_tarjan ;

    int choix = 0;
    while(choix != 7)
    {
        clear_console();

        afficher_graphe(os);

        os << "(1) Ajouter arc" << endl;
        os << "(2) Supprimer arc" << endl;
        os << "(3) Calcul des distances" << endl;
        os << "(4) Composantes fortement connexes selon Tarjan" << endl;
        os << "(5) Ordonnancement" << endl;
        os << "(6) Dijkstra" << endl;
        os << "(7) Retour" << endl << endl;

        is >> choix;

        switch (choix)
        {
            case 1:
                os << "Saisir le numero du sommet de depart : ";
                is >> sommet1;
                os << "Saisir le numero du sommet d'arrivee : ";
                is >> sommet2;
                d_liste_graphes[d_graphe_courant]->fs_aps()->ajouter_arc(sommet1 , sommet2);
                break;
            case 2:
                os << "Saisir le numero du sommet de depart : ";
                is >> sommet1;
                os << "Saisir le numero du sommet d'arrivee : ";
                is >> sommet2;
                d_liste_graphes[d_graphe_courant]->fs_aps()->supprimer_arc(sommet1 , sommet2);
                break;
            case 3:

                d_liste_graphes[d_graphe_courant]->fs_aps()->matrice_distance(tableau_distance);


                for (int i = 1  ; i <= tableau_distance[0][0] ; i++)
                {
                    cout << "Distance de "<<i<<" vers : "<<endl ;
                    for (int j = 1  ; j <= tableau_distance[0][0] ; j++)
                    {
                        if (i!=j)
                        {
                            if (tableau_distance[i][j] !=-1)
                                cout <<" -> "<< j << " = "<< tableau_distance[i][j] <<endl;
                            else
                                cout <<" -> "<< j << " n'existe pas " <<endl;
                        }
                    }
                    cout << endl ;
                }

                os << "Appuiez sur 1 pour continuer";
                is >> test;
                break;
            case 4 :
                d_liste_graphes[d_graphe_courant]->fs_aps()->tarjan() ;
                os << "Appuiez sur 1 pour continuer";
                is >> test;
                break ;
            case 5 :
                d_liste_graphes[d_graphe_courant]->fs_aps()->ordonnancement (d_ordo,lc_ordo, fpc_ordo, appc_ordo);
                maxi =0 ;
                for (int i = 1 ; i <lc_ordo[0] ; i++)
                {
                    if(maxi <lc_ordo[i])maxi = lc_ordo[i] ;
                    cout << "Tâche "<<i<<" = "<<d_ordo[i]<<" jours"<<endl ;
                }
                cout << "La durée du projet est de "<<maxi<<" jours"<<endl;

                os << "Appuiez sur 1 pour continuer";
                is >> test;
                break ;
            case 6 :

                break ;
            default:
                break;
        }
    }
}

void Interface::menu_creer_graphe(std::ostream &os, std::istream &is)
{
    bool oriente;
    int nbr_sommet;

    clear_console();
    afficher_graphe(os, d_graphe_courant);

    os << "0 : Graphe non oriente" << endl;
    os << "1 : Graphe oriente" << endl;

    is >> oriente;

    os << "Quel est le nombre de sommets ?" << endl;
    is >> nbr_sommet;

    d_liste_graphes.push_back(new Conteneur{new Liste{nbr_sommet, oriente}, oriente});
}

void Interface::menu_modifier_graphe(std::ostream &os, std::istream &is)
{
    os << "Fonction en construction (ou pas... personne ne le sait...)" << endl;
    system("pause");
}

void Interface::menu_supprimer_graphe(std::ostream &os, std::istream &is)
{
    int choix;

    clear_console();

    for(unsigned int i = 0; i < d_liste_graphes.size(); i++)
    {
        os << i << " ------------------------" << endl;
        afficher_graphe(os, i);
    }

    os << "Numero du graphe à supprimer : ";
    is >> choix;

    if(d_liste_graphes.size() == 1)
    {
        d_liste_graphes.pop_back();
        d_liste_graphes.resize(0);
    }
    else
    {
        for(unsigned int i = choix; i < d_liste_graphes.size(); i++)
        {
            d_liste_graphes[i] = d_liste_graphes[i+1];
        }
        d_liste_graphes.resize(d_liste_graphes.size()-1);
    }

}



