/**------------------------------------------
//  Project 2 - Music Library
    Course: CS 251, Spring 2023.
    System: Visual Studio Code 2023
    Author: Alejandro Bravo
 ---------------------------------------------**/
#include <fstream>//for file reading
#include <iostream>//for input/output
#include <string> //to use string functions
#include <set>//for set functions
#include <map>//for map functions
using namespace std;
// INSERTS GIVEN HELPERS CODE BELOW - DO NOT REMOVE
#include "helpers.cpp"
// INSERTS GIVEN HELPERS CODE ABOVE - DO NOT REMOVE

//passses set name to make sure every file is only read once, passes filename userwants loaded, passes the library to store it in
void load(map<string, set<string>>& library, string fileName, bool& fileLoaded, set<string>& name) {//function to load the file data 
    string contents;//for artists and songs
    string key;//key that is albums 
    bool continues = true;//sets always to continue until same file is trying to be read
    if (fileName == "") {//if no file detected reads default file
        fileName = "musicdatabase.txt";//default file
    }

    if (name.count(fileName)) {//checks if file has been read
        continues = false;//
    }

    name.insert(fileName);
    ifstream file;
    file.open(fileName);//opens file
    if (file.is_open()) {//checks that file opens
        if (continues) {
            if (!file.fail()) {//checks that file doesnt fail
                while (getline(file, contents)) {//continues until no more can be read
                    if (library.count(contents)) {//checks if first line is unique so once it reads same album name a new key should be created for next
                        key = "";//sets key to empty so it can be stored as a key
                    }
                    else if (key.empty()) {//if key is empty its unique and stores the line of the album
                        key = contents;//stores album name as key
                    }
                    else {
                        library[key].insert(contents);//else stores artist name and songs in the set of the map
                    }
                }
            }
        }
        file.close();//closes file
        fileLoaded = true;//sets to true since file is store
    }

    else if (!file.is_open()) {//prints error message when file not found;
        cout << "Error: Could not open music library file - " << fileName << endl;//else if no file in directory prints error message
        file.close();//closes file
    }
}

void printLibrary(map<string, set<string>>& library) {//prints out library 
    cout << "Your Current Music Library Includes" << endl;
    cout << "===================================" << endl;
    for (auto& [key, values] : library) {//goes through the map
        cout << key << endl;//prints the keys
        for (auto& contents : values) {//goes through the set in the map
            if (!isdigit(contents.at(0))) {//checks that its an artist
                cout << " " << contents << endl;//prints out artist
            }
        }
        for (auto& contents : values) {
            if (isdigit(contents.at(0))) {//checks that its a song
                cout << "   " << contents << endl;//prints song
            }
        }
    }
    cout << endl;
}

int songNum(map<string, set<string>>& library) {//function used in stats prints how much songs in the album
    int counter = 0;
    for (auto& [key, values] : library) {//loops through map
        for (auto& contents : values) {//loops through set
            if (isdigit(contents.at(0))) {//checks that its a song
                counter++;//increments count
            }
        }

    }
    return counter;//reutrns songs found
}

void stats(map<string, set<string>>& library, bool& fileLoaded, string remains) {//function that prints out the librarys stats
    set<string>compare;//set to store unique artists
    int songs = 0;
    string artist;
    for (auto& [key, values] : library) {//loops through the map
        for (auto& contents : values) {//loops through the set in map
            if (!isdigit(contents.at(0))) {//checks if its an artist
                compare.insert(contents);//inserts artists into set
            }
        }
    }

    cout << "Overall Music Library Stats" << endl;//message that prints out stats of the library
    cout << "===========================" << endl;
    cout << "Total Records: " << library.size() << endl;//prints record size
    cout << "Total Unique Artists: " << compare.size() << endl;//prints unique size
    cout << "Total Songs: " << songNum(library) << endl << endl;//prints the amount of songs in library
    if (remains == "-d") {//checks if user input asks to print current library
        printLibrary(library);//outputs current library
    }
}

