///problem 1-b coded by Saifullah Talukder
/*
Take x and n as input and and find the sum of the following two series upto nth term.
sinx (Please find the series online or somewhere else. It's difficult to write it here.)
*/
 
#include <stdio.h>
 
int main ()
{
    int i,j,n,x,flag,fact,exp;
    double ans=0;
 
    scanf ("%d %d",&x,&n);
    fact=1;
    exp=x;
    flag=-1;
 
    for (i=0;i<n;i++) {
        ans+=((exp*1.0)/(fact*1.0))*flag*-1;
        exp*=x*x;
        j=2*(i+1);
        fact*=j*(j+1);
        flag*=-1;
    }
    printf ("%lf\n",ans);
 
    return 0;
}
