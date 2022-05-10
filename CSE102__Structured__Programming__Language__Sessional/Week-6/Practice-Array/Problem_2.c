/*
Coded by Saifullah Talukder
Statement: Write a program that takes a string (array of characters) and checks if it is a palindrome or not.
*/

#include <stdio.h>

int main ()
{
    int i,len,ck=1,n;
    char str[1001];

    scanf (" %[^\n]",str);
    for (len=0;str[len]!='\0';len++);
    n=len/2;
    len-=1;
    for (i=0;i<n;i++) {
        if (str[i]!=str[len-i]) {
            ck=0;
            break;
        }
    }
    if (ck) printf ("The string is a palindrome.");
    else printf ("The string is not a palindrome.");

    return 0;
}
