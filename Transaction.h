#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include <iomanip>
#include "C:\\Users\\PC\\Desktop\\poooop\\DateTime.h"  // Đảm bảo rằng đường dẫn này là chính xác trong môi trường của bạn

using namespace std;

class Transaction {
private:
    string transactionID;
    string transactionType;  // "Deposit" hoặc "Withdraw"
    double amount;
    DateTime date;
    string accountID;
    string note;

public:
    // Constructor
    Transaction(string id, string type, double amt, string accID, string note, const DateTime &dt)
        : transactionID(id), transactionType(type), amount(amt), date(dt), accountID(accID), note(note) {}

    // Getters
    string getTransactionID() const { return transactionID; }
    string getTransactionType() const { return transactionType; }
    double getAmount() const { return amount; }
    DateTime getDate() const { return date; }
    string getAccountID() const { return accountID; }
    string getNote() const { return note; }

    // Hiển thị giao dịch
    void printTransaction() const {
        cout << "Transaction ID: " << transactionID << "\n"
             << "Type: " << transactionType << "\n"
             << "Amount: " << fixed << setprecision(2) << amount << "\n"
             << "Date: " << date.toString() << "\n"
             << "Account ID: " << accountID << "\n"
             << "Note: " << note << "\n";
    }

    // Tạo ID giao dịch tự động
    static string generateTransactionID() {
        static int counter = 1;  // Counter để tạo ID giao dịch tự động
        return "T" + to_string(counter++);
    }

    // Destructor (Nếu cần thiết, để quản lý bộ nhớ và tài nguyên khác)
    ~Transaction() {
        cout << "Transaction object destroyed\n";
    }
};

#endif