void exportFile(map<string, set<string>>& library, string remains) {//function to export the library into a file
    ofstream MyFile(remains);//opens file
    if (remains == "") {//checks if user entered file
        MyFile.close();
        MyFile.open("musicdatabase.txt");//opens default file
    }

    for (auto& [key, values] : library) {//loops through map
        MyFile << key << endl;//exports the maps keys
        for (auto& contents : values) {//loops through map's set
            if (!isdigit(contents.at(0))) {//checks if its a artist
                MyFile << contents << endl;//exports artist
            }
        }
        for (auto& contents : values) {//loops through set
            if (isdigit(contents.at(0))) {//checks if its a song
                MyFile << contents << endl;//exports song
            }
        }
        MyFile << key << endl;//exports key at the end of last song
    }
}

void readMap(map<string, set<string>>& library, string e) {//function that reads albums 
    int counter = 0;
    set<string>foundRecords;//set that will be used to store found albums
    for (auto& [key, values] : library) {//loops through map
        if (key.find(e) != string::npos) {//checks to see if key is found
            foundRecords.insert(key);//inserts almbum name into set
            counter++;//increments counter
        }
    }

    if (counter >= 1) {//checks that album is found
        for (auto& e : foundRecords) {
            cout << e << endl;//prints album
        }
    }
}

void readArtist(map<string, set<string>>& library, string e, set<string>& foundRecords) {//function that searches user artist
    for (auto& [key, values] : library) {//loops through map
        for (auto& contents : values) {//loops through set
            if (!isdigit(contents.at(0))) {//checks if its an artist
                if (contents.find(e) != string::npos) {//checks that user artist is found in albums
                    foundRecords.insert(key);//stores album name where artist is found
                }
            }
        }
    }
}

void readSong(map<string, set<string>>& library, string e, set<string>& foundRecords) {//function that searches user song
    for (auto& [key, values] : library) {//loops through map
        for (auto& contents : values) {//loops through set
            if (isdigit(contents.at(0))) {//checks if its an song
                if (contents.find(e) != string::npos) {//checks that user song is found in albums
                    foundRecords.insert(key);//stores album name where song is found
                }
            }
        }
    }
}

void songDifference(map<string, set<string>>& library, string first, string second, set<string>& foundRecords) {//function that checks for song differemnce
    for (auto& [key, values] : library) {//loops through the keys
        for (auto& contents : values) {//loops through the contents
            if (isdigit(contents.at(0))) {//checks if its a song
                if (contents.find(first) != string::npos) {//checks if users song is found
                    if (contents.find(second) != string::npos) {//checks if users song is found     
                    }
                    else {
                        foundRecords.insert(key);//stores album name
                    }
                }
            }
        }

    }

}

void artistDifference(map<string, set<string>>& library, string first, string second, set<string>& foundRecords) {//function that finds artist difference
    for (auto& [key, values] : library) {//loops through the keys
        for (auto& contents : values) {//loops through the contents
            if (!isdigit(contents.at(0))) {//checks if its a song
                if (contents.find(first) != string::npos) {//checks if users song is found
                    if (contents.find(second) != string::npos) {//checks if users song is found     
                    }
                    else {
                        foundRecords.insert(key);//stores album name
                    }
                }
            }
        }

    }

}

void songIntersect(map<string, set<string>>& library, set<string>& artists, set<string>& foundRecords) {//function that finds the song intersection
    string word;
    for (auto& a : artists) {//stores artists user wanted into one string
        word += a;
        word += " ";
    }

    word.replace(word.size() - 1, word.size(), "");//checks if any extra space at end is added and removes it
    for (auto& [key, values] : library) {//loops through the keys
        for (auto& contents : values) {//loops through the contents
            if (isdigit(contents.at(0))) {//checks if its a song
                if (contents.find(word) != string::npos) {//checks if users song is found
                    foundRecords.insert(key);//stores album name
                }
            }
        }
    }
}

void artistIntersect(map<string, set<string>>& library, string word, set<string>& foundRecords) {//function that looks for artist intesection
    word.replace(word.size() - 1, word.size(), "");//checks for white space at end of the word and removes it
    for (auto& [key, values] : library) {//loops through map
        for (auto& contents : values) {//loops through maps set
            if (!isdigit(contents.at(0))) {//checks if its an artist
                if (contents.find(word) != string::npos) {//looks for user desired artist
                    foundRecords.insert(key);//stores the album name artist is found in
                }
            }
        }
    }
}

