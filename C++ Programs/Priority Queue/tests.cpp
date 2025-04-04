/// @file tests.cpp
/// @date March 17, 2023
/**------------------------------------------
//  Project 5 - Priority Quene
    Course: CS 251, Spring 2023.
    System: Visual Studio Code 2023
    Author: Alejandro Bravo
 ---------------------------------------------**/
/// Provided testing file to implement framework based tests in. The examples
/// below demonstrates a basic empty test in each framework with a single
/// assertion. The version uses the supplied catch.hpp file in starter code.
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023
// Catch 1.0 Framework Testing
#define CATCH_CONFIG_MAIN
#include "priorityqueue.h"
#include "catch.cpp"
using namespace std;
TEST_CASE("Testing default constructor"){//testing default constructor to make sure private data members are intialized
    priorityqueue<int>container;//calls default constructor of a integer priority quene
    REQUIRE(container.Size()==0);//checks if size is 0
    REQUIRE(container.getRoot() == nullptr);//cehcks if root is null
    priorityqueue<string>container2;//calls default constructor of a string priority quene
    REQUIRE(container2.Size()==0);//checks if size is 0
    REQUIRE(container2.getRoot() == nullptr);//cehcks if root is null
    priorityqueue<bool>container3;//calls default constructor of a bool priority quene
    REQUIRE(container3.Size()==0);//checks if size is 0
    REQUIRE(container3.getRoot() == nullptr);//checks to make sure root is null
    priorityqueue<long>container4;//calls default constructor of a long priority quene
    REQUIRE(container4.Size()==0);//checks if size is 0
    REQUIRE(container4.getRoot() == nullptr);//cehcks if root is null
    priorityqueue<char>container5;//calls default constructor of a char priority quene
    REQUIRE(container5.Size()==0);//checks if size is 0
    REQUIRE(container5.getRoot() == nullptr);//cehcks if root is null
    priorityqueue<double>container6;//calls default constructor of a double priority quene
    REQUIRE(container6.Size()==0);//checks if size is 0
    REQUIRE(container6.getRoot() == nullptr);//cehcks if root is null
    priorityqueue<short>container7;//calls default constructor of a short priority quene
    REQUIRE(container7.Size()==0);//checks if size is 0
    REQUIRE(container7.getRoot() == nullptr);//cehcks if root is null
    priorityqueue<float>container8;//calls default constructor of a float priority quene
    REQUIRE(container8.Size()==0);//checks if size is 0
    REQUIRE(container8.getRoot() == nullptr);//cehcks if root is null
    priorityqueue<wchar_t>container9;//calls default constructor of a wide char priority quene
    REQUIRE(container9.Size()==0);//checks if size is 0
    REQUIRE(container9.getRoot() == nullptr);//cehcks if root is null
}

TEST_CASE("Testing enquene function integers only"){//testing that the enquene function is working correctlty with ints even with duplicates
    priorityqueue<int>container;//calls default constructor
    REQUIRE(container.Size()==0);//checks if values are intiliazed
    container.enqueue(3,1);//adds a value of 3 with priority 1
    REQUIRE(container.Size()==1);//checks to see if node is added to the tree
    container.enqueue(3213,3);//adds another node
    REQUIRE(container.Size()==2);
    container.enqueue(2,3);//adds a duplicate node
    REQUIRE(container.Size()==3);//checks that it's still inserted
    container.enqueue(334234,133);
    REQUIRE(container.Size()==4);//checks to see if node is added to the tree
    container.enqueue(3213,33);//adds another node
    REQUIRE(container.Size()==5);
    container.enqueue(21231,3);//adds a duplicate node
    REQUIRE(container.Size()==6);
    container.enqueue(0,0);//adds another node
    REQUIRE(container.Size()==7);
    container.enqueue(23,1);//adds a duplicate node
    REQUIRE(container.Size()==8);
    container.enqueue(212,-2);//adds another node
    REQUIRE(container.Size()==9);
    container.enqueue(-23,-3);//adds a duplicate node
    REQUIRE(container.Size()==10);
}

