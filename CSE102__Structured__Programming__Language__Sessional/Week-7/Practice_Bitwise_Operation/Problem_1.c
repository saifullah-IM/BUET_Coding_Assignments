/*
Problem 1 coded by Saifullah Talukder
Statement:
Write the following functions
    a.setBit(n,m). Set mth bit of n
    b.xtractBit(n). Return rightmost bit of n
    c.resetBit(n,m) Clear mth bit of n and returns the updated value

Take two arrays A and B of english letters. For each array,if ith letter of the english alphabet is present in the array set the ith bit
of an integer variable. Let's assume these integers are a and b. Compute the union,intersection of two arrays A and B. Also compute A-B.
Print them using english letters.
*/

#include <stdio.h>

int setBit (int n,int m)
{
    int mask=1;
    mask=mask<<m;
    return mask|n;
}

int xtractBit (int n)
{
    int mask=1;
    return mask&n;
}

int resetBit (int n,int m)
{
    int mask=1;
    mask=~(mask<<m);
    return mask&n;
}

int main()
{
    int i,a,b,U,I,M;
    char A[1000],B[1000];

    scanf(" %[^\n]",A);
    scanf(" %[^\n]",B);

    a=0;
    b=0;
    for (i=0;A[i]!='\0';i++) a=setBit(a,A[i]-'a');
    for (i=0;B[i]!='\0';i++) b=setBit(b,B[i]-'a');

    U=a|b;
    printf ("Union : ");
    for (i=0;i<26;i++) {
        if (xtractBit(U)) printf ("%c ",'a'+i);
        U=U>>1;
    }
    printf ("\n");

    I=a&b;
    printf ("Intersection : ");
    for (i=0;i<26;i++) {
        if (xtractBit(I)) printf ("%c ",'a'+i);
        I=I>>1;
    }
    printf ("\n");

    M=(a^b)&a;
    printf ("Minus : ");
    for (i=0;i<26;i++) {
        if (xtractBit(M)) printf ("%c ",'a'+i);
        M=M>>1;
    }

    return 0;
}