void searchSong(map<string, set<string>>& library, string name) {//function to search song in the library
    set<string>foundRecords;//set to store albums found 
    set<string>song;//set to store song name
    string firstName;
    string secondName;
    bool second = true;
    int counter = 0;
    for (int i = 0; i < name.size(); i++) {
        if (name[i] == ' ') {//checks to see if user input has mutiple names
            counter++;
        }
    }

    if (counter >= 1) {
        splitFirstWord(name, firstName, secondName);
        if (secondName.find('+') != string::npos) {//oooks for the plus operator 
            second = false;
            int index = secondName.find('+');
            if (secondName.at(secondName.size() - 1) == ' ') {//checks for white space at the end of the word
                secondName.replace(secondName.size() - 1, secondName.size(), "");//removes whitespace at end of string

            }
            secondName = secondName.substr(index + 1, secondName.size() - 1);
            firstName[0] = toupper(firstName[0]);//upppercases first letter in user word
            secondName[0] = toupper(secondName[0]);//uppercases first letter in user word
            song.insert(firstName);//inserts song into set
            song.insert(secondName);
            songIntersect(library, song, foundRecords);//looks for intersection 

        }
        else if (secondName.find('-') != string::npos) {//oooks for the plus operator 
            second = false;
            int index = secondName.find('-');
            if (secondName.at(secondName.size() - 1) == ' ') {//checks for white space at the end of the word
                secondName.replace(secondName.size() - 1, secondName.size(), "");//removes whitespace at end of string

            }
            secondName = secondName.substr(index + 1, secondName.size() - 1);
            firstName[0] = toupper(firstName[0]);//upppercases first letter in user word
            secondName[0] = toupper(secondName[0]);//uppercases first letter in user word
            songDifference(library, firstName, secondName, foundRecords);//looks for intersection 

        }

        else {
            tolower(firstName);//lowers user inputs
            tolower(secondName);
            firstName[0] = toupper(firstName[0]);//uppercases first letter in user input
            secondName[0] = toupper(secondName[0]);
            song.insert(firstName);//inserts songs into set
            song.insert(secondName);
        }

    }

    else {//else loop runs when user only searches for one single word song
        tolower(name);//lowercases users one word
        name[0] = toupper(name[0]);//uppercases first letter
        song.insert(name);//inserts song
    }

    if (second) {//checks if mutiple words are used for song
        for (auto& e : song) {//loops through song set
            readSong(library, e, foundRecords);//looks for songs in library
        }
    }
    cout << "Your search results exist in the following albums: " << endl;
    for (auto& e : foundRecords) {//loops through albums that songs are in
        cout << e << endl;//prints out album name
    }
    cout << endl;
}

void searchAlbum(map<string, set<string>>& library, string name) {//function that searches for user album
    set<string>albumNames;//set to store album names
    string firstName;
    string secondName;
    int counter = 0;
    for (int i = 0; i < name.size(); i++) {//for loop to check if user album name is more than one word
        if (name[i] == ' ') {
            counter++;
        }
    }

    if (counter >= 1) {//if loop executes when user album name is more than one word
        splitFirstWord(name, firstName, secondName);
        tolower(firstName);//lowers album name
        tolower(secondName);
        firstName[0] = toupper(firstName[0]);//uppercases first letter in every word in album name
        secondName[0] = toupper(secondName[0]);
        albumNames.insert(firstName);//inserts album name into set
        albumNames.insert(secondName);
    }

    else {//else loop executes when album name is only one word 
        tolower(name);//lowercases album name
        name[0] = toupper(name[0]);//uppercases first letter in album
        albumNames.insert(name);//inserts album name into set
    }
    cout << "Your search results exist in the following albums: " << endl;
    for (auto& e : albumNames) {//loops through album names
        readMap(library, e);//looks for album in library
    }
    cout << endl;
}

