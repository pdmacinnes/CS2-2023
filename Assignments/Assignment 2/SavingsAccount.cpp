#include "SavingsAccount.h"
#include <iostream>

SavingsAccount::SavingsAccount(int accountNumber, double balance, double interestRate)
    : BankAccount(accountNumber, balance), interestRate(interestRate) {}

void SavingsAccount::setInterestRate(double rate) {
    interestRate = rate;
}

double SavingsAccount::getInterestRate() const {
    return interestRate;
}

void SavingsAccount::postInterest() {
    // Calculate and post interest based on the interest rate
    double interest = getBalance() * interestRate;
    deposit(interest); // Deposit the interest into the account
    std::cout << "Interest of $" << interest << " has been posted." << std::endl;
}

void SavingsAccount::withdraw(double amount) {
    if (amount > 0 && amount <= getBalance()) {
        // Implement withdrawal logic
        balance -= amount;
        std::cout << "Withdrawn $" << amount << ". New balance: $" << balance << std::endl;
    } else {
        std::cout << "Invalid withdrawal amount or insufficient balance." << std::endl;
    }
}

void SavingsAccount::printAccountInfo() const {
    std::cout << "Savings Account Information:" << std::endl;
    std::cout << "Account Number: " << getAccountNumber() << std::endl;
    std::cout << "Balance: $" << getBalance() << std::endl;
    std::cout << "Interest Rate: " << interestRate << std::endl;
}
