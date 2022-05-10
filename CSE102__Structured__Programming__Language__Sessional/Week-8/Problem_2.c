/*
Problem 2 coded by Saifullah Talukder

Statement:
In a Sudoku puzzle there is an n * n (2 ≤ n ≤ 9) sized grid. The goal of Sudoku is to assign every cell in the grid a digit from 1 to n
subject to the constraint that each digit can be used only once in each row and column.

Now write a program using bitwise operations that tests if a grid of n * n digits is a solution to sudoku puzzle or not and prints 1 it 
is. Otherwise prints a 0 The first line of the input is contains the value of n. Then n*n digits follows.

You are not allowed to use multidimensional arrays.

*/

#include <stdio.h>

int main ()
{
    int i,j,n,ara[10],aux[10],flag,ret;

    scanf ("%d",&n);
    flag=0;
    for (i=0;i<n;i++) aux[i]=0;
    for (i=0;i<n;i++) {
        for (j=1;j<=n;j++) aux[i]=aux[i]^j;
    }

    for (j=0;j<n;j++) {
        for (i=0;i<n;i++) scanf ("%d",&ara[i]);
        for (i=0;i<n;i++) aux[i]=aux[i]^ara[i];
        ret=0;
        for (i=0;i<n;i++) ret=ret^ara[i];
        for (i=1;i<=n;i++) ret=ret^i;
        flag=(ret|flag);
    }

    for (i=0;i<n;i++) flag=(flag|aux[i]);
    if (flag) printf ("0");
    else printf ("1");

    return 0;
}
