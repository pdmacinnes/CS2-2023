#include "IBDAccount.h"
#include <iostream>

IBDAccount::IBDAccount(int accountNumber, double balance, double interestRate)
    : SavingsAccount(accountNumber, balance, interestRate), termMonths(12), withdrawalsPerTerm(0) {
    // Initialize properties specific to IBDAccount
}

void IBDAccount::setTerm(int months) {
    if (months == 6 || months == 12) {
        termMonths = months;
        withdrawalsPerTerm = 0; // Reset withdrawals for the new term
    } else {
        std::cout << "Invalid term duration. Allowed values are 6 or 12 months." << std::endl;
    }
}

void IBDAccount::deposit(double amount) {
    if (withdrawalsPerTerm == 0) {
        SavingsAccount::deposit(amount);
    } else {
        std::cout << "Deposits are restricted to once per term." << std::endl;
    }
}

void IBDAccount::withdraw(double amount) {
    if (withdrawalsPerTerm == 0) {
        SavingsAccount::withdraw(amount);
        withdrawalsPerTerm++;
    } else {
        std::cout << "Withdrawals are restricted to once per term." << std::endl;
    }
}

void IBDAccount::postInterest() {
    if (termMonths == 6) {
        // Calculate and post interest for a 6-month term (80% of the 12-month term)
        double termInterest = getBalance() * (interestRate * 0.8);
        deposit(termInterest);
        std::cout << "6-Month Term Interest Applied: $" << termInterest << std::endl;
    } else if (termMonths == 12) {
        // Calculate and post interest for a 12-month term
        double termInterest = getBalance() * interestRate;
        deposit(termInterest);
        std::cout << "12-Month Term Interest Applied: $" << termInterest << std::endl;
    }
}

void IBDAccount::printAccountInfo() const {
    SavingsAccount::printAccountInfo();
    std::cout << "Term Duration: " << termMonths << " months" << std::endl;
}
