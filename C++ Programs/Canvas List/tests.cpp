/// @filename tests.cpp
/// @date March 7, 2023
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "shape.h"
#include "canvaslist.h"
using namespace std;

TEST_CASE("Testing shape default constructor"){//test that is testing the shape default constructor and getters from the shape class
  Shape shape;//calls default constructor
  REQUIRE(shape.getX()==0);//gets the x value of shape
  REQUIRE(shape.getY()==0);//gets the y value of shape
  Shape* shape2 = shape.copy();//checks the copy function 
  REQUIRE(shape2->getX()==0);//gets the x value of shape
  REQUIRE(shape2->getY()==0);//gets the y value of shape
}

TEST_CASE("Testing shape parametized constructor"){//test that is testing the shape parametized constructor and getters from the shape class
  Shape shape(2,4);//calls parametized constructor
  REQUIRE(shape.getX()==2);//gets the x value of shape
  REQUIRE(shape.getY()==4);//gets the y value of shape
  shape.setX(1000);//sets x to 1000 so we are testing setters for shape class
  shape.setY(1000);//sets x to 1000 so we are testing setters for shape class
  REQUIRE(shape.getX()==1000);//gets the x value of shape
  REQUIRE(shape.getY()==1000);//gets the y value of shape
  Shape* shape2 =shape.copy();//checks the copy function 
  REQUIRE(shape2->getX()==1000);//gets the x value of shape
  REQUIRE(shape2->getY()==1000);//gets the y value of shape
}

TEST_CASE("Testing rectangle default constructor"){//test that is testing the rectangle default constructor and getters from the rectangle class
  class Rectangle* rectangle;//calls default constructor
  REQUIRE(rectangle->getWidth()==0);//gets the width value of rectangle
  REQUIRE(rectangle->getHeight()==0);//gets the height value of rectangle
  class Rectangle* rectangle2 = rectangle->copy();//checks the copy function 
  REQUIRE(rectangle2->getHeight()==0);//gets the width value of rectangle
  REQUIRE(rectangle2->getWidth()==0);//gets the height value of rectangle
}

TEST_CASE("Testing rectangle parametized constructor"){//test that is testing the rectangle parametized constructor and getters from the recatngle class
  class Rectangle* rectangle(100,223);//calls default constructor
  REQUIRE(rectangle.getWidth()==100);//gets the width value of rectangle
  REQUIRE(rectangle.getHeight()==223);//gets the height value of rectangle
  class Rectangle* rectangle2 = rectangle.copy();//checks the copy function 
  REQUIRE(rectangle2->getHeight()==223);//gets the width value of rectangle
  REQUIRE(rectangle2->getWidth()==100);//gets the height value of rectangle
}

TEST_CASE("Testing rectangle second parametized constructor"){//test that is testing the rectangle that contains x,y,base, and height.
  Shape shape;//calls parametized constructor for shape class
  class Rectangle rectangle(22,32,100,223);//calls default constructor
  REQUIRE(rectangle.getWidth()==100);//gets the width value of rectangle
  REQUIRE(rectangle.getHeight()==223);//gets the height value of rectangle
  REQUIRE(rectangle.getX()==22);//gets the x value of shape
  REQUIRE(rectangle.getY()==32);//gets the y value of shape
  REQUIRE(rectangle.getHeight()==223);//gets the height value of rectangle
  class Rectangle* rectangle2 = rectangle.copy();//checks the copy function 
  REQUIRE(rectangle2->getHeight()==223);//gets the width value of rectangle
  REQUIRE(rectangle2->getWidth()==100);//gets the height value of rectangle
  REQUIRE(rectangle.getX()==22);//gets the x value of shape
  REQUIRE(rectangle.getY()==32);//gets the y value of shape
}

TEST_CASE("Testing circle default constructor"){//test that is testing the circle default constructor and getters from the circle class
  Circle circle;//circle object
  REQUIRE(circle.getRadius()==0);//gets the radius value of circle
  Circle* circle2 = circle.copy();//checks the copy function 
  REQUIRE(circle2->getRadius()==0);//gets the radius value of circle
}

