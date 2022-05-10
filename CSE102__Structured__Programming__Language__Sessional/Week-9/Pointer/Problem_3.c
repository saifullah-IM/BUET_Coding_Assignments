/*
Problem_3 coded by Saifullah Talukder
Statement:
3. Write a program using pointer arithmetic that intermixes two equal length strings i.e.
given two strings X=” ” and Y=” ” you have to create x1x2x3….xn y1y2y3..yn another string
such that Z=” x1y1x2y2x3y3... xnyn ”.
*/

#include <stdio.h>

int main ()
{
    int i,j,k,n;
    char *X,*Y,*Z,*S;

    scanf ("%d",&n);
    X=(char *) malloc(n*sizeof(char));
    Y=(char *) malloc(n*sizeof(char));
    S=Z=(char *) malloc(2*n*sizeof(char));

    scanf (" %[^\n]",X);
    scanf (" %[^\n]",Y);

    n=2*n;
    j=k=0;
    for (i=0;i<n;i++) {
    /*naive way
        if (i%2==0) {
            *(Z+i)=*(X+j);
            j++;
        }
        else {
            *(Z+i)=*(Y+k);
            k++;
        }*/
        //smart way
        *Z++ = *X++;
        *Z++ = *Y++;

    }
    for (i=0;i<n;i++) printf ("%c",*(S+i));

    return 0;
}