TEST_CASE("Testing enquene function strings only"){//testing that the enquene function is working correctlty with strings even with duplicates
    priorityqueue<string>container;//calls default constructor
    string tester= "";
    container.enqueue("dasda",3);//adds a root node
    REQUIRE(container.Size()==1);
    container.enqueue("easy",3);//adds a duplicate priority node
    REQUIRE(container.Size()==2);
    container.enqueue("medium",4);//adds a another node
    REQUIRE(container.Size()==3);
    container.enqueue("hard",1);//adds a another node
    REQUIRE(container.Size()==4);
    container.enqueue("hard",2);//adds a another node with same string value
    REQUIRE(container.Size()==5);
    container.enqueue("test",6);//adds a another node
    REQUIRE(container.Size()==6);
    container.enqueue("testing",2);//adds a another 
    REQUIRE(container.Size()==7);
    container.enqueue("testing",2);//adds a another node with same string value and duplicate
    REQUIRE(container.Size()==8);
    container.enqueue(tester,2);//adds a another node with same string value
    REQUIRE(container.Size()==9);
    container.enqueue(" ",6);//adds a another node with same string value
    REQUIRE(container.Size()==10);
}

TEST_CASE("Testing enquene function doubles only"){//testing that the enquene function is working correctlty with doubles even with duplicates
    priorityqueue<double>container;//calls default constructor
    container.enqueue(1.2222,2);//adds a double priority node
    REQUIRE(container.Size()==1);
    container.enqueue(2.4324,2);//adds a double duplicate priority node
    REQUIRE(container.Size()==2);
    container.enqueue(1.2222,2);//adds a double priority node
    REQUIRE(container.Size()==3);
    container.enqueue(1.2222,5);//adds a double duplicate value priority node
    REQUIRE(container.Size()==4);
    container.enqueue(1.2222,5);//adds a double duplicate value and duplicate priority node
    REQUIRE(container.Size()==5);
    container.enqueue(9.564563,1000);//adds a double priority node
    REQUIRE(container.Size()==6);
    container.enqueue(213123123.2,1000);//adds a double priority node
    REQUIRE(container.Size()==7);
}

TEST_CASE("Testing enquene function char only"){//testing that the enquene function is working correctlty with chars even with duplicates
    priorityqueue<char>container;//calls default constructor
    container.enqueue('c',2);//adds a char priority node
    REQUIRE(container.Size()==1);
    container.enqueue('s',2);//adds a char duplicate priority node
    REQUIRE(container.Size()==2);
    container.enqueue('r',3);//adds a char priority node
    REQUIRE(container.Size()==3);
    container.enqueue('r',3);//adds a char priority duplicate node and a duplicate value node
    REQUIRE(container.Size()==4);
    container.enqueue('1',3);//adds a char number node and a duplicate value node
    REQUIRE(container.Size()==5);
    container.enqueue('3',7);//adds a char priority node
    REQUIRE(container.Size()==6);
}

TEST_CASE("Testing enquene function bool only"){//testing that the enquene function is working correctlty with bool even with duplicates
    priorityqueue<bool>container;//calls default constructor
    for(int i =0; i < 50; i++){//for loop testing bool with a different priority each time
        container.enqueue(true,i);
        REQUIRE(container.Size()==1+i);

    }

    for(int i =0; i < 50; i++){//for loop testing bool with a the same priority but different value each time
        container.enqueue(false,i);
        REQUIRE(container.Size()==51+i);
    }    
    priorityqueue<bool>container2;//calls default constructor
    REQUIRE(container2.Size()==0);
    container2.enqueue(true,7);//adds a bool priority node
    REQUIRE(container2.Size()==1);
    container2.enqueue(true,7);//adds a bool duplicate and same value priority node
    REQUIRE(container2.Size()==2);
}

