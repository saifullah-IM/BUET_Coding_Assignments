/*بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيم*/

#include<iostream>
#include<cmath>
#define PI (2.0*acos(0.0))
#define EPS 0.0001
using namespace std;

class Point2D
{
	double x,y;
public:
    Point2D (double x=0.0,double y=0.0) {this->x=x,this->y=y;}
    void getXY (double &x,double &y);
    void setValue (double x=0.0,double y=0.0);
    Point2D operator+ (Point2D other);
    Point2D operator* (double a);
    bool operator== (Point2D other);
    bool operator!= (Point2D other);
    void print ();
};

void Point2D::setValue(double x,double y)
{
    this->x=x;
    this->y=y;
}

void Point2D::getXY(double &x,double &y)
{
    x=this->x;
    y=this->y;
}

Point2D Point2D::operator+(Point2D other)
{
    Point2D res;
    res.x=x+other.x;
    res.y=y+other.y;
    return res;
}

Point2D Point2D::operator*(double a)
{
    Point2D res(x*a,y*a);
    return res;
}

bool Point2D::operator==(Point2D other)
{
    return (x==other.x && y==other.y);
}

bool Point2D::operator!=(Point2D other)
{
    return (x!=other.x || y!=other.y);
}

void Point2D::print()
{
    cout<<x<<' '<<y<<endl;
}



class Circle
{
	Point2D center;
	double radius;
public:
	Circle();
	Circle(Point2D c, double r);
	void setCircle (Point2D c, double r);
	void getCircle (Point2D &c, double &r);
	double area();
	Circle operator*(double a);
	Circle operator+(Point2D P);
	Circle operator+(Circle other);
	Circle operator-(Circle other);
	bool operator==(Circle other);
	bool operator>(Circle other);
	bool operator>=(Circle other);
	bool operator<(Circle other);
	bool operator<=(Circle other);
	Circle operator++();
	Circle operator++(int a);
	void print();
};

Circle::Circle()
{
    Point2D center(0,0);
    this->center=center;
    this->radius=0.0;
}

Circle::Circle(Point2D c,double r)
{
    center=c;
    radius=r;
}

void Circle::setCircle(Point2D c,double r)
{
    center=c;
    radius=r;
}

void Circle::getCircle(Point2D &c,double &r)
{
    c=center;
    r=radius;
}

double Circle::area()
{
    return 2.0*PI*radius;
}

Circle Circle::operator*(double a)
{
    Circle res(center*a,radius*a);
    return res;
}

Circle Circle::operator+(Point2D P)
{
    Circle res(center+P,radius);
    return res;
}

Circle Circle::operator+(Circle other)
{
    double a;
    Circle res;

    a=radius/(radius+other.radius);
    res.setCircle(center*a+other.center*(1-a),radius+other.radius);
}

Circle Circle::operator-(Circle other)
{
    double a;
    Circle res;

    a=radius/(radius+other.radius);
    res.setCircle(center*a+other.center*(1-a),radius-other.radius);
}

bool Circle::operator==(Circle other)
{
    return (fabs(area()-other.area())<EPS);
}

bool Circle::operator>(Circle other)
{
    return area()>other.area();
}

bool Circle::operator>=(Circle other)
{
    return (fabs(area()-other.area())<EPS) || (*this>other);
}

bool Circle::operator<(Circle other)
{
    return area()<other.area();
}

bool Circle::operator<=(Circle other)
{
    return (fabs(area()-other.area())<EPS) || (*this<other);
}

Circle Circle::operator++()
{
    radius+=1.0;
    return *this;
}

Circle Circle::operator++(int a)
{
    Circle res=*this;
    radius+=1.0;
    return res;
}

void Circle::print()
{
    cout<<"Center is ";
    center.print();
    cout<<"radius is ";
    cout<<radius<<endl;
}



class Rectangle
{
    Point2D top_right,bottom_left;
public:
    Rectangle ();
    Rectangle (Point2D top_right,Point2D bottom_left);
    void setRectangle (Point2D top_right,Point2D bottom_left);
    void getRectangle (Point2D &top_right,Point2D &bottom_left);
    Rectangle operator+(Point2D P);
    Rectangle operator*(double a);
    void print();
};

