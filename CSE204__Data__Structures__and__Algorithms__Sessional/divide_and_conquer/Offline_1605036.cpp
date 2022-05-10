#include<cstdio>
#include<vector>
using namespace std;

class point {
public:
    int x,y;

    bool operator<(point A) {
        if (x==A.x) return (y<A.y);
        else return (x<A.x);
    }
    bool operator>(point A) {
        if (x==A.x) return (y>A.y);
        else return (x>A.x);
    }
    bool operator==(point A) {
        return (x==A.x && y==A.y);
    }
};

const int mx=1e6+6;
const int inf=2e9+9;
point ara[mx],temp[mx];

vector<bool> findDominant (int lo,int hi)
{
    int n=hi-lo+1;
    n=(n<1 ? 1 : n);
    vector<bool> ans(n);
    for (int i=0;i<n;i++) ans[i]=false;

    if (lo>=hi) return ans;
    int mid=(lo+hi)/2;

    findDominant(lo,mid);
    findDominant(mid+1,hi);

    int i,j,k,yy,xx;
    xx=yy=inf;
    for (i=lo,j=mid+1,k=lo;k<=hi;k++) {
        if (i==mid+1 || (j<=hi && ara[i]>ara[j])) {
            temp[k]=ara[j++];
            if (yy>temp[k].y) {
                yy=temp[k].y;
                xx=temp[k].x;
            }
            else if (yy<temp[k].y) ans[k-lo]=true;
            else if (yy==temp[k].y && xx<temp[k].x) ans[k-lo]=true;
            else if (yy==temp[k].y && xx==temp[k].x) ans[k-lo]=ans[k-lo-1];
        }
        else {
            temp[k]=ara[i++];
            if (yy>temp[k].y) {
                yy=temp[k].y;
                xx=temp[k].x;
            }
            else if (yy<temp[k].y) ans[k-lo]=true;
            else if (yy==temp[k].y && xx<temp[k].x) ans[k-lo]=true;
            else if (yy==temp[k].y && xx==temp[k].x) ans[k-lo]=ans[k-lo-1];
        }
    }

    for (int i=lo;i<=hi;i++) ara[i]=temp[i];

    return ans;
}

int main ()
{
    freopen("input.txt","r",stdin);
    ///freopen("output.txt","w",stdout);

    int n;
    scanf ("%d",&n);
    for (int i=0;i<n;i++) {
        scanf("%d %d",&ara[i].x,&ara[i].y);
    }

    vector<bool> ans(n);
    ans=findDominant(0,n-1);
    for (int i=0;i<n;i++) {
        if (ans[i]) continue;
        printf ("%d %d\n",ara[i].x,ara[i].y);
    }

    return 0;
}
