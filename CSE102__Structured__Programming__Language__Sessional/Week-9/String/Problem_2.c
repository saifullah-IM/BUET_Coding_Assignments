/*
Problem 2 coded by Saifullah Talukder

Statement:
Write a program that tests whether a string is palindrome or not, ignoring the white
spaces (i.e.tab and space) and prints “Palindrome” if it is.
*/

#include <stdio.h>

int main ()
{
    int i,j,len;
    char str[100];

    scanf (" %[^\n]",str);
    for (len=0;str[len]!='\0';len++);
    for (i=0,j=0;i<len;i++) {
        if (str[i]>='a' && str[i]<='z') {
            str[j]=str[i];
            j++;
        }
        if (str[i]>='A' && str[i]<='Z') {
            str[j]=str[i]-'A'+'a';
            j++;
        }
    }
    str[j]='\0';
    len=j;
    j/=2;

    for (i=0;i<=j;i++) {
        if (str[i]!=str[len-1-i]) break;
    }
    if (i==j+1) printf ("Palindrome");
    else printf ("Not Palindrome");

    return 0;
}
