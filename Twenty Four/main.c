#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
/**------------------------------------------
//  Project 1 - TwentyFour
    Course: CS 211, Spring 2023.
    System: Visual Studio Code 2023
    Author: Alejandro Bravo
 ---------------------------------------------**/
void Welcome() {//welcome message
    printf("Welcome to the game of TwentyFour.\n");
    printf("Use each of the four numbers shown below exactly once, \n");
    printf("combining them somehow with the basic mathematical operators (+,-,*,/) \n");
    printf("to yield the value twenty-four.\n");
}

void print() {//prints nothing for arguments
    printf("");
}

void getArguments(int argc, char* argv[], int* easy, int* debug) {//checks arguments in commanad line
    if (argc == 1) // checks if there is arguement else it uses default values
        print();//prints argument 
    else {
        while ((argc -= 2) > 0) { // while there is another pair of strings
            if (argv[1][0] != '-')  //checks if other values doesnt equal - so it takes as user input
                print();//prints argument 
            switch (argv[1][1]) { //checks for rows and symbol/letter user wants
            case 'd':
                *debug = atoi(argv[2]);//checks user input for debug mode
                break;
            case 'e':
                *easy = atoi(argv[2]);//checks easy mode for debug mode
                break;

            default: //our default values
                *easy = 1;//easy mode is on
                *debug = 0;//debug mode is off
                break;
            }
            argv += 2; // continues the loop until no more words
        }
    }
}

void modeEasy(int* arr) {//function to play the 10 easy puzzles
    int number = (rand() % 10) + 1;//picks random easy puzzle
    if (number == 1) {//puzzle 1
        arr[0] = 3;
        arr[1] = 9;
        arr[2] = 4;
        arr[3] = 1;
    }

    else if (number == 2) {//puzzle 2
        arr[0] = 8;
        arr[1] = 5;
        arr[2] = 8;
        arr[3] = 1;
    }

    else if (number == 3) {//puzzle 3
        arr[0] = 6;
        arr[1] = 1;
        arr[2] = 5;
        arr[3] = 1;
    }

    else if (number == 4) {//puzzle 4
        arr[0] = 2;
        arr[1] = 8;
        arr[2] = 7;
        arr[3] = 8;
    }

    else if (number == 5) {//puzzle 5
        arr[0] = 5;
        arr[1] = 2;
        arr[2] = 9;
        arr[3] = 2;
    }

    else if (number == 6) {//puzzle 6
        arr[0] = 2;
        arr[1] = 6;
        arr[2] = 8;
        arr[3] = 4;
    }

    else if (number == 7) {//puzzle 7
        arr[0] = 5;
        arr[1] = 5;
        arr[2] = 4;
        arr[3] = 3;
    }

    else if (number == 8) {//puzzle 8
        arr[0] = 6;
        arr[1] = 6;
        arr[2] = 2;
        arr[3] = 6;
    }

    else if (number == 9) {//puzzle 9
        arr[0] = 8;
        arr[1] = 4;
        arr[2] = 2;
        arr[3] = 6;
    }

    else if (number == 10) {//puzzle 10
        arr[0] = 6;
        arr[1] = 2;
        arr[2] = 8;
        arr[3] = 1;
    }
}

