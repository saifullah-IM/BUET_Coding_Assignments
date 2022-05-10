/*
Problem_1 coded by Saifullah Talukder
Statement: Write a program to calculate the value of PI.
*/

#include <stdio.h>
#include <stdlib.h>

struct point {
    double x,y;
};

struct circle {
    struct point o;
    double r;
};

int inSide (struct point p,struct circle c)  /// checks if a point is within a circle
{
    double r,R;
    r=c.r*c.r;
    R=(p.x-c.o.x)*(p.x-c.o.x)+(p.y-c.o.y)*(p.y-c.o.y);

    if (R>r) return 0;
    else return 1;
}

int main ()
{
    int r,i,n,cnt=0;
    double x,y,PI;
    struct circle C;
    struct point P,O;

    C.r=C.o.x=C.o.y=0.5;
    srand(time(NULL)); ///to generate random number based on time
    n=1000000;
    
/*
The main idea is that the ratio of area of a square and a circle inscribed in it is 4 : PI. So, if we find this ratio we can calculate
the value of PI. For this we are going to generate large number of (here 1000000) random points and check if it is within the circle or
not. If it is inside the circle we increase the value of cnt. Finally the ratio of total number of points (all points will be inside the 
square) : cnt should be roughly close to the desired ratio.
*/
   
    for (i=0;i<n;i++) {  
        r=rand(); ///generates random number
        x=(r*1.0)/RAND_MAX; /// RAND_MAX is the highest value this function can generate. By dividing by this number we make sure the 
        r=rand(); /// is between 0 to 1. Here we use a circle whose centre is at (0.5,0.5) and radius is 0.5. So the point must be between
        y=(r*1.0)/RAND_MAX; ///0 to 1 to be inside the square
        P.x=x;
        P.y=y;  /// we have a random point (x,y)
        cnt+=inSide(P,C); 
    }

    PI=(cnt*1.0*4.0)/(n*1.0);
    printf ("Value of PI=%lf\n",PI);

    return 0;
}
