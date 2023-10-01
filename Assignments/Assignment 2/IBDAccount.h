#pragma once
#include "SavingsAccount.h"

class IBDAccount : public SavingsAccount 
{
public:
    IBDAccount(int accountNumber, double balance, double interestRate);
    void setTerm(int months);
    void deposit(double amount) override;
    void withdraw(double amount) override;
    void postInterest() override;
    void printAccountInfo() const override;
    
private:
    int termMonths;
    int withdrawalsPerTerm;
};
