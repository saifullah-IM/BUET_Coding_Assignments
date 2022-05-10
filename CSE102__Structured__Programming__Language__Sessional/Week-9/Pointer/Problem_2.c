/*
Problem_2 coded by Saifullah Talukder
Statement:
2. Write a program to allocate the following:
a. An integer array of size 10
b. A character array of size 10
c. A double array of size 10
Finally print all the addresses of the elements of the arrays.
*/

#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int *I,i;
    char *C;
    double *D;

    I=(int *) malloc(10*sizeof(int));
    C=(char *) malloc(10*sizeof(char));
    D=(double *) malloc(10*sizeof(double));

    printf ("For integer:\n\n");
    for (i=0;i<10;i++) printf ("%p\n",I+i);
    printf ("\n");

    printf ("For character:\n\n");
    for (i=0;i<10;i++) printf ("%p\n",C+i);
    printf ("\n");

    printf ("For double:\n\n");
    for (i=0;i<10;i++) printf ("%p\n",D+i);

    return 0;
}