TEST_CASE("Testing enquene function float only"){//testing that the enquene function is working correctlty with float even with duplicates
    priorityqueue<float>container;//calls default constructor
    for(int i =0; i < 50; i++){//for loop testing bool with a different priority each time and different value
        container.enqueue(.12313+i,i);
        REQUIRE(container.Size()==1+i);
    }

    for(int i =0; i < 50; i++){//for loop testing bool with a the same priority but different value each time
        container.enqueue(.985774+i,i);
        REQUIRE(container.Size()==51+i);
    }    

    for(int i =0; i < 50; i++){//for loop testing bool with a the same priority and same value each time
        container.enqueue(.985774,i);
        REQUIRE(container.Size()==101+i);
    }    
    priorityqueue<float>container2;//calls default constructor
    container2.enqueue(.985774,1);
    REQUIRE(container2.Size()==1);
    container2.enqueue(.985774,1);//node with same priority and value
    REQUIRE(container2.Size()==2);
    container2.enqueue(.2,1);//node with same priority and different value
    REQUIRE(container2.Size()==3);
    container2.enqueue(.2,4);//node with same value but different priority
    REQUIRE(container2.Size()==4);  
}

TEST_CASE("Testing toString function with ints"){//testing that the toString function is working correctlty with ints even with duplicates
vector<int>prioritys;//intiliaze two vectors holding value and priority
vector<int>values;
int n = 9;//size of array
int vals[] = {123123, 13126, 112317, 63213, 7123, 1238, 55769, 98792, 78971};//declared values
int prs[] = {1, 1, 1, 1, 1, 2, 2, 2, 2};
priorityqueue<int> pq;//integer quene declared
for (int i = 0; i < 9; i++) {
    pq.enqueue(vals[i], prs[i]);//adds to the enquene
    prioritys.push_back(prs[i]);//adds to the vectors
    values.push_back(vals[i]);
}

stringstream ss;
    for (int j = 0; j < values.size(); j++){//prints message of to outstream using data from vectors
        ss << prioritys.at(j) << " value: " << values.at(j) << endl;
    }
REQUIRE(pq.toString()== ss.str());//checks to make sure both strings are the same
   pq.begin();
       
}

TEST_CASE("Testing toString function with strings"){//testing that the toString function is working correctlty with strings even with duplicates
vector<int>prioritys;
vector<string>values;
int n = 9;//size of array
string vals[] = {"I", "LOVE", "THIS", "PROJECT", "VERY", "FUN", "AND", "TREES", "GREAT"};//string array
int prs[] = {4, 67,87, 99, 100, 104, 107, 123, 23123};//int array
priorityqueue<string> pq;//string quene
for (int i = 0; i < 9; i++) {
    pq.enqueue(vals[i], prs[i]);//adds strings to quene
    prioritys.push_back(prs[i]);//adds prioirty numbers to vector
    values.push_back(vals[i]);//adds values to vector
}

stringstream ss;
    for (int j = 0; j < values.size(); j++){
        ss << prioritys.at(j) << " value: " << values.at(j) << endl;//adds values to the outstream
    }
REQUIRE(pq.toString()== ss.str());//compares the strings 
}

TEST_CASE("Testing toString function with bools"){//testing that the toString function is working correctlty with bools even with duplicates
vector<int>prioritys;
vector<bool>values;//bool vector that holds bool values
int n = 12;//array size
bool vals[] = {true, true, false, true, false, true, false, true, false, false,false,false};//array with bool values
int prs[] = {4, 67,87, 99, 100, 104, 107, 123, 23123,3123123,321312313,565654644};//priority numbers
priorityqueue<bool> pq;//priority quene with bool variables
for (int i = 0; i < n; i++) {
    pq.enqueue(vals[i], prs[i]);//fills enquene with bool variables
    prioritys.push_back(prs[i]);//fills vector with prioirty numbers
    values.push_back(vals[i]);//fills vector with bool values
}

stringstream ss;
    for (int j = 0; j < values.size(); j++){
        ss << prioritys.at(j) << " value: " << values.at(j) << endl;//gets values from vectors and stores to the outstream
    }
REQUIRE(pq.toString()== ss.str());//checks if the strings equal eachother
}

TEST_CASE("Testing overload function with ints"){//testing that the overload function is working correctlty with ints even with duplicates
    priorityqueue<int>container;//calls default constructor
    priorityqueue<int>container2;//calls default constructor
    for(int i= 0 ;i<8;i++){//for loop that adds to container
        container.enqueue(i,i+5);

    }
     container.enqueue(3213,3);//adds another node
     container.enqueue(2,3);//adds a duplicate node
    container2 = container;//testing overload function
    stringstream ss;
    ss<< 3 << " value: " << 3213 <<endl;//adds values to the string stream
    ss<< 3 << " value: " << 2 <<endl;
    for(int i= 0 ;i<8;i++){
        ss << i+5 << " value: " << i << endl;
    }
   REQUIRE(container2.toString()== ss.str());//compares the strings 
   REQUIRE(container2.Size()==10);//checks to make sure size updated
  container.clear();    
}

