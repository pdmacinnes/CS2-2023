// I read online that #pragma once replaces ifndef, define and endif so I'm using it in this program
#pragma once

class BankAccount 
{
public:
    BankAccount(int accountNumber, double balance);
    int getAccountNumber() const;
    double getBalance() const;
    virtual void deposit(double amount);
    virtual void withdraw(double amount);
    void printAccountInfo() const;

protected:
    double balance;

private:
    int accountNumber;
    
};
