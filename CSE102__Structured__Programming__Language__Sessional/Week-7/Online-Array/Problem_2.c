/*
Problem 2 coded by Saifullah Talukder
Statement:
Write a program to compute the median and mode of an array of integers. Take the number of elements of the array and the elements as input.
*/

#include<stdio.h>

int main()
{
    int i,j,n,mode,temp,flag,cnt;
    double median;
    scanf ("%d",&n);
    int ara[n];
    for (i=0;i<n;i++) scanf ("%d",&ara[i]);

    for (i=0;i<n;i++) {
        for (j=i;j<n;j++) {
            if (ara[i]>ara[j]) {
                temp=ara[i];
                ara[i]=ara[j];
                ara[j]=temp;
            }
        }
    }

    flag=0;
    i=0;
    while (i<n) {
        j=i;
        while (ara[i]==ara[j]) i++;
        cnt=i-j;
        if (cnt>=flag) {
            mode=ara[j];
            flag=cnt;
        }
    }
    if (n%2==0) {
        median=(ara[n/2]*1.0+ara[(n-2)/2]*1.0)/2;
    }
    else median=ara[(n-1)/2];

    printf ("Mode : %d\n",mode);
    printf ("Median : %lf\n",median);

    return 0;
}
