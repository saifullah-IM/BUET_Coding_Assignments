#include <iostream>
#include <cmath>
#define PI (2.0*acos(0.0))
using namespace std;

typedef enum {UNDEFINED, POINT2D, POINT3D, CIRCLE, SQUARE, RECTANGLE, SPHERE} STYPE;

class Shape
{
	STYPE type;
public:
	Shape();
	Shape(STYPE type);
	virtual void print();
	virtual double area();
	virtual bool contains(const Shape *rhs);
	//Intentionally made non-virtual
	bool operator==(const Shape &rhs);
	virtual ~Shape(){}
};

Shape::Shape()
{
	type = UNDEFINED;
}

Shape::Shape(STYPE argtype)
{
	type = argtype;
}

double Shape::area()
{
	cout << "I am a dummy Shape";
	return 0.0;
}

bool Shape::contains(const Shape *rhs)
{
	cout << "You see this, because appropriate contains function is undefined";
	return false;
}

void Shape::print()
{
	cout << "Type: " << type;
}

bool Shape::operator==(const Shape &rhs)
{
	if(type==rhs.type) return true;
	else return false;
}

class Circle;
class Rectangle;
class Point3D;
class Sphere;

class Point2D : virtual public Shape
{
	double x,y;
public:
	Point2D();
	Point2D(STYPE argtype, int argx, int argy);
	void print();
	double area();
	bool contains(Shape *rhs);
	bool contains(const Point2D *rhs);
	bool operator==(const Point2D &rhs);

	double getX() const { return x; }
	double getY() const { return y; }
	double distance(const Point2D P);
	~Point2D(){}
};

class Circle : public Shape
{
	Point2D center;
	double radius;
public:
	Circle();
	Circle(STYPE type, Point2D c, double r);
	double area();
	void print();
	bool contains(Shape * s);
	bool contains(const Point2D * p);
	bool contains(const Circle * rhs);
	bool contains(Rectangle * R);
	bool operator==(const Circle &rhs);
	~Circle(){}
};

class Rectangle : public Shape
{
	Point2D topRight;
	Point2D bottomLeft;
public:
	Rectangle();
	Rectangle(STYPE type, Point2D tr, Point2D bl);
	void print();
	double area();
	bool contains(Shape *rhs);
	bool operator==(Rectangle &rhs);
	Point2D getbottom_left() {return bottomLeft;}
	Point2D gettop_right () {return topRight;}
	~Rectangle(){};
};

class Shape3D : virtual public Shape
{
public:
	Shape3D();
	Shape3D(STYPE type);
	virtual double volume();
	~Shape3D(){}
};

class Point3D :public Point2D , public Shape3D
{
    double z;
public:
    Point3D();
    Point3D(STYPE type, double argx, double argy, double argz);
    void print();
    //double area(); Not needed, base version is sufficient
	bool contains(Shape *rhs);
	bool contains(Point3D *rhs);
	double distance(Point3D P);
	~Point3D(){}
};

class Sphere : public Shape3D
{
	Point3D center;
	double radius;
public:
	Sphere();
	Sphere(STYPE type, Point3D c, double r);
	void print();
	double area();
	double volume();
	bool contains(Shape * rhs);
	bool contains(const Point3D * p);
	bool contains(const Sphere * s);
	~Sphere(){}
};

///Beginning of Point2D

Point2D::Point2D()
{
	x = 0.0;
	y = 0.0;
}

Point2D::Point2D(STYPE argtype, int argx, int argy) : Shape(argtype)
{
	x = argx;
	y = argy;
}

void Point2D::print()
{
	Shape::print();
	cout << " (" << x << "," << y << ")";
}

double Point2D::area()
{
	return 0.0;
}

bool Point2D::contains(Shape *rhs)
{
	Point2D *pointType = dynamic_cast<Point2D*>(rhs);
	if(pointType!=NULL)
	{
		//Supported
		return contains(pointType);
	}
	//By default, use base
	return Shape::contains(rhs);
}

bool Point2D::contains(const Point2D *rhs)
{
	if(x==rhs->x && y==rhs->y) return true;
	else return false;
}

bool Point2D::operator==(const Point2D &rhs)
{
	if( !Shape::operator==(rhs) ) return false;
	if( x==rhs.x && y==rhs.y ) return true;
	else return false;
}

double Point2D::distance(Point2D P)
{
    double ans;
    ans=sqrt((x-P.x)*(x-P.x)+(y-P.y)*(y-P.y));
    return ans;
}

///Ending of Point2D
///Beginning of Circle

Circle::Circle()
{
    Point2D P(POINT2D,0,0);
    double R=0.0;
    center=P;
    radius=R;
}

Circle::Circle(STYPE type, Point2D c, double r) : Shape(type)
{
    center=c;
    radius=r;
}

double Circle::area()
{
    return PI*radius*radius;
}

void Circle::print()
{
    Shape::print();
    cout<<" Center of the circle is ";
    center.print();
    cout<<"\nRadius of the circle is "<<radius;
}

