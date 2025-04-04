/**------------------------------------------
    Project 4 - Database of Students
    Course: CS 211, Spring 2023.
    System: Visual Studio Code 2023
    Author: Alejandro Bravo
 ---------------------------------------------**/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct {//struct that contains student information
	char* name;
	char* id;
	double gpa;
	int creditHours;
} Student;

typedef struct StudentNode{//student node struct that will connect all student nodes
	Student* pStudent;
	struct StudentNode* pNext;
} StudentNode;

typedef struct {//database struct 
	StudentNode* pIDList;//stores all students stored alpahbetiacally based on idea
	StudentNode* pHonorRollList;//stores students on honor roll
	StudentNode* pAcademicProbationList;//stores student with probration
	StudentNode* pFreshmanList;//stores students that are considered freshman
	StudentNode* pSophomoreList;//stores students that are considered sophmore
	StudentNode* pJuniorList;//stores students that are considered junior
	StudentNode* pSeniorList;//stores students that are considered senior
    StudentNode* pHead;//stores students that are considered senior
} Database;

void printHead(Database database) {//function that prints the first 10 students in the list
StudentNode* head = database.pIDList;
if(head == NULL){//if list is empty returns error message
        printf("There are no students matching that criteria.\n\n");
        return;
    }
int counter =0;
    for (StudentNode* iteratingNode = head; iteratingNode != NULL; iteratingNode = iteratingNode->pNext) {//iterates through the list using for loop
       if(counter==10){
        break;
        }
        printf("%s:\n", iteratingNode->pStudent->name);//prints name
        printf("\tID - %s\n", iteratingNode->pStudent->id);//prints id
        printf("\tGPA - %.2f\n", iteratingNode->pStudent->gpa);//prints gpa
        printf("\tCredit Hours - %d\n\n", iteratingNode->pStudent->creditHours);//prints credit hours
        counter++;
    }
}

void printHonorRoll(Database database) {//prints honor roll students
StudentNode* head = database.pHonorRollList;
if(head == NULL){//if list is empty returns error message
        printf("There are no students matching that criteria.\n\n");
        return;
    }
     for (StudentNode* iteratingNode = head; iteratingNode != NULL; iteratingNode = iteratingNode->pNext) {//iterates through the list using for loop
       
        printf("%s:\n", iteratingNode->pStudent->name);//prints name
        printf("\tID - %s\n", iteratingNode->pStudent->id);//prints id
        printf("\tGPA - %.2f\n", iteratingNode->pStudent->gpa);//prints gpa
        printf("\tCredit Hours - %d\n\n", iteratingNode->pStudent->creditHours);//prints credit hours
    }
}

void printProbation(Database database) {//prints probation students
StudentNode* head = database.pAcademicProbationList;
if(head == NULL){//if list is empty returns error message
        printf("There are no students matching that criteria.\n\n");
        return;
    }
     for (StudentNode* iteratingNode = head; iteratingNode != NULL; iteratingNode = iteratingNode->pNext) {//iterates through the list using for loop
       
        printf("%s:\n", iteratingNode->pStudent->name);//prints name
        printf("\tID - %s\n", iteratingNode->pStudent->id);//prints id
        printf("\tGPA - %.2f\n", iteratingNode->pStudent->gpa);//prints gpa
        printf("\tCredit Hours - %d\n\n", iteratingNode->pStudent->creditHours);//prints credit hours
    }
}

void printFreshStudents(Database database) {//prints freshman students
StudentNode* head = database.pFreshmanList;
if(head == NULL){//if list is empty returns error message
        printf("There are no students matching that criteria.\n\n");
        return;
    }
     for (StudentNode* iteratingNode = head; iteratingNode != NULL; iteratingNode = iteratingNode->pNext) {//iterates through the list using for loop
       
        printf("%s:\n", iteratingNode->pStudent->name);//prints name
        printf("\tID - %s\n", iteratingNode->pStudent->id);//prints id
        printf("\tGPA - %.2f\n", iteratingNode->pStudent->gpa);//prints gpa
        printf("\tCredit Hours - %d\n\n", iteratingNode->pStudent->creditHours);//prints credit hours
    }
}

