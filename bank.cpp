#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Account
{
    int accountNumber;
    string name;
    double balance;
};

vector<Account> accounts;

void loadAccounts()
{
    ifstream file("accounts.txt");
    if (file)
    {
        Account acc;
        while (file >> acc.accountNumber >> acc.name >> acc.balance)
        {
            accounts.push_back(acc);
        }
        file.close();
    }
}

void saveAccounts()
{
    ofstream file("accounts.txt");
    for (const auto &acc : accounts)
    {
        file << acc.accountNumber << " " << acc.name << " " << acc.balance << endl;
    }
    file.close();
}

bool accountExists(int accNum)
{
    for (const auto &acc : accounts)
    {
        if (acc.accountNumber == accNum)
            return true;
    }
    return false;
}

void createAccount()
{
    Account newAcc;
    cout << "Enter Account Number: ";
    cin >> newAcc.accountNumber;
    if (accountExists(newAcc.accountNumber))
    {
        cout << "Error: Account number already exists!\n";
        return;
    }
    cout << "Enter Name: ";
    cin >> newAcc.name;
    cout << "Enter Initial Balance: ";
    cin >> newAcc.balance;
    if (newAcc.balance < 0)
    {
        cout << "Error: Initial balance cannot be negative!\n";
        return;
    }
    accounts.push_back(newAcc);
    saveAccounts();
    cout << "Account Created Successfully!\n";
}

void deposit()
{
    int accNum;
    double amount;
    cout << "Enter Account Number: ";
    cin >> accNum;
    for (auto &acc : accounts)
    {
        if (acc.accountNumber == accNum)
        {
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            if (amount < 0)
            {
                cout << "Error: Cannot deposit a negative amount!\n";
                return;
            }
            acc.balance += amount;
            saveAccounts();
            cout << "Deposit Successful! New Balance: " << acc.balance << "\n";
            return;
        }
    }
    cout << "Error: Account not found!\n";
}

void withdraw()
{
    int accNum;
    double amount;
    cout << "Enter Account Number: ";
    cin >> accNum;
    for (auto &acc : accounts)
    {
        if (acc.accountNumber == accNum)
        {
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;
            if (amount < 0 || amount > acc.balance)
            {
                cout << "Error: Invalid withdrawal amount!\n";
                return;
            }
            acc.balance -= amount;
            saveAccounts();
            cout << "Withdrawal Successful! New Balance: " << acc.balance << "\n";
            return;
        }
    }
    cout << "Error: Account not found!\n";
}

void displayAccounts()
{
    cout << left << setw(15) << "Account Number" << setw(15) << "Name" << setw(15) << "Balance" << endl;
    for (const auto &acc : accounts)
    {
        cout << left << setw(15) << acc.accountNumber << setw(15) << acc.name << setw(15) << acc.balance << endl;
    }
}

void deleteAccount()
{
    int accNum;
    cout << "Enter Account Number to delete: ";
    cin >> accNum;
    for (auto it = accounts.begin(); it != accounts.end(); ++it)
    {
        if (it->accountNumber == accNum)
        {
            accounts.erase(it);
            saveAccounts();
            cout << "Account Deleted Successfully!\n";
            return;
        }
    }
    cout << "Error: Account not found!\n";
}

int main()
{
    loadAccounts();
    int choice;
    do
    {
        cout << "\nBank Management System\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Display Accounts\n";
        cout << "5. Delete Account\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            deposit();
            break;
        case 3:
            withdraw();
            break;
        case 4:
            displayAccounts();
            break;
        case 5:
            deleteAccount();
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }
    } while (choice != 6);
    return 0;
}
