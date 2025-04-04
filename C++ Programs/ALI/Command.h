#pragma once
#include <iostream>
#include <string>
using namespace std; 
class ALI;

class Command {
public:
    Command(ALI* ali) : ali(ali) {}
    virtual void execute() = 0;//virtual function that will be overrided by devirved classes
    string opcode;//opcaode that stores command we use

protected:
    ALI* ali;//ali instance that will be inherited by other dervived classes
};

class LDA : public Command{//Dervied LDA class declaration 
public:
    LDA(ALI* ali, const string& symbol);
    void execute() override;

private:
    string symbol;//stores variable name we will read from
};

class STR : public Command{//Dervied STR class declaration 
public:
    STR(ALI* ali);
    void execute() override;
    void execute(const string& symbol); // Overloaded method for STR with a symbol
};

class ADD : public Command{//Dervied ADD class declaration 
public:
    ADD(ALI* ali);
    void execute() override;
};

class SUB : public Command {//Dervied SUB class declaration 
public:
    SUB(ALI* ali);
    void execute() override;
};

class XCH : public Command {//Dervied XCH class declaration 
public:
    XCH(ALI* ali);
    void execute() override;
};

class JMP : public Command {//Dervied JMP class declaration 
public:
    JMP(ALI* ali, int address);
    void execute() override;

private:
    int address;//stores line number we will jump too
};

class JZS : public Command{//Dervied JZS class declaration 
public:
    JZS(ALI* ali, int address);
    void execute() override;

private:
    int address;//stores line number we will jump too 
};

class HLT : public Command{//Dervied HLT class declaration 
public:
    HLT(ALI* ali);
    void execute() override;
};
