#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <unordered_map>

class UserManager {
private:
    std::string dbFile = "users.db";
    std::unordered_map<std::string, std::string> users;

public:
    UserManager();
    bool loadUsers();
    bool userExists(const std::string& username);
    bool verifyPin(const std::string& username, const std::string& pin);
    void createUser(const std::string& username, const std::string& pin);
};

#endif
