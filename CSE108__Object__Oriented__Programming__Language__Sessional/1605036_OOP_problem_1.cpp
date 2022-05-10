/*بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيم*/

#include <iostream>
#include <cmath>
using namespace std;

class Point2D
{
	int x,y;
public:
	Point2D(){ x = 0; y = 0; }
	Point2D(int x, int y);
	void setX(int x);
	void setY(int y);
	void setPoint (int x,int y);
	int getX();
	int getY();
	double distance(Point2D P);
};

Point2D::Point2D(int argx,int argy)
{
	x = argx;
	y = argy;
}

void Point2D::setX(int argx)
{
	x = argx;
}

void Point2D::setY(int argy)
{
	y = argy;
}

void Point2D::setPoint(int x,int y)
{
    this->x=x;
    this->y=y;
}

int Point2D::getX()
{
	return x;
}

int Point2D::getY()
{
	return y;
}

double Point2D::distance(Point2D P)
{
    double ans;
    ans=sqrt(((x-P.getX())*(x-P.getX())*1.0)+((y-P.getY())*(y-P.getY())*1.0));
    return ans;
}

class Triangle {
    Point2D P1,P2,P3;
public:
    Triangle();
    Triangle(Point2D A,Point2D B,Point2D C);
    void setVertex1 (Point2D P);
    void setVertex2 (Point2D P);
    void setVertex3 (Point2D P);
    Point2D getVertex1 ();
    Point2D getVertex2 ();
    Point2D getVertex3 ();
    bool ifSimilar (Triangle T);
    double area ();
};

Triangle::Triangle()
{
    P1.setPoint(0,0);
    P2.setPoint(0,0);
    P3.setPoint(0,0);
}

Triangle::Triangle(Point2D A,Point2D B,Point2D C)
{
    P1=A;
    P2=B;
    P3=C;
}

void Triangle::setVertex1(Point2D P)
{
    P1=P;
}

void Triangle::setVertex2(Point2D P)
{
    P2=P;
}

void Triangle::setVertex3(Point2D P)
{
    P3=P;
}

Point2D Triangle::getVertex1()
{
    return P1;
}

Point2D Triangle::getVertex2()
{
    return P2;
}

Point2D Triangle::getVertex3()
{
    return P3;
}

double Triangle::area()
{
    double A;
    A=0.5*(P1.getX()*P2.getY()+P2.getX()*P3.getY()+P3.getX()*P1.getY()-P2.getX()*P1.getY()-P3.getX()*P2.getY()-P1.getX()*P3.getY());
    if (A<0.0) A=-A;
    return A;
}

bool Triangle::ifSimilar(Triangle T)
{
    double a1,b1,c1,a2,b2,c2;;

    a1=P1.distance(P2);
    b1=P2.distance(P3);
    c1=P3.distance(P1);
    a2=T.getVertex1().distance(T.getVertex2());
    b2=T.getVertex2().distance(T.getVertex3());
    c2=T.getVertex3().distance(T.getVertex1());

    if ((a1/a2)==(b1/b2) && (b1/b2)==(c1/c2)) return true;
    else return false;
}

int main ()
{
    int x,y;
    double A;
    Point2D P;
    Triangle T1,T2;

    //cout<<"Enter 3 vertexes of a triangle"<<endl;
    //cin>>x>>y;
    //P.setPoint(x,y);
    P.setPoint(1,1);
    T1.setVertex1(P);
    //cin>>x>>y;
    //P.setPoint(x,y);
    P.setPoint(1,9);
    T1.setVertex2(P);
    //cin>>x>>y;
    //P.setPoint(x,y);
    P.setPoint(7,1);
    T1.setVertex3(P);

    //cout<<"Enter 3 vertexes of another triangle"<<endl;
    //cin>>x>>y;
    //P.setPoint(x,y);
    P.setPoint(0,0);
    T2.setVertex1(P);
    //cin>>x>>y;
    //P.setPoint(x,y);
    P.setPoint(0,4);
    T2.setVertex2(P);
    //cin>>x>>y;
    //P.setPoint(x,y);
    P.setPoint(3,0);
    T2.setVertex3(P);

    if (T1.area()==T2.area()) cout<<"The area of the two triangles are equal"<<endl;
    else cout<<"The area of the two triangles are not equal"<<endl;
    cout<<"Area of first triangle = "<<T1.area()<<endl;
    cout<<"Area of second triangle = "<<T2.area()<<endl;

    if (T1.ifSimilar(T2)) cout<<"The two triangles are similar"<<endl;
    else cout<<"The two triangles are not similar"<<endl;

    return 0;
}