bool calcuateValue(char* myArray, int* arr) {//checks if array is equal to 24
    double currValue = 0.0;
    double firstVal = arr[0];//assigns values from array
    double secondVal = arr[1];
    double thirdVal = arr[2];
    double fourthVal = arr[3];
    int first = firstVal;//sets values to integers to print out
    int second = secondVal;
    int third = thirdVal;
    int fourth = fourthVal;
    int curVal = 0;//sets current value for integer
    char operator1 = myArray[0];//gets first user operator
    char operator2 = myArray[1];//gets second operator
    char operator3 = myArray[2];//gets third operator
    int const win = 24;//winning score
    if (myArray[0] == '/') {//checks if user first input is division
        currValue = firstVal / secondVal;
        curVal = firstVal / secondVal;//divides first two values
        printf("%d %c %d = %d.\n", first, operator1, second, curVal);
        if (myArray[1] == '*') {//if loops that check the second operator entered by user
            printf("%d %c %d = ", curVal, operator2, third);
            curVal = curVal * thirdVal;//mutiplys values
            currValue = currValue * thirdVal;
        }

        else if (myArray[1] == '+') {
            printf("%d %c %d = ", curVal, operator2, third);
            currValue = currValue + thirdVal;//adds values
            curVal = curVal + thirdVal;
        }

        else if (myArray[1] == '-') {
            printf("%d %c %d = ", curVal, operator2, third);
            currValue = currValue - thirdVal;//subtracts values
            curVal = curVal - thirdVal;
        }

        else if (myArray[1] == '/') {
            printf("%d %c %d = ", curVal, operator2, third);
            curVal = curVal / thirdVal;//divides values
            currValue = currValue / thirdVal;
        }
        printf("%d.\n", curVal);
        if (myArray[2] == '*') {//if loops that check what the last operator was
            printf("%d %c %d = ", curVal, operator3, fourth);
            currValue = currValue * fourthVal;
            curVal = curVal * fourthVal;//mutiplys values
        }

        else if (myArray[2] == '+') {//adds values
            printf("%d %c %d = ", curVal, operator3, fourth);
            currValue = currValue + fourthVal;
            curVal = curVal + fourthVal;
        }

        else if (myArray[2] == '-') {
            printf("%d %c %d = ", curVal, operator3, fourth);
            curVal = curVal - fourthVal;//subtracts values
            currValue = currValue - fourthVal;
        }

        else if (myArray[2] == '/') {
            printf("%d %c %d = ", curVal, operator3, fourth);
            currValue = currValue / fourthVal;//divides values
            curVal = curVal / fourthVal;

        }
        printf("%d.\n", curVal);//prints last value value
    }

    else if (myArray[0] == '*') {//checks if user input for first operator is mutiplication 
        currValue = firstVal * secondVal;//mutiplys first two values
        curVal = firstVal * secondVal;
        printf("%d %c %d = %d.\n", first, operator1, second, curVal);
        if (myArray[1] == '*') {//if loops that check what second operator entered
            printf("%d %c %d = ", curVal, operator2, third);
            curVal = curVal * thirdVal;
            currValue = currValue * thirdVal;
        }
        else if (myArray[1] == '+') {
            printf("%d %c %d = ", curVal, operator2, third);
            currValue = currValue + thirdVal;//adds to second and third values
            curVal = curVal + thirdVal;
        }

        else if (myArray[1] == '-') {
            printf("%d %c %d = ", curVal, operator2, third);
            currValue = currValue - thirdVal;//subtracts current value and third value
            curVal = curVal - thirdVal;
        }

        else if (myArray[1] == '/') {
            printf("%d %c %d = ", curVal, operator2, third);
            curVal = curVal / thirdVal;//divides current value and third value
            currValue = currValue / thirdVal;
        }
        printf("%d.\n", curVal);//prints last value
        if (myArray[2] == '*') {
            printf("%d %c %d = ", curVal, operator3, fourth);
            currValue = currValue * fourthVal;
            curVal = curVal * fourthVal;
        }

        else if (myArray[2] == '+') {
            printf("%d %c %d = ", curVal, operator3, fourth);
            currValue = currValue + fourthVal;
            curVal = curVal + fourthVal;
        }

        else if (myArray[2] == '-') {
            printf("%d %c %d = ", curVal, operator3, fourth);
            curVal = curVal - fourthVal;//subtracts current value and third value
            currValue = currValue - fourthVal;
        }

        else if (myArray[2] == '/') {
            printf("%d %c %d = ", curVal, operator3, fourth);
            currValue = currValue / fourthVal;//divides current value and fourth value
            curVal = curVal / fourthVal;
        }
        printf("%d.\n", curVal);//prints equal value
    }

    else if (myArray[0] == '+') {
        currValue = firstVal + secondVal;
        curVal = firstVal + secondVal;
        printf("%d %c %d = %d.\n", first, operator1, second, curVal);
        if (myArray[1] == '*') {
            printf("%d %c %d = ", curVal, operator2, third);
            curVal = curVal * thirdVal;
            currValue = currValue * thirdVal;

        }
        else if (myArray[1] == '+') {
            printf("%d %c %d = ", curVal, operator2, third);
            currValue = currValue + thirdVal;
            curVal = curVal + thirdVal;
        }

        else if (myArray[1] == '-') {
            printf("%d %c %d = ", curVal, operator2, third);
            currValue = currValue - thirdVal;//subtracts current value and third value
            curVal = curVal - thirdVal;
        }

        else if (myArray[1] == '/') {
            printf("%d %c %d = ", curVal, operator2, third);
            curVal = curVal / thirdVal;//divides current value and third value
            currValue = currValue / thirdVal;
        }
        printf("%d.\n", curVal);//prints equal value
        if (myArray[2] == '*') {
            printf("%d %c %d = ", curVal, operator3, fourth);
            currValue = currValue * fourthVal;
            curVal = curVal * fourthVal;
        }

        else if (myArray[2] == '+') {
            printf("%d %c %d = ", curVal, operator3, fourth);
            currValue = currValue + fourthVal;
            curVal = curVal + fourthVal;
        }

        else if (myArray[2] == '-') {
            printf("%d %c %d = ", curVal, operator3, fourth);
            curVal = curVal - fourthVal;//subtracts current value and fouth value
            currValue = currValue - fourthVal;
        }

        else if (myArray[2] == '/') {
            printf("%d %c %d = ", curVal, operator3, fourth);
            currValue = currValue / fourthVal;//divides current value and fourth value
            curVal = curVal / fourthVal;
        }
        printf("%d.\n", curVal);//prints equal value
    }
    else if (myArray[0] == '-') {//checks if first operator is subtraction
        currValue = firstVal - secondVal;
        curVal = firstVal - secondVal;//subtracts current value and second value
        printf("%d %c %d = %d.\n", first, operator1, second, curVal);//prints equal value
        if (myArray[1] == '*') {
            printf("%d %c %d = ", curVal, operator2, third);
            curVal = curVal * thirdVal;
            currValue = currValue * thirdVal;
        }

        else if (myArray[1] == '+') {//adds the numbers
            printf("%d %c %d = ", curVal, operator2, third);
            currValue = currValue + thirdVal;
            curVal = curVal + thirdVal;
        }

        else if (myArray[1] == '-') {//subtracts the numbers
            printf("%d %c %d = ", curVal, operator2, third);
            currValue = currValue - thirdVal;
            curVal = curVal - thirdVal;
        }

        else if (myArray[1] == '/') {//divides the numbers
            printf("%d %c %d = ", curVal, operator2, third);
            curVal = curVal / thirdVal;
            currValue = currValue / thirdVal;
        }
        printf("%d.\n", curVal);
        if (myArray[2] == '*') {//mutiplys the numbers
            printf("%d %c %d = ", curVal, operator3, fourth);
            currValue = currValue * fourthVal;
            curVal = curVal * fourthVal;
        }

        else if (myArray[2] == '+') {//adds the numbers
            printf("%d %c %d = ", curVal, operator3, fourth);
            currValue = currValue + fourthVal;
            curVal = curVal + fourthVal;
        }

        else if (myArray[2] == '-') {//subtracts the numbers
            printf("%d %c %d = ", curVal, operator3, fourth);
            curVal = curVal - fourthVal;
            currValue = currValue - fourthVal;
        }

        else if (myArray[2] == '/') {//divides the numbers
            printf("%d %c %d = ", curVal, operator3, fourth);
            currValue = currValue / fourthVal;
            curVal = curVal / fourthVal;

        }
        printf("%d.\n", curVal);//prints equal value
    }
    if (currValue == win) {
        return true;
    }
    else {
        return false;
    }
}

