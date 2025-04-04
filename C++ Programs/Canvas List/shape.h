#pragma once
using namespace std;
/////This is a shape header file where we implement the shape class and its children to be able to 
//make shape objects so we are able to store them in our canvas linked list

class Shape//main parent class for shapes
{
    protected://allows child classes to be able to access the list
        int x;//data members
        int y;

    public: 
        Shape();//default constructor
        Shape(int x, int y);//parametized constructor
        virtual ~Shape();//destructor
        virtual Shape* copy();//gets a copy of the current shape
        int getX() const;//returns x data member
        int getY() const; // returns y data member
        void setX(int val);//sets x value
        void setY(int val2);//sets y value
        virtual void printShape() const;//prints out info of shape
};

class Circle : public Shape // circle child class
{
    private:
        int radius;//radius data member 

    public: 
        Circle();//circle constructor
        Circle(int r);//circle parametized constructor with only radius
        Circle(int x, int y, int r);//circle parametized constructor with x,y ,and radius
        virtual ~Circle();//destructir
        virtual Circle* copy();
        int getRadius() const;//gets radius
        void setRadius(int);//sets radius
        virtual void printShape() const;//prints info about circle 
};

class Rectangle: public Shape //rectangle child class
{
    private:// private data members
        int width;
        int height;

    public: 
        Rectangle();//default constructor
        Rectangle(int w, int h);//parametized constructor with width and height
        Rectangle(int x, int y, int w, int h);//parametized constructor with x,y,width,height
        virtual ~Rectangle();//destructor
        virtual Rectangle* copy();
        int getWidth() const;//returns width
        int getHeight() const;//returns heigh
        void setWidth(int w);//sets width
        void setHeight(int h);//sets height
        virtual void printShape() const;//prints info about shape
};

class RightTriangle : public Shape //right triangle child class
{
    private://private data members
        int base;
        int height;

    public: 
        RightTriangle();//default constructor
        RightTriangle(int b, int h);//parametized constructor with base and height
        RightTriangle(int x, int y, int b, int h);//parametized function with x,y,base,height
        virtual ~RightTriangle();//destructor
        virtual RightTriangle* copy();
        int getBase() const;//returns base
        int getHeight() const;//returns height
        void setBase(int b) ;//sets base
        void setHeight(int h);//sets height
        virtual void printShape() const;//prints info about right triangle
};

///////////////////////////////////////////////////////////////////////////////////////// Parent Shape class declarations
Shape::Shape(){//default contructor for shape class 
    x = 0;//sets data members to 0
    y= 0;
}

Shape::Shape(int x2, int y2){//parametized constructor for shape class 
    x= x2;//sets x of shape by user input
    y = y2;//sets y of shape by user input
}

Shape::~Shape(){

}

Shape* Shape:: copy(){
  Shape *s = new Shape(x,y);
  return s;
}

int Shape::getX()const{//returns x from the shape class
    return x;
}

int Shape::getY()const{//gets y from the shape class
    return y;
}

void Shape::setX(int x2){//sets x in the shape class
    x = x2;
}

void Shape::setY(int y2){//sets y in th shape class
    y = y2;
}

void Shape::printShape()const{//prints out information about the shape
cout << "It's a Shape at x: "<< x << " "<< "y: " << y  << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////// Circle child class declarations
Circle::Circle(){//default constructor
    radius=0;
}

Circle::Circle(int r){//parametized constructor with radius
    radius = r;
}

Circle::Circle(int x2,int y2, int r){//parametized constructor with x and y and radius
    x = x2;
    y= y2;
    radius = r;
}

Circle::~Circle(){//destructor defined so program doesnt crash since virtual

}

Circle* Circle:: copy(){ //creates a new object and returns it
  Circle *s = new Circle(x,y,radius);//creates new circle
  return s;
}

void Circle::setRadius(int r){//sets radius of circle
    radius = r;
}

int Circle::getRadius() const{ //returns radius of circle
    return radius;
}

void Circle::printShape()const{//prints out information about the shape
cout << "It's a Circle at x: "<< x << ", "<< "y: " << y <<", radius: " << radius << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////// Rectangle Child class declarations
Rectangle::Rectangle(){//default constructor for rectangle class
    width = 0; //sets data members to 0
    height = 0;
}

Rectangle::Rectangle(int w , int h){//parametized function with height and width
  width = w;
  height = h;
}

Rectangle::Rectangle(int x2, int y2, int w, int h){//parametized function with x,y,width, and height
 x= x2;//sets data members based on user input
 y=y2;
 width=w;
 height=h;
}

Rectangle::~Rectangle(){//destructor and is defined so program doesnt crash or any warnings are given

}

Rectangle* Rectangle:: copy(){ //creates a new object and returns it
  Rectangle *s = new Rectangle(x,y,width,height);//creates new rectangle
  return s;
}

void Rectangle::setWidth(int w){ //returns radius of circle
    width = w;
}

void Rectangle::setHeight(int h){
    height = h;
}

int Rectangle::getWidth() const{ //returns radius of circle
    return width;
}
int Rectangle::getHeight() const{ //returns radius of circle
    return height;
}

void Rectangle::printShape()const{//prints out information about the shape
    cout << "It's a Rectangle at x: "<< x << ", "<< "y: " << y <<", with width: " << width << " and height: " << height << endl;
}
////////////////////////////////////////////////////////////////////// Right triangle class declarations
RightTriangle::RightTriangle(){//default constructor for right triangle
    base = 0;//sets data members to 0
    height =0;
}

RightTriangle::RightTriangle(int b, int h){//parametized consturctor with base and height
    base = b;//assigns base and height based on user input
    height =h;
}

RightTriangle::RightTriangle(int x2, int y2, int b, int h){//parametized constructor with x,y,base, and height
   x= x2;//assigns x,y,base and height based on user input
   y= y2;
   base = b;
   height = h;
}

RightTriangle::~RightTriangle(){//destructor for right triangle left empty to avoid errors or warnings

}

RightTriangle* RightTriangle:: copy(){ //creates a new object and returns it
  RightTriangle *s = new RightTriangle(x,y,base,height);//creates new right triangle and returns it
  return s;
}

void RightTriangle::setBase(int b){//sets base of right triangle based on user input
   base = b;
}

void RightTriangle::setHeight(int h){//sets height of right triangle based on user input
   height = h; 
}

int RightTriangle::getBase() const{//gets the base of the right triangle
    return base;
}

int RightTriangle::getHeight() const{//gets the height of the right triangle
    return height;
}

void RightTriangle::printShape()const{//prints out information about the shape
    cout << "It's a Right Triangle at x: "<< x << ", "<< "y: " << y <<", with base: " << base << " and height: " << height << endl;
}