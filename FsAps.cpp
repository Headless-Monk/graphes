#include "FsAps.h"

// constructeur
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

// méthodes

vector <int> FsAps::distance(int sommet)
{
    int n = longueurAps();
    vector <int> d ;
    for (int i =0 ; i <= n ; i++) d[i]=-1;
    d[0] = n ;
    vector <int> fa ;
    int t= 0; int q=1 ;int x ; int p=1 ; int k=0 ;
    fa[1] = sommet ;
    d[sommet] = 0 ;

    while(t < q)
    {
        k++;
        for (int i = t+1 ; i <= q ; i++)
        {
            for (int j = d_aps[fa[i]] ; (x=d_fs[j]) != 0 ; j++)
            {
                if (d[x] == -1)
                {
                    d[x] = k ;
                    fa[++p]=x;
                }
            }
        }
        t=q;
        q=p;
    }
    return d ;
}
vector <vector<int>> FsAps::matrice_distance ()
{
    vector <vector<int>> dist ;
    int n = longueurAps() ;
    for (int i = 1 ; i <= n ; i++)dist[i]=distance(i);
    dist [0][0] = n;
    return dist ;
}

void FsAps::tarjan()
{
    int n = longueurAps() ;
    nbc = 0 ;
    for (int i =1 ; i<= n ; i++)
    {
        num[i] = 0 ;
        enTarj[i] = false ;
    }
    pilch[0] = 0 ;
    tarj[0] = 0 ;
    for (int s= 1 ; s<= n ;s++)
        if(num[s] = 0) traversee(s);
    prem[0]= nbc ;
}

void FsAps::traversee(int s)
{
    int t ; int p = 1 ;
    num [s] = p ;
    p++ ;
    mu[s] = num[s];
    empiler(s, tarj);
    enTarj[s] = true;
    for (int k = d_aps[s] ; (t=d_fs[k])!= 0 ; k++)
    {
        if (num[t] == 0)
        {
            traversee(t) ;
            if (num[t] < mu[s])mu[s] = mu[t] ;
            else
            {
                if (enTarj[t] && (num[t] < num[s]))
                    if (num[t] < num[s])
                        mu[s] = num[t] ;
            }
        }
    }
    if (mu[s] == num[s])
    {
        nbc ++ ;
        int x = tarj[0] ;
        prem[nbc] = x;
        while (x != s)
        {
            empiler(x, pilch) ;
            cfc[x] = nbc ;
            x = tarj[x] ;
        }
    }
}

void FsAps::empiler(int x , vector<int> pilchEmpiler)
{
    pilchEmpiler [x] = pilchEmpiler[0] ;
    pilchEmpiler[0] = x ;
}

// accesseurs

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