bool calculateEasyValues(int* arr) {//function that checks for valid operators/length/if equals 24
    char myArray[3];//intilazed array for operators
    char operator1[100];//intiliazed for numbers in puzzles
    char operator2[100];
    char operator3;
    char userInput[100];
    char operator4[100];
    bool operator5 = false;//bool variables to make sure userinput is a valid operator
    bool operator6 = false;
    bool operator7 = false;
    bool length = false;//intiliazed bool variable to check if length is 3
    bool operator =false;
    scanf("%s", operator1);//takes user input
    for (int i = 0; i < strlen(operator1); i++) {
        myArray[i] = *(operator1 + i);//stores user input into a char array
    }

    if (myArray[0] == '/' || myArray[0] == '*' || myArray[0] == '+' || myArray[0] == '-') {// checks for the first operator
        operator5 = true;
    }


    if (myArray[1] == '/' || myArray[1] == '*' || myArray[1] == '+' || myArray[1] == '-') {//checks for valid second operator
        operator6 = true;
    }

    if (myArray[2] == '/' || myArray[2] == '*' || myArray[2] == '+' || myArray[2] == '-') { //checs for valid third operator
        operator7 = true;
    }

    if (strlen(operator1) != 3) {//error message when user input isnt only 3 chars
        printf("Error! The number of operators is incorrect. Please try again.\n\n");
    }
    else {
        length = true;//sets true that length is 3
        if ((!operator5 || !operator6 || !operator7)) {//error message when a invalid operators was entered
            printf("Error! Invalid operator entered. Please try again.\n\n");
        }
        else {
            operator = true;//otherwise sets true
        }
    }

    if (length && operator) {//if length is 3 and operators are valid
        if (calcuateValue(myArray, arr)) {//checks if numbers are 24
            printf("Well done! You are a math genius.\n");//prints out win message
            printf("\nWould you like to play again? Enter N for no and any other character for yes.\n");//asks if you want to play again
            scanf("%s", userInput);//scans to continue playing

        }
        else {
            printf("Sorry. Your solution did not evaluate to 24.\n\n");//otherwise prints you didnt get 24
            printf("Would you like to play again? Enter N for no and any other character for yes.");//asks if want to play again
            scanf("%s", userInput);//scans user output

        }
        if (strcmp(userInput, "N") == 0) {//checks if user wants to play again and stops loop
            return true;
        }
        else {//contiunes playing
            return false;
        }
    }

}

