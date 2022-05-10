/*
Problem_2 coded by Saifullah Talukder
Statement:
1. Write a structure named Over. Each Over has three members,
    a. A character array representing the name of the bowler,
    b. An integer array representing the number of runs given in each ball.
    c. An integer representing the number of wickets taken in that over.
Using the above structure implement the following functions.
    a. int netRunRate(Over overs[], int n) - Here n is the number of overs
in the overs array. The function returns the net run rate(total run/ number of
overs) computed from the provided array of Overs .
    b. int compareOver(Over x, Over y) - returns 0 if run/wicket ratio for Over
x is more than Over y . Otherwise returns 1.
    c. Over bestOver(Over overs[],int n) -Here n is the number of overs in
the overs array. Using compareOver function find out the best Over in the
array overs and return a copy of the best one.
*/

#include <stdio.h>

struct Over {
    int wkt;
    char name[20];
    int runs[6];
};

double netRunRate(struct Over overs[], int n)
{
    int i,j,R=0;
    double ans;

    for (i=0;i<n;i++) {  ///n overs
        for (j=0;j<6;j++) R+=overs[i].runs[j];  ///6 balls in an over
    }
    ans=(R*1.0)/(n*1.0);

    return ans;
}

int compareOver (struct Over x,struct Over y)
{
    int i,r1,r2;
    double k1,k2;

    r1=r2=0;
    for (i=0;i<6;i++) r1+=x.runs[i];
    for (i=0;i<6;i++) r2+=y.runs[i];
    k1=r1*1.0*y.wkt; ///to avoid division by 0
    k2=r2*1.0*x.wkt;

    if (k1>k2) return 0;
    else if (k1==k2) return (x.wkt>y.wkt); ///prioritizing wickets if k1==k2
    else return 1;
}

struct Over bestOver(struct Over overs[],int n)
{
    int i;
    struct Over best;

    best=overs[0];
    for (i=1;i<n;i++) {
        if (compareOver(overs[i],best)) best=overs[i];  ///keeping the best over in best
    }

    return best;  ///returning best
}

int main ()
{
    int i,j,n;
    double netrr;
    struct Over overs[100],best;

    scanf ("%d",&n);
    for (i=0;i<n;i++) {
        scanf (" %[^\n]",overs[i].name);
        for (j=0;j<6;j++) scanf ("%d",&overs[i].runs[j]);
        scanf ("%d",&overs[i].wkt);
    }

    netrr=netRunRate(overs,n);
    best=bestOver(overs,n);
    printf ("Net Run Rate: %lf\n",netrr);
    printf ("%s\n",best.name);
    for (i=0;i<6;i++) printf ("%d ",best.runs[i]);
    printf ("\n%d\n",best.wkt);

    return 0;
}
