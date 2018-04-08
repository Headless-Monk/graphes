#include "Interface.h"
#include <cstdlib>

Interface::Interface() : d_graphe_courant{0}, d_type_courant{0}, d_liste_graphes{}
{
    graphe_pour_tests();
}

void Interface::graphe_pour_tests()
{
    /*graphe 1*/
    d_liste_graphes.push_back(new Conteneur{});

    Liste *l1 = new Liste{4};

    l1->ajouter_successeur(1,1);
    l1->ajouter_successeur(1,2);
    l1->ajouter_successeur(2,3);
    l1->ajouter_successeur(2,4);
    l1->ajouter_successeur(3,2);
    l1->ajouter_successeur(4,1);

    d_liste_graphes[0]->liste(l1);
    d_graphe_courant = 0;

    /*graphe 2*/
    d_liste_graphes.push_back(new Conteneur{});

    Liste *l2 = new Liste{4};

    l2->ajouter_successeur(2,1);
    l2->ajouter_successeur(3,2);
    l2->ajouter_successeur(3,4);
    l2->ajouter_successeur(4,1);
    l2->ajouter_successeur(4,2);
    l2->ajouter_successeur(4,4);

    d_liste_graphes[1]->liste(l2);

    /*graphe 3, fs aps*/
    d_liste_graphes.push_back(new Conteneur{});

    vector<int> tab = {9,0,2,0,1,3,0,0} ;

    FsAps *fsaps1 = new FsAps{tab};
    d_liste_graphes[2]->fsaps(fsaps1);
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
            {
                os << "Graphe liste indisponible" << endl;
            }
        break;
    case 1 :
        /*matrice*/
        if(d_liste_graphes[numero]->matrice())
            /*os << *d_liste_graphes[numero]->matrice()*/;
        else
        {
                os << "Graphe matrice indisponible" << endl;
        }
        break;
    case 2 :
        /*fs_aps*/
        if(d_liste_graphes[numero]->fs_aps())
            os << *d_liste_graphes[numero]->fs_aps();
        else
        {
                os << "Graphe Fs Aps indisponible" << endl;
        }
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
    while(choix != 4)
    {
        clear_console();

        afficher_graphe(os);

        os << "(1) Changer de graphe courant" << endl;
        os << "(2) Changer le mode d'affichage du graphe" << endl;
        os << "(3) Actions sur le graphe" << endl;
        os << "(4) Quitter" << endl << endl;


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
                break;
            default:
                break;
        }
    }
}

void Interface::menu_matrice(std::ostream &os, std::istream &is)
{
    /*reprendre menu_liste*/
}

void Interface::menu_fs_aps(std::ostream &os, std::istream &is)
{
    int sommet1=0, sommet2=0, test ;
    int ** tableau_distance ;
    int* fsr_graphe_reduit, * apsr_graphe_reduit,*lc_ordo, *fpc_ordo,* appc_ordo;
    int *d = new int[3];
    d[0]=1;d[1]=2 ;d[2]=3 ;
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
                            if (tableau_distance[i][j] !=-1)
                                cout <<" -> "<< j << " = "<< tableau_distance[i][j] <<endl;
                            else
                                cout <<" -> "<< j << " n'existe pas " <<endl;
                    }
                    cout << endl ;
                }

                os << "Appuiez sur 1 pour continuer";
                is >> test;
                break;
            case 4 :
                d_liste_graphes[d_graphe_courant]->fs_aps()->tarjan() ;
                d_liste_graphes[d_graphe_courant]->fs_aps()->graphe_reduit(fsr_graphe_reduit , apsr_graphe_reduit ) ;

                /*
                cfc_tarjan = d_liste_graphes[d_graphe_courant]->fs_aps()->getCfc() ;
                cout << "Il y a "<< sizeof(apsr_graphe_reduit)-1 << "composantes fortements connexes" <<endl ;
                for (int i = 1 ; i <= sizeof(cfc_tarjan) ; i++)
                {
                    cout << "Sommet "<< i << " dans la composante : "<< cfc_tarjan[i] ;
                }
                */
                os << "Appuiez sur 1 pour continuer";
                is >> test;
                break ;
            case 5 :
                d_liste_graphes[d_graphe_courant]->fs_aps()->ordonnancement (d,lc_ordo, fpc_ordo, appc_ordo);


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

