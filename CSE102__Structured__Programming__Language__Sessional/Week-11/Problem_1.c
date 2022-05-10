/*
Problem 1 coded by Saifullah Talukder
Statement:
Write a recursive function to calculate the factorial of an integer.
*/

#include <stdio.h>

long long factorial (int n)
{
    if (n==0) return 1;
    else return n*factorial(n-1);
}
int main ()
{
    int n;
    long long ans;

    scanf ("%d",&n);
    ans=factorial(n);
    printf ("%lld\n",ans);

    return 0;
}