void printArray(int* myArray) {//prints array to user to see the numbers they get
    printf("\nThe numbers to use are: ");
    for (int i = 0; i < 4; i++) {//prints four numbers
        if (i == 3) {
            printf("%d.\n", myArray[i]);
        }
        else {
            printf("%d, ", myArray[i]);
        }
    }
    printf("Enter the three operators to be used, in order (+,-,*, or /): ");//asks user to input opeators
}

void calcFirst(char op, double* result, int i, int j) {//calcualtes first two values
    double val1 = i;//switches ints to doubles
    double val2 = j;
    if (op == '+') {//checks if first operator is addition
        *result += val1 + val2;
    }

    else if (op == '-') {//checks is subtraction is first operator
        *result += val1 - val2;
    }

    else if (op == '/') {//checks if division is first operator
        *result += val1 / val2;
    }

    else if (op == '*') {//checks is multiplications is first operator
        *result += val1 * val2;
    }
}

void calcSecond(char op2, double* result, int k) {//calculates 3rd value and current value
    double val1 = k;//switches int to double
    if (op2 == '+') {//checks if addition is 2nd operator
        *result += val1;
    }

    else if (op2 == '-') {//checks if subtraction
        *result -= val1;
    }

    else if (op2 == '/') {//checks if division
        *result /= val1;
    }

    else if (op2 == '*') {//checks if multiplication
        *result *= val1;
    }
}

void calcThird(char op3, double* result, int k) {//calculates last value and current value
    double val1 = k;//switches to double
    if (op3 == '+') {//checks if addition is last operator
        *result += val1;
    }

    else if (op3 == '-') {//checks if subtraction is last operator
        *result -= val1;
    }

    else if (op3 == '/') {//checks if division is last operator
        *result /= val1;
    }

    else if (op3 == '*') {//checks if multiplication is last operator
        *result *= val1;
    }
}

