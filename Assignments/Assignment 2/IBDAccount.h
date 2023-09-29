#pragma once
#include "SavingsAccount.h"

class IBDAccount : public SavingsAccount {
public:
    IBDAccount(int accountNumber, double balance, double interestRate);
    void setTerm(int months); // Set the term to 6 or 12 months
    void deposit(double amount) override; // Restrict deposits to once per term
    void withdraw(double amount) override; // Restrict withdrawals to once per term
    void postInterest() override; // Calculate and post term-specific interest
    void printAccountInfo() const override;
    
private:
    int termMonths; // 6 or 12 months term
    int withdrawalsPerTerm; // Track the number of withdrawals in the current term
};
