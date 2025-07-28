#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

class Transaction {
public:
    std::string type;
    double amount;
    std::string date;

    Transaction(std::string t, double amt);
    Transaction(std::string t, double amt, std::string d);
    void print() const;
};

class Account {
private:
    double balance;
    std::vector<Transaction> history;
    std::string username;

public:
    Account(std::string user);
    void deposit(double amount);
    void withdraw(double amount);
    void showBalance() const;
    void showHistory() const;
    void saveToFile() const;
    void loadFromFile();
};

#endif
