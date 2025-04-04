/**------------------------------------------
//  Project 4 -  Assembly Language Interpreter
    Course: CS 474, Fall 2024.
    System: Visual Studio Code 2024
    Author: Alejandro Bravo
 ---------------------------------------------**/
#include "ALI.h"
#include <iostream>
#include <string>
using namespace std;
int main(){
    ALI ali;//creates instance of ali classs
    cout << "Enter the filename: ";
    string filename;
    cin >> filename; //takes user filename
    ali.loadProgram(filename);//reads in file
    ali.userLoop();//runs while loop to step or run all instructions
    return 0;
}
