#include "Command.h"
#include "ALI.h"
#include <iostream>
#include <string>
using namespace std;
STR::STR(ALI* ali) : Command(ali){}//class definition for STR command

void STR::execute(){//execute function when no parameter is passed
    cerr << "STR command requires a variable name." << endl;
}

void STR::execute(const string& symbol){//execute function when parameter is passed(done correctly then)
    int address = ali->instructionHash[symbol];//gets address of symbol
    ali->dataMemory[address] = ali->accumulator;//stores value of variable
    opcode = "STR";
    cout << "Executed opcode: " << opcode << endl;//prints STR is ran
}

LDA::LDA(ALI* ali, const string& symbol) : Command(ali), symbol(symbol) {}//class deinftion for STR command

void LDA::execute(){//execute function that will load in varaible name
    int address = ali->instructionHash[symbol];//gets address of symbol
    if (address != -1){
        ali->accumulator = ali->dataMemory[address]; //loads in varaible value into accumulator
        ali->zeroBit = (ali->accumulator == 0);
        opcode = "LDA";
        cout << "Executed opcode: " << opcode << endl;//shows LDA was exectued
    } 
    else {
        cout << "ERROR: " << symbol << "' not found." << endl;//else gives error message
    }
}

ADD::ADD(ALI* ali) : Command(ali) {}//ADD class definition 

void ADD::execute(){
    int result = ali->accumulator + ali->dataRegister;//adds accumlator and data register
    if (result > 32767 || result < -32768) {
        cout << "OVERFLOW ADDING DIDN'T HAPPEN" << endl;
        return;
    }
    ali->accumulator = result;//accumlator is set as the result
    ali->zeroBit = (ali->accumulator == 0);
    opcode = "ADD";
    cout << "Executed opcode: " << opcode << endl;//prints ADD is executed
}

SUB::SUB(ALI* ali) : Command(ali) {}//sub class definition

void SUB::execute(){
    cout << "Executed opcode: SUB" << endl;
    int result =  ali->dataRegister - ali->accumulator;//subtracts register B to register A
    if (result > 32767 || result < -32768) {//makes sure it doesnt overflow 
        cout << "OVERFLOW SUBTRACTION DIDN'T HAPPEN." << endl;
        return;
    }
    ali->accumulator = result;//stores as accumulator new value
    ali->zeroBit = (ali->accumulator == 0);
}

XCH::XCH(ALI* ali) : Command(ali){}//XCH definition

void XCH::execute() {
    opcode = "XCH";
    cout << "Executed opcode: " << opcode << endl;//says executed XCH
    int temp = ali->accumulator;//gets accumaltor value
    ali->accumulator = ali->dataRegister;//stores data register as accumulator value
    ali->dataRegister = temp;//stores accumluator old value as data register
}

JMP::JMP(ALI* ali, int address) : Command(ali), address(address){}//JMP definition 

void JMP::execute() {
    opcode = "JMP";
    cout << "Executed opcode: " << opcode << endl;//prints out that JMP is executed
    ali->programCounter = address - 1;//sets program counter to address and one back so it executes line it wants
}

JZS::JZS(ALI* ali, int address) : Command(ali), address(address){}//JZS definition 

void JZS::execute() {
    opcode = "JZS";
    cout << "Executed opcode: " << opcode << endl;//prints JZS is executed
    if (ali->zeroBit) {
        ali->programCounter = address - 1;//sets program counter to address and one back so it executes line it wants
    }
}

HLT::HLT(ALI* ali) : Command(ali){}//HLT class definition

void HLT::execute() {
    ali->halted = true;//sets halted as true
    opcode = "HLT";
    cout << "Executed opcode: " << opcode << endl;//prints that HLt is executed
}
