/*
CSE Online Week-6(loop)
Problem 1 coded by Saifullah Talukder
Statement:
Write a C program that will take an integer x and prints its
binary representation. You can use loops and conditionals if
necessary. Here x can be 0 ≤ x ≤ 2 (Using array is prohibited).
*/

#include <stdio.h>

int main ()
{
    int i,j,P=1,n;

    scanf ("%d",&n);
    if (n==0) printf ("0");
    else {
        while (P<=n) P*=2;
        P/=2;
        while (P!=0) {
            printf ("%d",n/P);
            n-=(P)*(n/P);
            P/=2;
        }
    }

    return 0;
}
