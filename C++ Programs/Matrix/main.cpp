/**------------------------------------------
//  Project 3 - Matrix Implementation
    Course: CS 251, Spring 2023.
    System: Visual Studio Code 2023
    Author: Alejandro Bravo
 ---------------------------------------------**/
#include <fstream>//for file reading
#include <iostream>//for input/output
#include <string> //to use string functions 
#include "mymatrix.h"
using namespace std;

int test1(mymatrix<int>matrix) {//tests size of default constructor
    int counter = 0;
    if (matrix.size() == 16) {//checks if size is correct
        counter++;
    }

    if (matrix.numrows() == 4) {//checks if number of rows are correct
        counter++;
    }

    return counter;
}


int test2(mymatrix<int>matrix) {//tests size of different size matrix
    int counter = 0;
    if (matrix.size() == 24) {//checks if size is correct
        counter++;
    }

    if (matrix.numrows() == 4) {//checks number rows
        counter++;
    }

    return counter;
}

int test3(mymatrix<int>matrix) {//tests growing cols and checks if shrink happens for default matrix
    int counter = 0;
    matrix.growcols(2, 8);//grows row 2 by 4 columns 
    if (matrix.size() == 20) {
        counter++;
    }

    if (matrix.numrows() == 4) {//makes sure row arent created
        counter++;
    }
    matrix.growcols(2, 2);//checks if it shrinks the matrix
    if (matrix.size() == 20) {//checks for same size again to see if shrinks
        counter++;
    }

    return counter;
}

int test4(mymatrix<int>matrix) {//tests growing cols and checks if shrink happens for parametized matrix
    int counter = 0;
    matrix.growcols(3, 20);//grows row 3 by 10 columns 
    if (matrix.size() == 110) {
        counter++;
    }

    if (matrix.numrows() == 10) {//makes sure the rows dont change
        counter++;
    }
    matrix.growcols(1, 9);//checks if it shrinks the matrix
    if (matrix.size() == 110) {//checks for same size again to see if shrinks
        counter++;
    }

    return counter;
}

int test5(mymatrix<int>matrix) {//tests grow function for default constructor 
    int counter = 0;
    matrix.grow(8, 8);//grows row and columns by 4
    if (matrix.size() == 64) {//checks if size is changed 
        counter++;
    }

    if (matrix.numrows() == 8) {//makes sure the rows change
        counter++;
    }
    matrix.growcols(6, 6);//checks if it shrinks the matrix
    if (matrix.size() == 64) {//checks for same size again to see if shrinks
        counter++;
    }

    return counter;
}

int test6(mymatrix<int>matrix) {//tests grow function for parametized  
    int counter = 0;
    matrix.grow(20, 20);//grows row and columns by 10
    if (matrix.size() == 400) {//checks if size is changed 
        counter++;
    }

    if (matrix.numrows() == 20) {//makes sure the rows change
        counter++;
    }
    matrix.growcols(1, 1);//checks if it shrinks the matrix
    if (matrix.size() == 400) {//checks for same size again to see if shrinks
        counter++;
    }

    return counter;
}

int test7(mymatrix<int>matrix) {//tests at function for default consttuctor 
    int counter = 0;
    if (matrix.at(2, 2) == 0) {//checks if value is default to 0
        counter++;
    }
    matrix.at(2, 3) = 1;//see if at changes value at row 2 column 3 
    if (matrix.at(2, 3) == 1) {//checks if value is changed
        counter++;
    }

    matrix.at(3, 3) = 5;//checks edges if value changes
    if (matrix.at(3, 3) == 5) {//checks if value is changed
        counter++;
    }

    return counter;
}

int test8(mymatrix<int>matrix) {//tests at function for parametized function
    int counter = 0;
    if (matrix.at(1, 1) == 0) {//checks if value is default to 0
        counter++;
    }
    matrix.at(2, 2) = 1;//see if at changes value at row 2 column 2 
    if (matrix.at(2, 2) == 1) {//checks if value is changed
        counter++;
    }

    matrix.at(1, 2) = 5;//checks edges if value changes
    if (matrix.at(1, 2) == 5) {//checks if value is changed
        counter++;
    }

    return counter;
}

int test9(mymatrix<int>matrix) {//tests operator function for default constructor
    int counter = 0;
    if (matrix(3, 3) == 0) {//checks if value is default to 0
        counter++;
    }
    matrix(2, 2) = 1;//see if at changes value at row 2 column 2 
    if (matrix(2, 2) == 1) {//checks if value is changed
        counter++;
    }

    matrix(1, 1) = 5;//checks edges if value changes
    if (matrix(1, 1) == 5) {//checks if value is changed
        counter++;
    }

    return counter;
}