void searchArtist(map<string, set<string>>& library, string name) {//function that searches the user artist
    set<string>foundRecords;//stores albums
    set<string>artist;//stores artist
    string firstName;
    string secondName;
    string word;
    bool second = true;
    int counter = 0;
    for (int i = 0; i < name.size(); i++) {//for loop that checks if us artist name is more than one word
        if (name[i] == ' ') {
            counter++;
        }
    }

    if (counter >= 1) {//executes when artist is more than one word
        splitFirstWord(name, firstName, secondName);
        if (secondName.find('+') != string::npos) {//checks for plus operator
            second = false;
            int index = secondName.find('+');
            if (secondName.at(secondName.size() - 1) == ' ') {//checks if end of string has a space
                secondName.replace(secondName.size() - 1, secondName.size(), "");//removes space 
            }
            secondName = secondName.substr(index + 1, secondName.size() - 1);
            firstName[0] = toupper(firstName[0]);//uppercases first letter in artist word
            secondName[0] = toupper(secondName[0]);
            word = firstName + " " + secondName;
            artistIntersect(library, word, foundRecords);//looks for artist intersectection
        }

        else if (secondName.find('-') != string::npos) {//oooks for the plus operator 
            second = false;
            int index = secondName.find('-');
            if (secondName.at(secondName.size() - 1) == ' ') {//checks for white space at the end of the word
                secondName.replace(secondName.size() - 1, secondName.size(), "");//removes whitespace at end of string

            }
            secondName = secondName.substr(index + 1, secondName.size() - 1);
            firstName[0] = toupper(firstName[0]);//upppercases first letter in user word
            secondName[0] = toupper(secondName[0]);//uppercases first letter in user word
            artistDifference(library, firstName, secondName, foundRecords);//looks for intersection 

        }

        else {
            tolower(firstName);//lowercases words of user
            tolower(secondName);
            firstName[0] = toupper(firstName[0]);//uppercases first letter 
            secondName[0] = toupper(secondName[0]);
            artist.insert(firstName);//inserts artist into set
            artist.insert(secondName);
        }
    }

    else {//executes when album name is only one word
        tolower(name);//lowercases artist name
        name[0] = toupper(name[0]);
        artist.insert(name);//inserts artist name
    }

    if (second) {
        for (auto& e : artist) {//loops through artist set
            readArtist(library, e, foundRecords);//looks for artist in set
        }
    }
    cout << "Your search results exist in the following albums: " << endl;
    for (auto& e : foundRecords) {//prints out album name of artist found
        cout << e << endl;
    }
    cout << endl;
}

void search(map<string, set<string>>& library, string remains) {//function that searches for what the user wants
    string type;
    string extra;
    splitFirstWord(remains, type, extra);
    if (type == "album") {//checks to see if user wants to search an album
        searchAlbum(library, extra);
    }
    else if (type == "artist") {//checks to see if user wants to search a artist
        searchArtist(library, extra);
    }

    else if (type == "song") {//checks to see if user wants to search a song
        searchSong(library, extra);
    }
}

int main()
{
    string userEntry;//string for user entry
    string command;//string for user command
    string remains;//string for user fileName or other data
    bool fileLoaded = false;//boolean to keep track if file is loaded
    map<string, set<string>> library;//main map where library/files is stored
    set<string>file;//set to keep count of each file that has been read
    // Display welcome message once per program execution
    cout << "Welcome to the Music Library App" << endl;
    cout << "--------------------------------" << endl;
    // Stay in menu until exit command
    do
    {
        cout << endl;
        cout << "Enter a command (help for help): " << endl;//asks user for command
        getline(cin, userEntry);//takes user input
        cout << endl;
        // Split the user entry into two pieces
        splitFirstWord(userEntry, command, remains);
        tolower(command);//lowers command

        // take an action, one per iteration, based on the command
        if (command == "help")//checks if user command is help
        {
            helpCommand();//calls help command function to print all commands
        }
        else if (command == "clear")//checks if user wants to clear the library
        {
            library.clear();//clears library
        }
        else if (command == "export")//checks if user wants to export library
        {
            exportFile(library, remains);//calls export function to export library so far
        }
        else if (command == "load")//checks if user wants to load data
        {
            load(library, remains, fileLoaded, file);//calls load function to read in files into a map
            //passes main map, filename, boolean to make sure file is loaded once, and set to store files
        }
        else if (command == "stats")//checks if user wants stats
        {
            stats(library, fileLoaded, remains);//calls stats function that prints the stats of the library
            //passes main map, file bool to make sure its data is loaded, and what type of stats user wants
        }
        else if (command == "search")//checks if user wants to search for album/artist
        {
            if (remains == "") {//makes sure user doesnt search nothing
                cout << "Error: Search terms cannot be empty." << endl;
                cout << "No results found." << endl << endl;
            }
            else {
                search(library, remains);//calls search function that looks for what user wants
                //passes main map, and what type of search user wants 
            }
        }
    } while (command != "exit");//keeps looping until user wants to exit
    cout << "Thank you for using the Music Library App" << endl;//prints thank you message
    return 0;
}
