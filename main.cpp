#include <iostream>
#include <unordered_map>
#include <vector>
#include "C:\\Users\\PC\\Desktop\\poooop\\Report.h"
#include "C:\\Users\\PC\\Desktop\\poooop\\User.h"
#include "C:\\Users\\PC\\Desktop\\poooop\\Transaction.h"
#include "C:\\Users\\PC\\Desktop\\poooop\\Loan.h"


using namespace std;

int main() {
    unordered_map<string, User> users;
    User* loggedInUser = nullptr;
    vector<Transaction> transactionHistory;
    vector<Loan> loanList;

    int choice;
    do {
        cout << "\n--- MENU CHINH ---\n";
        cout << "1. Dang ky\n";
        cout << "2. Dang nhap\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser(users);
                break;
            case 2:
                loggedInUser = login(users);
                if (loggedInUser) {
                    int userChoice;
                    do {
                        cout << "\n--- MENU TAI KHOAN ---\n";
                        cout << "1. Them tai khoan\n";
                        cout << "2. Xoa tai khoan\n";
                        cout << "3. Xem so du tai khoan\n";
                        cout << "4. Sua tai khoan\n";
                        cout << "5. Bao cao tai chinh\n";
                        cout << "6. Them giao dich\n";
                        cout << "7. Them khoan vay\n";
                        cout << "0. Dang xuat\n";
                        cout << "Nhap lua chon: ";
                        cin >> userChoice;

                        switch (userChoice) {
                            case 1:
                                loggedInUser->addAccount();
                                break;
                            case 2:
                                loggedInUser->deleteAccount();
                                break;
                            case 3:
                                loggedInUser->viewBalance();
                                break;
                            case 4:
                                loggedInUser->editAccount();
                                break;
                            case 5:
                                loggedInUser->viewReports(transactionHistory, loanList);
                                break;
                            case 6:
                                loggedInUser->addTransaction(transactionHistory);
                                break;
                            case 7:
                                loggedInUser->addLoan(loanList);
                                break;
                            case 0:
                                cout << "Dang xuat...\n";
                                loggedInUser = nullptr;
                                break;
                            default:
                                cout << "Lua chon khong hop le.\n";
                        }
                    } while (loggedInUser != nullptr);
                }
                break;
            case 0:
                cout << "Thoat chuong trinh...\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);

    return 0;
}