TEST_CASE("Testing circle parametized constructor"){//test that is testing the circle parametized constructor and getters from the circle class
  Circle circle(3);//circle object that calls parametized constructor
  REQUIRE(circle.getRadius()==3);//gets the radius value of circle
  Circle* circle2= circle.copy();//checks the copy function 
  REQUIRE(circle2->getRadius()==3);//gets the radius value of circle
}

TEST_CASE("Testing circle second parametized constructor"){//test that is testing the rectangle that contains x,y,and radius
  Shape shape;//calls default  constructor for shape class
  Circle circle(1000,2222,44444);//circle object that calls parametized constructor
  REQUIRE(circle.getRadius()==44444);//gets the radius value of circle
  REQUIRE(circle.getX()==1000);//gets the x value of shape
  REQUIRE(circle.getY()==2222);//gets the y value of shape
  Circle* circle2= circle.copy();//checks the copy function 
  REQUIRE(circle2->getRadius()==44444);//gets the radius value of circle
  REQUIRE(circle2->getX()==1000);//gets the x value of shape
  REQUIRE(circle2->getY()==2222);//gets the y value of shape
} 

TEST_CASE("Testing Right Triangle default constructor"){//test that is testing the Right Triangle default constructor and getters from the Right Triangle class
  RightTriangle right;//calls default constructor
  REQUIRE(right.getBase()==0);//gets the base value of Right Triangle
  REQUIRE(right.getHeight()==0);//gets the height value of Right Triangle
  RightTriangle* right2 = right.copy();//checks the copy function 
  REQUIRE(right2->getBase()==0);//gets the base value of Right Triangle
  REQUIRE(right2->getHeight()==0);//gets the height value of Right Triangle
}

TEST_CASE("Testing Right Triangle parametized constructor"){//test that is testing the Right Triangle parametized constructor and getters from the Right Triangle class
  RightTriangle right(343242,52342342);//calls parametized constructor
  REQUIRE(right.getBase()==343242);//gets the base value of Right Triangle
  REQUIRE(right.getHeight()==52342342);//gets the height value of Right Triangle
  RightTriangle* right2 = right.copy();//checks the copy function 
  REQUIRE(right2->getHeight()==52342342);//gets the base value of Right Triangle
  REQUIRE(right2->getBase()==343242);//gets the height value of Right Triangle
}

TEST_CASE("Testing Right Triangle second parametized constructor"){//test that is testing the Right Triangle that contains x,y,base, and height.
  Shape shape;//calls parametized constructor for shape class
  RightTriangle right(1,2,3,4);//calls parametized constructor
  REQUIRE(right.getBase()==3);//gets the base value of Right Triangle
  REQUIRE(right.getHeight()==4);//gets the height value of Right Triangle
  REQUIRE(right.getX()==1);//gets the x value of shape
  REQUIRE(right.getY()==2);//gets the y value of shape
  RightTriangle* right2 = right.copy();//checks the copy function 
  REQUIRE(right2->getHeight()==4);//gets the nase value of Right Triangle
  REQUIRE(right2->getBase()==3);//gets the height value of Right Triangle
  REQUIRE(right2->getX()==1);//gets the x value of shape
  REQUIRE(right2->getY()==2);//gets the y value of shape
}

