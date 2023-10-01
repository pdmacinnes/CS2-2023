/*
Assignment 2 by Patrick MacInnes
*/

#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "IBDAccount.h"
#include <iostream>

// This uses the BankAccount.h
BankAccount::BankAccount(int accountNumber, double balance) : accountNumber(accountNumber), balance(balance) {}

int BankAccount::getAccountNumber() const 
{
    return accountNumber;
}

double BankAccount::getBalance() const 
{
    return balance;
}

void BankAccount::deposit(double amount) 
{
    if (amount > 0) 
    {
        balance += amount;
        std::cout << "Deposited $" << amount << ". New balance: $" << balance << std::endl;
    } else 
    {
        std::cout << "Invalid deposit amount." << std::endl;
    }
}

void BankAccount::withdraw(double amount) 
{
    if (amount > 0 && amount <= balance) 
    {
        balance -= amount;
        std::cout << "Withdrawn $" << amount << ". New balance: $" << balance << std::endl;
    } else {
        std::cout << "Invalid withdrawal amount or insufficient balance." << std::endl;
    }
}

void BankAccount::printAccountInfo() const 
{
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Balance: $" << balance << std::endl;
}

// This uses the CheckingAccount.h
CheckingAccount::CheckingAccount(int accountNumber, double balance, double interestRate, double minBalance, double serviceCharges)
    : BankAccount(accountNumber, balance), interestRate(interestRate), minBalance(minBalance), serviceCharges(serviceCharges) {}

void CheckingAccount::setInterestRate(double rate) 
{
    interestRate = rate;
}

double CheckingAccount::getInterestRate() const 
{
    return interestRate;
}

void CheckingAccount::setMinBalance(double minBalance) 
{
    this->minBalance = minBalance;
}

double CheckingAccount::getMinBalance() const 
{
    return minBalance;
}

void CheckingAccount::setServiceCharges(double charges) 
{
    serviceCharges = charges;
}

double CheckingAccount::getServiceCharges() const
 {
    return serviceCharges;
}

void CheckingAccount::postInterest() 
{
    double interest = getBalance() * interestRate;
    deposit(interest);
}

bool CheckingAccount::belowMinBalance() const 
{
    return getBalance() < minBalance;
}

void CheckingAccount::writeCheck(double amount) 
{
    if (amount > 0) 
    {
        // Check if the account has enough balance
        if (getBalance() >= amount) 
        {
            withdraw(amount);
            std::cout << "Check for $" << amount << " has been written." << std::endl;
        } else 
        {
            std::cout << "Insufficient balance to write the check." << std::endl;
        }
    } else 
    { 
        std::cout << "Invalid check amount." << std::endl;
    }
}

void CheckingAccount::withdraw(double amount) 
{
    if (amount > 0 && amount <= balance) 
    {
        balance -= amount;
        std::cout << "Withdrawn $" << amount << ". New balance: $" << balance << std::endl;
    } else 
    {
        std::cout << "Invalid withdrawal amount or insufficient balance." << std::endl;
    }
}

void CheckingAccount::printAccountInfo() const 
{
    std::cout << "Checking Account Information:" << std::endl;
    std::cout << "Account Number: " << getAccountNumber() << std::endl;
    std::cout << "Balance: $" << getBalance() << std::endl;
    std::cout << "Interest Rate: " << interestRate << std::endl;
    std::cout << "Minimum Balance Requirement: $" << minBalance << std::endl;
    std::cout << "Service Charges: $" << serviceCharges << std::endl;
}

// This uses the SavingsAccount.h
SavingsAccount::SavingsAccount(int accountNumber, double balance, double interestRate)
    : BankAccount(accountNumber, balance), interestRate(interestRate) {}

void SavingsAccount::setInterestRate(double rate) 
{
    interestRate = rate;
}

double SavingsAccount::getInterestRate() const 
{
    return interestRate;
}

void SavingsAccount::postInterest() 
{
    // Calculate and post interest based on the interest rate
    double interest = getBalance() * interestRate;
    deposit(interest); // Deposit the interest into the account
    std::cout << "Interest of $" << interest << " has been posted." << std::endl;
}

void SavingsAccount::withdraw(double amount) 
{
    if (amount > 0 && amount <= getBalance()) 
    {
        balance -= amount;
        std::cout << "Withdrawn $" << amount << ". New balance: $" << balance << std::endl;
    } else 
    {
        std::cout << "Invalid withdrawal amount or insufficient balance." << std::endl;
    }
}

void SavingsAccount::printAccountInfo() const 
{
    std::cout << "Savings Account Information:" << std::endl;
    std::cout << "Account Number: " << getAccountNumber() << std::endl;
    std::cout << "Balance: $" << getBalance() << std::endl;
    std::cout << "Interest Rate: " << interestRate << std::endl;
}

// This uses the IBDAccount.h
IBDAccount::IBDAccount(int accountNumber, double balance, double interestRate)
    : SavingsAccount(accountNumber, balance, interestRate), termMonths(12), withdrawalsPerTerm(0){}