int test10(mymatrix<int>matrix) {//tests operator function for default constructor
    int counter = 0;
    if (matrix(7, 7) == 0) {//checks if value is default to 0
        counter++;
    }
    matrix(7, 9) = 40;//see if at changes value at row 7 column 9 
    if (matrix(7, 9) == 40) {//checks if value is changed
        counter++;
    }

    matrix(4, 4) = 2000;//checks edges if value changes
    if (matrix(4, 4) == 2000) {//checks if value is changed
        counter++;
    }

    return counter;
}

int test11(mymatrix<int>matrix) {//tests scalar multiplication for default constructor
    int counter = 0;
    matrix.operator*(3);//mutiplys all values by 3
    if (matrix(2, 2) == 0) {//checks if value is default to 0 after scalar is still 0 since 0*3
        counter++;
    }
    matrix(1, 1) = 40;//see if at changes value at row 1 column 1
    matrix.operator*(10);

    if (matrix(1, 1) == 400) {//checks if value is changed
        counter++;
    }

    matrix(3, 3) = 2000;//checks edges if value changes
    matrix.operator*(5);
    if (matrix(3, 3) == 10000) {//checks if value is changed
        counter++;
    }

    return counter;
}

int test12(mymatrix<int>matrix) {//tests scalar multiplication for parametized constructor
    int counter = 0;
    matrix.operator*(5);//mutiplys all values by 5
    if (matrix(2, 2) == 0) {//checks if value is default to 0 after scalar is still 0 since 0*5
        counter++;
    }
    matrix(7, 7) = 20;//see if at changes value at row 1 column 1 
    matrix.operator*(10);

    if (matrix(7, 7) == 200) {//checks if value is changed
        counter++;
    }

    matrix(5, 6) = 72724;//checks edges if value changes
    matrix.operator*(5);
    if (matrix(5, 6) == 363620) {//checks if value is changed
        counter++;
    }

    return counter;
}

int test13(mymatrix<int>matrix,mymatrix<int>matrix2,mymatrix<int>matrix3) {//tests that matrix are rectangular
    int counter = 0;
    if( matrix.isRectangular1(matrix2) && matrix2.isRectangular2(matrix3)){
        counter++;
    }
    return counter;
 }

 int test16(mymatrix<int>matrix,mymatrix<int>matrix2,mymatrix<int>matrix3) {//tests that matrix are rectangular
    int counter = 0;
     matrix3 = matrix*matrix2;//mutiplys matrix
    if( matrix3.size()==6){//checks that size of new matrix is right
        counter++;
    }
    return counter;
 }

 int test14(mymatrix<int>matrix) {//tests mutiple functions for default constructor
    int counter = 0;
    matrix.grow(5,5);//checks grow function 
    if (matrix.size() == 25) {
        counter++;
    }
    matrix.growcols(3,25);//checks grow columns function
    if (matrix.size() == 45) {
        counter++;
    }

    if (matrix.numrows() == 5) {
        counter++;
    }

     matrix.at(3,23)= 2014929;//checks at function
    if (matrix(3,23) == 2014929) {//checks operator function
        counter++;
    }

    matrix.operator*(5);//mutiplys all values by 5
    if (matrix(2, 2) == 0) {//checks if value is default to 0 after scalar is still 0 since 0*5
        counter++;
    }
    matrix(2, 2) = 20;//see if at changes value at row 2 column 2 
    matrix.operator*(10);

    if (matrix(2, 2) == 200) {//checks if value is changed
        counter++;
    }

    matrix(1, 1) = 72724;//checks edges if value changes
    matrix.operator*(5);
    if (matrix(1, 1) == 363620) {//checks if value is changed
        counter++;
    }

    return counter;
}

