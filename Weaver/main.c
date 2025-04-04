/**------------------------------------------
//  Project 2 - Weaver
	Course: CS 211, Spring 2023.
	System: Visual Studio Code 2023
	Author: Alejandro Bravo
 ---------------------------------------------**/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
int wordsFound(int length) {//function that finds amount of words found
	int counter = 0;
	char filename[] = "words.txt";
	FILE* filePtr = fopen(filename, "r"); // "r" means we open the file for reading
	// Check that the file was able to be opened
	if (filePtr == NULL) {
		printf("Error: could not open %s for reading\n", filename);
		exit(-1);
	}

	// Read each word from file, and print them one by one
	char inputString[81];
	while (fscanf(filePtr, "%s", inputString) != EOF) {
		if (strlen(inputString) == length) {
			counter++;//adds to counter
		}
	}

	// Close the file
	fclose(filePtr);
	return counter;//returns counter of words that file has found with that specfic length
}

void freeArray(char** array, int size) {//frees the array
	for (int i = 0; i < size; i++) {
		free(*(array + i));//frees every row in the array
	}
	free(array); //frees the array
}

void add(char* fileWord, char*** theArray, int* currentSize, int* maxSize) {//function that adds data in array
	char** pNew = NULL;//makes new pointer to transger array
	if (*currentSize >= *maxSize) { // checks if the array needs more space
		pNew = malloc(sizeof(char*) * (*currentSize + 1)); // allocate memory to be able to store more words
		*maxSize = (*maxSize + 1);//increases size of array
		for (int i = 0; i < *currentSize; i++) { // copy old values to new array
			*(pNew + i) = *(*theArray + i);//sets values of old array to new array
		}
		free(*theArray); // frees old array
		*theArray = pNew; // points to new array
	}
	char* newString = malloc(sizeof(char) * (strlen(fileWord) + 1));//creates new string to copy old string
	strcpy(newString, fileWord);//copies file word to one string 
	*(*theArray + *currentSize) = newString;//sets string into the array
	(*currentSize)++;//increases current size
}

bool isFound(char** array, char* beginWord, char* endWord, int size) {//checks to see if words are in the dictionary
	bool found1 = false;//intiliazed bool variables
	bool found2 = false;
	for (int i = 0; i < size; i++) {//loops through array
		if (strcmp(*(array + i), beginWord) == 0) {//checks in array if user entered words are in dictionary
			found1 = true;//sets to true
		}
	}

	if (!found1) {//if dictionary word isnt found gives error message
		printf("Your word, '%s', is not a valid dictionary word. Try again.\n", beginWord);
	}
	else {
		for (int i = 0; i < size; i++) {//loops through array 
			if (strcmp(*(array + i), endWord) == 0) {//compares the arraay value and user word
				found2 = true;//sets to true if found in dictionary

			}
		}

		if (!found2) {//if word isnt found error is outputted
			printf("Your word, '%s', is not a valid dictionary word. Try again.\n", endWord);
		}
	}

	if (found1 && found2) {//if both words are found returns true
		return true;
	}

	else {
		return false;//if one of the words isnt found return false
	}

}

bool isFound2(char** array, char* beginWord, int* size) {//checks to see if words are in the dictionary
	bool found1 = false;//intiliazed bool variables
	for (int i = 0; i < size; i++) {//loops through array
		if (strcmp(*(array + i), beginWord) == 0) {//checks in array if user entered words are in dictionary
			found1 = true;//sets to true
			break;
		}
	}

	if (!found1) {//if dictionary word isnt found gives error message
		printf("Your word, '%s', is not a valid dictionary word. Try again.\n", beginWord);
	}

	if (found1) {//if both words are found returns true
		return true;
	}

	else {
		return false;//if one of the words isnt found return false
	}
}

void randomWord(char* Word, char** array, int length) {//function that gives random word from dictionary
	int number = (rand() % length);//picks random word
	for (int i = 0; i < length; i++) {//loops through array
		if (i == number) {//gets word at that index
			strcpy(Word, *(array + i));//passes the string by reference
			break;//breaks so it doesnt keep reading array
		}
	}
}

bool isRight(char* userGuess, char* temp, int* length) {//function that checks if the user only changes word by one character
	int counter = 0;
	for (int i = 0; i < *length; i++) {//loops through the array
		if (temp[i] != userGuess[i]) {//checks how much characters are changed
			counter++;//adds to count
		}
	}

	if (counter == 1) {//if exactly one character is changed then the word is correct
		return true;//returns true
	}
	return false;//if word is changed more than one character returns false
}

