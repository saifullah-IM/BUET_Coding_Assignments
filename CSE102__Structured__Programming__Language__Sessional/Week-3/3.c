/*
Problem 3 coded by Saifullah Talukder
Statement:
Take two integers as input and find the number of prime numbers between them (inclusive).
*/
 
#include <stdio.h>
 
int main ()
{
    int n1,n2,i,j,min,max,ans=0;
 
    scanf ("%d %d",&n1,&n2);
    min=n1<n2 ? n1 : n2;
    max=n1>n2 ? n1 : n2;
 
    for (i=min;i<=max;i++) {
        for (j=2;j<i;j++) if (i%j==0) break;
        if (j==i) ans++;
    }
    printf ("%d\n",ans);
 
    return 0;
}