int test15(mymatrix<int>matrix) {//tests mutiple functions for parametized constructor
    int counter = 0;
    matrix.grow(1000,1000);//checks grow function 
    if (matrix.size() == 1000000) {
        counter++;
    }
    matrix.growcols(3,25);//checks grow columns function doesnt shrink
    if (matrix.size() == 1000000) {
        counter++;
    }

    if (matrix.numrows() == 1000) {
        counter++;
    }

     matrix.at(3,23)= 9872377;//checks at function
    if (matrix(3,23) == 9872377) {//checks operator function
        counter++;
    }

    matrix.operator*(5);//mutiplys all values by 5
    if (matrix(999,999) == 0) {//checks if value is default to 0 after scalar is still 0 since 0*5
        counter++;
    }
    matrix(454,454) = 4000;//see if at changes value at row 2 column 2 
    matrix.operator*(10);

    if (matrix(454, 454) == 40000) {//checks if value is changed
        counter++;
    }

    matrix(44, 44) = 75465;//checks edges if value changes
    matrix.operator*(5);
    if (matrix(44, 44) == 377325) {//checks if value is changed
        counter++;
    }
    return counter;
}

int main() {
    mymatrix<int>matrix;//default matrix
    mymatrix<int>matrix2(4, 6);//changed value matrix
    mymatrix<int>matrix3(10, 10);//large matrix
    //when calling functions and passing the matrix then the copy consructor is always being tested
    if (test1(matrix) == 2) {//tests defualt constructor
        cout << "Congrats you passed test 1" << endl;

    }

    else {
        cout << "You failed one or more cases in test 1" << endl;
    }

    if (test2(matrix2) == 2) {//tests different size matrix
        cout << "Congrats you passed test 2" << endl;

    }

    else {
        cout << "You failed one or more cases for test2" << endl;
    }

    if (test3(matrix) == 3) {//tests default construcor
        cout << "Congrats you passed test 3" << endl;

    }

    else {
        cout << "You failed one or more cases for test3" << endl;
    }

    if (test4(matrix3) == 3) {//tests different size matrix
        cout << "Congrats you passed test 4" << endl;

    }

    else {
        cout << "You failed one or more cases for test 4" << endl;
    }

    if (test5(matrix) == 3) {//tests different size matrix
        cout << "Congrats you passed test 5" << endl;

    }

    else {
        cout << "You failed one or more cases for test 5" << endl;
    }

    if (test6(matrix2) == 3) {//tests different size matrix
        cout << "Congrats you passed test 6" << endl;
    }

    else {
        cout << "You failed one or more cases for test 6" << endl;
    }

    if (test7(matrix) == 3) {//tests different size matrix
        cout << "Congrats you passed test 7" << endl;
    }

    else {
        cout << "You failed one or more cases for test 7" << endl;
    }

    if (test8(matrix2) == 3) {//tests different size matrix
        cout << "Congrats you passed test 8" << endl;
    }

    else {
        cout << "You failed one or more cases for test 8" << endl;
    }

    if (test9(matrix) == 3) {//tests default constructor matrix
        cout << "Congrats you passed test 9" << endl;
    }

    else {
        cout << "You failed one or more cases for test 9" << endl;
    }

    if (test10(matrix3) == 3) {//tests different size matrix
        cout << "Congrats you passed test 10" << endl;
    }

    else {
        cout << "You failed one or more cases for test 10" << endl;
    }

    if (test11(matrix) == 3) {//tests default constructor size matrix
        cout << "Congrats you passed test 11" << endl;
    }

    else {
        cout << "You failed one or more cases for test 11" << endl;
    }

    if (test12(matrix3) == 3) {//tests parametized constructor size matrix
        cout << "Congrats you passed test 12" << endl;
    }

    else {
        cout << "You failed one or more cases for test 12" << endl;
    }

    if (test13(matrix,matrix2,matrix3) == 1) {//tests default constructor size matrix
        cout << "Congrats you passed test 13" << endl;
    }

    else {
        cout << "You failed one or more cases for test 13" << endl;
    }
    
     if (test14(matrix) == 7) {//tests parametized constructor size matrix
        cout << "Congrats you passed test 14" << endl;
    }

    else {
        cout << "You failed one or more cases for test 14" << endl;
    }

    if (test15(matrix2) == 7) {//tests parametized constructor size matrix
        cout << "Congrats you passed test 15" << endl;
    }

    else {
        cout << "You failed one or more cases for test 15" << endl;
    }

    mymatrix<int>matrix4(3,4);//default matrix
    mymatrix<int>matrix5(4,2);
    mymatrix<int>matrix6(1,1);
    matrix6 = matrix4*matrix5;
    if (test16(matrix4,matrix5,matrix6) == 1) {//tests parametized matrixes for multiplying
        cout << "Congrats you passed test 16" << endl;
    }

    else {
        cout << "You failed one or more cases for test 16" << endl;
    }
    return 0;
}