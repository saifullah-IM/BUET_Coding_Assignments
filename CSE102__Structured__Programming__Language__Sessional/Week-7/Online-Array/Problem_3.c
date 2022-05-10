/*
Problem 3 coded by Saifullah Talukder
Statement:
Write a program that replaces all occurrence of an element in an array of elements. The first line contains three integers. They are number
of elements in the array, the number to be replaced and the number to be replaced with. The elements of the array will also be input.
*/

#include<stdio.h>

int main()
{
    int i,n,u,v;
    scanf ("%d %d %d",&n,&u,&v);
    int ara[n];
    for (i=0;i<n;i++) scanf ("%d",&ara[i]);

    for (i=0;i<n;i++) {
        if (ara[i]==u) ara[i]=v;
    }
    for (i=0;i<n;i++) printf ("%d ",ara[i]);

    return 0;
}