bool Circle::contains(Shape *s)
{
	Point2D *pointType = dynamic_cast<Point2D*>(s);
	if(pointType!=NULL)
	{
		//Supported
		return contains(pointType);
	}
	Circle *circleType = dynamic_cast<Circle*>(s);
	if(circleType!=NULL)
	{
		//Supported
		return contains(circleType);
	}
	Rectangle *rectangleType = dynamic_cast<Rectangle*>(s);
	if(rectangleType!=NULL)
	{
		//Supported
		return contains(rectangleType);
	}
	//By default
	return Shape::contains(s);
}

bool Circle::contains(const Point2D *P)
{
    double dist;
    dist=center.distance(*P);
    if (dist<=radius) return true;
    else return false;
}

bool Circle::contains(const Circle *rhs)
{
	double R,dist;

	dist=center.distance(rhs->center);
	R=radius-rhs->radius;
	if (R>dist) return true;
	else return false;
}

bool Circle::contains(Rectangle *R)
{
    Point2D A,C;
    A=R->getbottom_left();
    C=R->gettop_right();

    Point2D B(POINT2D,C.getX(),A.getY());
    Point2D D(POINT2D,A.getX(),C.getY());

    bool ans=contains(&A) && contains(&B) && contains(&C) && contains(&D);
    return ans;
}

bool Circle::operator==(const Circle &rhs)
{
    if (!Shape::operator==(rhs)) return false;
    return (radius==rhs.radius);
}

///Ending of Circle
///Beginning of Rectangle

Rectangle::Rectangle() : Shape()
{
    Point2D A(POINT2D,0,0);
    topRight=bottomLeft=A;
}

Rectangle:: Rectangle (STYPE type, Point2D tr, Point2D bl) : Shape(type)
{
    topRight=tr;
    bottomLeft=bl;
}

void Rectangle::print()
{
    Shape::print();
    cout<<"\nTop Right point is ";
    topRight.print();
    cout<<"\nBottom Left point is ";
    bottomLeft.print();
}

double Rectangle::area()
{
    double height,width;
    height=(topRight.getX()-bottomLeft.getX());
    width=(topRight.getY()-bottomLeft.getY());
    return height*width;
}

bool Rectangle::contains(Shape *rhs)
{
    Point2D *ptr=dynamic_cast<Point2D*>(rhs);
    if (ptr!=NULL) {
        if (ptr->getX()>=bottomLeft.getX() && ptr->getX()<=topRight.getX() && ptr->getY()>=bottomLeft.getY() && ptr->getY()<=topRight.getY())
            return true;
        else return false;
    }
    return Shape::contains(rhs);
}

bool Rectangle::operator==(Rectangle &rhs)
{
    if (!Shape::operator==(rhs)) return false;
    return (area()==rhs.area());
}

///Ending of Rectangle
///Beginning of Point3D

Point3D::Point3D()
{
    z = 0;
}

Point3D::Point3D(STYPE type, double argx, double argy, double argz) : Point2D(type,argx,argy) , Shape(type)
{
    z=argz;
}

void Point3D::print()
{
	Shape::print();
    cout << " (" << getX() << "," << getY() << "," << z << ")";
}

bool Point3D::contains(Shape *rhs)
{
    Point3D *ptr=dynamic_cast<Point3D*>(rhs);
    if (ptr!=NULL) return contains(ptr);
    else return Shape::contains(rhs);
}

bool Point3D::contains(Point3D *rhs)
{
    if (getX()==rhs->getX() && getY()==rhs->getY() && z==rhs->z) return true;
    else return false;
}

double Point3D::distance (Point3D P)
{
    double dist_x,dist_y,dist_z;
    dist_x=(getX()-P.getX())*(getX()-P.getX());
    dist_y=(getY()-P.getY())*(getY()-P.getY());
    dist_z=(z-P.z)*(z-P.z);
    return sqrt(dist_x+dist_y+dist_z);
}

///Ending of Point3D
///Beginning of Shape3D

Shape3D::Shape3D()
{

}

Shape3D::Shape3D(STYPE argtype) : Shape(argtype)
{

}

double Shape3D::volume()
{
	cout << "You see this, because appropriate function is missing in the derived class";
	return 0.0;
}

///Ending of Shape3D
///Beginning of Sphere

Sphere::Sphere()
{
    radius=0;
}

Sphere::Sphere(STYPE type, Point3D c, double r) : Shape3D(type) , Shape(type)
{
    center=c;
    radius=r;
}

void Sphere::print()
{
    Shape::print();
    cout<<"\nThe center of the sphere is ";
    center.print();
    cout<<" and the radius is ";
    cout<<radius;
}

double Sphere::area()
{
    return 4.0*PI*radius*radius;
}

double Sphere::volume()
{
    return (4.0/3.0)*PI*radius*radius;
}

