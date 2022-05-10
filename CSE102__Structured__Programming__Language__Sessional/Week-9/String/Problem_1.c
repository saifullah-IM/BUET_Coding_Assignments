/*
Problem 1 coded by Saifullah Talukder

Statement:
Write a program that takes two string and tests whether they are anagrams of each other
and prints “Anagram” if they are otherwise prints “Not Anagram”.
An anagram is the result of rearranging the letters of a word or phrase to produce a new
word or phrase, using all the original letters exactly once; for example, the word anagram
can be rearranged into "nagaram".
*/

#include <stdio.h>

int main ()
{
    int i,j,ara1[26],ara2[26],ln1,ln2,ln,k;
    char str1[100],str2[100];

    scanf (" %[^\n]",str1);
    scanf (" %[^\n]",str2);
    for (ln1=0;str1[ln1]!='\0';ln1++);
    for (ln2=0;str2[ln2]!='\0';ln2++);


    for (i=0;i<26;i++) {
        ara1[i]=ara2[i]=0;
    }
    ln=ln1>ln2 ? ln1 : ln2;
    for (i=0;i<ln;i++) {
        if (str1[i]>='a' && str1[i]<= 'z') {
            k=str1[i]-'a';
            ara1[k]++;
        }
        if (str1[i]>='A' && str1[i]<= 'Z') {
            k=str1[i]-'A';
            ara1[k]++;
        }
        if (str2[i]>='a' && str2[i]<= 'z') {
            k=str2[i]-'a';
            ara2[k]++;
        }
        if (str2[i]>='A' && str2[i]<= 'Z') {
            k=str2[i]-'A';
            ara2[k]++;
        }
    }
    for (i=0;i<26;i++) if (ara1[i]!=ara2[i]) break;
    if (i==26) printf ("Anagram");
    else printf ("Not Anagram\n");

    return 0;
}
