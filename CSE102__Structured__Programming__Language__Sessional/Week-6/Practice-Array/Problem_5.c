/*
Coded by Saifullah Talukder
Statement:
Write a program that finds out the average difference from the maximum value of an array of integers.
*/

#include <stdio.h>

int main ()
{
    int i,n,max,sum=0;
    double ans;
    scanf ("%d",&n);
    int ara[n];

    for (i=0;i<n;i++) scanf ("%d",&ara[i]);
    max=ara[0];
    for (i=1;i<n;i++) if (max<ara[i]) max=ara[i];
    for (i=0;i<n;i++) sum+=(max-ara[i]);
    ans=(sum*1.0)/n;
    printf ("%lf\n",ans);
    
    return 0;
}