bool play(char** array, char* beginWord, char* endWord, int* length, int* size) {//main function that will keep playing the game until user enters q or finishes game
	bool wordLength = false;//initiliazed bool variables
	bool dictWord = false;
	char temp[81] = "";//temp array that holds user guesses
	bool userWon = false;
	bool correctMove = false;
	int counter2 = 1;
	char userGuess[81] = "";//array for user word
	strcpy(temp, beginWord);//copies the beginword to temp array
	while (!userWon && strcmp(userGuess, "q") != 0) {//checks user doesnt output q or doesnt get to the word
		while (!wordLength && !dictWord && !correctMove && strcmp(userGuess, "q") != 0) {//keeps checking to make sure the word meets the length and is dictionary word
			if (counter2 == 1) {
				printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", counter2, beginWord, endWord);//when the first time it prints begin and end word
			}

			else {//when user contiues his guess is previous word and goal word is the end word
				printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", counter2, temp, endWord);
			}
			scanf("%s", userGuess);//takes user input
			int counter = 0;
			if (strcmp(userGuess, "q") == 0) {//checks if user wants to quit
				break;
			}
			if (userWon) {//checks if user wins
				break;
			}
			if (strlen(userGuess) != *length) {//checks length of begin word
				printf("Your word, '%s', is not a %d-letter word. Try again.\n", userGuess, *length);
			}

			else {
				counter++;
			}
			if (counter == 1) {//if both are correct length then continues
				wordLength = true;
				counter = 0;
			}

			if (wordLength) {//checks if word length is met then checks to see if its a dictionary word
				if (isFound2(array, userGuess, *size)) {//checks file to find word
					dictWord = true;
				}

				else {//sets everything back to false to try again
					wordLength = false;
					dictWord = false;
					correctMove = false;
				}
			}

			if (dictWord && wordLength) {//checks to make sure length and the word is in the dictionary
				if (isRight(userGuess, temp, length)) {//checks if user moves only one character
					strcpy(temp, userGuess);//sets the user guess the temp
				}

				else {//if moves more than one character than error message is outputted
					printf("Your word, '%s', is not exactly 1 character different. Try again.\n", userGuess);
					wordLength = false;
					dictWord = false;
					correctMove = false;
				}
			}
		}

		if (strcmp(temp, endWord) != 0) {//checks to see if user wins(finds the end word)
			wordLength = false;//sets everything to false if user hasnt won
			dictWord = false;
			correctMove = false;
		}

		else {
			userWon = true;//user word is the same as end word so user wins and breaks 
			break;
		}
		counter2++;
	}

	if (userWon) {//checks if user won
		printf("Congratulations! You changed '%s' into '%s' in %d moves.\n", beginWord, endWord, counter2);//prints win message 
	}

	return true;
}

