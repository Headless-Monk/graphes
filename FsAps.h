#ifndef FSAPS_H
#define FSAPS_H

#include <iostream>
#include <vector>

using namespace std ;

class FsAps
{
    public:

        FsAps(vector<int>, vector<int>);
        FsAps(vector<int>);
        vector <int> getFs() const;
        vector <int> getAps() const;
        int longueurFs() const;
        int longueurAps() const ;
        int nombreArc() const;

    private:
    	vector <int> d_fs ;
    	vector <int> d_aps ;
};


#endif // FSAPS_H
