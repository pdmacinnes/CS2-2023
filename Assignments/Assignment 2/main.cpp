#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "IBDAccount.h"
#include <iostream>

int main() {
    // Test BankAccount
    BankAccount account1(1001, 1000.0);
    account1.deposit(500.0);
    account1.withdraw(200.0);

    std::cout << "Bank Account Information:" << std::endl;
    std::cout << "Account Number: " << account1.getAccountNumber() << std::endl;
    std::cout << "Balance: $" << account1.getBalance() << std::endl;

    // Test CheckingAccount
    CheckingAccount checking1(2001, 2000.0, 0.03, 500.0, 25.0);
    checking1.deposit(1000.0);
    checking1.withdraw(600.0);
    checking1.postInterest();

    std::cout << "\nChecking Account Information:" << std::endl;
    std::cout << "Account Number: " << checking1.getAccountNumber() << std::endl;
    std::cout << "Balance: $" << checking1.getBalance() << std::endl;

    // Test SavingsAccount
    SavingsAccount savings1(3001, 3000.0, 0.05);
    savings1.deposit(500.0);
    savings1.withdraw(200.0);
    savings1.postInterest();

    std::cout << "\nSavings Account Information:" << std::endl;
    std::cout << "Account Number: " << savings1.getAccountNumber() << std::endl;
    std::cout << "Balance: $" << savings1.getBalance() << std::endl;

    // Test IBDAccount
    IBDAccount ibd1(4001, 4000.0, 0.06);
    ibd1.deposit(1000.0);
    ibd1.withdraw(200.0);
    ibd1.postInterest();

    std::cout << "\nIBD Account Information:" << std::endl;
    std::cout << "Account Number: " << ibd1.getAccountNumber() << std::endl;
    std::cout << "Balance: $" << ibd1.getBalance() << std::endl;

    // Further testing, error handling, and boundary tests can be added based on your requirements.

    return 0;
}
