#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#include "Transaction.h"

using namespace std;

class Account {
private:
    string accountID;
    string accountName;
    double balance;
    User user;
    vector<Transaction> listTransaction;

public:
    // Constructor
    Account(string id, string name, double initialBalance, const User& accountUser)
        : accountID(id), accountName(name), balance(initialBalance), user(accountUser) {}

    // Getters
    string getAccountID() const { return accountID; }
    string getAccountName() const { return accountName; }
    double getBalance() const { return balance; }
    User getUser() const { return user; }

    // Deposit money
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "So tien gui khong hop le!" << endl;
            return;
        }
        balance += amount;
        cout << "So tien gui: " << amount << ", So du: " << balance << endl;
    }

    // Transfer money
    void transfer(Account& targetAccount, double amount) {
        if (amount <= 0 || amount > balance) {
            cout << "So tien chuyen khong hop le" << endl;
            return;
        }
        balance -= amount;
        targetAccount.deposit(amount);
        cout << "Da chuyen " << amount << " den tai khoan ID: " << targetAccount.getAccountID() << endl;
    }

    // Withdraw money
    void withdraw(double amount) {
        if (amount <= 0 || amount > balance) {
            cout << "So tien rut khong hop le!" << endl;
            return;
        }
        balance -= amount;
        court << "Da rut: " << amount << ", So du con lai: " << balance << endl;
    }

    // Spending report statistical
    void spendingReportStatistical() const {
        cout << "--- Spending Report ---\n";
        for (const auto& transaction : listTransaction) {
            if (transaction.getTransactionType() == "Rut tien") {
                transaction.printTransaction();
            }
        }
    }

    // Update balance based on transactions
    void updateBalance() {
        balance = 0;
        for (const auto& transaction : listTransaction) {
            if (transaction.getTransactionType() == "Tien gui") {
                balance += transaction.getAmount();
            } else if (transaction.getTransactionType() == "Rut tien") {
                balance -= transaction.getAmount();
            }
        }
        cout << "Da cap nhat so du. So du moi: " << balance << endl;
    }

    // Add a transaction
    void addTransaction(const Transaction& transaction) {
        listTransaction.push_back(transaction);
        cout << "Chuyen khoan: " << transaction.getTransactionID() << endl;
        updateBalance();
    }

    // Destructor
    ~Account() {
        cout << "Account object destroyed\n";
    }
};

#endif
