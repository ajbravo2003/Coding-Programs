#include "Account.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

Transaction::Transaction(string t, double amt) : type(t), amount(amt) {
    time_t now = time(0);
    date = ctime(&now);
    date.pop_back(); // remove newline
}

Transaction::Transaction(string t, double amt, string d) : type(t), amount(amt), date(d) {}

void Transaction::print() const {
    cout << setw(10) << type << " | $" << setw(8) << fixed << setprecision(2) << amount << " | " << date << endl;
}

Account::Account(string user) : balance(0.0), username(user) {}

void Account::deposit(double amount) {
    if (amount <= 0) {
        cout << "Invalid deposit.\n";
        return;
    }
    balance += amount;
    history.emplace_back("Deposit", amount);
    cout << "Deposited $" << amount << ". New balance: $" << balance << endl;
}

void Account::withdraw(double amount) {
    if (amount <= 0 || amount > balance) {
        cout << "Invalid or insufficient funds.\n";
        return;
    }
    balance -= amount;
    history.emplace_back("Withdraw", amount);
    cout << "Withdrew $" << amount << ". New balance: $" << balance << endl;
}

void Account::showBalance() const {
    cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
}

void Account::showHistory() const {
    if (history.empty()) {
        cout << "No transactions.\n";
        return;
    }
    for (const auto& t : history)
        t.print();
}

void Account::saveToFile() const {
    string filepath = username + ".txt";
    ofstream out(filepath);
    out << "balance:" << balance << "\n";
    for (const auto& t : history)
        out << t.type << "," << t.amount << "," << t.date << "\n";
    out.close();
}

void Account::loadFromFile() {
    string filepath = username + ".txt";
    ifstream in(filepath);
    if (!in) {
        cout << "New account created.\n";
        return;
    }

    string line;
    getline(in, line);
    if (line.rfind("balance:", 0) == 0)
        balance = stod(line.substr(8));

    while (getline(in, line)) {
        size_t p1 = line.find(',');
        size_t p2 = line.rfind(',');
        if (p1 == string::npos || p2 == string::npos || p1 == p2) continue;

        string type = line.substr(0, p1);
        double amt = stod(line.substr(p1 + 1, p2 - p1 - 1));
        string date = line.substr(p2 + 1);

        history.emplace_back(type, amt, date);
    }
    in.close();
}
