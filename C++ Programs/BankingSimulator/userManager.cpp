#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

UserManager::UserManager() {
    loadUsers();
}

bool UserManager::loadUsers() {
    ifstream in(dbFile);
    if (!in) return false;

    string line;
    while (getline(in, line)) {
        istringstream ss(line);
        string username, pin;
        if (getline(ss, username, ',') && getline(ss, pin)) {
            users[username] = pin;
        }
    }
    in.close();
    return true;
}

bool UserManager::userExists(const string& username) {
    return users.find(username) != users.end();
}

bool UserManager::verifyPin(const string& username, const string& pin) {
    return users[username] == pin;
}

void UserManager::createUser(const string& username, const string& pin) {
    ofstream out(dbFile, ios::app);
    out << username << "," << pin << "\n";
    users[username] = pin;
}