void printSophStudents(Database database) {//prints sophmore students
StudentNode* head = database.pSophomoreList;
if(head == NULL){//if list is empty returns error message
        printf("There are no students matching that criteria.\n\n");
        return;
    }
   for (StudentNode* iteratingNode = head; iteratingNode != NULL; iteratingNode = iteratingNode->pNext) {//iterates through the list using for loop
       
        printf("%s:\n", iteratingNode->pStudent->name);//prints name
        printf("\tID - %s\n", iteratingNode->pStudent->id);//prints id
        printf("\tGPA - %.2f\n", iteratingNode->pStudent->gpa);//prints gpa
        printf("\tCredit Hours - %d\n\n", iteratingNode->pStudent->creditHours);//prints credit hours
    }
}

void printJuniorStudents(Database database) {//prints junior students
StudentNode* head = database.pJuniorList;
if(head == NULL){//if list is empty returns error message
        printf("There are no students matching that criteria.\n\n");
        return;
    }
   for (StudentNode* iteratingNode = head; iteratingNode != NULL; iteratingNode = iteratingNode->pNext) {//iterates through the list using for loop
       
        printf("%s:\n", iteratingNode->pStudent->name);//prints name
        printf("\tID - %s\n", iteratingNode->pStudent->id);//prints id
        printf("\tGPA - %.2f\n", iteratingNode->pStudent->gpa);//prints gpa
        printf("\tCredit Hours - %d\n\n", iteratingNode->pStudent->creditHours);//prints credit hours
    }
}

void printSeniorStudents(Database database) {//prints senior students
StudentNode* head = database.pSeniorList;
    if(head == NULL){//if list is empty returns error message
        printf("There are no students matching that criteria.\n\n");
        return;
    }
     for (StudentNode* iteratingNode = head; iteratingNode != NULL; iteratingNode = iteratingNode->pNext) {//iterates through the list using for loop
        printf("%s:\n", iteratingNode->pStudent->name);//prints name
        printf("\tID - %s\n", iteratingNode->pStudent->id);//prints id
        printf("\tGPA - %.2f\n", iteratingNode->pStudent->gpa);//prints gpa
        printf("\tCredit Hours - %d\n\n", iteratingNode->pStudent->creditHours);//prints credit hours
    }
}

bool printStudent(Database database,char* ID){//function that looks for student 
    StudentNode* head = database.pHead;
    while(head!=NULL){
        if(strcmp(head->pStudent->id,ID)==0){       
        printf("%s:\n", head->pStudent->name);//prints name
        printf("\tID - %s\n", head->pStudent->id);//prints id
        printf("\tGPA - %.2f\n", head->pStudent->gpa);//prints gpa
        printf("\tCredit Hours - %d\n\n", head->pStudent->creditHours);//prints credit hours
        return true;
        }
        head = head->pNext;//moves to next node
    }
    return false;
}

void addToHonorRoll(Database* database) {//function that adds to honor roll list by using ID list and sorts by gpa
    StudentNode* tempNode = NULL;
    StudentNode* traversingNode = database->pHead;//gets head to Id
    while (traversingNode != NULL) {//keeps going until end of list
        if (traversingNode->pStudent->gpa >= 3.5) {//checks if gpa is higher or equal to 3.5
            StudentNode* pNewNode = (StudentNode*)malloc(sizeof(StudentNode));//creates a new node to store in the honor roll list
            pNewNode->pStudent = traversingNode->pStudent;//copies node
            pNewNode->pNext = NULL;
            if (tempNode == NULL) {//checks if theres no head
                tempNode = pNewNode;//creates a head node
            }
            else if (pNewNode->pStudent->gpa <= tempNode->pStudent->gpa) {//checks if gpa is lower to add in front
                pNewNode->pNext = tempNode;
                tempNode = pNewNode;
            }
            else {//else keeps going through list and adds node until its gpa of new node is less than current node
                StudentNode* prev = tempNode;//creaes two new nodes to traverse
                StudentNode* curr = tempNode->pNext;
                while (curr != NULL && pNewNode->pStudent->gpa > curr->pStudent->gpa) {//keeps going until gpa is bigger or end of list
                    prev = curr;
                    curr = curr->pNext;//keeps going to next node
                }
                pNewNode->pNext = curr;//assigns node before node thats gpa is bigger than new node
                prev->pNext = pNewNode;
            }
        }
        traversingNode = traversingNode->pNext;//moves to next node
    }
    database->pHonorRollList = tempNode;//assigns tempnode to head of honor roll list
}

