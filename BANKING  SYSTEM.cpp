#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Transaction {
public:
    string type;
    double amount;
    time_t timestamp;

    Transaction(string type, double amount) {
        this->type = type;
        this->amount = amount;
        this->timestamp = time(nullptr); // current time
    }

    void display() const {
        cout << "Type: " << type << ", Amount: " << amount
             << ", Time: " << ctime(&timestamp); // formatted time
    }
};

class Account {
private:
    string accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(string accNo) : accountNumber(accNo), balance(0.0) {}

    string getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "? Invalid deposit amount.\n";
            return;
        }
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        cout << "? Deposit successful.\n";
    }

    void withdraw(double amount) {
        if (amount <= 0 || amount > balance) {
            cout << "? Invalid withdrawal amount.\n";
            return;
        }
        balance -= amount;
        transactions.emplace_back("Withdrawal", amount);
        cout << "? Withdrawal successful.\n";
    }

    void transfer(Account &receiver, double amount) {
        if (amount <= 0 || amount > balance) {
            cout << "? Transfer failed. Check balance or amount.\n";
            return;
        }
        balance -= amount;
        receiver.balance += amount;

        transactions.emplace_back("Transfer Out", amount);
        receiver.transactions.emplace_back("Transfer In", amount);

        cout << "? Transfer successful.\n";
    }

    void showTransactions() const {
        if (transactions.empty()) {
            cout << "No transactions.\n";
            return;
        }
        cout << "--- Transaction History ---\n";
        for (const auto &t : transactions) {
            t.display();
        }
    }
};

class Customer {
private:
    string name;
    string customerId;
    Account account;

public:
    Customer(string name, string customerId, string accNo)
        : name(name), customerId(customerId), account(accNo) {}

    string getName() const {
        return name;
    }

    string getCustomerId() const {
        return customerId;
    }

    Account& getAccount() {
        return account;
    }

    void showInfo() const {
        cout << "Customer: " << name << " (ID: " << customerId << ")\n";
        cout << "Account No: " << account.getAccountNumber() << "\n";
        cout << "Balance: $" << account.getBalance() << "\n";
    }
};

// Test system
int main() {
    Customer alice("Alice", "C101", "A1001");
    Customer bob("Bob", "C102", "A1002");

    alice.getAccount().deposit(500);
    alice.getAccount().withdraw(100);
    alice.getAccount().transfer(bob.getAccount(), 200);

    cout << "\n--- Alice's Account Info ---\n";
    alice.showInfo();
    alice.getAccount().showTransactions();

    cout << "\n--- Bob's Account Info ---\n";
    bob.showInfo();
    bob.getAccount().showTransactions();

    return 0;
}

