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
        vector <int> distance(int) ;
        vector <vector<int>> matrice_distance () ;
        void tarjan() ;
        void traversee( int) ;
        void empiler(int, vector <int>) ;

        // accesseur
        vector <int> getFs() const;
        vector <int> getAps() const;
        int longueurFs() const;
        int longueurAps() const ;
        int nombreArc() const;

    private:
    	vector <int> d_fs ;
    	vector <int> d_aps ;

    	vector <int> num, mu, prem, pilch, cfc, tarj ;
        vector <bool> enTarj ;
        int nbc ;
};


#endif // FSAPS_H
