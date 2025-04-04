#include <iostream>
#include <stdexcept>
using namespace std;

class SequenceableCollection{
public: //defines public data memebers/functions
    int basicSize();//returns the size of the contiguous region currently allocated to the receiver            
    int size();//returns size of elements currently stored in the receiver                     
    SequenceableCollection& insertAt(int i, int x);//inserts x inside reciever before i posititon
    int find(int x);//returns index of where x is located                             
    SequenceableCollection& removeAt(int i);//deletes the element at posititon i          
    SequenceableCollection& iterate(int (*fn)(int));//applies function to each element in the reciever
    SequenceableCollection();//default constructor            
    SequenceableCollection(const SequenceableCollection& other); //copy constructor that performs deep copy
    SequenceableCollection(int x);//constructor that takes an intial element
    ~SequenceableCollection();//destructor 
    void display();//helper function to display the collection                   

private://defines private data members/functions
    int _start;//start variable to define where start of collection is       
    int _end;//end variable to define where end of collection is               
    int length;//stores length of the collection
    void grow();//non public function that allocates a new contiguous region of storage for the elements stored in the receiver
    int* data;//pointer to first element in array
};

