/*بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيم*/

#include<iostream>
#include<cmath>
#define PI (2.0*acos(0.0))
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
	void print();
	~Point2D(){ x = 0; y = 0; }
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

void Point2D::print()
{
	cout << "(" << x << "," << y << ")";
}

class Circle
{
	Point2D center;
	double radius;
public:
	Circle();
	Circle(Point2D c, double r);
	void setCenter (Point2D c);
	void setRadius (double r);
	void setCircle (Point2D c, double r);
	void getCircle (Point2D &c, double &r);
	double area();
	void print();
	int intersect(Circle rhs);
	int contains(Circle rhs);
	int contains(Point2D p);
	double perimeter();
	~Circle();
};

Circle::Circle()
{
    Point2D center(0,0);
    this->center=center;
    double radius=0.0;
    this->radius=radius;
}

Circle::~Circle()
{
    Point2D center(0,0);
    this->center=center;
    double radius=0.0;
    this->radius=radius;
}

Circle::Circle(Point2D c, double r)
{
    center=c;
    radius=r;
}

void Circle::setCenter(Point2D c)
{
    center=c;
}

void Circle::setRadius(double r)
{
    radius=r;
}

void Circle::setCircle(Point2D c, double r)
{
    center=c;
    radius=r;
}

void Circle::getCircle(Point2D &c, double &r)
{
    c=center;
    r=radius;
}

double Circle::area()
{
	return PI*radius*radius;
}

int Circle::intersect(Circle rhs)
{
	double R,dist_x,dist_y,dist;

	dist_x=(center.getX()-rhs.center.getX())*(center.getX()-rhs.center.getX())*1.0;
	dist_y=(center.getY()-rhs.center.getY())*(center.getY()-rhs.center.getY())*1.0;
	dist=sqrt(dist_x+dist_y);
	R=radius+rhs.radius;
	if (R>dist && !this->contains(rhs)) return 1;
	else return 0;
}

int Circle::contains(Circle rhs)
{
	double R,dist_x,dist_y,dist;

	dist_x=(center.getX()-rhs.center.getX())*(center.getX()-rhs.center.getX())*1.0;
	dist_y=(center.getY()-rhs.center.getY())*(center.getY()-rhs.center.getY())*1.0;
	dist=sqrt(dist_x+dist_y);
	R=radius-rhs.radius;
	if (R>dist) return 1;
	else return 0;
}

int Circle::contains(Point2D p)
{
	double dist_x,dist_y,dist;

	dist_x=(center.getX()-p.getX())*(center.getX()-p.getX())*1.0;
	dist_y=(center.getY()-p.getY())*(center.getY()-p.getY())*1.0;
	dist=sqrt(dist_x+dist_y);
	if (radius>dist) return 1;
	else return 0;
}

double Circle::perimeter()
{
    return 2.0*PI*radius;
}

void Circle::print()
{
	cout<<"Center: ";
	center.print();
	cout<<" Radius: "<<radius<<endl;
}

class Rectangle
{
    Point2D top_right,bottom_left;
public:
    Rectangle ();
    Rectangle (Point2D top_right,Point2D bottom_left);
    void setTop_right (Point2D top_right);
    void setBottom_left (Point2D bottom_left);
    void setRectangle (Point2D top_right,Point2D bottom_left);
    void getRectangle (Point2D &top_right,Point2D &bottom_left);
	double area();
	int intersect(Rectangle rhs);
	int contains(Point2D p);
	int contains(Rectangle rhs);
	int inside(Circle c);
	double perimeter();
	void print();
	~Rectangle ();
};

Rectangle::Rectangle()
{
    Point2D top_right(0,0),bottom_left(0,0);
    this->top_right=top_right;
    this->bottom_left=bottom_left;
}

Rectangle::~Rectangle()
{
    Point2D top_right(0,0),bottom_left(0,0);
    this->top_right=top_right;
    this->bottom_left=bottom_left;
}

Rectangle::Rectangle(Point2D top_right,Point2D bottom_left)
{
    this->top_right=top_right;
    this->bottom_left=bottom_left;
}

void Rectangle::setTop_right(Point2D top_right)
{
    this->top_right=top_right;
}

