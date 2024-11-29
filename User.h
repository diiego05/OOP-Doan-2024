#ifndef USER_H
#define USER_H 

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "C:\\Users\\PC\\Desktop\\poooop\\Loan.h"
#include "C:\\Users\\PC\\Desktop\\poooop\\Transaction.h"
#include "C:\\Users\\PC\\Desktop\\poooop\\Report.h"

using namespace std;

// Định nghĩa lớp Account
class Account {
public:
    string accountID;
    string accountName;
    double balance;

    Account(string id, string name, double balance)
        : accountID(id), accountName(name), balance(balance) {}
};

// Định nghĩa lớp User
class User {
private:
    string userID;
    string name;
    string email;
    string password;
    vector<Account> listAccount;

public:
    User() = default;
    User(string id, string name, string email, string password)
        : userID(id), name(name), email(email), password(password) {}

    string getUserID() const { return userID; } 
    bool authenticate(const string& inputPassword) const {
        return password == inputPassword;
    }

    // Thêm tài khoản
    void addAccount() {
        string id, accountName;
        double balance;
        cout << "Nhap ID tai khoan: ";
        cin >> id;
        cin.ignore(); 
        cout << "Nhap ten tai khoan: ";
        getline(cin, accountName);
        cout << "Nhap so du ban dau: ";
        cin >> balance;
        listAccount.emplace_back(id, accountName, balance);
        cout << "Da them tai khoan.\n";
    }

    // Xóa tài khoản
    void deleteAccount() {
        if (listAccount.empty()) {
            cout << "Khong co tai khoan de xoa.\n";
            return;
        }
        string id;
        cout << "Nhap ID tai khoan can xoa: ";
        cin >> id;
        for (auto it = listAccount.begin(); it != listAccount.end(); ++it) {
            if (it->accountID == id) {
                listAccount.erase(it);
                cout << "Da xoa tai khoan.\n";
                return;
            }
        }
        cout << "Tai khoan khong ton tai.\n";
    }

    // Xem số dư các tài khoản
    void viewBalance() {
        if (listAccount.empty()) {
            cout << "Khong co tai khoan nao.\n";
            return;
        }
        cout << "Danh sach so du cac tai khoan:\n";
        for (const auto& acc : listAccount) {
            cout << "ID: " << acc.accountID
                      << ", Ten: " << acc.accountName
                      << ", So du: " << acc.balance << "\n";
        }
    }

    // Sửa thông tin tài khoản
    void editAccount() {
        if (listAccount.empty()) {
            cout << "Khong co tai khoan nao de sua.\n";
            return;
        }
        string id;
        cout << "Nhap ID tai khoan can sua: ";
        cin >> id;
        for (auto& acc : listAccount) {
            if (acc.accountID == id) {
                cout << "Nhap ten moi: ";
                cin.ignore();
                getline(cin, acc.accountName);
                cout << "Nhap so du moi: ";
                cin >> acc.balance;
                cout << "Da cap nhat thong tin tai khoan.\n";
                return;
            }
        }
        cout << "Tai khoan khong ton tai.\n";
    }

    // Báo cáo tài chính: tổng số dư các tài khoản
    void reportFinancial() {
        if (listAccount.empty()) {
            cout << "Khong co tai khoan nao.\n";
            return;
        }
        double totalBalance = 0;
        for (const auto& acc : listAccount) {
            totalBalance += acc.balance;
        }
        cout << "Tong so du cua tat ca tai khoan: " << totalBalance << "\n";
    }

    // Thêm giao dịch
    void addTransaction(vector<Transaction> &transactionHistory) {
        string accountID;
        double amount;
        cout << "Nhap ID tai khoan: ";
        cin >> accountID;
        cout << "Nhap so tien giao dich: ";
        cin >> amount;

        DateTime currentDate = DateTime().getCurrentDate();
        string type = (amount > 0) ? "Deposit" : "Withdraw";
        string note;
        cout << "Nhap ghi chu: ";
        cin.ignore();
        getline(cin, note);

        Transaction newTransaction(
            Transaction::generateTransactionID(),
            type,
            amount,
            accountID,
            note,
            currentDate
        );

        transactionHistory.push_back(newTransaction);
        cout << "Giao dich thanh cong.\n";
    }

    // Thêm khoản vay
    void addLoan(vector<Loan> &loanList) {
        Loan newLoan;
        newLoan.createLoan();
        loanList.push_back(newLoan);
        cout << "Da them khoan vay thanh cong.\n";
    }

    // Báo cáo tài chính (gồm giao dịch và các khoản vay)
    void viewReports(const vector<Transaction> &transactionHistory, const vector<Loan> &loanList) {
        Report report(transactionHistory, loanList);
        cout << "\n--- BAO CAO TAI CHINH ---\n";
        report.reportIncomeAndExpenditure();
        report.reportLoans();
    }
};

// Đăng nhập
User* login(unordered_map<string, User>& users) {
    string userID, password;
    cout << "\n--- Dang nhap ---\n";
    cout << "Nhap UserID: ";
    cin >> userID;
    cout << "Password: ";
    cin >> password;

    auto it = users.find(userID);
    if (it != users.end() && it->second.authenticate(password)) {
        cout << "Dang nhap thanh cong!\n";
        return &it->second;
    }
    cout << "UserID hoac Password khong dung. Vui long thu lai.\n";
    return nullptr;
}

// Đăng ký người dùng
void registerUser(unordered_map<string, User>& users) {
    string id, name, email, password;
    cout << "\n--- Dang ky tai khoan ---\n";
    cout << "UserID: ";
    cin >> id;

    if (users.find(id) != users.end()) {
        cout << "UserID da ton tai. Vui long chon UserID khac.\n";
        return;
    }

    cout << "Ten: ";
    cin.ignore();
    getline(cin, name);
    cout << "Email: ";
    getline(cin, email);
    cout << "Password: ";
    cin >> password;

    users.emplace(id, User(id, name, email, password));
    cout << "Dang ky thanh cong!\n";
}

#endif
