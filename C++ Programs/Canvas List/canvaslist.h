
#pragma once
#include "shape.h"
#include <iostream>
using namespace std;
///////////////////////////////////
//this is a header file that where we will implement the linked list that is our canvas
//the purpose is to make a list and be able to store the shapes as values.
class ShapeNode//shape node class
{
public:
    Shape* value;//pointer of the value of the node
    ShapeNode* next;//pointer to the next node in the list
};

class CanvasList//canvas linked list
{
private://data members
    int listSize;
    ShapeNode* listFront;

public:
    CanvasList();//default constructor 
    CanvasList(const CanvasList& other);//copy constructor
    CanvasList operator=(const CanvasList&other);

    virtual ~CanvasList();//destructor
    void clear();//clears out the list

    void insertAfter(int index, Shape* Nodes);
    void push_front(Shape* head);//pushes the node infront of the list
    void push_back(Shape* head);//pushes node at the end of the list

    void removeAt(int index);//removes 
    Shape* pop_front();//deletes the front node
    Shape* pop_back();//deletes the end node

    ShapeNode* front() const;//returns the front node
    bool isempty() const;//checks if list is empty
    int size() const;//returns size of list

    int find(int x, int y) const;//finds the index of shape with x and y 
    Shape* shapeAt(int index) const;//finds the shape at a index

    void draw() const;//prints information of all shapes in list
    void printAddresses() const;//prints addresses of all nodes and shape nodes
};

CanvasList::CanvasList() {//default constructor that intiliazes all values
    listSize = 0;
    listFront = nullptr;
}

CanvasList::CanvasList(const CanvasList& other) {//copy constructor that makes a copy of data members and is a deep copy
    this->listSize = 0;//sets the size to zero since our push back function adds to the size
    this->listFront = nullptr;//sets pointer to null
    ShapeNode* iteratingNode = other.listFront;//creates a iterating node
    while (iteratingNode != nullptr) {//traveres through the other list
        push_back(iteratingNode->value->copy());//pushes back the shape object so it can be stored in the list
        iteratingNode = iteratingNode->next;//keeps traversing till null
    }
}

CanvasList::~CanvasList() {//destructor

}

void CanvasList::push_front(Shape* object){//function that prepends to the list
    ShapeNode* tempNode = new ShapeNode;//creates a new shape node
    tempNode->value = object;//sets the object of the shape as the value so we can access shape functions later on
    tempNode->next = listFront;//list front is added in the list
    listFront = tempNode;//sets the node as the new object
    listSize++;
    //delete tempNode -it crashes program
}

ShapeNode* CanvasList::front()const {//function that returns the front of the list value
    return listFront;
}

int CanvasList::size()const {//function that returns size of the list
    return listSize;
}

bool CanvasList::isempty()const {//function that checks if the list is empty
    if (listSize == 0) {//checks if there are any nodes in the linked list
        return true;
    }

    else {//if list isnt empty returns false
        return false;
    }
}

void CanvasList::push_back(Shape* Node){//function that adds a shape node to the end of the canvas list
    ShapeNode* tempNode = new ShapeNode;//creates a tempoary node that will store the shape values
    tempNode->value = Node;//sets the shape node as the list value
    tempNode->next = NULL;//sets null the the next node since we will be adding at the end of list we must make sure it will be null after that
    if (isempty()){//checks if the list is empty
        listFront = tempNode;//sets the node at the end which is the front since no nodes
    }
               
    else {//if list is greater than 0(more nodes in the list)
        ShapeNode* tempNode2 = listFront;//sets temporary node to the front
        while (tempNode2->next != NULL){//iterates through the list until it reaches the end
            tempNode2 = tempNode2->next;//keeps moving to next node until it breaks out of loop
        }
        tempNode2->next = tempNode;//once we break off loop we have reached the end so we add node at the end
        }
    //delete tempNode-it crashes program
    listSize++;
}

void CanvasList::draw()const {//function that draws the canvas which prints all the shapes info in the linked list
    ShapeNode* iteratorNode = listFront;//sets iterator node to the front
    while (iteratorNode != NULL){//iterates through the list until it reaches the end
        iteratorNode->value->printShape();//prints info for each shape in the canvas list
        iteratorNode = iteratorNode->next;//keeps moving to next node until it reaches the end of the list
    }
    delete iteratorNode;
}

void CanvasList::insertAfter(int index, Shape *Nodes){//function that adds a node after the index number
    if (index < 0 || index >= listSize) {//checks to make sure it's within the 
    }

    else{
        ShapeNode *iteratingNode = listFront;//create a iterating node
        for (int i = 0; i < index; i++){//for loop to keep itertating until we reach the index
            iteratingNode = iteratingNode->next;
        }
            ShapeNode *addingNode = new ShapeNode();//creating a new node so we can add into the list 
            addingNode->value = Nodes;//stores the shape info into the node
            addingNode->next = iteratingNode->next;//moves to the node after the index 
            iteratingNode->next = addingNode;//adds the node
            //delete addingNode -it crashes program
            listSize++;
    }
}