void IBDAccount::setTerm(int months) 
{
    if (months == 6 || months == 12) 
    {
        termMonths = months;
        withdrawalsPerTerm = 0; // Reset withdrawals for the new term
    } else 
    {
        std::cout << "Invalid term duration. Allowed values are 6 or 12 months." << std::endl;
    }
}

void IBDAccount::deposit(double amount)
{
    if (withdrawalsPerTerm == 0) 
    {
        SavingsAccount::deposit(amount);
    } else 
    {
        std::cout << "Deposits are restricted to once per term." << std::endl;
    }
}

void IBDAccount::withdraw(double amount) 
{
    if (withdrawalsPerTerm == 0) 
    {
        SavingsAccount::withdraw(amount);
        withdrawalsPerTerm++;
    } else 
    {
        std::cout << "Withdrawals are restricted to once per term." << std::endl;
    }
}

void IBDAccount::postInterest() 
{
    if (termMonths == 6) 
    {
        // Calculate and post interest for a 6-month term
        double termInterest = getBalance() * (interestRate * 0.8);
        deposit(termInterest);
        std::cout << "6-Month Term Interest Applied: $" << termInterest << std::endl;
    } else if (termMonths == 12) 
    {
        // Calculate and post interest for a 12-month term
        double termInterest = getBalance() * interestRate;
        deposit(termInterest);
        std::cout << "12-Month Term Interest Applied: $" << termInterest << std::endl;
    }
}

void IBDAccount::printAccountInfo() const 
{
    SavingsAccount::printAccountInfo();
    std::cout << "Term Duration: " << termMonths << " months" << std::endl;
}

// Test functions with all thre scenarios
void runBankAccountTests() 
{
    std::cout << "Testing BankAccount class:" << std::endl;

    // Test 1: Valid deposit and withdrawal
    BankAccount account1(1001, 1000.0);
    account1.deposit(500.0);
    account1.withdraw(200.0);

    // Test 2: Invalid withdrawal
    account1.withdraw(1500.0);

    // Test 3: Attempting a transaction with invalid data
    account1.deposit(-100.0);

    std::cout << "Test 1 - Valid deposit and withdrawal:" << std::endl;
    account1.printAccountInfo();
    std::cout << "Test 2 - Invalid withdrawal (exceeding balance):" << std::endl;
    account1.printAccountInfo();
    std::cout << "Test 3 - Attempting a transaction with invalid data:" << std::endl;
    account1.printAccountInfo();
}

void runCheckingAccountTests() 
{
    std::cout << "Testing CheckingAccount class:" << std::endl;

    // Test 1: Valid check writing
    CheckingAccount account2(2001, 1500.0, 0.02, 1000.0, 10.0);
    account2.writeCheck(500.0);

    // Test 2: Insufficient balance for check writing
    account2.writeCheck(1000.0);

    // Test 3: Attempting a transaction with invalid data
    account2.writeCheck(-200.0);

    std::cout << "Test 1 - Valid check writing:" << std::endl;
    account2.printAccountInfo();
    std::cout << "Test 2 - Insufficient balance for check writing:" << std::endl;
    account2.printAccountInfo();
    std::cout << "Test 3 - Attempting a transaction with invalid data:" << std::endl;
    account2.printAccountInfo();
}

void runSavingsAccountTests() 
{
    std::cout << "Testing SavingsAccount class:" << std::endl;

    // Test 1: Valid deposit and withdrawal
    SavingsAccount account3(3001, 2000.0, 0.03);
    account3.deposit(500.0);
    account3.withdraw(300.0);

    // Test 2: Invalid withdrawal
    account3.withdraw(3000.0);

    // Test 3: Attempting a transaction with invalid data
    account3.deposit(-100.0);

    std::cout << "Test 1 - Valid deposit and withdrawal:" << std::endl;
    account3.printAccountInfo();
    std::cout << "Test 2 - Invalid withdrawal (exceeding balance):" << std::endl;
    account3.printAccountInfo();
    std::cout << "Test 3 - Attempting a transaction with invalid data:" << std::endl;
    account3.printAccountInfo();
}

void runIBDAccountTests() 
{
    std::cout << "Testing IBDAccount class:" << std::endl;

    // Test 1: Valid deposit and withdrawal for IBDAccount
    IBDAccount account4(4001, 3000.0, 0.05);
    account4.setTerm(12); // Set a 12-month term
    account4.deposit(1000.0);
    account4.withdraw(500.0);
    account4.postInterest(); // Test postInterest for a 12-month term

    // Test 2: Attempting a withdrawal before the term ends
    account4.setTerm(6); // Set a 6-month term
    account4.withdraw(1000.0);

    // Test 3: Attempting a transaction with invalid data
    account4.deposit(-200.0);

    std::cout << "Test 1 - Valid deposit and withdrawal for IBDAccount:" << std::endl;
    account4.printAccountInfo();
    std::cout << "Test 2 - Attempting a withdrawal before the term ends:" << std::endl;
    account4.printAccountInfo();
    std::cout << "Test 3 - Attempting a transaction with invalid data:" << std::endl;
    account4.printAccountInfo();
}

int main() 
{
    runBankAccountTests();
    runCheckingAccountTests();
    runSavingsAccountTests();
    runIBDAccountTests();
    return 0;
}
