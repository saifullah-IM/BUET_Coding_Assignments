/*
Problem 1 coded by Saifullah Talukder
Statement:
Write a program that takes a character array and prints the nth left rotation of the array.
Take the size of the array, the elements of the array and n as input.
*/

#include<stdio.h>

int main()
{
    int i,j,n,m;
    scanf ("%d",&m);
    char ara[m],ch;
    for (i=0;i<m;i++) scanf (" %c",&ara[i]);
    scanf ("%d",&n);

    for (i=0;i<n;i++) {
        ch=ara[0];
        for (j=1;j<m;j++) ara[j-1]=ara[j];
        ara[j-1]=ch;
    }
    for (i=0;i<m;i++) printf ("%c ",ara[i]);

    return 0;
}
