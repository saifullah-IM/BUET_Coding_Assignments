/*
Problem 5 coded by Saifullah Talukder
Statement:
Write a recursive function to print all the permutations of a given string of size n.
*/

#include <stdio.h>

int n,isTaken[1000];
char ans[1000];

void permute (int i,char *str)
{
    int j;

    if (i==n) {
        ans[n]='\0';
        printf ("%s\n",ans);
        return;
    }

    for (j=0;j<n;j++) {
        if (isTaken[j]==0) {
            ans[i]=str[j];
            isTaken[j]=1;
            permute(i+1,str);
            isTaken[j]=0;  ///What we are doing here is called backtracking. To understand how it works you may watch this video: https://www.youtube.com/watch?v=nYFd7VHKyWQ&index=1&list=PLrmLmBdmIlpslxZUHHWmfOzNn6cA7jvyh
        }
    }
}

int main ()
{
    char str[1000];

    scanf ("%d",&n);
    scanf (" %[^\n]",str);
    printf ("\n");
    permute(0,str);

    return 0;
}
