#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

const int mx=1e5+5;
const int inf=1e9+9;

class edgeInfo {
    int u,v,w;
public:
    bool operator<(edgeInfo A) {
        return (w<A.w);
    }
    bool operator>(edgeInfo A) {
        return (w>A.w);
    }
    bool operator==(edgeInfo A) {
        return (w==A.w);
    }
    edgeInfo operator=(edgeInfo A) {
        u=A.u, v=A.v, w=A.w;
        return *this;
    }
    void setValue (int x,int y,int z) {
        u=x, v=y, w=z;
    }
    void getValue (int& x,int& y,int& z) {
        x=u, y=v, z=w;
    }
};

edgeInfo ara[mx],temp[mx];

void mergeSort (int lo,int hi)
{
    if (lo>=hi) return;

    int mid=(lo+hi)/2;
    mergeSort(lo,mid);
    mergeSort(mid+1,hi);

    int i,j,k;
    for (i=lo,j=mid+1,k=lo;k<=hi;k++) {
        if (i==mid+1 || (j<=hi && ara[i]>ara[j])) {
            temp[k]=ara[j++];
        }
        else {
            temp[k]=ara[i++];
        }
    }

    for (int i=lo;i<=hi;i++) ara[i]=temp[i];
}

int parent[mx];
int Find (int u)
{
    if (parent[u]==u) return u;
    else return (parent[u]=Find(parent[u]));
}

void Union (int u,int v)
{
    int x=Find(u);
    int y=Find(v);
    parent[y]=x;
}

bool taken[mx];
int kruskal (int n,int m)
{
    int ans=0;
    memset(taken,0,sizeof(taken));
    for (int i=0;i<m;i++) parent[i]=i;

    for (int i=0;i<m;i++) {
        int u,v,w;
        ara[i].getValue(u,v,w);
        int x=Find(u);
        int y=Find(v);
        if (x!=y) {
            ans+=w;
            Union(u,v);
            taken[i]=true;
        }
    }

    return ans;
}

int main ()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n,m;
    cin>>n>>m;
    for (int i=0;i<m;i++) {
        int u,v,w;
        cin>>u>>v>>w;
        ara[i].setValue(u,v,w);
    }
    mergeSort(0,m-1);
    int ans=kruskal(n,m);

    cout<<"Added edges:"<<endl;
    for (int i=0;i<m;i++) {
        if (taken[i]) {
            int u,v,w;
            ara[i].getValue(u,v,w);
            cout<<'('<<u<<','<<v<<')'<<endl;
        }
    }
    cout<<endl<<"MST weight = "<<ans<<endl;

    return 0;
}