Shape* CanvasList::pop_back(){//function that returns a pointer to the shape info for the last element to delete 
     if (listFront == NULL) {//checks to see if the list is empty
        return NULL;
    }

     else {
        ShapeNode* tempNode = NULL;//temp node to be able to hold the list once end node is deleted
        ShapeNode* iteratingNode = listFront;//iterating node that is set to the front of the list
        while (iteratingNode->next != NULL) {//while loop that traverses through the list and stops at last node
            tempNode = iteratingNode;//copies the nodes
            tempNode->value = iteratingNode->value;//copies shape objects
            iteratingNode = iteratingNode->next;//continues to next node
        }
        Shape* value = iteratingNode->value;//gets the end shape memory address
        if (tempNode == NULL) {//checks to make sure tempNode isnt null
            listFront = NULL;//sets list front to null
        } 
        else {
            tempNode->next = NULL;//sets the end node to be NULL after since last node will be deleted
        }
        delete iteratingNode;//deletes the node at the end but not shape
        
        listSize--;
        return value;//returns pointer of the shape at the end of the list
    }
}

Shape* CanvasList::pop_front(){//function that returns the shape pointer in a list to delete
    if (isempty()){//checks to see if the list is empty
        return NULL;
    }

    Shape* frontShape = listFront->value;//gets the value of the shape in the first node
    ShapeNode* temp = listFront;//creates new temp to get access to the list
    listFront = listFront->next;//list front moves to next node since first one is deleted
    delete temp;//deletes temp since its no longer needed 
    listSize--;
    return frontShape;//returns the pointer of the shape in front of the list
}

void CanvasList::removeAt(int index){//function that removes a node at a index
if(index < 0 || index > listSize) {//checks to make sure it's within the index of list
}

else{
     ShapeNode* temp = listFront; //create temp node
     if (index == 0) {//checks if its the beginning of the node
        listFront = listFront->next;//moves the listfront to the next node
        temp->next = NULL;//makes sure end equals null
        listSize--;
        delete temp; //deletes node
    }
    else {
        for (int i = 0; i < index - 1; i++) {//iterates through the list
            temp = temp->next;
        }
        ShapeNode* nodeAtIndex = temp->next; //creates a new node which is where the index is
        temp->next = temp->next->next;//moves the other nodes
        nodeAtIndex->next = NULL;//sets the end node to be nULL
        listSize--;
        delete nodeAtIndex;//deletes the node
    }
}
}

int CanvasList::find(int x2 , int y2)const{//function that returns the index of the element at the certain x and y
    ShapeNode* iteratorNode = listFront;//sets iterator node to the front
    int counter = 0; 
    while (iteratorNode != NULL) {//iterates through the list until it reaches the end
        if(iteratorNode->value->getX()==x2 && iteratorNode->value->getY()==y2){//checks the list until the x value and y value shape is found
            return counter;
        }
        iteratorNode = iteratorNode->next;//keeps moving to next node until it reaches the end of the list
        counter++;
    }
    delete iteratorNode;
    return -1;//if x and y isnt found then return -1
}


Shape* CanvasList::shapeAt(int index)const{//function that returns the shape at the index
 if (index < 0 || index > listSize) {//checks to make sure the index is within the list size
     return nullptr;
 }
 else{
    ShapeNode* iteratorNode = listFront;//sets iterator node to the front
    int counter = 0;
    while (iteratorNode!= NULL){//iterates through the list until it reaches the end
       if(counter == index){//checks when the index is the same as the counter
            return iteratorNode->value;//returns the shape at the index
       }
       iteratorNode = iteratorNode->next;//moves on to next node
       counter++;
    }
    delete iteratorNode;
 }
   return nullptr;//returns nullptr if nothing is found at the wanted index
}

void CanvasList::printAddresses() const{//function that prints the addresses of the node and shape node
    ShapeNode* iteratorNode = listFront;//sets iterator node to the front
    while (iteratorNode != NULL){//iterates through the list until it reaches the end
      cout << "Node Address: " <<iteratorNode << " Shape Address: " << iteratorNode->value << endl;//prints the addresses
      iteratorNode = iteratorNode->next;//iterates to the next node
    }
    delete iteratorNode;
}

void CanvasList::clear(){//clear function that deletes the internal shapes and memory
   ShapeNode* iteratorNode = listFront;//creates iterator node
   ShapeNode* iteratorNode2= nullptr;//creates another iterator node
   while (iteratorNode != NULL){//while loop the traverses throught the list
       iteratorNode2 = iteratorNode->next;//moves to the next value
       delete iteratorNode->value;//deletes shape in node
       delete iteratorNode;//deletes the iterator node
       iteratorNode = iteratorNode2;
   }
   delete iteratorNode2;
    listSize = 0;//sets list to zero and list front to null
    listFront = NULL;
}

CanvasList CanvasList::operator=(const CanvasList&other){//operator function 
    this->listSize = 0;//sets the size to zero since our push back function adds to the size
    this->listFront = nullptr;//sets pointer to null
    ShapeNode* iteratingNode = other.listFront;//creates a iterating node
    while (iteratingNode != nullptr) {//traveres through the other list
        push_back(iteratingNode->value->copy());//pushes back the shape object so it can be stored in the list
        iteratingNode = iteratingNode->next;//keeps traversing till null
    }
    return *this;//returns a pointer to the list
}