int main() {
	srand(1);//for gradescope submissions and random generator
	char* array = NULL;//char array that will hold all words
	int length = 0;//initiliaze sizes to keep growing array
	int currentSize = 0;
	int maxSize = 0;
	bool wordLength = false;
	bool dictWord = false;
	bool played = false;
	char beginWord[81];//user begin word array
	char endWord[81];//user end word array
	int continueGame = 0;//user end word array
	int size = 0;
	int length2 = 0;
	array = malloc(sizeof(char) * maxSize);//makes space for one spot in array
	printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");//prints welcome/game message
	printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
	printf("Enjoy!\n\n");
	printf("How many letters do you want to have in the words? ");
	scanf("%d", &length);//takes user length word
	printf("Number of %d-letter words found: %d.\n\n", length, wordsFound(length));//tells user how much words found of length
	size = wordsFound(length);
	char filename[] = "words.txt";//gets file of words text
	FILE* filePtr = fopen(filename, "r"); // "r" means we open the file for reading
	if (filePtr == NULL) {//gives error if file cant be found
		printf("Error: could not open %s for reading\n", filename);
		exit(-1);
	}

	// Read each word from file, and print them one by one
	char inputString[81] = "";
	while (fscanf(filePtr, "%s", inputString) != EOF) {//reads in file using string
		if (strlen(inputString) == length) {//checks length is user length
			add(inputString, &array, &currentSize, &maxSize);//calls add function to dynamically grow array
		}
	}

	// Close the file
	fclose(filePtr);
	while (!played) {
		printf("Enter starting and ending words, or 'r' for either for a random word: ");//asks user to pick their starting words
		scanf("%s", beginWord);//reads user words
		scanf("%s", endWord);
		if (strcmp(beginWord, "r") == 0) {//gives random word if r is inputted
			randomWord(beginWord, array, size);
		}

		if (strcmp(endWord, "r") == 0) {
			randomWord(endWord, array, size);
		}

		while (!wordLength && !dictWord) {//keeps checking to make sure the word meets the length and is dictionary word
			int counter = 0;
			if (strlen(beginWord) != length) {//checks length of begin word
				printf("Your word, '%s', is not a %d-letter word. Try again.\n", beginWord, length);

			}
			else {
				counter++;
				if (strlen(endWord) != length) {//checks end word length
					printf("Your word, '%s', is not a %d-letter word. Try again.\n", endWord, length);
				}
				else {
					counter++;
				}

			}
			if (counter == 2) {//if both are correct length then continues
				wordLength = true;
				counter = 0;
			}
			else {
				printf("Enter starting and ending words, or 'r' for either for a random word: ");//if not the right size user trys again
				scanf("%s", beginWord);//takes users new words
				scanf("%s", endWord);
				if (strcmp(beginWord, "r") == 0) {
					randomWord(beginWord, array, size);//gives random word if they want
				}

				if (strcmp(endWord, "r") == 0) {
					randomWord(endWord, array, size);//gives random word
				}
			}

			if (wordLength) {//checks if word length is met then checks to see if its a dictionary word
				if (isFound(array, beginWord, endWord, currentSize)) {//checks file to find word
					dictWord = true;
				}
				else {
					printf("Enter starting and ending words, or 'r' for either for a random word: ");//if word not a dictionary word then ask for user input again
					scanf("%s", beginWord);//takes user word input
					scanf("%s", endWord);
					wordLength = false;

					if (strcmp(beginWord, "r") == 0) {//checks to see if word is random
						randomWord(beginWord, array, size);//gets a random word
					}

					if (strcmp(endWord, "r") == 0) {//checks to see if word is random
						randomWord(endWord, array, size);//gets a randome word
					}
				}
			}
		}

		if (wordLength && dictWord) {//if word meets word length and is from dictionary then plays the game
			printf("Your starting word is: %s.\n", beginWord);//prints out game information
			printf("Your ending word is: %s.\n\n", endWord);
			printf("On each move enter a word of the same length that is at most 1 character different and is also in the dictionary.\n");
			printf("You may also type in 'q' to quit guessing.\n");
			if (play(array, beginWord, endWord, &length, &size)) {//user plays the game until won or quit
				played = true;
			}
		}

		printf("\nEnter: \t1 to play again,\n");//asks user if they want to play again or quit
		printf("\t2 to change the number of letters in the words and then play again, or\n");
		printf("\t3 to exit the program.\n");
		printf("Your choice --> ");
		scanf("%d", &continueGame);
		if (continueGame == 1) {
			played = false;//sets all bools to false so game contiunes with same amount of letters
			dictWord = false;
			wordLength = false;

		}

		else if (continueGame == 2) {//continues game with new letter length
			freeArray(array,size);//frees the array before resizing
			array = malloc(sizeof(char) * maxSize);//makes space for one spot in array
			printf("How many letters do you want to have in the words?");
			scanf("%d", &length2);//takes the length of new words
			length = length2;//sets orginal length to new length
			printf("Number of %d-letter words found: %d.\n\n", length, wordsFound(length));//tells user how much words found of length
			size = wordsFound(length);//sets size to new word length
			filePtr = fopen(filename, "r"); // "r" means we open the file for reading
			if (filePtr == NULL) {//gives error if file cant be found
				printf("Error: could not open %s for reading\n", filename);
				exit(-1);
			}
			currentSize = 0;//set sizes back to 0
			maxSize = 0;
			//Read each word from file, and print them one by one
			while (fscanf(filePtr, "%s", inputString) != EOF) {//reads in file using string
				if (strlen(inputString) == length) {//checks length is user length
					add(inputString, &array, &currentSize, &maxSize);//calls add function to dynamically grow array	
				}
			}
			fclose(filePtr);//closes file
			played = false;//sets bools to false so game can continue
			dictWord = false;
			wordLength = false;
		}

		else if (continueGame == 3) {//exits the game
			printf("\n");
			played = true;//sets to true so it stops the game
		}
	}
	freeArray(array,size);//frees the array after exiting
	printf("Thanks for playing!\n");
	printf("Exiting...");
	return 0;
}