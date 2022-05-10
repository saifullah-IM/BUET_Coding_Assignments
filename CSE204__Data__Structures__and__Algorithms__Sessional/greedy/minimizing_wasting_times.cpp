#include<iostream>
#include<algorithm>

using namespace std;

const int mx=1e5+5;
typedef pair<int,int> PII;

bool sortFunction (PII A,PII B)
{
    return A.first<B.first;
}

PII ara[mx];
int main ()
{
    int n;

    cin>>n;
    for (int i=1;i<=n;i++) {
        cin>>ara[i-1].first;
        ara[i-1].second=i;
    }
    sort(ara,ara+n,sortFunction);

    cout<<"The order in which customers should be serviced:"<<'\n';
    for (int i=0;i<n;i++) cout<<ara[i].second<<' ';
    cout<<'\n';

    return 0;
}
