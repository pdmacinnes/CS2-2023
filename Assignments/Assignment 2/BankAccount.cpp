#include "BankAccount.h"
#include <iostream>

BankAccount::BankAccount(int accountNumber, double balance) : accountNumber(accountNumber), balance(balance) {}

int BankAccount::getAccountNumber() const {
    return accountNumber;
}

double BankAccount::getBalance() const {
    return balance;
}

void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        std::cout << "Deposited $" << amount << ". New balance: $" << balance << std::endl;
    } else {
        std::cout << "Invalid deposit amount." << std::endl;
    }
}

void BankAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        std::cout << "Withdrawn $" << amount << ". New balance: $" << balance << std::endl;
    } else {
        std::cout << "Invalid withdrawal amount or insufficient balance." << std::endl;
    }
}

void BankAccount::printAccountInfo() const {
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Balance: $" << balance << std::endl;
}

