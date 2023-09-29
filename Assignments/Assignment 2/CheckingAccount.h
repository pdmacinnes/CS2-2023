#pragma once
#include "BankAccount.h"

class CheckingAccount : public BankAccount {
public:
    CheckingAccount(int accountNumber, double balance, double interestRate, double minBalance, double serviceCharges);
    void setInterestRate(double rate);
    double getInterestRate() const;
    void setMinBalance(double minBalance);
    double getMinBalance() const;
    void setServiceCharges(double charges);
    double getServiceCharges() const;
    void postInterest();
    bool belowMinBalance() const;
    void writeCheck(double amount);
    void withdraw(double amount) override;
    void printAccountInfo() const;

private:
    double interestRate;
    double minBalance;
    double serviceCharges;
};
