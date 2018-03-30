#include "FsAps.h"

FsAps::FsAps(vector<int> fs, vector<int> aps)
{
    d_fs = fs ;
    d_aps = aps ;
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
    return (longueurFs()-longueurAps());
}
