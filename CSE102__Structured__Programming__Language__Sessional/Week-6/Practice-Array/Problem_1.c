/*
Coded by Saifullah Talukder
Statement: Write a program that computes the standard devaiation of n integers.
The first line of input is the number of integers n.Then follows n integers.
*/

#include <stdio.h>
#include <math.h>

int main ()
{
    int i,n,sum=0;
    double avg,S=0,ans;
    scanf ("%d",&n);
    int ara[n];

    for (i=0;i<n;i++) {
        scanf ("%d",&ara[i]);
        sum+=ara[i];
    }
    avg=(sum*1.0)/(n*1.0);
    for (i=0;i<n;i++) {
        S+=(avg-ara[i]*1.0)*(avg-ara[i]*1.0);
    }
    ans=sqrt(S/n);
    printf ("Standard deviation is %lf\n",ans);

    return 0;
}
