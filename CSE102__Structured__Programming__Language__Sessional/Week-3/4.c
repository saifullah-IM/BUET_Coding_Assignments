/*
Problem 4 coded by Saifullah Talukder
Take an integer as input and print a triangle consisting of that many lines.
Look at the output to better understand the format of the triangle.
*/
 
#include <stdio.h>
 
int main ()
{
    int i,j,n;
 
    scanf ("%d",&n);
 
    for (i=n;i>0;i--) {
        for (j=n-i;j>0;j--) printf ("  ");
        for (j=0;j<i;j++) printf ("* ");
        printf ("\n");
    }
 
    return 0;
}
