/*
Problem 2 coded by Saifullah Talukder
Statement:
Write a recursive function to calculate the nth fibonacci number.
*/

#include <stdio.h>

long long fib[1000];

long long fibonacci (int n)
{
    if (n==0) return 0;
    else if (n==1) return 1;
    else if (fib[n]!=0) return fib[n]; ///No need to calculate the same result twice. If we have already calculated it, we simply return that value.
    else {
        fib[n]=fibonacci(n-1)+fibonacci(n-2); ///We save the value to use it later. This is done to avoid repeating the same calculation. If you think carefully you can easily understand that this function calls the same state multiple times.
        return fib[n];
    }
}

int main ()
{
    int n;
    long long ans;

    scanf ("%d",&n);
    ans=fibonacci(n);
    printf ("%lld\n",ans);

    return 0;
}
