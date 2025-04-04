/**------------------------------------------
//  Project 3 - Sequenceable Collection
    Course: CS 474, Fall 2024.
    System: Visual Studio Code 2024
    Author: Alejandro Bravo
 ---------------------------------------------**/
#include "SequenceableCollection.cpp"//includes definitions of collection classes
#include <iostream>//for input/output
using namespace std;

int main() {
    SequenceableCollection collection; //creates class object and calls constructor
    cout << "default size: " <<collection.size() << endl; //checks default sizes
    cout << "default basic size: " <<collection.basicSize() << endl;

    collection.insertAt(0,1); //inserts element at index 0
    collection.insertAt(9,2); //invalid i so no value is inserted.
    collection.insertAt(1,2);
    collection.insertAt(2,3);
    collection.display(); //displays current array values so 1 2 3
    collection.insertAt(1,6);//insert where element is present 
    collection.display(); //correct output 1 6 2 3

    collection.removeAt(3);//removes 3
    collection.removeAt(3); //invalid i since index 3 no longer exists(out of bounds)
    collection.removeAt(6);//invalid out of bounds i   
    collection.display(); //should display 1 6 2

    for(int i = 0 ; i < 5; i++){//adds more to activate grow function
        collection.insertAt(i+3,10+i);
    }
    collection.display(); //should output 1 6 2 10 11 12 13 14
    cout<< "growing function called and new basic size: " <<collection.basicSize();//should output 16 meaning it doubled
    cout << "Current collection size: " << collection.size();//should output 8

    collection.removeAt(4);//removing after growth in index 4 (10)
    collection.insertAt(2,17);//adding elements after growth
    collection.insertAt(2,16);
    collection.display(); //should output 1 6 16 17 2 10 12 13 14

    cout << "element index: " << collection.find(1) <<endl;//should print 0
    cout << "element index: " << collection.find(121)<<endl;//finds nothing and returns -1
    cout << "element index: " << collection.find(4)<<endl;//finds nothing since it was deleted so returns -1

    SequenceableCollection collections(collection); //calls copy constructor
    cout<< "New object created with copy contructor" << endl;
    cout << "element index: " << collections.find(14) <<endl;//should print 8
    cout << "size: " <<collections.size() << endl; //checks default sizes with a parameter should print 9
    cout << "basic size: " <<collections.basicSize() << endl;//should still be 16
    collections.display();//should display  1 6 16 17 2 10 12 13 14 same as collection
    collection.display();

    SequenceableCollection* collections2 = new SequenceableCollection();//creates new object
    collections2->insertAt(0, 1);
    collections2->insertAt(1, 2);
    collections2->insertAt(2, 3);
    collections2->display(); //outputs: 1 2 3
    delete collections2;// calls the destructor and deletes the memory

    return 0;
}