Rectangle::Rectangle()
{
    Point2D top_right(0.0,0.0),bottom_left(0.0,0.0);
    this->top_right=top_right;
    this->bottom_left=bottom_left;
}

Rectangle::Rectangle(Point2D top_right,Point2D bottom_left)
{
    this->top_right=top_right;
    this->bottom_left=bottom_left;
}

void Rectangle::setRectangle(Point2D top_right,Point2D bottom_left)
{
    this->top_right=top_right;
    this->bottom_left=bottom_left;
}

void Rectangle::getRectangle(Point2D &top_right,Point2D &bottom_left)
{
    top_right=this->top_right;
    bottom_left=this->bottom_left;
}

Rectangle Rectangle::operator+(Point2D P)
{
    Rectangle res;
    res.top_right=top_right+P;
    res.bottom_left=bottom_left+P;
    return res;
}

Rectangle Rectangle::operator*(double a)
{
    Rectangle res;
    res.top_right=top_right*a;
    res.bottom_left=bottom_left*a;
    return res;
}

void Rectangle::print()
{
    cout<<"top_right is ";
    top_right.print();
    cout<<"bottom_left is ";
    bottom_left.print();
}

int main()
{
    cout<<"Demonstration of Point"<<endl<<endl;

    Point2D P1(1.0,2.3),P2(3.5,6.9),P3,P;
    cout<<"Let P1(1.0,2.3), P2(3.5,6.9) and P=P1+P2"<<endl;
    P=P1+P2;
    cout<<"P is ";
    P.print();
    cout<<"Let P1(1.0,2.3) and P3=P=P1*1.5"<<endl;
    P3=P=P1*1.5;
    cout<<"P is ";
    P.print();
    cout<<endl;
    if (P==P3) cout<<"P and P3 are equal"<<endl;
    else cout<<"P and P3 are not equal"<<endl;
    if (P1!=P2) cout<<"P1 and P2 are not equal"<<endl;
    else cout<<"P1 and P2 are equal"<<endl;

    cout<<endl<<"****************************************"<<endl<<"Demonstration of Circle"<<endl<<endl;

    Circle C1(P1,5.4),C2(P2,3.8),C3,C4,C5(P,5.4);
    cout<<"Let Circle C1(P1,5.4),C2(P2,3.8),C5(P,5.4)"<<endl;
    cout<<"C3=C2*2.1"<<endl;
    C3=C2*2.1;
    C3.print();
    cout<<"C3=C1+P"<<endl;
    C3=C1+P;
    C3.print();
    cout<<"C3=C1+C2"<<endl;
    C3=C1+C2;
    C3.print();
    cout<<"C3=C1-C2"<<endl;
    C3=C1-C2;
    C3.print();
    cout<<endl;

    if (C1==C5) cout<<"C1 and C5 are equal"<<endl;
    else cout<<"C1 and C5 are not equal"<<endl;
    if (C1>C2) cout<<"C1 is greater than C2"<<endl;
    else cout<<"C1 is not greater than C2"<<endl;
    if (C1>=C5) cout<<"C1 is greater than or equal to C5"<<endl;
    else cout<<"C1 is less than C5"<<endl;
    if (C2<C1) cout<<"C2 is less than C1"<<endl;
    else cout<<"C2 is not less than C1"<<endl;
    if (C2>=C5) cout<<"C2 is greater than or equal to C5"<<endl;
    else cout<<"C2 is less than C5"<<endl;

    cout<<endl<<"****************************************"<<endl<<"Demonstration of Rectangle"<<endl<<endl;
    Rectangle R(P1,P2),R1,R2;
    cout<<"Let R(P1,P2) and R1=R+P and R2=R1*1.76"<<endl;
    R1=R+P;
    cout<<"R1 is "<<endl;
    R1.print();
    R2=R1*1.76;
    cout<<"R2 is "<<endl;
    R2.print();

	return 0;
}
