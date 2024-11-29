#ifndef REPORT_H
#define REPORT_H

#include <vector>
#include <iostream>
#include <iomanip>
#include "Transaction.h"
#include "Loan.h"

using namespace std;

class Report {
private:
    vector<Transaction> transactionHistory;  // Lịch sử giao dịch
    vector<Loan> loanList;                   // Danh sách các khoản vay

public:
    // Constructor với tham số là lịch sử giao dịch và danh sách các khoản vay
    Report(const vector<Transaction> &transHistory, const vector<Loan> &loans)
        : transactionHistory(transHistory), loanList(loans) {}

    // Báo cáo thu nhập và chi tiêu
    void reportIncomeAndExpenditure() {
        double income = 0, expenditure = 0;

        // Tính toán tổng thu nhập và chi tiêu từ lịch sử giao dịch
        for (const auto &trans : transactionHistory) {
            if (trans.getTransactionType() == "Deposit") {
                income += trans.getAmount();  // Thu nhập
            } else if (trans.getTransactionType() == "Withdraw") {
                expenditure += trans.getAmount();  // Chi tiêu
            }
        }

        // Hiển thị báo cáo thu nhập và chi tiêu
        cout << "Income: " << fixed << setprecision(2) << income << "\n"
             << "Expenditure: " << fixed << setprecision(2) << expenditure << "\n";
    }

    // Báo cáo các khoản vay
    void reportLoans() {
        cout << "\n--- Loan Report ---\n";
        
        // Duyệt qua danh sách các khoản vay và hiển thị thông tin
        if (loanList.empty()) {
            cout << "No loans available.\n";
            return;
        }
        
        for (const auto &loan : loanList) {
            loan.displayLoanDetails();
            loan.displayRepaymentHistory();
            cout << "---------------------------------\n";
        }
    }

    // Báo cáo tổng kết về tài chính
    // void reportFinancialSummary() {
    //     double totalLoanAmount = 0;
    //     for (const auto &loan : loanList) {
    //         totalLoanAmount += loan.calculateInterest();  // Tính tổng lãi suất của các khoản vay
    //     }
    //     cout << "Total Loan Interest: " << fixed << setprecision(2) << totalLoanAmount << "\n";
    // }
};

#endif