void addToProbation(Database* database) {//function that adds to probation list by using ID list and sorts it by gpa
     StudentNode* tempNode = NULL;
    StudentNode* traversingNode = database->pHead;//gets head to Id
    while (traversingNode != NULL) {//keeps going until end of list
        if (traversingNode->pStudent->gpa < 2.0) {//checks if gpa is higher or equal to 2.0
            StudentNode* pNewNode = (StudentNode*)malloc(sizeof(StudentNode));//creates a new node to store in the honor roll list
            pNewNode->pStudent = traversingNode->pStudent;//copies node
            pNewNode->pNext = NULL;
            if (tempNode == NULL) {//checks if theres no head
                tempNode = pNewNode;//creates a head node
            }
            else if (pNewNode->pStudent->gpa <= tempNode->pStudent->gpa) {//checks if gpa is lower to add in front
                pNewNode->pNext = tempNode;
                tempNode = pNewNode;
            }
            else {//else keeps going through list and adds node until its gpa of new node is less than current node
                StudentNode* prev = tempNode;//creaes two new nodes to traverse
                StudentNode* curr = tempNode->pNext;
                while (curr != NULL && pNewNode->pStudent->gpa > curr->pStudent->gpa) {//keeps going until gpa is bigger or end of list
                    prev = curr;
                    curr = curr->pNext;//keeps going to next node
                }
                pNewNode->pNext = curr;//assigns node before node thats gpa is bigger than new node
                prev->pNext = pNewNode;
            }
        }
        traversingNode = traversingNode->pNext;//moves to next node
    }
    database->pAcademicProbationList = tempNode;//assigns tempnode to head of probation list
}

void addToFreshman(Database* database) {//function that adds to freshman list and sorts by name
    StudentNode* newListNode = NULL;
    StudentNode* tempNode = database->pHead;//sets head of ID list to temp
    while (tempNode != NULL) {//traverse till end of list
        if (tempNode->pStudent->creditHours < 30 && tempNode->pStudent->creditHours >= 0 ) {//checks for credit hours of seniors
            StudentNode* temp2 = (StudentNode*)malloc(sizeof(StudentNode));//creates a new node
            temp2->pStudent = tempNode->pStudent; //assigns node to temp
            temp2->pNext = NULL;//makes sure its null incase of end of list
            if (newListNode == NULL) {//checks if there is no head
                newListNode = temp2;//assigns as head
            }
            else if (strcmp(temp2->pStudent->name, newListNode->pStudent->name) < 0){//compares name of current node and node inserted
                temp2->pNext = newListNode;//adds infront current node
                newListNode = temp2;
            }
            else {
                StudentNode* currNode = newListNode->pNext;//creates new node to add before the node inserted
                StudentNode* prev = newListNode;
                while (currNode != NULL && strcmp(temp2->pStudent->name, currNode->pStudent->name) > 0) {//keeps adding node until its no greater than current one
                    prev = currNode;
                    currNode = currNode->pNext;//moves to next node
                }
                temp2->pNext = currNode;
                prev->pNext = temp2;
            }
        }
        tempNode = tempNode->pNext;//keeps going to next node 
    }
    database->pFreshmanList = newListNode;//assigns the newlistnode as the head of freshman list
}

