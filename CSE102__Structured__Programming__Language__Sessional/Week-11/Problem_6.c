/*
Problem 6 coded by Saifullah Talukder
Statement:
Create a structure of Vector (using typedef is prohibited). Then write functions to perform the following operations.
1. Dot multiplication between two vectors.
2. Scalar multiplication between two vectors.
3. Summation of two vectors.
4. Cross multiplication between two vectors.
*/

#include <stdio.h>

struct Vector {
    int x,y,z;
};

int dot (struct Vector A,struct Vector B)
{
    int ans;

    ans=A.x*B.x+A.y*B.y+A.z*B.z;
    return ans;
}

struct Vector scalar (int n,struct Vector A)
{
    A.x*=n;
    A.y*=n;
    A.z*=n;
    return A;
}

struct Vector sum (struct Vector A,struct Vector B)
{
    struct Vector ans;

    ans.x=A.x+B.x;
    ans.y=A.y+B.y;
    ans.z=A.z+B.z;

    return ans;
}

struct Vector cross (struct Vector A,struct Vector B)
{
    struct Vector ans;

    ans.x=A.y*B.z-A.z*B.y;
    ans.y=A.z*B.x-A.x*B.z;
    ans.z=A.x*B.y-A.y*B.x;

    return ans;
}

int main ()
{
    int n,ans;
    struct Vector A,B,ANS;

    scanf ("%d %d %d",&A.x,&A.y,&A.z);
    scanf ("%d %d %d",&B.x,&B.y,&B.z);

    ans=dot(A,B);
    printf ("Dot=%d\n",ans);

    scanf ("%d",&n);
    ANS=scalar(n,A);
    printf ("Scalar = %d %d %d\n",ANS.x,ANS.y,ANS.z);

    ANS=sum(A,B);
    printf ("Sum = %d %d %d\n",ANS.x,ANS.y,ANS.z);

    ANS=cross(A,B);
    printf ("Cross = %d %d %d\n",ANS.x,ANS.y,ANS.z);

    return 0;
}