void Rectangle::setBottom_left(Point2D bottom_left)
{
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

double Rectangle::area()
{
    double height,width;
    height=(top_right.getX()-bottom_left.getX())*1.0;
    width=(top_right.getY()-bottom_left.getY())*1.0;
    return height*width;
}

double Rectangle::perimeter()
{
    double height,width;
    height=(top_right.getX()-bottom_left.getX())*1.0;
    width=(top_right.getY()-bottom_left.getY())*1.0;
    return 2.0*(height+width);
}

int Rectangle::inside(Circle c)
{
    Point2D A(bottom_left.getX(),top_right.getY());
    Point2D B(top_right.getX(),bottom_left.getY());

    int ans=c.contains(A) && c.contains(bottom_left) && c.contains(B) && c.contains(top_right);
    return ans;
}

int Rectangle::contains(Point2D p)
{
    if (p.getX()>=bottom_left.getX() && p.getX()<=top_right.getX() && p.getY()>=bottom_left.getY() && p.getY()<=top_right.getY())
        return 1;
    else return 0;
}

int Rectangle::intersect(Rectangle rhs)
{
    Point2D A,B,C,D;
    rhs.getRectangle(A,C);
    B.setX(C.getX());
    B.setY(A.getY());
    D.setX(A.getX());
    D.setY(C.getY());

    if (this->contains(A) || this->contains(B) || this->contains(C) || this->contains(D) && !this->contains(rhs)) return 1;
    else return 0;
}

int Rectangle::contains(Rectangle rhs)
{
    Point2D A,B,C,D;
    rhs.getRectangle(A,C);
    B.setX(C.getX());
    B.setY(A.getY());
    D.setX(A.getX());
    D.setY(C.getY());

    if (this->contains(A) && this->contains(B) && this->contains(C) && this->contains(D)) return 1;
    else return 0;
}

void Rectangle::print ()
{
    cout<<"Top_right: ";
    top_right.print();
    cout<<"  Bottom_left: ";
    bottom_left.print();
    cout<<endl;
}

int main()
{
    Point2D A(0,0),B(1,2);
    Circle C,D,E,F;

    cout<<"Demonstrating Circle class"<<endl<<endl;

    C.setCircle(A,3.0);
    C.print();
    cout<<"Area of C: "<<C.area()<<endl;
    D.setCircle(B,2.0);
    if (C.intersect(D)) cout<<"C intersects D"<<endl;
    else cout<<"C doesn't intersect D"<<endl;
    B.setX(5);
    E.setCircle(B,2.0);
    if (C.intersect(E)) cout<<"C intersects E"<<endl;
    else cout<<"C doesn't intersect E"<<endl;
    B.setPoint(1,1);
    F.setCircle(B,1.0);
    if (C.contains(F)) cout<<"C contains F"<<endl;
    else cout<<"C doesn't contain F"<<endl;
    if (C.contains(E)) cout<<"C contains E"<<endl;
    else cout<<"C doesn't contain E"<<endl;

    cout<<endl<<"Demonstrating Rectangle class"<<endl<<endl;

    Point2D M(6,10),N(1,2);
    Rectangle P,Q,R,S;
    B.setX(8),B.setY(5);

    P.setRectangle(B,A);
    Q.setRectangle(N,M);
    P.print();
    cout<<"Area of P: "<<P.area()<<endl;
    if (P.intersect(Q)) cout<<"P intersects Q"<<endl;
    else cout<<"P doesn't intersect Q"<<endl;
    M.setX(10),N.setX(9);
    R.setRectangle(N,M);
    if (P.intersect(R)) cout<<"P intersects R"<<endl;
    else cout<<"P doesn't intersect R"<<endl;

    M.setPoint(7,4),N.setPoint(2,3);
    S.setRectangle(N,M);
    if (P.contains(S)) cout<<"P contains S"<<endl;
    else cout<<"P doesn't contain S"<<endl;
    if (P.contains(Q)) cout<<"P contains Q"<<endl;
    else cout<<"P doesn't contain Q"<<endl;
    C.setRadius(10.0);
    if (P.inside(C)) cout<<"P is inside C"<<endl;
    else cout<<"P is not inside C"<<endl;
    B.setPoint(6,6);
    D.setCenter(B);
    if (P.inside(D)) cout<<"P is inside D"<<endl;
    else cout<<"P is not inside D"<<endl;

	return 0;
}
