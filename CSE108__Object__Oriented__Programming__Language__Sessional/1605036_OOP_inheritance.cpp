#include <iostream>
#include <cmath>
#define PI 3.1415926
using namespace std;

class Shape {
public:
    virtual void print();
    virtual double area();
    virtual double volume();
    virtual bool contains(Shape S);
};
class Shape3D : public Shape {

};

double Shape::area()
{
	cout << "I am a dummy Shape";
	return 0.0;
}

double Shape::volume()
{
	cout << "I am a dummy Shape";
	return 0.0;
}

bool Shape::contains(const Shape rhs)
{
	return false;
}

void Shape::print()
{
	cout << "error ";
}

class Point2D : public Shape {
    int x,y;
public:
    Point2D (int x=0,int y=0)
    {
        this->x=x;
        this->y=y;
    }
    void setP (int x,int y)
    {
        this->x=x;
        this->y=y;
    }
    void print ()
    {
        cout <<"("<<x<<", "<<y<<")"<<endl;
    }
    int getX () {return x;}
    int getY () {return y;}
};

class Point3D : public Shape3D  {
    int x,y,z;
public:
    Point3D (int x=0,int y=0,int z=0)
    {
        this->x=x;
        this->y=y;
        this->z=z;
    }
    void print ()
    {
        cout <<"("<<x<<", "<<y<<", "<<z<<")"<<endl;
    }
    int getX () {return x;}
    int getY () {return y;}
    int getZ () {return z;}
};

class Circle3D : public Shape3D {
    Point3D center;
    double radius;
public:
    Circle3D (Point3D p,double R=0.0)
    {
        center=p;
        radius=R;
    }
    void print ()
    {
        cout<<"This is a circle whose center is ";
        center.print();
        cout<<"and radius is "<<radius<<endl;
    }
    double area () {return PI*radius*radius;}
    double volume () {return 0;}
    bool contains (Point3D p)
    {
        if (p.getZ()!=center.getZ()) return false;
        double d;
        d=(center.getX()-p.getX())*(center.getX()-p.getX())+(center.getY()-p.getY())*(center.getY()-p.getY());
        d=sqrt(d);
        if (d<=radius) return true;
        else return false;
    }
};

class Rectangle : public Shape {
protected:
    Point2D TR,BL;
public:
    //Rectangle (Point2D A,Point2D B) {BL=A,TR=B;}
    double area ()
    {
        int u,v;
        u=TR.getX()-BL.getX();
        v=TR.getY()-BL.getY();
        return u*v;
    }
    bool contains (Point2D P)
    {
        if (P.getX()>=BL.getX() && P.getX()<=TR.getX() && P.getY()>=BL.getY() && P.getY()<=TR.getY())
            return true;
        else return false;
    }
};

class Square : public Rectangle {
public:
    Square (Point2D P,int side)
    {
        BL.setP(P.getX(),P.getY());
        TR.setP(P.getX()+side,P.getY()+side);
    }
    void print ()
    {
        cout<<"This is a square ans its bottom left point is ";
        BL.print();
        cout<<"and its side length is "<<TR.getX()-BL.getX()<<endl;
    }
};

int main()
{
    Point3D p(5,5,5);
    Point3D p3(7,7,7);
    Shape3D * s3d = new Circle3D(p, 10);
    cout << s3d->area()<<endl;
    cout << s3d->volume()<<endl; //should print 0
    cout << s3d->contains(p3)<<endl;
    Point2D p1(10,10);
    Point2D p2(7,7);
    Shape * s = new Square(p1, 20);
    s->print(); //should print bottom-left point and side-length
    cout << s->area()<<endl;
    cout << s->contains(p2)<<endl;
}
