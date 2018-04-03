#ifndef FSAPS_H
#define FSAPS_H

#include <iostream>
#include <vector>

using namespace std ;

class FsAps
{
    public:

        // constructeur
        FsAps(vector<int>, vector<int>);
        FsAps(vector<int>);

        // méthodes
        vector <int> distance(int, vector <int> ) ;
        vector <vector<int>> matrice_distance (vector <vector<int>>) ;
        void tarjan() ;
        void graphe_reduit(int *& , int *&) ;
        void traversee( int) ;
        void empiler(int, vector <int>) ;
        void dijkstra(int**, int s, int *&, int *&) ;
        void ordonnancement (int* , int *& , int *& , int *& );

        // gestion structure
        void ajouter_arc(int, int) ;
        void supprimer_arc(int, int) ;

        // accesseur
        vector <int> getFs() const;
        vector <int> getAps() const;

        int index_getFs(int i) const;
        int index_getAps(int i) const;

        void index_setFs(int i, int valeur);
        void index_setAps(int i, int valeur);

        int longueurFs() const;
        int longueurAps() const ;
        int nombreArc() const;


        void afficher(std::ostream &os) const;
        /*surcharges opérateur*/
        friend std::ostream& operator<<(std::ostream& os, const FsAps &fsaps);

    private:
    	vector <int> d_fs ;
    	vector <int> d_aps ;

    	vector <int> num, mu, prem, pilch, cfc, tarj ;
        vector <bool> enTarj ;
        int nbc ;
};


#endif // FSAPS_H