TEST_CASE("Testing mutiple shapes"){//test that is testing all shapes in the shape class
  Shape shape;//calls parametized constructor for shape class
  RightTriangle right(32131,23123,123123,4312312);//calls parametized constructor
  Circle circle(331,313,3123);//circle object that calls parametized constructor
  class Rectangle rectangle(10231230,223123123);//calls default constructor
  Shape shape2(231231,43123);//calls parametized constructor
  REQUIRE(shape2.getX()==231231);//gets the x value of shape
  REQUIRE(shape2.getY()==43123);//gets the y value of shape
  shape2.setX(8888);//sets x to 8888 so we are testing setters for shape class
  shape2.setY(77777);//sets x to 77777 so we are testing setters for shape class
  REQUIRE(shape2.getX()==8888);//gets the x value of shape
  REQUIRE(shape2.getY()==77777);//gets the y value of shape
  REQUIRE(rectangle.getWidth()==10231230);//gets the width value of rectangle
  REQUIRE(rectangle.getHeight()==223123123);//gets the height value of rectangle
  REQUIRE(right.getBase()==123123);//gets the base value of Right Triangle
  REQUIRE(right.getHeight()==4312312);//gets the height value of Right Triangle
  REQUIRE(right.getX()==32131);//gets the x value of shape
  REQUIRE(right.getY()==23123);//gets the y value of shape
  REQUIRE(circle.getRadius()==3123);//gets the radius value of circle
  REQUIRE(circle.getX()==331);//gets the x value of shape
  REQUIRE(circle.getY()==313);//gets the y value of shape
}

TEST_CASE("CanvasList default constructor"){//test that is testing the default constructor of canvas list
    CanvasList list;
    REQUIRE(list.size() == 0);//checks if size is 0	    
    REQUIRE(list.front()==0);//checks if listfront is 0

}

TEST_CASE("CanvasList push back/push front functions"){//test that is testing the push front and push back function of canvas list class
	CanvasList list;
  Shape *shape = new Shape(3, 5);
	list.push_front(shape);//pushes new shape infront
  REQUIRE(list.size() == 1);//checks if size is 1
  shape = new Circle(6, 7, 7);//creates a new circle shape
	list.push_front(shape);//puhses shape infront of list
  REQUIRE(list.size() == 2);//checks if size is 3
	shape = new Rectangle(0111, 1022);//creates new rectangle
	list.push_back(shape);
  REQUIRE(list.size() == 3);//checks if size is 4
	shape = new RightTriangle(1222, 2222, 11113, 42222);
	list.push_front(shape);
  REQUIRE(list.size() == 4);//checks if size is 5
}

TEST_CASE("CanvasList delete elements functions"){//test that is testing the pop front and pop back function in the canvas list class
	CanvasList list;
  Shape *shape = new Shape(1232, 3212412);
	list.push_front(shape);//pushes new shape infront
  shape = new Circle(8221, 94124, 9342);//creates a new circle shape
	list.push_front(shape);//puhses shape infront of list
	delete list.pop_back();//deletes the last element
  REQUIRE(list.size() == 1);//checks if size is 1 since we subtract one to the list
	delete list.pop_front();//deletes first element in list
  REQUIRE(list.size() == 0);//checks if size is 0 since we should have deleted all nodes in list
}

TEST_CASE("Finding at and shape at functions"){//test that is testing the shape at and find at functions of the canvas list
	CanvasList list;
  Shape *shape = new Shape(2, 32);
	list.push_front(shape);//pushes new shape infront
  shape = new Circle(8, 9, 9);//creates a new circle shape
	list.push_front(shape);//puhses shape infront of list
  shape = new Rectangle(0111, 1022);//creates new rectangle
	list.push_back(shape);//pushes rectangle to the list
	int loc = list.find(2,32);
  REQUIRE(loc == 1);//checks if shape is found within the list and is in index 1
  loc = list.find(2,3222);
  REQUIRE(loc == -1);//checks to make sure it doesnt find a certain shape with the x value of 2 and y value of 3222
}

