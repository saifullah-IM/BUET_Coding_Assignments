/*
Problem 3 coded by Saifullah Talukder
Statement:
Write a recursive function to calculate the Greatest common divisor of two numbers.
*/

#include <stdio.h>

int GCD (int a,int b)
{
    if (b==0) return a;
    else return GCD(b,a%b);
}

int main ()
{
    int a,b,ans;

    scanf ("%d %d",&a,&b);
    ans=GCD(a,b);
    printf ("%d\n",ans);

    return 0;
}
