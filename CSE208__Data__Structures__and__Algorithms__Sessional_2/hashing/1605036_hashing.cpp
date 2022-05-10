#include<bits/stdc++.h>
using namespace std;

const int base=29;
typedef long long ll;
int modpow(ll x,int n,int N)
{
    ll ans=1;
    while (n>0) {
        if (n%2==1) ans=(ans*x)%N;
        x=(x*x)%N;
        n/=2;
    }
    return (int) ans;
}
int hasH1 (string str,int N)
{
    ll val=0;
    int n=str.size();
    for (int i=0;i<n;i++) {
        int x=(str[i]-'a')+1;
        val=(val+x*modpow(base,i+1,N))%N;
    }
    return (int) val;
}
int hasH2 (string str,int N)
{
    ll val=0;
    int n=str.size();
    for (int i=0;i<n;i++) {
        int x=str[i]-'a';
        val=(val^(x*modpow(base,i+1,N)))%N;
    }
    return (int) val;
}

typedef pair<string,int> PSI;
const int mx=2e4+5;

class hashTable {
    list<PSI> chain[mx];
    PSI dHash[mx];
    PSI qHash[mx];
    int MOD;
    int (*hash1) (string,int);
    int (*hash2) (string,int);
public:
    int colcnt[3];
    int hitcnt[3];
    hashTable (int (*h1)(string,int), int (*h2)(string,int)) {
        hash1=h1;
        hash2=h2;
        MOD=mx;
        for (int i=0;i<mx;i++) dHash[i].first=qHash[i].first='#';
        memset(colcnt,0,sizeof(colcnt));
        memset(hitcnt,0,sizeof(hitcnt));
    }
    void insert (PSI A) {
        int idx=hash1(A.first,MOD);
        idx=(idx+MOD)%MOD;
        chain[idx].push_back(A);
        colcnt[0]+=chain[idx].size()-1;

        ll i=0;
        int val=idx;
        int axval=hash2(A.first,MOD);
        axval=(axval+MOD)%MOD;
        while (dHash[val].first!="#") {
            i++;
            val=((val+axval)%MOD+MOD)%MOD;
        }
        colcnt[1]+=i;
        dHash[val]=A;

        i=0;
        val=idx;
        int c1,c2;
        c1=31,c2=37;
        while (qHash[val].first!="#") {
            i++;
            val=((idx+c1*i*axval+c2*i*i*axval)%MOD+MOD)%MOD;
        }
        colcnt[2]+=i;
        qHash[val]=A;
    }
    void search (string str) {
        int idx=hash1(str,MOD);
        idx=(idx+MOD)%MOD;
        list<PSI>::iterator it=chain[idx].begin();
        ll i=1;
        while (true) {
            PSI A=*it;
            if (A.first==str) break;
            i++;
            it++;
        }
        hitcnt[0]+=i;

        i=0;
        int val=idx;
        int axval=hash2(str,MOD);
        axval=(axval+MOD)%MOD;
        while (dHash[val].first!=str) {
            i++;
            val=((val+axval)%MOD+MOD)%MOD;
        }
        hitcnt[1]+=i+1;

        i=0;
        val=idx;
        int c1,c2;
        c1=31,c2=37;
        while (qHash[val].first!=str) {
            i++;
            val=((idx+c1*i*axval+c2*i*i*axval)%MOD+MOD)%MOD;
        }
        hitcnt[2]+=i+1;
    }
};

set<string> myset;
vector<string> vec;

void randomGenerator(string str,int n,int sz)
{
    if (vec.size()>=n) return;
    if (str.size()==sz) {
        if (myset.find(str)==myset.end()) {
            myset.insert(str);
            vec.push_back(str);
        }
        return;
    }
    for (int i=0;i<26;i++) {
        char ch=('a'+i);
        string temp=str+ch;
        randomGenerator(temp,n,sz);
    }
}

int main ()
{
    int n=10000;
    randomGenerator("",n,7);
    ///cout<<"Generated"<<endl;

    hashTable H1(&hasH1,&hasH2);
    hashTable H2(&hasH2,&hasH1);
    for (int i=0;i<n;i++) {
        PSI A;
        A.first=vec[i];
        A.second=i+1;
        H1.insert(A);
        H2.insert(A);
    }
    ///cout<<"Inserted"<<endl;

    for (int i=0;i<n/10;i++) {
        srand(time(NULL));
        int y=rand()%10;
        int x=i*10+y;
        H1.search(vec[x]);
        H2.search(vec[x]);
    }
    cout<<"\t\t\t\t\t"<<"Hash 1"<<"\t\t\t\t\t"<<"Hash 2"<<endl;
    cout<<"\t\t\t"<<"No of Collision"<<"\t\t"<<"Avg Hit";
    cout<<"\t\t"<<"No of Collision"<<"\t\t"<<"Avg Hit"<<endl;
    cout<<"Chaining Method\t\t\t"<<H1.colcnt[0]<<"\t\t   "<<H1.hitcnt[0]/1000.0<<"\t\t ";
    cout<<H2.colcnt[0]<<"\t\t   "<<H2.hitcnt[0]/1000.0<<endl;
    cout<<"Double Hashing\t\t\t"<<H1.colcnt[1]<<"\t\t   "<<H1.hitcnt[1]/1000.0<<"\t\t ";
    cout<<H2.colcnt[1]<<"\t\t   "<<H2.hitcnt[1]/1000.0<<endl;
    cout<<"Custom Probing\t\t\t"<<H1.colcnt[2]<<"\t\t   "<<H1.hitcnt[2]/1000.0<<"\t\t ";
    cout<<H2.colcnt[2]<<"\t\t   "<<H2.hitcnt[2]/1000.0<<endl;

    return 0;
}
