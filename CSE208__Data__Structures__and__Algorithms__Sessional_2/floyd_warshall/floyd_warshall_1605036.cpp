#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

const int mx=505;
int weight[mx][mx],dist[mx][mx],path[mx][mx];
bool edge[mx][mx];

bool floydWarshall (int n)
{
    for (int i=1;i<=n;i++) {
        dist[i][i]=0;
        path[i][i]=i;
    }

    for (int k=1;k<=n;k++) {
        for (int i=1;i<=n;i++) {
            for (int j=1;j<=n;j++) {
                if (dist[i][j]>dist[i][k]+dist[k][j]) {
                    dist[i][j]=dist[i][k]+dist[k][j];
                    path[i][j]=path[k][j];
                }
            }
        }
    }

    for (int i=1;i<=n;i++) {
        if (dist[i][i]<0) return true;
    }

    return false;
}

int main ()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    memset(edge,0,sizeof(edge));
    memset(dist,63,sizeof(dist));
    memset(path,-1,sizeof(path));

    int n,m;
    cin>>n;
    cin>>m;

    for (int i=0;i<m;i++) {
        int u,v,w;
        cin>>u>>v>>w;
        edge[u][v]=true;
        weight[u][v]=dist[u][v]=w;
        path[u][v]=u;
    }

    bool negCycle=floydWarshall(n);

    cout<<"Distance Matrix"<<endl;
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=n;j++) {
            if (path[i][j]==-1) cout<<"inf"<<'\t';
            else cout<<dist[i][j]<<'\t';
        }
        cout<<endl;
    }

    cout<<endl<<"Predecessor Matrix"<<endl;
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=n;j++) {
            cout<<path[i][j]<<'\t';
        }
        cout<<endl;
    }

    cout<<endl;
    if (negCycle) cout<<"Negative cycle exists"<<endl;
    else cout<<"No negative cycle"<<endl;

    return 0;
}
