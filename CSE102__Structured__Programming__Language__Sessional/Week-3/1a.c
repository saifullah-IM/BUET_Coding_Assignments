
//Problem 1-a coded by Saifullah Talukder

/* 
Problem Statement
Take x and n as input and and find the sum of the following series upto nth term.
e^-x (Please find the series online or somewhere else. It's difficult to write it here.)
*/

#include <stdio.h>

int main ()
{
    int i,fact=1,n,x,flag=-1,exp=1;
    double ans=0;

    scanf ("%d %d",&x,&n);
    for (i=0;i<n;) {
        ans+=((exp*1.0)/(fact*1.0))*flag*-1;
        fact*=++i;
        exp*=x;
        flag*=-1;
    }
    printf ("%lf\n",ans);

    return 0;
}

