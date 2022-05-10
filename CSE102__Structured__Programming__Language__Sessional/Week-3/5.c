/*
Problem 5 coded by Saifullah Talukder
Take an integer as input and print "Yes" (without quotes) if it's a fibonacci number, print "No" (without quotes) if not.
*/
 
#include <stdio.h>
 
int main ()
{
    int i,n,f1,f2,next;
 
    scanf ("%d",&n);
    f1=f2=1;
    while (f2<n) {
        next=f1+f2;
        f1=f2;
        f2=next;
    }
    if (f2==n) printf ("Yes\n");
    else printf ("No\n");
 
    return 0;
}
