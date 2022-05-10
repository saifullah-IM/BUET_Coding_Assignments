/*
Problem 2 coded by Saifullah Talukder

Statement:
Perform the following in a single program
***Write a function int numberOfTokens(char a[], char c) which returns the number of tokens in string a where delimiter is character c.
***Write a function char* firstIndexOfToken(char a[],char c) which allocates a character array dynamically, copies the elements of the 
first token, places a null character at the end, and returns the pointer pointing to the first character of the token.
***Write a program using the functions described in 2.a and 2.b to generate all the tokens of a given string and store them in 
multidimensional array. Allocate all the pointers dynamically. Finally print all the tokens from multidimensional array.

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int numberofTokens (char ara[],char ch)
{
    int i,len,ans=0;
    len=strlen(ara);

    if (ch>='A' && ch<='Z') ch=ch-'A'+'a';
    for (i=0;i<len;i++) {
        if (ara[i]>='A' && ara[i]<='Z') ara[i]=ara[i]-'A'+'a';
        if (ara[i]==ch) ans++;
    }
    ans++;

    return ans;
}

char* firstIndexOfToken (char ara[],char ch)
{
    int i,len,idx;
    char *ptr;
    len=strlen(ara);

    if (ch>='A' && ch<='Z') ch=ch-'A'+'a';
    for (i=0;i<len;i++) {
        if (ara[i]==ch) {
            idx=i;
            break;
        }
    }

    ptr=(char *)malloc((idx+1)*sizeof(char));
    for (i=0;i<idx;i++) {
        *(ptr+i)=ara[i];
    }
    *(ptr+idx)='\0';

    return ptr;
}

int main ()
{
    int i,j,ans,len,idx,temp;
    char str[1000],ch,*ptr,**qtr;

    scanf (" %[^\n]",str);
    scanf ("%*c%c",&ch);
    len=strlen(str);
    ans=numberofTokens(str,ch);
    printf ("Number of tokens=%d\n",ans);

    ptr=firstIndexOfToken(str,ch);

    qtr=(char **)malloc(sizeof(char *)*ans);

    j=0;
    for (i=0;i<ans;i++) {
        *(qtr+i)=(char *)malloc(len*sizeof(char));
        ptr=firstIndexOfToken(str+j,ch);
        *(qtr+i)=ptr;
        printf ("%s\n",*(qtr+i));
        j+=strlen(ptr)+1;
    }

    return 0;
}
