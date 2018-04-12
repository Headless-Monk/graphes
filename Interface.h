#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include <ostream>
#include <stdint.h>

#include "Conteneur.h"

class Interface
{
    public:
        Interface();

        void graphe_pour_tests();


        void clear_console();
        void afficher_graphe(std::ostream &os);
        void afficher_graphe(std::ostream &os, int numero);
        void menu_principal(std::ostream &os, std::istream &is);


        void menu_liste(std::ostream &os, std::istream &is);
        void menu_matrice(std::ostream &os, std::istream &is);
        void menu_fs_aps(std::ostream &os, std::istream &is);

    private:
        int d_graphe_courant;
        int d_type_courant; /* 0:liste ; 1:matrice ; 2:fs_aps*/
        vector <Conteneur*> d_liste_graphes;

};


#endif // INTERFACE_H
