/*
Problem_1 coded by Saifullah Talukder
Statement:
1. Write a program that prints all the addresses of the elements of
a. an integer array
b. a character array
c. a double array
*/

#include <stdio.h>

int main ()
{
    int i,n;
    void *ptr;
    int *p;
    char *q;
    double *r;
    scanf ("%d",&n);
    int ara[n];
    char str[n];
    double dbl[n];

    p=ara;
    printf ("For integer:\n\n");
    for (i=0;i<n;i++) printf ("%p\t\t%d\n",p+i);

    q=str;
    printf ("For character:\n\n");
    for (i=0;i<n;i++) printf ("%p\t\t%d\n",q+i);

    r=dbl;
    printf ("For double:\n\n");
    for (i=0;i<n;i++) printf ("%p\t\t%d\n",r+i);

    /*ptr=ara;
    printf ("For integer:\n\n");
    for (i=0;i<n;i++) printf ("%p\n",(int *) ptr+i);*////We can do all of them using only one pointer variable of void type. We just have to typecast it while printing.

    return 0;
}
