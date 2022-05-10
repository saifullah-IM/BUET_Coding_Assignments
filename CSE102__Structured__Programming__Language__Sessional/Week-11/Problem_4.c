/*
Problem 4 coded by Saifullah Talukder
Statement:
Write a recursive function to print the binary representation of an integer.
*/

#include <stdio.h>

void binary (int n)
{
    if (n/2==0) {
        printf ("%d",n);
        return;
    }
    else binary (n/2);

    printf ("%d",n%2);  ///We print later, call first. This is done to reverse the binary string.
    return;
}

int main ()
{
    int n;

    scanf ("%d",&n);
    binary(n);

    return 0;
}
