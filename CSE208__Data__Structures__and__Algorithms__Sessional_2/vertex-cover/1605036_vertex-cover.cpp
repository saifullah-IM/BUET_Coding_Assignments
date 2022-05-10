#include<bits/stdc++.h>
using namespace std;

const int mx=1e5+5;
typedef pair<int,int> PII;

class edgeInfo {
public:
    int u,v;
    void setValue (int a,int b) {
        u=a,    v=b;
    }
    void getValue (int& a,int& b) {
        a=u,    b=v;
    }
};

edgeInfo edgeList[mx];
int degree[mx];
vector<PII> Graph[mx];

int findMax (int m,set<int> myset)
{
    int ans=-1,maxi=-1;
    set<int>:: iterator it=myset.begin();
    while(it!=myset.end()) {
        int i,u,v;
        i=*it;
        edgeList[i].getValue(u,v);
        if (maxi<degree[u]+degree[v]) {
            maxi=degree[u]+degree[v];
            ans=i;
        }
        it++;
    }
    if (ans==-1) {
        cout<<"findMax error"<<' '<<myset.size()<<endl;
        exit(-1);
    }
    return ans;
}

vector<int> maxChoose (int m)
{
    set<int> myset;
    vector<int> ans;
    for (int i=1;i<=m;i++) myset.insert(i);
    while (true) {
        int x=findMax(m,myset);
        if (myset.find(x)==myset.end()) {
            cout<<"Can't find max edge"<<endl;
            exit(-1);
        }
        myset.erase(x);

        int u,v;
        edgeList[x].getValue(u,v);
        ///edgeList[x].setValue(-1,-1);
        ans.push_back(u);   ans.push_back(v);
        if (myset.empty()) return ans;

        for (int i=0;i<Graph[u].size();i++) {
            PII it=Graph[u][i];
            if (myset.find(it.second)==myset.end()) continue;
            degree[it.first]--;
            ///edgeList[it.second].setValue(-1,-1);
            myset.erase(it.second);
            if (myset.empty()) return ans;
        }
        for (int i=0;i<Graph[v].size();i++) {
            PII it=Graph[v][i];
            if (myset.find(it.second)==myset.end()) continue;
            degree[it.first]--;
            ///edgeList[it.second].setValue(-1,-1);
            myset.erase(it.second);
            if (myset.empty()) return ans;
        }

        degree[u]=degree[v]=0;
        ///Graph[u].clear();
        ///Graph[v].clear();
    }

    cout<<"maxChoose error"<<endl;
    exit(-1);
}

vector<int> random (int m)
{
    set<int> myset;
    vector<int> ans;
    for (int i=1;i<=m;i++) myset.insert(i);

    while (true) {
        int x=rand()%myset.size();
        if (x>=myset.size()) {
            cout<<"Random choosing error"<<endl;
            exit(-1);
        }
        set<int>::iterator it=myset.begin();
        for (int i=1;i<=x;i++) it++;
        x=*it;
        myset.erase(x);
///cout<<"erased"<<endl;
        int u,v;
        edgeList[x].getValue(u,v);
        ///edgeList[x].setValue(-1,-1);
        ans.push_back(u);   ans.push_back(v);
        if (myset.empty()) return ans;

        for (int i=0;i<Graph[u].size();i++) {///cout<<"---"<<i<<endl;
            PII it=Graph[u][i];
            if (myset.find(it.second)==myset.end()) continue;
            degree[it.first]--;
            ///edgeList[it.second].setValue(-1,-1);
            myset.erase(it.second);
            if (myset.empty()) return ans;
        }
        for (int i=0;i<Graph[v].size();i++) {
            PII it=Graph[v][i];
            if (myset.find(it.second)==myset.end()) continue;
            degree[it.first]--;
            ///edgeList[it.second].setValue(-1,-1);
            myset.erase(it.second);
            if (myset.empty()) return ans;
        }

        degree[u]=degree[v]=0;
        ///Graph[u].clear();
        ///Graph[v].clear();
    }

    cout<<"random error"<<endl;
    exit(-1);
}

void reset (int m)
{
    memset(degree,0,sizeof(degree));
    for (int i=1;i<=m;i++) {
        int u,v;
        edgeList[i].getValue(u,v);
        degree[u]++;
        degree[v]++;
    }
}

int main ()
{
    freopen("graph_4.txt","r",stdin);
    ///freopen("output-1.txt","w",stdout);
    int n,m;
    cin>>n>>m;

    for (int i=1;i<=m;i++) {
        int u,v;
        cin>>u>>v;  ///cout<<i<<' '<<u<<' '<<v<<endl;
        edgeList[i].setValue(u,v);
        degree[u]++;
        degree[v]++;
        Graph[u].push_back(make_pair(v,i));
        Graph[v].push_back(make_pair(u,i));
    }///cout<<"input"<<endl;
    vector<int> ans;
    for (int i=0;i<5;i++) {
        ans=random(m);
        cout<<"random -> "<<ans.size()<<endl;
        reset(m);
    }
    for (int i=0;i<5;i++) {
        ans=maxChoose(m);
        cout<<"maxChoose -> "<<ans.size()<<endl;
        reset(m);
    }

    return 0;
}