void addToSophmore(Database* database) {//function that adds to sophmore list and sorts by name
   StudentNode* newListNode = NULL;
    StudentNode* tempNode = database->pHead;//sets head of ID list to temp
    while (tempNode != NULL) {//traverse till end of list
        if (tempNode->pStudent->creditHours >= 30 &&tempNode->pStudent->creditHours <= 59) {//checks for credit hours of seniors
            StudentNode* temp2 = (StudentNode*)malloc(sizeof(StudentNode));//creates a new node
            temp2->pStudent = tempNode->pStudent; //assigns node to temp
            temp2->pNext = NULL;//makes sure its null incase of end of list
            if (newListNode == NULL) {//checks if there is no head
                newListNode = temp2;//assigns as head
            }
            else if (strcmp(temp2->pStudent->name, newListNode->pStudent->name) < 0){//compares name of current node and node inserted
                temp2->pNext = newListNode;//adds infront current node
                newListNode = temp2;
            }
            else {
                StudentNode* currNode = newListNode->pNext;//creates new node to add before the node inserted
                StudentNode* prev = newListNode;
                while (currNode != NULL && strcmp(temp2->pStudent->name, currNode->pStudent->name) > 0) {//keeps adding node until its no greater than current one
                    prev = currNode;
                    currNode = currNode->pNext;//moves to next node
                }
                temp2->pNext = currNode;
                prev->pNext = temp2;
            }
        }
        tempNode = tempNode->pNext;//keeps going to next node 
    }
    database->pSophomoreList = newListNode;//assigns the newlistnode as the head of sophmore list
}

void addToJunior(Database* database){//function that adds to junior list and sorts by name
    StudentNode* newListNode = NULL;
    StudentNode* tempNode = database->pHead;//sets head of ID list to temp
    while (tempNode != NULL) {//traverse till end of list
        if (tempNode->pStudent->creditHours >= 60 &&tempNode->pStudent->creditHours <= 89 ) {//checks for credit hours of seniors
            StudentNode* temp2 = (StudentNode*)malloc(sizeof(StudentNode));//creates a new node
            temp2->pStudent = tempNode->pStudent; //assigns node to temp
            temp2->pNext = NULL;//makes sure its null incase of end of list
            if (newListNode == NULL) {//checks if there is no head
                newListNode = temp2;//assigns as head
            }
            else if (strcmp(temp2->pStudent->name, newListNode->pStudent->name) < 0){//compares name of current node and node inserted
                temp2->pNext = newListNode;//adds infront current node
                newListNode = temp2;
            }
            else {
                StudentNode* currNode = newListNode->pNext;//creates new node to add before the node inserted
                StudentNode* prev = newListNode;
                while (currNode != NULL && strcmp(temp2->pStudent->name, currNode->pStudent->name) > 0) {//keeps adding node until its no greater than current one
                    prev = currNode;
                    currNode = currNode->pNext;//moves to next node
                }
                temp2->pNext = currNode;
                prev->pNext = temp2;
            }
        }
        tempNode = tempNode->pNext;//keeps going to next node 
    }
    database->pJuniorList = newListNode;//assigns the newlistnode as the head of junior list
}

void addToSenior(Database* database){//function that takes the IDlist and adds all nodes that fit senior critera
    StudentNode* newListNode = NULL;
    StudentNode* tempNode = database->pHead;//sets head of ID list to temp
    while (tempNode != NULL) {//traverse till end of list
        if (tempNode->pStudent->creditHours >= 90) {//checks for credit hours of seniors
            StudentNode* temp2 = (StudentNode*)malloc(sizeof(StudentNode));//creates a new node
            temp2->pStudent = tempNode->pStudent; //assigns node to temp
            temp2->pNext = NULL;//makes sure its null incase of end of list
            if (newListNode == NULL) {//checks if there is no head
                newListNode = temp2;//assigns as head
            }
            else if (strcmp(temp2->pStudent->name, newListNode->pStudent->name) < 0){//compares name of current node and node inserted
                temp2->pNext = newListNode;//adds infront current node
                newListNode = temp2;
            }
            else {
                StudentNode* currNode = newListNode->pNext;//creates new node to add before the node inserted
                StudentNode* prev = newListNode;
                while (currNode != NULL && strcmp(temp2->pStudent->name, currNode->pStudent->name) > 0) {//keeps adding node until its no greater than current one
                    prev = currNode;
                    currNode = currNode->pNext;//moves to next node
                }
                temp2->pNext = currNode;
                prev->pNext = temp2;
            }
        }
        tempNode = tempNode->pNext;//keeps going to next node 
    }
    database->pSeniorList = newListNode;//assigns the newlistnode as the head of senior list
}