TEST_CASE("Inserting and deleting at an index"){//test that is testing the insert after and remove at functions
	CanvasList list;
  Shape *shape = new Shape(999, 4314);
	list.push_front(shape);//pushes new shape infront
  shape = new Circle(8, 9, 9);//creates a new circle shape
	list.push_front(shape);//puhses shape infront of list
	list.insertAfter(1, new Rectangle(3,4,5,5));//adds rectangle after index 1
  int index = list.find(3,4);
  REQUIRE(index == 2);//checks if shape is found within the list and is in index 2
	list.removeAt(0);//removes node at index 0
  index = list.find(8,9);//finds shape with x that is 8 and y that is 9
  REQUIRE(index == -1 );//checks if shape is not found since we deleted the first shape in the list
	list.removeAt(452341231);//removes at the index
	REQUIRE(list.size() == 2);//checks for list size to make sure nothing was removed since that's not a valid index
}

TEST_CASE("Clearing and making a copy of the canvas list"){//testing the clear function and the copy constructor of the canvas list
	CanvasList list;
	CanvasList second = list;//calls copy constructor 
  REQUIRE(list.size()==second.size());//checks if the size is the same between the lists
  REQUIRE(list.front()==second.front());//checks the pointer to the first node is the same
	list.clear();//clears the linked list
	REQUIRE(list.size()==0);//checks if the size is 0 since we clear
  REQUIRE(list.front()==0);//checks if pointer is 0 since we clear
}

TEST_CASE("Testing operator function "){//testing the operator= function in the canvas list 
	CanvasList list;
  CanvasList list2;
  Shape *shape = new Shape(124312, 3232);
	list.push_front(shape);//pushes new shape infront
  shape = new Circle(38, 92, 92);//creates a new circle shape
	list.push_front(shape);//puhses shape infront of list
  shape = new Rectangle(022111, 10223213,1212312,1231231);//creates new rectangle
  list2 = list;//calls the opeartor function 
  REQUIRE(list.size()==list2.size());//checks if the size is the same between the lists
  REQUIRE(list.front()!=list2.front());//checks the pointer to the first node is not the same
}

TEST_CASE("Testing all the functions at once "){//testing all the functions in the canvas list
  CanvasList list;
  CanvasList list2;
  Shape *shape = new Shape(999, 4314);
	list.push_front(shape);//pushes new shape infront
  shape = new Circle(8123,31239, 9213);//creates a new circle shape
	list.push_front(shape);//puhses shape infront of list
	list.insertAfter(1, new Rectangle(78,999,767,5111));//adds rectangle after index 1
  int index = list.find(32,42);
  REQUIRE(index == -1);//checks if shape is not found within the list
	list.removeAt(0);//removes node at index 0
  index = list.find(8123,31239);//finds shape with x that is 8123 and y that is 31239
  REQUIRE(index == -1 );//checks if shape is not found since we deleted the first shape in the list
	list.removeAt(452341231);//removes at the index
	REQUIRE(list.size() == 2);//checks for list size to make sure nothing was removed since that's not a valid index
  list.push_front(shape);//pushes new shape infront
  shape = new Circle(33123128, 931232, 92312312);//creates a new circle shape
	list.push_front(shape);//puhses shape infront of list
  shape = new Rectangle(122, 22,23,42);//creates new rectangle
  list2 = list;//calls the opeartor function 
  REQUIRE(list.size()==list2.size());//checks if the size is the same between the lists
  REQUIRE(list.front()!=list2.front());//checks the pointer to the first node is not the same
  list.clear();//clears the linked list
	REQUIRE(list.size()==0);//checks if the size is 0 since we clear
  REQUIRE(list.front()==0);//checks if pointer is 0 since we clear
  list.push_front(shape);//pushes new shape infront
  shape = new Circle(8222, 22229, 22229);//creates a new circle shape
	list.push_front(shape);//puhses shape infront of list
  shape = new Rectangle(01112,32222,312123,4321412);//creates new rectangle
	list.push_back(shape);//pushes rectangle to the list
	index = list.find(01112,32222);
  REQUIRE(index == 2);//checks if shape is found within the list and is in index 2
  index = list.find(222222,32221222);
  REQUIRE(index == -1);//checks to make sure it doesnt find a certain shape with the x value of 222222 and y value of 32221222
}