bool Sphere::contains(Shape *rhs)
{
    Point3D *P=dynamic_cast<Point3D*>(rhs);
    if (P!=NULL) return contains(P);
    Sphere *S=dynamic_cast<Sphere*>(rhs);
    if (S!=NULL) return contains(S);
    return Shape::contains(rhs);
}

bool Sphere::contains(const Point3D *P)
{
    double dist;
    dist=center.distance(*P);
    if (dist<=radius) return true;
    else return false;
}

bool Sphere::contains(const Sphere *S)
{
    double dist,R;
    dist=center.distance(S->center);
    R=radius-S->radius;
    if (R>dist) return true;
    else return false;
}

///Ending of Sphere
///Beginning of main

int main(void)
{
	while(1)
	{
		int choice;
		Shape * shape;
		Shape3D * shape3D;
		Point2D * point2D;

        cout << "1. Point2D 2. Rectangle 3. Circle\n";
        cout << "4. Point3D 5. Sphere. 0. Exit\n";
        cout << "\nYour choice:";
        cin >> choice;

		switch(choice)
		{
			case 1:
				shape = new Point2D(POINT2D, 5.0,10.0);
				shape->print();
				cout << "\nArea: " << shape->area()<<endl<<endl;
				break;
			case 2: {
				Point2D p1(POINT2D,5.0,5.0);
				Point2D p2(POINT2D,20.0,20.0);
				shape = new Rectangle(RECTANGLE, p2, p1);
				shape->print();
				cout << "\nArea: " << shape->area()<<endl<<endl;
				break;
            }
			case 3: {
				Point2D p1(POINT2D,0.0,0.0);
				shape = new Circle(CIRCLE,p1,10.0);
				break;
			}
			case 4: {
				shape3D = new Point3D(POINT3D,5.0,10.0,20.0);
				shape3D->print();
				cout << "\nArea: " << shape3D->area()<<endl;
				cout << "\nVolume: " << shape3D->volume()<<endl<<endl;
				break;
			}
			case 5: {
				Point3D p1(POINT3D,0.0,0.0,0.0);
				shape3D = new Sphere(SPHERE,p1,10.0);
				shape3D->print();
				cout << "\nArea: " << shape3D->area()<<endl;
				cout << "\nVolume: " << shape3D->volume()<<endl<<endl;
				break;
			}
		}
		if(choice==0) {
            cout<<endl;
            break;
		}
	}

	cout<<endl<<"***** Further demonstration of other functions *****"<<endl<<endl;
    Point2D p1(POINT2D,5.0,5.0);
    Point2D p2(POINT2D,20.0,20.0);
    Point2D p3(POINT2D, 5.0,10.0);
    p1.print();
    cout<<endl;
    p2.print();
    cout<<endl;
    p3.print();
    if (p1.contains(&p2)) cout<<endl<<"First point contains the second one"<<endl<<endl;
    else cout<<endl<<"First point doesn't contain the second one"<<endl<<endl;

    Rectangle R(RECTANGLE, p2, p1);
    R.print();
    if (R.contains(&p3)) cout<<endl<<"The rectangle contains the third point"<<endl<<endl;
    else cout<<endl<<"The rectangle doesn't contain the third point"<<endl<<endl;

    Circle C1(CIRCLE,p1,10.0);
    Circle C2(CIRCLE,p2,12.0);
    C1.print();
    cout<<endl;
    C2.print();
    cout<<endl;
    if (C1.contains(&p2)) cout<<endl<<"The first circle contains the second point"<<endl;
    else cout<<endl<<"The first circle doesn't contain the second point"<<endl;
    if (C1==C2) cout<<"The circles are equal to each other"<<endl;
    else cout<<"The circles are not equal to each other"<<endl;
    if (C2.contains(&C1)) cout<<"The second circle contains the first one"<<endl;
    else cout<<"The second circle doesn't contain the first one"<<endl;
    if (C2.contains(&R)) cout<<"The second circle contains the rectangle"<<endl<<endl;
    else cout<<"The second circle doesn't contain the rectangle"<<endl<<endl;

    Point3D P1(POINT3D,0.0,0.0,0.0);
    Point3D P2(POINT3D,5.0,8.0,3.0);
    P1.print();
    cout<<endl;
    P2.print();
    cout<<endl;
    if (P1.contains(&P2)) cout<<endl<<"First 3D point contains the second one"<<endl<<endl;
    else cout<<endl<<"First 3D point doesn't contain the second one"<<endl<<endl;

    Sphere S1(SPHERE,P1,10.0);
    Sphere S2(SPHERE,P2,12.0);
    S1.print();
    cout<<endl;
    S2.print();
    cout<<endl;
    if (S1.contains(&P2)) cout<<endl<<"The first sphere contains the second 3D point"<<endl;
    else cout<<endl<<"The first sphere doesn't contain the second 3D point"<<endl;
    if (S2.contains(&S1)) cout<<"The second sphere contains the first one"<<endl<<endl;
    else cout<<"The second sphere doesn't contain the first one"<<endl<<endl;

	return 0;
}
