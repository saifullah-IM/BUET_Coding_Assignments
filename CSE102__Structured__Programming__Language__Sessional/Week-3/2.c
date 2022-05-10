/*
Problem 2 coded by Saifullah Talukder
Statement:
Take two integers as input and find the LCM (least common multiple) of them. (Finding GCD i.e greatest common divisor to do is prohibited).
*/

 
#include <stdio.h>
 
int main ()
{
    int lcm,a,b,i;
 
    scanf ("%d %d",&a,&b);
 
    for (i=1;i<=a;i++) {
        lcm=b*i;
        if (lcm%a==0) break;
    }
 
    printf ("%d\n",lcm);
    return 0;
}
 
/*
solution using GCD
    lcm=a*b;
 
    while (b>0) {
        t=b;
        b=a%b;
        a=t;
    }
 
    lcm/=a;
*/