void debugsMode(int* arr) {//function that runs the debug mode
    char array[4];
    array[0] = '+';//assigns operators to array
    array[1] = '-';
    array[2] = '*';
    array[3] = '/';
    double val1 = 0.0;//intilized double variables
    double val2 = 0.0;
    double val3 = 0.0;
    double val4 = 0.0;
    int counter = 1;//intilize counter
    double result = 0.0;
    printf("\n");
    for (int i = 1; i < 10; i++) {//for loops that loops through first number
        for (int j = 1; j < 10; j++) {//loops through second nunmber
            for (int k = 1; k < 10; k++) {//loops through third number
                for (int l = 1; l < 10; l++) {//loops through 4th number
                    for (int op1 = 0; op1 < 4; op1++) {//loops through first operator
                        for (int op2 = 0; op2 < 4; op2++) {//loops through second operator
                            for (int op3 = 0; op3 < 4; op3++) {//loops through third operator
                                calcFirst(array[op1], &result, i, j);//calculates first two values
                                calcSecond(array[op2], &result, k);//calculates 3rd value
                                calcThird(array[op3], &result, l);//calculates fourth value
                                if ((result - 24.0) < 0.001 && (result - 24.0) >= 0) {//checks if total is 24
                                    if (counter == 3188) {//prints out last line without new line
                                        printf("%d. %d%c%d%c%d%c%d", counter, i, array[op1], j, array[op2], k, array[op3], l);
                                    }
                                    else {//prints new line for everything else
                                        printf("%d. %d%c%d%c%d%c%d\n", counter, i, array[op1], j, array[op2], k, array[op3], l);

                                    }
                                    counter++;//adds to counter

                                }
                                result = 0.0;//sets result to 0
                            }

                        }
                    }

                }
            }
        }
    }
}

void hardMode(int* arr) {//function to calculate hard mode
    int number = (rand() % 3188) + 1;//picks random number from 1-3188
    char array[4];//intialize array
    array[0] = '+';//sets values to array
    array[1] = '-';
    array[2] = '*';
    array[3] = '/';
    double val1 = 0.0;//initilize double variables
    double val2 = 0.0;
    double val3 = 0.0;
    double val4 = 0.0;
    int counter = 1;
    double result = 0.0;
    printf("\n");
    for (int i = 1; i < 10; i++) {//for loops that goes through 4 numbers
        for (int j = 1; j < 10; j++) {
            for (int k = 1; k < 10; k++) {
                for (int l = 1; l < 10; l++) {
                    for (int op1 = 0; op1 < 4; op1++) {//for loops that goes through the 4 operators
                        for (int op2 = 0; op2 < 4; op2++) {
                            for (int op3 = 0; op3 < 4; op3++) {
                                calcFirst(array[op1], &result, i, j);//calculates first and second number
                                calcSecond(array[op2], &result, k);//calculates third number
                                calcThird(array[op3], &result, l);//calculates fourth number
                                if ((result - 24.0) < 0.001 && (result - 24.0) >= 0) {//checks if values is 24
                                    if (counter == number) {//checks if counter is random number 
                                        arr[0] = i;//assigns values in array that are from the number randomly picked
                                        arr[1] = j;
                                        arr[2] = k;
                                        arr[3] = l;
                                    }

                                    counter++;//adds to counter

                                }
                                result = 0.0;//sets result to 0
                            }

                        }
                    }

                }
            }
        }
    }
}
    
int main(int argc, char* argv[]) {//main function
    srand(1);//gets new puzzles every time
    bool easyMode = true;//sets easy mode to true by default
    bool debugMode = false;//sets debug mode by default off
    bool continueGame = false;//contniue game set to off
    int easy = 1;//arguments for terminal intputs
    int debug = 0;
    int myArray[4];//initilaze int array
    int count = 0;
    char userInput[100];
    Welcome();//prints welcome mesasage
    getArguments(argc, argv, &easy, &debug); //pass to command line to get our inputs
    if (debug == 1) {//checks if debug mode is on or off
        debugMode = true;
    }

    else if (debug == 0) {
        debugMode = false;
    }

    if (debugMode) {//if on runs debug mode
        debugsMode(myArray);
    }

    while (!continueGame) {//continues game until user enters N
        if (easy == 0) {//checks if easy mode is on
            easyMode = false;
        }

        else if (easyMode == 1) {
            easyMode = true;
        }

        if (easyMode) {//if easy mode run then picks easy puzzle
            modeEasy(myArray);
            printArray(myArray);//prints 4 numbers from the puzzle
            continueGame = calculateEasyValues(myArray);//checks if user values are 24

        }
        else if (!easyMode) {//if easy mode is turned off hard mode is turned on
            hardMode(myArray);
            printArray(myArray);//prints numbers from hard puzzle
            continueGame = calculateEasyValues(myArray);//checks if user inputs equals 24
        }
    }
    printf("\nThanks for playing!");//prints thank you message
    return 0;
}