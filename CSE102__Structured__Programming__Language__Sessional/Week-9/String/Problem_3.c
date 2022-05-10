/*
Problem 3 coded by Saifullah Talukder

Statement:
Write down a function int find(char s[], char sub[]) which will find and
return the position of the first occurrence of the string sub inside string s . The function
returns -1 if sub doesn’t occur in s at all. Write down a program that will read two strings
s1 and s2 and print all occurrences of string s2 in s1 . Print not found if s2 does not
occur at all in s1.
*/

#include <stdio.h>

int find (char s[],char sub[])
{
    int ln1,ln2,i,j,k,ans=-1;
    char str[1000],substr[1000];
    for (ln1=0;s[ln1]!='\0';ln1++){
        if (s[ln1]>='A' && s[ln1]<='Z') str[ln1]=s[ln1]-'A'+'a';
        else str[ln1]=s[ln1];
    }
    for (ln2=0;sub[ln2]!='\0';ln2++){
        if (sub[ln2]>='A' && sub[ln2]<='Z') substr[ln2]=sub[ln2]-'A'+'a';
        else substr[ln2]=sub[ln2];
    }

    if (ln1>=ln2) {
        for (i=0;i<ln1;i++) {
            if (str[i]==substr[0]) {
                k=i+1;
                for (j=1;j<ln2;j++,k++) {
                    if (str[k]!=substr[j]) break;
                }
                if (j==ln2) return i;
            }
        }
    }

    return -1;
}

int main ()
{
    int i,k,ans;
    char s1[1000],s2[1000];

    scanf (" %[^\n]",s1);
    scanf (" %[^\n]",s2);
    ans=find(s1,s2)+1;
    if (ans==0) printf ("not found");
    else printf ("%d ",ans);

    while (1) {
        k=find(s1+ans,s2);
        if (k==-1) break;
        else {
            ans+=k+1;
            printf ("%d ",ans);
        }
    }

    return 0;
}
