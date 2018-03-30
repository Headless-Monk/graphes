#include "FsAps.h"

FsAps::FsAps(vector<int> fs, vector<int> aps)
{
    d_fs = fs ;
    d_aps = aps ;
}

FsAps::FsAps(vector<int> fs)
{
    d_fs = fs ;

    vector<int>aps ;
    aps.push_back(0);
    aps.push_back(d_fs.at(1));

    for (int i = 1 ;i < d_fs.size() ; i++)
        if (d_fs.at(i) == 0 && (i+1)<d_fs.size()) aps.push_back(d_fs.at(i+1));

    d_aps = aps ;
    d_aps.insert(d_aps.begin(),d_aps.size()); // longueur aps
}


vector <int> FsAps::getFs() const
{
    return d_fs;
}
vector <int> FsAps::getAps() const
{
    return d_aps;
}
int FsAps::longueurFs()const
{
    return d_fs.size();
}
int FsAps::longueurAps() const
{
     return d_aps.size();
}
int FsAps::nombreArc()const
{
    return ((longueurFs()-1)-(longueurAps()-1)); // on enleve fs[0] et aps[0]
}
