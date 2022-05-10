/*
Problem 1 coded by Saifullah Talukder

Statement:
Write a program using bitwise operations, that subtracts 2^n from an integer x where 0 ≤ n ≤ 31 using. Take n and x as input. You cannot use
library function(except I/O related ones) and loops.

*/

#include <stdio.h>

int main ()
{
    int x,n,ans;

    scanf ("%d %d",&n,&x);
    ans=x-(1<<n);
    printf ("%d\n",ans);

    return 0;
}
