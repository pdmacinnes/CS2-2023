#include "CheckingAccount.h"
#include <iostream>

CheckingAccount::CheckingAccount(int accountNumber, double balance, double interestRate, double minBalance, double serviceCharges)
    : BankAccount(accountNumber, balance), interestRate(interestRate), minBalance(minBalance), serviceCharges(serviceCharges) {}

void CheckingAccount::setInterestRate(double rate) {
    interestRate = rate;
}

double CheckingAccount::getInterestRate() const {
    return interestRate;
}

void CheckingAccount::setMinBalance(double minBalance) {
    this->minBalance = minBalance;
}

double CheckingAccount::getMinBalance() const {
    return minBalance;
}

void CheckingAccount::setServiceCharges(double charges) {
    serviceCharges = charges;
}

double CheckingAccount::getServiceCharges() const {
    return serviceCharges;
}

void CheckingAccount::postInterest() {
    // Calculate and post interest based on the interest rate
    double interest = getBalance() * interestRate;
    deposit(interest); // Deposit the interest into the account
}

bool CheckingAccount::belowMinBalance() const {
    return getBalance() < minBalance;
}

void CheckingAccount::writeCheck(double amount) {
    if (amount > 0) {
        // Check if the account has sufficient balance
        if (getBalance() >= amount) {
            withdraw(amount);
            std::cout << "Check for $" << amount << " has been written." << std::endl;
        } else {
            std::cout << "Insufficient balance to write the check." << std::endl;
        }
    } else {
        std::cout << "Invalid check amount." << std::endl;
    }
}

void CheckingAccount::withdraw(double amount) {
    // Implement the withdrawal logic here
    // You can use the same logic as in the BankAccount::withdraw method.
}

void CheckingAccount::printAccountInfo() const {
    std::cout << "Checking Account Information:" << std::endl;
    std::cout << "Account Number: " << getAccountNumber() << std::endl;
    std::cout << "Balance: $" << getBalance() << std::endl;
    std::cout << "Interest Rate: " << interestRate << std::endl;
    std::cout << "Minimum Balance Requirement: $" << minBalance << std::endl;
    std::cout << "Service Charges: $" << serviceCharges << std::endl;
}
