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

    for (unsigned int i = 1 ;i < d_fs.size() ; i++)
        if (d_fs.at(i) == 0 && (i+1)<d_fs.size()) aps.push_back(i+1);

    d_aps = aps ;
    d_aps.insert(d_aps.begin(),d_aps.size()+1); // longueur aps
}

// méthodes

void FsAps::distance(int sommet, int *& d)
{

    int n = longueurAps();
    d= new int [n] ;
    for (int i =0 ; i <= n ; i++) d[i]=-1;
    d[0] = n ;
    int * fa = new int [n] ;
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

}
void FsAps::matrice_distance ( int **& dist)
{

    int n = longueurAps() ;
    dist =  new int * [n] ;
    dist[0] = new int [1] ;

    for (int i = 1 ; i <= n ; i++)
        distance(i, dist[i]);

    dist[0][0] = n-1;

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
        if(num[s] == 0)
            traversee(s);
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

void FsAps::graphe_reduit(int *& fsr, int *& apsr)
{
    nbc = prem[0] ;
    apsr = new int [nbc +1];
    apsr[0] = nbc ;
    fsr = new int [longueurFs()+1] ;
    bool* deja_mis = new bool [nbc +1] ;
    int k = 0 ;
    for (int c= 1 ; c<= nbc ; c++)
    {
        for (int i = 1 ; i<= nbc ; i++)
        {
            deja_mis[i] = false ;
        }
        deja_mis[c] = true ;
        int s =prem[c] ;
        apsr[c] = k+1 ;
        int t ;
        while (s!= 0)
        {
            for (int l = d_aps[s] ; (t=d_fs[l])!=0 ; l++)
            {
                if (!deja_mis[cfc[t]])
                {
                    k++ ;
                    fsr[k] = cfc[t] ;
                    deja_mis[cfc[t]] =true;
                } //if
            }//for
            s=pilch[s] ;
        }//while
        k++ ;
        fsr[k] =0;
    }//for
    fsr[0] = k ;
}

void FsAps::empiler(int x , vector<int> pilchEmpiler)
{
    pilchEmpiler [x] = pilchEmpiler[0] ;
    pilchEmpiler[0] = x ;
}

void FsAps::dijkstra(int** c, int s, int *& d, int *& pred)
{
    const int MAXCOUNT = 100 ;
    int n = longueurAps() ;
    int cpt = n-1 ;
    int mini, j, x;
    d = new int [n+1] ;
    pred = new int [n+1] ;
    bool *dans_S = new bool [n+1] ;

    for (int i = 1 ; i<=n ; i++)
    {
        d[i] = c[s][i];
        dans_S[i] = true ;
    }
    dans_S[s] = false ;
    while (cpt>0)
    {
        mini = MAXCOUNT ;
        for (int i = 1 ; i <= n ;i++)
        {
            if (dans_S[i])
            {
                if (d[i]< mini)
                {
                    mini = d[i];
                    j=i;
                }
            }
        }//for

        if (mini == MAXCOUNT)break ;
        dans_S[j]=false;
        cpt-- ;
        for (int k = d_aps[j] ; (x=d_fs[k])!=0 ; k++)
        {
            if (dans_S[x])
            {
                int v = d[j] + c[j][x] ;
                if(v< d[x])
                {
                    d[x] = v ;
                    pred[x] = j;
                }
            }
        } //for
    }//while
}//dijkstra
void FsAps::ordonnancement (int* d , int *& lc , int *& fpc , int *& appc)
{
    int n = longueurAps() ;
    int m = longueurAps() ;
    lc = new int [n+1] ; lc[0]=n ;
    appc = new int [n+1] ; appc[0] = n ;
    fpc = new int [m+1] ; fpc[0] = m ;
    lc [1] = 0 ;
    fpc[1] = 0 ;
    appc[1] = 1;
    int kc = 1 ;
    for (int i = 2 ; i<= n ; i++)
    {
        lc[i] = 0;
        appc[i] = kc + 1 ;
        int j ;
        for (int k = d_aps[i] ; (j= fpc[k])!=0 ; k++)
        {
            int lg = lc[j]+d[j] ;
            if (lg >= lc[i])
            {
                if(lg>lc[i])
                {
                    lc[i] = lg ;
                    kc = appc[i] ;
                    fpc[kc] = j ;
                }
                else fpc[++kc] = j ;
            }
        } // for
        fpc[++kc] =  0;
    }
}

void FsAps::ajouter_arc(int s1, int s2)
{
    int indice = d_aps[s1] ;
    d_fs.insert(d_fs.begin()+indice, s2) ;
    if(d_aps[s1+1])
    {
        for (int i = s1+1 ; i <= longueurAps() ; i++)
            d_aps[i]++ ;
    }
}
void FsAps::supprimer_arc(int s1, int s2)
{
    int indice = 0 ;
    int supp = 0 ;

    for (int i = 1 ; i <longueurFs() ; i++)
    {
        if(d_fs[i]==0)indice++ ;
        else if(s1 == indice && d_fs[i]==s2)
        {
            supp = indice ;
            d_fs.erase(d_fs.begin()+i) ;
            break ;
        }
    }
    if(d_aps[supp+1] && supp!=0)
    {
        for (int i = s1+1 ; i <= longueurAps() ; i++)
            d_aps[i]-- ;
    }
}

void FsAps::afficher(std::ostream &os) const
{
    os << "Fs : [ " ;
    for (int i =0 ; i<longueurFs() ; i++)
    {
        os << d_fs[i] ;
    }
    os << " ]" << std::endl ;

    os << "Aps : [ " ;
    for (int i =0 ; i<longueurAps() ; i++)
    {
        os << d_aps[i] ;
    }
    os << " ]" << std::endl ;
}

std::ostream& operator<<(std::ostream &os, const FsAps &fsaps)
{
    fsaps.afficher(os);
    return os;
}

// accesseurs
vector <int> FsAps::getCfc() const
{
    return cfc;
}

vector <int> FsAps::getFs() const
{
    return d_fs;
}

vector <int> FsAps::getAps() const
{
    return d_aps;
}

int FsAps::index_getFs(int i) const
{
    return d_fs[i];
}

int FsAps::index_getAps(int i) const
{
    return d_aps[i];
}

void FsAps::index_setFs(int i, int valeur)
{
    d_fs[i] = valeur;
}

void FsAps::index_setAps(int i, int valeur)
{
    d_aps[i] = valeur;
}

int FsAps::longueurFs() const
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