TEST_CASE("Testing == operator function with integers"){//testing that the overload function is working correctlty with ints even with duplicates
   priorityqueue<int> pq;
   priorityqueue<int> pq2;
//    REQUIRE(pq==pq2);//checks to make sure both bst are the same when empty
//    pq.enqueue(1,2);
//   // REQUIRE(!(pq==pq2));//checks to make bst arent the same
//       pq2.enqueue(1,2);
    pq2.clear();
    pq.clear();
   for(int i = 0 ; i < 50; i++){
    pq2.enqueue(i,i+5);//adds values to the enquene
   }
    pq2.enqueue(1,1);//node with same priority and value
    pq2.enqueue(2,1);//node with same priority and different value
    pq2.enqueue(3,1);//node with same value but different priority
      //REQUIRE(pq2 == pq);//checks to make sure theyre the same 
    pq.clear();
    pq = pq2;
     pq.clear();
    cout << pq.Size() << endl;
    cout << pq2.Size();
    pq2.clear();
   REQUIRE(pq2.Size()==0);//checks to make sure size updated
}

TEST_CASE("Testing begin and next functions"){
  priorityqueue<int> pq;
    pq.enqueue(10, 2);
    pq.enqueue(20, 1);
    pq.enqueue(30, 3);
    pq.enqueue(40, 2);
    pq.enqueue(50, 1);
    int value;
    int priority;
    pq.begin();
    while (pq.next(value, priority)) {
        cout << "Value: " << value << ", Priority: " << priority << endl;
    }
    cout << "Value: " << value << ", Priority: " << priority << endl;
}

TEST_CASE("Testing dequene function"){
    vector<int>prioritys;//intiliaze two vectors holding value and priority
vector<int>values;
int n = 9;//size of array
int vals[] = {123123, 13126, 112317, 63213, 7123, 1238, 55769, 98792, 78971};//declared values
int prs[] = {1, 1, 1, 1, 1, 2, 2, 2, 2};
 priorityqueue<int> pq;//integer quene declared
for (int i = 0; i < 8; i++) {
    pq.enqueue(vals[i], prs[i]);//adds to the enquene
    prioritys.push_back(prs[i]);//adds to the vectors
    values.push_back(vals[i]);
}
REQUIRE(pq.dequeue() == 123123);
pq.clear();

pq.enqueue(3,1);
pq.enqueue(4,2);
pq.enqueue(5,55);
 REQUIRE(pq.dequeue() == 3);
}

TEST_CASE("Sammy Haddad, shadd3@uic.edu TEST CASE: enqueue, dequeue, toString, size") {//Sammy Haddad, shadd3@uic.edu test case
    map<int, vector<int> > map;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};//value array
    int prs[] = {1, 2, 3, 2, 2, 2, 2, 3, 3};//array of prioritys
    priorityqueue<int> pq;
    for (int i = 0; i < n; i++) {//populates map and enquenes
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
    }
    REQUIRE(pq.Size() == 9);//checks size
    for (auto e: map) {
        int priority = e.first;
        vector <int> values = e.second;
        for (size_t j = 0; j < values.size(); j++){
            cout << "S";
            REQUIRE(pq.dequeue() == values[j]);//checks to make sure dequene function works
            
        }
    }
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("Testing Peek Function"){
      map<int, vector<int> > map;
    int n = 9;
    int vals[] = {435, 1435, 417, 36, 227, 348, 42349, 24232, 342};//value array
    int prs[] = {1, 4, 3, 4, 4, 5, 6, 7, 8};//array of prioritys
    priorityqueue<int> pq;
    for (int i = 0; i < n; i++) {//populates map and enquenes
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
        REQUIRE(pq.peek()==vals[0]);
    }
}