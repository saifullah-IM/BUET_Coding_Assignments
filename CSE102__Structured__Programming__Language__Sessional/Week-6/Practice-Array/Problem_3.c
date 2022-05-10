/*
Coded by Saifullah Talukder
Statement:
Write a program to sort an array of integers.
*/

#include <stdio.h>


int main ()
{
    int i,j,n,t;
    scanf ("%d",&n);
    int num[n];
    for (i=0;i<n;i++) scanf ("%d",&num[i]);

    for (i=0;i<n-1;i++) {
        for (j=i+1;j<n;j++) {
            if (num[i]>num[j]) {
                t=num[i];
                num[i]=num[j];
                num[j]=t;
            }
        }
    }

    return 0;
}
