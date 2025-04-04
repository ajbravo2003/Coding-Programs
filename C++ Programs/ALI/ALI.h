#include <iostream> //includes imports
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;
const int PROGRAM_MEMORY_SIZE = 128;//declares program memory
const int DATA_MEMORY_SIZE = 128;//declares data memory
const int MEMORY_SIZE = 256;//declares memory size
class Command;
class ALI{
public:
    ALI();//default constructor
    void loadProgram(const string& filename);//reads in file
    void userLoop();//executes while loop for user
    void executeLine();//runs only one line
    void executeAll();//runs all instructions
    void executeInstruction(const string& instruction);//runs instruction
    void printData() const;//prints info for debug/user
    bool halted;//creates bool to see if program halts
    string programMemory[PROGRAM_MEMORY_SIZE];//makes string program array that stores instructions
    int dataMemory[DATA_MEMORY_SIZE];//stores variable values
    int accumulator;//accumlator data memebres
    int dataRegister;//data register data memeber
    int programCounter;
    bool zeroBit;//keeps track of zero bit
    int counter;
    unordered_map<string, int> instructionHash;//stores instruction and its value when applicable 
private:
    int allocateData();//allocates memory
    void initialize();//fills in all memory spots with 0
};
