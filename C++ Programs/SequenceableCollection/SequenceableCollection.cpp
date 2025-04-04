#include "SequenceableCollection.h"//includes definitions of collection classes
#include <iostream>//for input/output
using namespace std;

int SequenceableCollection::basicSize(){//definition for basicSize function

    return length;//returns size of whole collection 
}

int SequenceableCollection::size(){//definition for size function 

    return  _end - _start + 1;//returns size of elements in collection that are occupied
}

SequenceableCollection& SequenceableCollection::insertAt(int i, int x){//definition for insertAt function
    int index = _start + i;

    if (i < 0 || i > size()){ //check if the index is valid (it must be between 0 and current size, inclusive)
        return *this; //does nothing
    }

    if (_end == length ){//if collection is full we make more room
        grow();  //calls grow to double the size of the array
    }

    for (int j = _end; j >= index; --j) { //shifts all elements to make space for new space
        data[j + 1] = data[j];  //Move element one position to the right
    }

    data[index] = x; //inserts element into the position we want
    ++_end;//adds to the end
    return *this;//returns changes
}

int SequenceableCollection::find(int x){//definition for find function
    int counter = 0; 
    for (int i = _start; i <= _end; ++i){ //iterates only between the start to end
        if (data[i] == x) { //looks for x value in array
            return counter;  //returns the index if the element is found
        }
        counter++;

    }
    return -1;//return -1 if not found 
}

SequenceableCollection& SequenceableCollection::removeAt(int i){//definition for removeAt function
    if (i < 0 || i >= size()) {
       return *this; //no changes are made if i is invalid
    }

    for (int j = _start + i; j < _end; ++j){ // shifts elements to fill the gap
        data[j] = data[j + 1];
    }

    --_end; //end is less now
    return *this;
}

SequenceableCollection& SequenceableCollection::iterate(int (*fn)(int)){//definition for iterate function
    //NO LONGER REQUIRED TO BE IMPLEMENTED...
    return *this;
}

SequenceableCollection::SequenceableCollection(){//definition for default constructor
    _start = 3;//initliaze values at the start   
    _end = 2;     
    length = 8;//should start with 8 elements
    data = new int[length];//create an array with 8 elements to store our values
    for (int i = 0; i < length; ++i){
        data[i] = 0;  //initliaze all values at 0
    }
   
}

SequenceableCollection::SequenceableCollection(const SequenceableCollection& other){//definition for copy constructor
    _start = other._start;//copies start and end from object
    _end = other._end;
    length = other.length;
    data = new int[length];//allocates memory of the length
    for (int i = 0; i < length; ++i){//initialize all elements to zero 
        data[i] = 0;  
    }
    for (int i = _start; i <= _end; ++i){//copies elements from array
        data[i] = other.data[i];  
    }
}

SequenceableCollection::SequenceableCollection(int x){//definition for constructor with start element
    _start = 3;//initliaze values at the start   
    _end = 3;     
    length = 8;//should start with 8 elements
    data = new int[length];//create an array with 8 elements to store our values
    for (int i = 0; i < length; ++i){
        data[i] = 0;  //initliaze all values at 0
    }
    data[_start] = x;//insert element as the start since only one value
}

SequenceableCollection::~SequenceableCollection(){//definition for destructor
    delete[] data; //deletes array
}

void SequenceableCollection::grow(){//definition for grow
    int newLength = length * 2;//doubles the size
    int* newData = new int[newLength];//creates new array with that size
    for (int i = _start; i <= _end; ++i) {//copies elements over
        newData[i] = data[i];
    }

    delete[] data; //deletes old array

    data = newData;//points to new array

    length = newLength;//sets the new length
}

void SequenceableCollection::display() {
    if (_end < _start){//checks to make sure its not empty
        cout << "The collection is empty." << endl;
        return;
    }
    cout << "Collection: ";
    for (int i = _start; i <= _end; ++i){//prints elemetns in collection
        cout << data[i] << " ";  
    }
    cout << endl; 
}