void addToId(Database* database){
     StudentNode* newListNode = NULL;
    StudentNode* tempNode = database->pHead;//sets head of ID list to temp
    while (tempNode != NULL) {//traverse till end of list
            StudentNode* temp2 = (StudentNode*)malloc(sizeof(StudentNode));//creates a new node
            temp2->pStudent = tempNode->pStudent; //assigns node to temp
            temp2->pNext = NULL;//makes sure its null incase of end of list
            if (newListNode == NULL) {//checks if there is no head
                newListNode = temp2;//assigns as head
            }
            else if (strcmp(temp2->pStudent->id, newListNode->pStudent->id) < 0){//compares name of current node and node inserted
                temp2->pNext = newListNode;//adds infront current node
                newListNode = temp2;
            }
            else {
                StudentNode* currNode = newListNode->pNext;//creates new node to add before the node inserted
                StudentNode* prev = newListNode;
                while (currNode != NULL && strcmp(temp2->pStudent->id, currNode->pStudent->id) > 0) {//keeps adding node until its no greater than current one
                    prev = currNode;
                    currNode = currNode->pNext;//moves to next node
                }
                temp2->pNext = currNode;
                prev->pNext = temp2;
            }
        
        tempNode = tempNode->pNext;//keeps going to next node 
    }
    database->pIDList = newListNode;//assigns the newlistnode as the head of senior list
}

void add(Database* dataBase, char* name, char* id, char* gpa, char* credits){//add function that adds students into the linked list of ID
    Student* tempStudent = (Student*) malloc(sizeof(Student));//creates new student
    tempStudent->gpa = atof(gpa);//sets GPA of user/file
    tempStudent->creditHours = atoi(credits);//sets credit hours to student
    tempStudent->name = (char*) malloc(strlen(name));//sets name thats from user/file
    tempStudent->id = (char*) malloc(strlen(id));//sets id from file/user
    strcpy(tempStudent->name, name);//copies the string to name
    strcpy(tempStudent->id, id);//copies id string to name
    StudentNode* iteratingNode = (StudentNode*) malloc(sizeof(StudentNode));//creates new student node
    iteratingNode->pStudent = (Student*) malloc(strlen(tempStudent));
   iteratingNode->pStudent = tempStudent;//sets current student to it
   iteratingNode->pNext = NULL;//makes sure its null incase its at end of list
    if (dataBase->pHead == NULL) {//checks if list is empty then we add a head
        dataBase->pHead = iteratingNode;
        return;
    }
    StudentNode* traversingNode = dataBase->pHead;
    while (traversingNode->pNext != NULL) {//checks if id is greater
        traversingNode = traversingNode->pNext;//keeps going until its not bigger
    }
    iteratingNode->pNext = traversingNode->pNext;//once we break out of loop we are able to set the node infront of the node that ID was smaller than it but next node id is bigger
    traversingNode->pNext = iteratingNode;
}

bool deleteStudent(Database* database, char* ID) {//function that deletes the student in the database
    StudentNode* iteratingNode = database->pHead;//node the iterates through ID list
    StudentNode* prev = NULL;//node to make sure to link the nodes
    while (iteratingNode != NULL) {//continues until null
        if (strcmp(iteratingNode->pStudent->id, ID) == 0){//checks if ID are the same
            if (prev == NULL){
                database->pHead = iteratingNode->pNext;//moves to next node
            } 
            else {
                prev->pNext = iteratingNode->pNext;
            }
            free(iteratingNode->pStudent->name);//frees the name
            free(iteratingNode->pStudent->id);//frees the ID
            free(iteratingNode->pStudent);//frees the student node
            free(iteratingNode);//frees the pointer
            return true;
        }
        prev = iteratingNode;//sets node equal to preivous node
        iteratingNode = iteratingNode->pNext;//goes to next node
    }
    return false;//returns false if no id in data base with that name
}

