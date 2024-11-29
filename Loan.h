#ifndef LOAN_H
#define LOAN_H

#include <iostream>
#include <list>
#include <string>
#include "C:\\Users\\PC\\Desktop\\poooop\\DateTime.h"
#include "C:\\Users\\PC\\Desktop\\poooop\\Repayment.h"

// Forward declaration của lớp User
class User;

using namespace std;

class Loan
{
private:
    string loanID;
    string lender;
    string borrower;
    double amount;
    double interestRate;
    DateTime startDate;
    DateTime endDate;
    string status;
    bool isLoan;
    string note;
    User* user;  // Dùng con trỏ tới User thay vì đối tượng User trực tiếp
    list<Repayment> repaymentHistory;

public:
    // Constructor mặc định
    Loan() : loanID(""), lender(""), borrower(""), amount(0), interestRate(0), startDate(), endDate(), status(""), isLoan(false), note(""), user(nullptr) {}

    // Phương thức tạo lịch trình trả nợ
    list<Repayment> getRepaymentSchedule() {
        list<Repayment> repaymentSchedule;
        int numRepayments;
        cout << "Enter number of repayments: ";
        cin >> numRepayments;
        for (int i = 0; i < numRepayments; i++) {
            Repayment repayment;
            repayment.getRepaymentDetails();
            repaymentSchedule.push_back(repayment);
        }
        return repaymentSchedule;
    }

    // Tính lãi suất của khoản vay
    double calculateInterest() {
        return amount * interestRate;
    }

    // Thêm một khoản trả nợ vào lịch sử trả nợ
    void addRepayment() {
        Repayment repayment;
        repayment.getRepaymentDetails();
        repaymentHistory.push_back(repayment);
    }

    // Cập nhật khoản trả nợ
    void updateRepayment() {
        int repaymentID;
        cout << "Enter repayment ID: ";
        cin >> repaymentID;
        list<Repayment>::iterator it;
        for (it = repaymentHistory.begin(); it != repaymentHistory.end(); it++) {
            if (it->getRepaymentID() == repaymentID) {
                it->getRepaymentDetails();
                break;
            }
        }
    }

    // Xóa khoản trả nợ
    void removeRepayment() {
        int repaymentID;
        cout << "Enter repayment ID: ";
        cin >> repaymentID;
        list<Repayment>::iterator it;
        for (it = repaymentHistory.begin(); it != repaymentHistory.end(); it++) {
            if (it->getRepaymentID() == repaymentID) {
                repaymentHistory.erase(it);
                break;
            }
        }
    }

    // Gửi nhắc nhở cho khoản vay quá hạn
    void sendReminder() {
        DateTime currentDate = DateTime().getCurrentDate();
        int daysOverdue = currentDate.calculateDaysDifference(endDate, currentDate);

        if (daysOverdue > 15) {
            cout << "Loan ID: " << loanID << " is overdue by " << daysOverdue << " days!" << endl;
            cout << "Reminder sent to borrower: " << borrower << endl;
        } else {
            cout << "Loan ID: " << loanID << " is not overdue yet." << endl;
        }
    }

    // Tạo thông tin khoản vay
    void createLoan() {
        cout << "Enter loan ID: ";
        cin >> loanID;
        cout << "Enter loan amount: ";
        cin >> amount;
        cout << "Enter interest rate (%): ";
        cin >> interestRate;
        cout << "Enter start date (day month year hour minute): ";
        cin >> startDate.day >> startDate.month >> startDate.year >> startDate.hour >> startDate.minute;
        cout << "Enter end date (day month year hour minute): ";
        cin >> endDate.day >> endDate.month >> endDate.year >> endDate.hour >> endDate.minute;
        if (!startDate.isValid() || !endDate.isValid()) {
            cout << "Invalid dates entered. Please try again.\n";
            createLoan();
        }
    }

    // Hiển thị thông tin khoản vay
    void displayLoanDetails() const {
        cout << "Loan ID: " << loanID << endl
             << "Amount: " << amount << endl
             << "Interest Rate: " << interestRate << "%" << endl
             << "Start Date: " << startDate.toString() << endl
             << "End Date: " << endDate.toString() << endl;
    }

    // Hiển thị lịch sử trả nợ
    void displayRepaymentHistory() const {
        for (const auto &repayment : repaymentHistory) {
            repayment.displayRepaymentDetails();
        }
    }

    // Destructor
    ~Loan() {
        cout << "Loan object destroyed" << endl;
    }

    // Friend class Repayment để truy cập các phương thức của lớp Loan
    friend class Repayment;
};

#endif
