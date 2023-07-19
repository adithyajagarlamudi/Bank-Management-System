#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h> 

using namespace std;

class Customer {
public:
    string name;
    string address;
    string contactDetails;
    string customerID;
};

class Account {
public:
    string accountNumber;
    string customerId;
    string accountType;
    double balance;
    string username;
    string password;
};

vector<Customer> customers;
vector<Account> accounts;

// Function to clear the Console screen
void clearConsole() {
    system("cls");
}

// Function to validate account username and password
bool validateAccount(const string& username, const string& password) {
    for (const auto& account : accounts) {
        if (account.username == username && account.password == password) {
            return true;
        }
    }
    return false;
}

// Function to add a new customer
void addCustomer(const string& accountNumber) {
    Customer customer;
    cout << "Enter customer name: ";
    cin.ignore();
    getline(cin, customer.name);
    cout << "Enter customer address: ";
    getline(cin, customer.address);
    cout << "Enter customer contact details: ";
    getline(cin, customer.contactDetails);

    // Generate a random customer ID
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, 9);
    string cust_id;
    for (int i = 0; i < 5; ++i) {
        cust_id += to_string(distribution(gen));
    }
    cust_id = "C" + cust_id;
    customer.customerID = cust_id; // Assign the generated customer ID
    
    customers.push_back(customer);

    // Update the customer ID in the relevant Account object
    for (auto& account : accounts) {
        if (account.accountNumber == accountNumber) {
            account.customerId = cust_id;
            break;
        }
    }

    cout << "=================================================" << endl;
    cout << "Customer added successfully!" << endl;
    cout << "Your Customer ID: " << cust_id << endl;
    cout << "=================================================" << endl;
}

// Function to display account balance
void displayBalance(const string& accountNumber) {
    bool found = false;
    for (const auto& account : accounts) {
        if (account.accountNumber == accountNumber) {
            cout << "Account Balance: Rs " << account.balance << endl;
            cout << "=================================================" << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account Not found" << endl;
    }
}

// Function to perform a deposit operation
void deposit() {
    string accountNumber;
    double amount;
    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    for (auto& account : accounts) {
        if (account.accountNumber == accountNumber) {
            account.balance += amount;
            cout << "=================================================" << endl;
            cout << "Deposit successful!" << endl;
            displayBalance(accountNumber);
            return;
        }
    }

    cout << "Account not found!" << endl;
}

// Function to perform a withdrawal operation
void withdraw() {
    string accountNumber;
    double amount;
    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    for (auto& account : accounts) {
        if (account.accountNumber == accountNumber) {
            if (account.balance >= amount) {
                account.balance -= amount;
                cout << "=================================================" << endl;
                cout << "Withdrawal successful!" << endl;
                displayBalance(accountNumber);
            } else {
                cout << "Insufficient balance!" << endl;
            }
            return;
        }
    }

    cout << "Account not found!" << endl;
}

// Function to display the list of customers
void displayCustomers() {
    cout << "=================================================" << endl;
    cout << "List of customers:" << endl;
    for (const auto& customer : customers) {
        cout << "Name: " << customer.name << endl;
        cout << "Address: " << customer.address << endl;
        cout << "Contact Details: " << customer.contactDetails << endl;
        cout << "CustomerID: " << customer.customerID << endl;
        cout << "----------------------------------------" << endl;
    }
    cout << "=================================================" << endl;
}

// Function to display the list of accounts
void displayAccounts() {
    cout << "=================================================" << endl;
    cout << "List of accounts:" << endl;
    for (const auto& account : accounts) {
        cout << "Account Number: " << account.accountNumber << endl;
        cout << "Customer ID: " << account.customerId << endl;
        cout << "Account Type: " << account.accountType << endl;
        cout << "Balance: Rs " << account.balance << endl;
        cout << "----------------------------------------" << endl;
    }
    cout << "=================================================" << endl;
}

// Function to grant a loan
void takeLoan() {
    string accountNumber;
    double loanAmount;

    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter loan amount: ";
    cin >> loanAmount;

    bool found = false;
    for (auto& account : accounts) {
        if (account.accountNumber == accountNumber) {
            if (account.balance >= (0.5 * loanAmount)) {
                account.balance += loanAmount;
                cout << "=================================================" << endl;
                cout << "Loan granted successfully!" << endl << "Updated ";
                displayBalance(accountNumber);
                found = true;
                break;
            } else {
                cout << "Didn't reach the eligibility criteria" << endl;
            }
        }
    }

    if (!found) {
        cout << "Account not found!" << endl;
    }
}

// Function to update account and customer information
void updateAccount(const string& accountNumber) {
    bool found = false;
    string cust_id;
    for (auto& account : accounts) {
        if (account.accountNumber == accountNumber) {
            cust_id = account.customerId;
            cout << "Update Account Information" << endl;
            cout << "Enter new account type: ";
            cin >> account.accountType;
            cout << "Enter new username: ";
            cin >> account.username;
            cout << "Enter new password: ";
            cin >> account.password;
            
            found = true;
            break;
        }
    }

    // Update relevant customer details
    for (auto& customer : customers) {
        if (customer.customerID == cust_id) {
            cout << "Update Customer Information" << endl;
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, customer.name);
            cout << "Enter new address: ";
            getline(cin, customer.address);
            cout << "Enter new contact details: ";
            getline(cin, customer.contactDetails);
            
            break;
        }
    }

    cout << "=======================================================" << endl;
    cout << "Account and Customer information updated successfully!" << endl;
    cout << "=======================================================" << endl;

    if (!found) {
        cout << "Account not found!" << endl;
    }
}