void deleteDatabase(Database* database) {//function that deletes the student in the database
    StudentNode* iteratingNode = database->pHead;//node the iterates through ID list
    StudentNode* prev = NULL;//node to make sure to link the nodes
    if(iteratingNode==NULL){
            return;
      }
    while (iteratingNode != NULL) {//continues until null
            prev = iteratingNode->pNext;//sets node equal to preivous node
            free(iteratingNode->pStudent->name);//frees the name
            free(iteratingNode->pStudent->id);//frees the ID
            free(iteratingNode->pStudent);//frees the student node
            free(iteratingNode);//frees the pointer
            iteratingNode = prev;//goes to next node
    }
}

int main() {
    char userInput[81];//intiliazed values
    char userInput2[81];//intiliazed values
    char fileName[81];
    bool validInput = false;
    bool validInput2 = false;
    bool validInput3 = false;
    bool endGame = false;
    Database database;//creates a database
    database.pAcademicProbationList=NULL;//makes sures all lists are set to null to be able to add to nodes and to keep program from crashing
    database.pFreshmanList=NULL;
    database.pHonorRollList=NULL;
    database.pIDList=NULL;
    database.pHead=NULL;
    database.pJuniorList=NULL;
    database.pSeniorList=NULL;
    database.pSophomoreList=NULL;
	printf("CS 211, Spring 2023\n");//prints welcome message
	printf("Program 4: Database of Students\n\n");
	printf("Enter E to start with an empty database, \n");
	printf("or F to start with a database that has information on students from a file.\n");
    while(!validInput){//keeps asking user for input if they dont choose E or F
    printf("Your choice --> ");
    scanf("%s", userInput);
    if (strcmp(userInput, "E") == 0){//leaves linked list empty
        validInput = true;
    }
    else if (strcmp(userInput, "F") == 0) {//takes file name to read the tudent
        printf("Enter the name of the file you would like to use: ");
        scanf("%s", fileName);
	    FILE* filePtr = fopen(fileName, "r"); // "r" means we open the file for reading
	    if (filePtr == NULL) {//gives error if file cant be found
		exit(-1);
	}
	char inputString[81] = "";//intiliaze file reading variables and student info 
    char Name[81]="";
    char IDS[81]="";
    char GPA[81];
    char Credits[81];
    int counter = 0;
    validInput = true;
    int row = 0;
    int column = 0;
    while (fgets(inputString,81, filePtr)) {//reads the line of the student 
            column = 0;
            row++;
            if (row == 1){//skips first line
                continue;
            }
            char* value = strtok(inputString, ",");//splits string by space to get each individual part
            while (value){
                if (column == 0) {
                strcpy(Name, value);//adds first name into a string
                }

                if (column ==1) {//reads IDS from students
                    strcpy(IDS, value);
                }
 
                if (column == 2) {//reads GPA from student
                    strcpy(GPA, value);
                }

                if (column == 3) {//reads credits from student 
                    strcpy(Credits, value);
                }
                value = strtok(NULL, ",");//gets next string in the line
                column++;

        }
         add(&database,Name,IDS,GPA,Credits);//adds student to the list
    }
        // Close the file
        fclose(filePtr);
    }
    else{//prints error message if user doesnt seletct E or F
        validInput = false;
        printf("Sorry, that input was invalid. Please try again.\n");
    }
    }
    while(!endGame){
    printf("\nEnter: \tC to create a new student and add them to the database,\n");//prints next menu option messages
	printf("\tR to read from the database,\n");
	printf("\tD to delete a student from the database, or\n");
	printf("\tX to exit the program.\n");
    while(!validInput2){//keeps going until valid option is inputted
	printf("Your choice --> ");
    scanf("%s", userInput2);//scans user option
    if(strcmp(userInput2, "C") == 0){//checks if user wants to create new student
    char name[81];
    char name2[81];
    char Id[81];
    char gpa[81];
    char credit[81];
    printf("Enter the name of the new student: ");//prompts user for student info
    scanf("%s", name);//scans first name
    strcpy(name2, name);//adds first name into a string
    strcat(name2, " ");//adds space
    scanf("%s", name);//scans user last name
    strcat(name2, name);//adds last name to first name
	printf("Enter the ID of the new student: ");
    scanf("%s", Id);//scans user ID
	printf("Enter the GPA of the new student: ");
    scanf("%s", gpa);//scans user gpa
	printf("Enter the credit hours of the new student: ");
    scanf("%s", credit);//scans user credit hours
	printf("Successfully added the following student to the database!\n");
    printf("%s:\n",name2);//prints user name
    printf("\tId - %s\n",Id);//prints user ID
    printf("\tGPA - %s\n",gpa);//prints user GPA
    printf("\tCredit Hours - %s\n",credit);//prints user credit hours
    add(&database,name2,Id,gpa,credit);//adds student to database
        validInput2 =true;
    }

    else if(strcmp(userInput2, "R") == 0){//checks if student wants to read the database
        validInput2 =true;
        int value = 0;
        printf("Select one of the following: \n");//prints menu messages
	    printf("\t1) Display the head (first 10 rows) of the database\n");
	    printf("\t2) Display students on the honor roll, in order of their GPA\n");
	    printf("\t3) Display students on academic probation, in order of their GPA\n");
	    printf("\t4) Display freshmen students, in order of their name\n");
	    printf("\t5) Display sophomore students, in order of their name\n");
	    printf("\t6) Display junior students, in order of their name\n");
	    printf("\t7) Display senior students, in order of their name\n");
	    printf("\t8) Display the information of a particular student\n");
        while(!validInput3){
	    printf("Your choice --> ");//takes user input
        scanf("%d",&value);
        if(value == 1){//displays first 10 rows
            addToId(&database);
            printHead(database);
            validInput3 = true; 
        }

        else if(value == 2){//displays honor roll students
            addToHonorRoll(&database);
            printHonorRoll(database);
            validInput3 = true; 
        }

        else if(value == 3){//displayes students on probation
            addToProbation(&database);
            printProbation(database);
            validInput3 = true;
        }

         else if(value == 4){//displays students on freshamn list
            addToFreshman(&database);
            printFreshStudents(database);
            validInput3 = true;
        }

        else if(value == 5){//displays students on sophmore list
            addToSophmore(&database);
            printSophStudents(database);
            validInput3 = true;
        }

        else if(value == 6){//displays students on sophmore list
            addToJunior(&database);
            printJuniorStudents(database);
            validInput3 = true;
        }

        else if(value == 7){//displays students on sophmore list
            addToSenior(&database);
            printSeniorStudents(database);
            validInput3 = true;
        }
        
        else if(value == 8){//displays students on sophmore list
            char userID[81]; 
            printf("Enter the id of the student to find: ");
            scanf("%s",userID);
            if(printStudent(database,userID)){
            }

            else{
                printf("Sorry, there is no student in the database with the id %s.\n",userID);
            }
            validInput3 = true;
        }

        else{
            validInput3 = false;
	        printf("Sorry, that input was invalid. Please try again.\n\n");
        }
        }
        validInput3 = false;
    }

    else if(strcmp(userInput2, "D") == 0){//checks if student wants to delete a student
        printf("Enter the id of the student to be removed: ");
        char userID[81]; 
        scanf("%s",userID);
         if(deleteStudent(&database,userID) == true){
            
            }

        else{
            printf("Sorry, there is no student in the database with the id %s.\n",userID);
        }
        validInput2 =true;

    }

    else if(strcmp(userInput2, "X") == 0){//checks if user wants to exit program
        validInput2 =true;
        endGame = true;
        break;
    }

    else{
	validInput2 =false;
    printf("Invalid option. Try again.\n");   
    }
    }
    validInput2 = false;
    }
     deleteDatabase(&database);

    printf("\nThanks for playing!\n");
	printf("Exiting...\n");
    return 0;
}