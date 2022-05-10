#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cassert>
using namespace std;

class myvector {
    int *ara;
    int sz,mxsz;
public:
    myvector (int n=2) {
        mxsz=n;
        sz=0;
        ara=(int *) malloc(mxsz * sizeof(int));
    }
    void reset (int n)
    {
        int *temp;
        temp=(int *) malloc(n * sizeof(int));
        int zz = sz < n ? sz : n;
        for (int i=0;i<zz;i++) temp[i]=ara[i];
        free(ara);
        ara=temp;
        mxsz=n;
    }
    void push_back(int x)
    {
        if (sz>=mxsz) reset(mxsz*2);
        ara[sz]=x;
        sz++;
    }
    void pop_back()
    {
        sz--;
        if (sz<mxsz/2 && sz>1) reset(mxsz/2);
    }
    int size ()
    {
        return sz;
    }
    int operator[] (int i) {
        return ara[i];
    }
};

class myqueue {
    int *ara;
    int mx,st,ed,sz;
public:
    myqueue() {
        mx=1005;
        ara=(int *) malloc(mx * sizeof(int));
        st=ed=sz=0;
    }
    void push (int x)
    {
        ara[ed]=x;
        ed++;
        ed%=mx;
        sz++;
    }
    int front ()
    {
        return ara[st];
    }
    void pop ()
    {
        if (sz==0) return;
        st++;
        st%=mx;
        sz--;
    }
    bool empty ()
    {
        if (sz==0) {
            assert(st==ed);
            return true;
        }
        return false;
    }
};

int cap[102][102];
myvector edges[102];

int flow (int s,int t)
{
    int i,u,v,n,ans,parent[102],pmax[102];
    myqueue myQ;
    ans=0;

    while (1) {
        memset(pmax,63,sizeof(pmax));
        memset(parent,-1,sizeof(parent));
        parent[s]=s;
        myQ.push(s);
        while (!myQ.empty()) {
            u=myQ.front();
            myQ.pop();
            n=edges[u].size();
            for (i=0;i<n;i++) {
                v=edges[u][i];
                if (cap[u][v]>0 && parent[v]==-1) {
                    parent[v]=u;
                    pmax[v]=min(pmax[u],cap[u][v]);
                    if (v!=t) myQ.push(v);
                    else {
                        ans+=pmax[t];
                        while (parent[v]!=v) {
                            u=parent[v];
                            cap[u][v]-=pmax[t];
                            cap[v][u]+=pmax[t];
                            v=u;
                        }
                        while (!myQ.empty()) myQ.pop();
                        break;
                    }
                }
            }
        }
        if (parent[t]==-1) break;
    }

    return ans;
}

int main ()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n,m;
    cin>>n>>m;

    memset(cap,-1,sizeof(cap));
    for (int i=0;i<m;i++) {
        int u,v,c;
        cin>>u>>v>>c;
        if (cap[u][v]==-1) {
            edges[u].push_back(v);
            ///edges[v].push_back(u);
            cap[u][v]=0;///cap[v][u]=0;
        }
        cap[u][v]+=c;
        ///cap[v][u]+=c;
    }

    int s,t;
    cin>>s>>t;
    int ans=flow(s,t);
    cout<<"Max flow for the graph is "<<ans<<endl;

    return 0;
}
