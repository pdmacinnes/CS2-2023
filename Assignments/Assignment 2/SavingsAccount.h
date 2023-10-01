#pragma once
#include "BankAccount.h"

class SavingsAccount : public BankAccount 
{
public:
    SavingsAccount(int accountNumber, double balance, double interestRate);
    void setInterestRate(double rate);
    double getInterestRate() const;
    virtual void postInterest();
    void withdraw(double amount) override;
    virtual void printAccountInfo() const;

protected:
    double interestRate;
};
