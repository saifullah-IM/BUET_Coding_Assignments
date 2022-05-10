/*
Problem 1 coded by Saifullah Talukder
Statement:
Write a program that prints all the occurrences of a character ch in a given string S .
*/

#include <stdio.h>

int main ()
{
    char str[1000],ch;
    int i,len,ck=0;

    scanf (" %[^\n]",str);
    scanf ("%*c%c",&ch);

    for (len=0;str[len]!='\0';len++){
        if (str[len]>='A' && str[len]<='Z') str[len]=str[len]-'A'+'a';
    }
    if (ch>='A' && ch<='Z') ch=ch-'A'+'a';
    for (i=0;i<len;i++) {
        if (str[i]==ch) {
            printf ("%d ",i+1);
            ck=1;
        }
    }
    if (!ck) printf ("Not Found\n");

    return 0;
}
