/*
CSE Online Week-6 (Loop)
Problem 3 coded by Saifullah Talukder
Statement:
Write a program that takes an integer n and prints the
triangle as shown below.

A
B C
D E F
G H I J
K L M N O

Hint: If you run out of letters you need to wrap around.
*/

#include <stdio.h>

int main ()
{
    int i,j,n,cnt=0;
    char ch='A';

    scanf ("%d",&n);
    for (i=1;i<=n;i++) {
        for (j=0;j<i;j++) {
            printf ("%c ",ch);
            cnt++;
            ch='A'+(cnt%26);
        }
        printf ("\n");
    }

    return 0;
}
