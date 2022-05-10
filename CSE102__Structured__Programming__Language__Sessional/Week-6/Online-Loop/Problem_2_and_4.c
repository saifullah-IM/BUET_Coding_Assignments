/*
CSE Online Week-6(Loop)
Problem 2 and 4 coded by Saifullah Talukder
Statement:
Problem 2:
Given n print the sum of following series up to n’th term.
1/1! − 1*(1+2)/2! + 1*(1+2)*(1+2+3)/3! −..... + (-1)^(n−1)*1*(1+2)*(1+2+3)* ......... *(1+2+3+.....+n)/n!

Problem 4: Solve problem 2 without nested loop.
*/


#include <stdio.h>

int main ()
{
    int i,n,sum=0;
    double term=-1.0,ans=0;

    scanf ("%d",&n);
    for (i=1;i<=n;i++) {
        sum+=i;
        term=(term*-1*(sum*1.0))/(i*1.0);
        ans+=term;
    }
    printf ("%lf\n",ans);

    return 0;
}
