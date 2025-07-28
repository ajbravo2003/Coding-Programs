#include "Account.h"
#include "UserManager.h"
#include <iostream>
#include <algorithm>   // for all_of

using namespace std;

int main() {
    UserManager manager;

    string username, pin;
    cout << "Enter username: ";
    cin >> username;

    if (manager.userExists(username)) {
        cout << "Enter PIN: ";
        cin >> pin;
        if (!manager.verifyPin(username, pin)) {
            cout << "Incorrect PIN.\n";
            return 1;
        }
    } else {
        cout << "New user. Set 4-digit PIN: ";
        cin >> pin;
        while (pin.length() != 4 || !all_of(pin.begin(), pin.end(), ::isdigit)) {
            cout << "Invalid PIN. Enter a 4-digit number: ";
            cin >> pin;
        }
        manager.createUser(username, pin);
        cout << "Account created.\n";
    }

    Account account(username);
    account.loadFromFile();

    int choice;
    double amount;
    do {
        cout << "\n1. Deposit\n2. Withdraw\n3. Balance\n4. History\n5. Save & Exit\n> ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Amount to deposit: ";
                cin >> amount;
                account.deposit(amount);
                break;
            case 2:
                cout << "Amount to withdraw: ";
                cin >> amount;
                account.withdraw(amount);
                break;
            case 3:
                account.showBalance();
                break;
            case 4:
                account.showHistory();
                break;
            case 5:
                account.saveToFile();
                cout << "Data saved. Goodbye!\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while (choice != 5);

    return 0;
}
