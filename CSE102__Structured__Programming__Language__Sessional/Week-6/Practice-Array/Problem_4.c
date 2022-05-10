/*
Coded by Saifullah Talukder
Statement:
Write a program to find out second maximum element in an array of integers.
*/

#include <stdio.h>

int main ()
{
    int i,j,n,t,max,sndmax;
    scanf ("%d",&n);
    int num[n];
    for (i=0;i<n;i++) scanf ("%d",&num[i]);

    if (num[0]>num[1]) {
        max=num[0];
        sndmax=num[1];
    }
    else {
        max=num[1];
        sndmax=num[0];
    }

    for (i=2;i<n;i++) {
        if (num[i]>=max) {
            sndmax=max;
            max=num[i];
        }
        else if (num[i]>sndmax) sndmax=num[i];
    }
    printf ("Second maximum number is %d\n",sndmax);

    return 0;
}