// Function to perform a transfer between accounts
void transfer() {
    string fromAccountNumber, toAccountNumber;
    double amount;

    cout << "Enter source account number: ";
    cin >> fromAccountNumber;
    cout << "Enter destination account number: ";
    cin >> toAccountNumber;
    cout << "Enter transfer amount: ";
    cin >> amount;

    bool fromAccountFound = false;
    bool toAccountFound = false;
    Account* fromAccount = nullptr;
    Account* toAccount = nullptr;

    for (auto& account : accounts) {
        if (account.accountNumber == fromAccountNumber) {
            fromAccount = &account;
            fromAccountFound = true;
        }
        if (account.accountNumber == toAccountNumber) {
            toAccount = &account;
            toAccountFound = true;
        }
    }

    if (fromAccountFound && toAccountFound) {
        if (fromAccount->balance >= amount) {
            fromAccount->balance -= amount;
            toAccount->balance += amount;
            cout << "=================================================" << endl;
            cout << "Transfer successful!" << endl;
            cout << "Updated source account balance: Rs " << fromAccount->balance << endl;
            cout << "Updated destination account balance: Rs " << toAccount->balance << endl;
            cout << "=================================================" << endl;
        } else {
            cout << "Insufficient balance in the source account!" << endl;
        }
    } else {
        cout << "One or both accounts not found!" << endl;
    }
}

// Function to close an account
void closeAccount() {
    string accountNumber;
    cout << "Enter account number to close: ";
    cin >> accountNumber;

    auto accountIt = accounts.begin();
    while (accountIt != accounts.end()) {
        if (accountIt->accountNumber == accountNumber) {
            string customerId = accountIt->customerId;
            // Remove account details
            accountIt = accounts.erase(accountIt);

            // Remove the associated customer details
            auto customerIt = customers.begin();
            while (customerIt != customers.end()) {
                if (customerIt->customerID == customerId) {
                    customerIt = customers.erase(customerIt);
                } else {
                    ++customerIt;
                }
            }

            cout << "Account closed successfully!" << endl;
            return;
        } else {
            ++accountIt;
        }
    }

    cout << "Account not found!" << endl;
}
// Function for user login
bool login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    Sleep(1000);
    clearConsole();
    if (validateAccount(username, password)) {
        cout << "-----------Login successful!------------------" << endl;
        return true;
    } else {
        cout << "Invalid username or password!" << endl;
        return false;
    }
}
// Function to handle the bank application menu
void bankApplicationMenu(const string& accountNumber) {
    int choice;
    do {
        cout << "---------------------------Bank Application Menu-------------------------------" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Take Loan" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Display Customers" << endl;
        cout << "5. Display Accounts" << endl;
        cout << "6. Display Balance" << endl;
        cout << "7. Close Account" << endl;
        cout << "8. Transfer" << endl;
        cout << "9. Update Account Info" << endl;
        cout << "0. Log Out" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                deposit();
                break;
            case 2:
                takeLoan();
                break;    
            case 3:
                withdraw();
                break;
            case 4:
                displayCustomers();
                break;
            case 5:
                displayAccounts();
                break;
            case 6:
                displayBalance(accountNumber);
                break;
            case 7:
                closeAccount();
                Sleep(4000);
                clearConsole();
                return;
            case 8:
                transfer();
                break;
            case 9:
                updateAccount(accountNumber);
                break;
            case 0:
                cout << "Logging Out..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    } while (choice != 0);
}

// Function to create a new account
void createAccount() {
    Account account;
    cout << "Enter account number: ";
    cin >> account.accountNumber;
    cout << "Enter account type: ";
    cin >> account.accountType;
    cout << "Enter initial balance: ";
    cin >> account.balance;

    // Validate username
    bool isUsernameTaken;
    do {
        isUsernameTaken = false;

        cout << "Enter username: ";
        cin >> account.username;

        // Check if the username already exists
        for (const auto& existingAccount : accounts) {
            if (existingAccount.username == account.username) {
                cout << "Username is already taken. Please choose a different username." << endl;
                isUsernameTaken = true;
                break;
            }
        }
    } while (isUsernameTaken);

    // Validate password
    while (true) {
        cout << "Enter password: ";
        cin >> account.password;

        // Password validation
        if (account.password.length() < 6 || !any_of(account.password.begin(), account.password.end(), [](char c) { return isupper(c); })) {
            cout << "Password should contain at least 6 characters and 1 uppercase letter. Please try again." << endl;
        } else {
            break;
        }
    }

    accounts.push_back(account);
    addCustomer(account.accountNumber);
    Sleep(5000);
    clearConsole();
    cout << "---------------------Account created successfully!----------------" << endl;
    cout << "-----------------Continue to login!-----------------" << endl;

    if (login()) {
        bankApplicationMenu(account.accountNumber);
    }
}



int main() {
    int choice;
    do {
        cout << "------------------Welcome--------------------" << endl;
        cout << "1. Existing user? Continue to Login" << endl;
        cout << "2. New user? Create new Account" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                if (login()) {
                    cout << "Enter account number: ";
                    string accno;
                    cin >> accno;
                    bankApplicationMenu(accno);
                }
                break;
            case 2:
                createAccount();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
