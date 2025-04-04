#include "ALI.h"
#include "Command.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

ALI::ALI(){//default constructor
    accumulator = 0; //sets all values to 0/false 
    dataRegister = 0;
    programCounter = 0; 
    zeroBit = false;
    halted = false;
    counter = 0;
    initialize();//fills in array with 0's
}

void ALI::initialize(){//definition of initialize
    fill(begin(programMemory), end(programMemory), 0);//fill program memory will all 0's
    fill(begin(dataMemory), end(dataMemory), 0);//fill in data memory to zero
}

int ALI::allocateData(){
    static int nextAddress = 0;//keeps track of our addresses
    if (nextAddress < DATA_MEMORY_SIZE) {
        return nextAddress++;//returns next address
    } 
    else{//out of program memory so we exit
        exit(0);
    }
}

void ALI::loadProgram(const string& filename){//loadProgram definiton that reads in file 
    ifstream file(filename);
    string line;
    int index = 0;
    while (getline(file, line) && index < PROGRAM_MEMORY_SIZE) {
        programMemory[index] = line;//stores instruction into array memory
        index++;//making sure we dont go over 250
    }
    file.close();//closes file
}

void ALI::userLoop(){//userLoop definiton that keeps loop running until user leaves
    string command;
    cout << "Welcome to my ALI interpreter:" << endl;
    while (command != "q"){//loop keeps running until command is q
        cout << "Enter a command:\n a - Run all instructions at once\n s - Step into next instruction\n q - Exit" << endl;
        cin >> command;
        if (command == "s"){//check if its s
            executeLine();
        } 
        else if (command == "a"){//checks if its a
            executeAll();
        } 
        else if (command == "q") {//when user enters q then it breaks
            cout << "Exiting..." << endl;
            break;
        } 
        else{//else give error message
            cout << "INVALID INPUT."<< endl;
        }
    }
}

void ALI::executeLine(){//defintion of executeLine
    if (halted) {//makes sure to check if program halted
        cout << "Program has halted." << endl;//keeps giving this till user exits
        return;
    }

    string instruction = programMemory[programCounter];//gets instruction based on program counter
    cout << "Executing instruction at line=" << programCounter << ": " << instruction << endl;//prints instruction that is gonna be executed
    executeInstruction(instruction);//executes instruction
    programCounter++;//updates values
    counter++;
    printData();//prints user info
}

void ALI::executeAll(){//defintion of executeAll that runs all functions
    int counter = 0; 
    while (programCounter < PROGRAM_MEMORY_SIZE && !halted){//runs program while we dont pass memory and isnt halted
        counter++;
        if (counter >= 1000){//when instructions go over 1000 we ask if user wants to continue
            cout << "Want to continue? Enter y or n: ";
            string input;
            cin >> input;

            if (input == "n"){//if user puts n then program halts 
                halted = true;
                break;
            } 
            else if (input == "y"){//if user puts y then program continues
                counter = 0;
            }
        }
        string instruction = programMemory[programCounter];//gets instruction
        executeInstruction(instruction);//executes instruction

        if (!halted){//while program hasnt halted then we move to next instruction 
            programCounter++;
        }
    }
    printData();//prints stats at the end
}

void ALI::executeInstruction(const string& instruction){//definition of executeInstruction which executes current instruction
    istringstream iss(instruction);
    string command;
    iss >> command;//reads in first word which is the instruction 

    if (command == "DEC"){//checks if function is declaring a variable
        string variable;
        iss >> variable;//reads in the next word which is the variable
        int address = allocateData();//moves address to next avaible one
        instructionHash[variable] = address;//stores data
        cout << "Allocated " << variable << " at address " << address << endl;
        cout << "Executed opcode: DEC" << endl;//prints to show we executed DEC
    } 
    else if (command == "LDA"){//checks if command is LDA
        string variable;
        iss >> variable;//takes in variable we want to load in
        LDA lda(this, variable);//creates lda instance
        lda.execute();//runs execute to load in variable value into accumulator
    } 
    else if (command == "LDI"){//checks if instruction is LDI
        int value;
        iss >> value;//reads in value 
        accumulator = value;//accumulator is set and value read in
    } 
    else if (command == "STR"){//checks if command is STR
        string variable;
        iss >> variable;//reads in variable to see what wants to be read in
        STR str(this);//creates instance of STR class
        str.execute(variable);//calls execute function to str value of variable into 
    } 
    else if (command == "ADD"){//checks if command is ADD
        ADD add(this);//creates instance of ADD
        add.execute();//calls exectute function that will add A and B registers and store in A
    } 
    else if (command == "SUB"){//checks if command is SUB
        SUB sub(this);//creates instance of SUB
        sub.execute();//calls exectute function that will subtract B - A registers and store in A
    } 
    else if (command == "XCH"){//checks if command is XCH 
        XCH xch(this);//creates instance of XCH command
        xch.execute();//calls execute function that swaps register values
    } 
    else if (command == "JMP"){//checks if command is JMP 
        int address;
        iss >> address;//gets line number we jump too
        JMP jmp(this, address);//creates JMP instance
        jmp.execute();//calls execute function that jmps program to line wanted
    } 
    else if (command == "JZS"){//checks if command is JZS
        int address;
        iss >> address;//read in line we will jump to
        JZS jzs(this, address);//creates an instance of JZS
        jzs.execute();//executes function that jumps if zero bit is 0
    } 
    else if (command == "HLT"){//checks if command is HLT
        HLT hlt(this);//creates HLT instance
        hlt.execute();//calls execute function that will halt the program
        halted = true;//halts the program
    } 
}

void ALI::printData() const {//definition of printData that prints relevant information of program
    cout << "Accumulator: " << accumulator << endl; //prints relevant information of registers
    cout << "Data Register: " << dataRegister << endl;
    cout << "Program Counter: " << programCounter << endl;
    cout << "Zero Bit: " << (zeroBit ? "true" : "false") << endl;

    cout << "Program Memory: ["; 
    for (int i = 0; i < PROGRAM_MEMORY_SIZE; ++i){//prints program memory which is instructions
        if (i != 0) cout << ", ";
        cout << "\"" << programMemory[i] << "\"";
    }
    cout << "]\n";

    cout << "Data Memory: [";
    for (int i = 0; i < DATA_MEMORY_SIZE; ++i){//prints variable values 
        if (i != 0) cout << ", ";
        cout << dataMemory[i];
    }
    cout << "]\n";
}

