#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm> // For find_if
using namespace std;

// Structure to represent a bank account
class Account {
private:
    string accountNumber;
    string accountHolderName;
    double balance;
    vector<string> transactionHistory; // Added transaction history

public:
    Account(string number, string name, double initialDeposit)
        : accountNumber(number), accountHolderName(name), balance(initialDeposit) {
        transactionHistory.push_back("Account created with initial deposit: " + to_string(initialDeposit));
    }

    string getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolderName() const {
        return accountHolderName;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        transactionHistory.push_back("Deposit: +" + to_string(amount) + ", New balance: " + to_string(balance));
    }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            transactionHistory.push_back("Withdrawal: -" + to_string(amount) + ", New balance: " + to_string(balance));
            return true;
        }
        return false;
    }

    const vector<string>& getTransactionHistory() const {
        return transactionHistory;
    }

    // Friend function to allow BankSystem to access private members if needed
    friend class BankSystem;
};

class BankSystem {
private:
    vector<Account> accounts;
    string dataFile = "bank_data.txt";

public:
    BankSystem() {
        loadData();
    }

    ~BankSystem() {
        saveData();
    }

    bool accountExists(const string& accountNumber) const {
        return any_of(accounts.begin(), accounts.end(),
                           [&](const Account& acc){ return acc.getAccountNumber() == accountNumber; });
    }

    void createAccount() {
        string accountNumber, name;
        double initialDeposit;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        if (accountExists(accountNumber)) {
            cout << "Account number already exists.\n";
            return;
        }

        cout << "Enter Account Holder Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Initial Deposit: ";
        cin >> initialDeposit;

        if (cin.fail() || initialDeposit < 0) {
            cout << "Invalid input for initial deposit.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        accounts.emplace_back(accountNumber, name, initialDeposit);
        cout << "Account created successfully.\n";
    }

    void deposit() {
        string accountNumber;
        double amount;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        auto it = find_if(accounts.begin(), accounts.end(),
                             [&](const Account& acc){ return acc.getAccountNumber() == accountNumber; });

        if (it != accounts.end()) {
            cout << "Enter amount to deposit: ";
            cin >> amount;
            if (cin.fail() || amount <= 0) {
                cout << "Invalid deposit amount.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            }
            it->deposit(amount);
            cout << "Deposit successful. Current balance: " << it->getBalance() << "\n";
        } else {
            cout << "Account not found.\n";
        }
    }

    void withdraw() {
        string accountNumber;
        double amount;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        auto it = find_if(accounts.begin(), accounts.end(),
                             [&](const Account& acc){ return acc.getAccountNumber() == accountNumber; });

        if (it != accounts.end()) {
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            if (cin.fail() || amount <= 0) {
                cout << "Invalid withdrawal amount.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            }
            if (it->withdraw(amount)) {
                cout << "Withdrawal successful. Current balance: " << it->getBalance() << "\n";
            } else {
                cout << "Insufficient balance.\n";
            }
        } else {
            cout << "Account not found.\n";
        }
    }

    void viewBalance() const {
        string accountNumber;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        auto it = find_if(accounts.begin(), accounts.end(),
                             [&](const Account& acc){ return acc.getAccountNumber() == accountNumber; });

        if (it != accounts.end()) {
            cout << "Account balance: " << it->getBalance() << "\n";
        } else {
            cout << "Account not found.\n";
        }
    }

    void viewTransactionHistory() const {
        string accountNumber;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        auto it = find_if(accounts.begin(), accounts.end(),
                             [&](const Account& acc){ return acc.getAccountNumber() == accountNumber; });

        if (it != accounts.end()) {
            cout << "\n--- Transaction History for Account: " << it->getAccountNumber() << " ---\n";
            for (const auto& transaction : it->getTransactionHistory()) {
                cout << "- " << transaction << "\n";
            }
            cout << "-------------------------------------------------------\n";
        } else {
            cout << "Account not found.\n";
        }
    }

    void listAccounts() const {
        cout << "\n--- List of Accounts ---\n";
        if (accounts.empty()) {
            cout << "No accounts exist yet.\n";
        } else {
            for (const auto& account : accounts) {
                cout << "Account Number: " << account.getAccountNumber()
                          << ", Holder: " << account.getAccountHolderName()
                          << ", Balance: " << account.getBalance() << "\n";
            }
        }
        cout << "-------------------------\n";
    }

private:
    void saveData() const {
        ofstream outFile(dataFile);
        if (outFile.is_open()) {
            for (const auto& account : accounts) {
                outFile << account.getAccountNumber() << ","
                        << account.getAccountHolderName() << ","
                        << account.getBalance() << "\n";
            }
            outFile.close();
            cout << "Data saved successfully.\n";
        } else {
            cerr << "Unable to open file for saving data.\n";
        }
    }

    void loadData() {
        ifstream inFile(dataFile);
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                stringstream ss(line);
                string segment;
                vector<string> data;
                while (getline(ss, segment, ',')) {
                    data.push_back(segment);
                }
                if (data.size() == 3) {
                    try {
                        accounts.emplace_back(data[0], data[1], stod(data[2]));
                    } catch (const invalid_argument& e) {
                        cerr << "Error parsing data from file: " << e.what() << "\n";
                    } catch (const out_of_range& e) {
                        cerr << "Error parsing data from file: " << e.what() << "\n";
                    }
                } else {
                    cerr << "Invalid data format in file.\n";
                }
            }
            inFile.close();
            cout << "Data loaded successfully.\n";
        } else {
            cout << "No existing data file found. Starting with an empty system.\n";
        }
    }
};

int main() {
    BankSystem bankSystem;
    int choice;

    do {
        cout << "\n--- Banking System Menu ---\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. View Balance\n";
        cout << "5. View Transaction History\n";
        cout << "6. List Accounts\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                bankSystem.createAccount();
                break;
            case 2:
                bankSystem.deposit();
                break;
            case 3:
                bankSystem.withdraw();
                break;
            case 4:
                bankSystem.viewBalance();
                break;
            case 5:
                bankSystem.viewTransactionHistory();
                break;
            case 6:
                bankSystem.listAccounts();
                break;
            case 0:
                cout << "Exiting the banking system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}