#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

class BankAccount {
    private:
        string accountHolderName;
        int accountNumber;
        float balance;
    public:
        BankAccount(string n, float b) : accountHolderName(n), balance(b) {};
        
        void deposit(double amount) { balance += amount; }
        
        void withdraw(double amount) { 
            if(amount > balance) {
                cout << "Error, cannot withdraw more than your account currently has";
            }
            else {
                balance -= amount;
            }
        }

        float getBalance() { return balance; }
};

enum MenuOptions {CREATE=1, DEPOSIT=2, WITHDRAW=3, CHECK=4, EXIT=5, INVALID=6};

MenuOptions getMenuOption();

bool isAlpha(string &str);

float stringToPositiveFloat(string &str);

void displayMenu();
void createAccount(BankAccount* &bankAccount, string name, float balance);
void invalidAccount();
void displayBalance(BankAccount *bankAccount);

int main() {

    MenuOptions menuOption;

    // Pointer to the user's bank account, initialized with nullptr
    BankAccount* bankAccount = nullptr;


    // Do...
    do {
        displayMenu();

        // Converts the inputted user string to the MenuOptions enum, with it defaulting to INVALID when there are errors
        menuOption = getMenuOption();
        
        //Stores the current user input
        string input = "";

        //Strings used for storing user-inputted name and initial balance
        string user_name = "";
        string user_amount = "";

        //Float used to store the user-inputted balance as a float
        float amount = -1.0f;

        switch(menuOption) {
            case CREATE:
                // If BankAccount ptr is nullptr, create a BankAccount instance and assign the address to the bankAccount ptr
                if(bankAccount == nullptr) {
                    cout << "Enter your account name: ";
                    cin >> input;

                    // While name is not alphanumeric, request another input
                    while(!isAlpha(input)) {
                        cin >> input;
                    }

                    user_name = input;

                    cout << "Please enter your initial deposit: ";
                    cin >> input;

                    // While the string converted to a float is invalid, request another input
                    amount = stringToPositiveFloat(input);
                    while(amount == -1) {
                        cin >> input;
                        amount = stringToPositiveFloat(input);
                    }

                    user_amount = input;

                    //Creates the new BankAccount, assign its address to the bankAccount ptr
                    createAccount(bankAccount, user_name, amount);
                    cout << "\n\nAccount created successfully!\n\n";
                }
                // Else BankAccount instance was already created
                else {
                    cout << "\nAccount already created, please choose another option(1-5)\n\n";
                }
                break;

            case DEPOSIT:
                // If bank account exists...
                if(bankAccount) {
                    cout << "\n\nPlease enter the deposit amount: ";
                    cin >> input;

                    //While the string converted to a float is invalid, request another input
                    amount = stringToPositiveFloat(input);
                    while(amount == -1) {
                        cin >> input;
                        amount = stringToPositiveFloat(input);
                    }

                    // Deferences the pointer, depositing the amount entered
                    bankAccount->deposit(amount);

                    // Displays the balance
                    displayBalance(bankAccount);

                }
                // Else bank account does not exist, request user to create one
                else {
                    invalidAccount();
                }
                break;
            case WITHDRAW:
                // If bank account exists...
                if(bankAccount) {
                    cout << "Please enter the withdrawal amount: ";
                    cin >> input;

                    // While the string converted to a float is invalid, request another input
                    amount = stringToPositiveFloat(input);
                    while(amount == -1) {
                        cin >> input;
                        amount = stringToPositiveFloat(input);
                    }

                    // Dereferences the pointer, withdrawing the amount entered if < the total balance.
                    bankAccount->withdraw(amount);

                    // Displays the balance
                    displayBalance(bankAccount);
                }
                else {
                    invalidAccount();
                }
                break;
            case CHECK:
                // If bank account exists...
                if(bankAccount) {
                    // Display the balance
                    displayBalance(bankAccount);
                }
                // Else bank account does not exist, request user to create one
                else {
                    invalidAccount();
                }
                break;
            case EXIT:
                cout << "\n\nExiting banking program...";
                break;
            // If INVALID, return to the beginning of the do-while loop
            case INVALID:
                break;
        }
        // ...while the user has not selected EXIT
    } while(menuOption != EXIT);

    // Delete the dynamically allocated bankAccount instance if created
    delete bankAccount;

    return 0;

}

// Displays the menu with user options
void displayMenu() {
    cout << "Welcome to the Simple Bank System" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Exit" << endl;
}

// Requests the user to enter a menu option, returns INVALID if errors are caught
MenuOptions getMenuOption() {
    string option;
    cout << "\n\n Enter your choice: ";
    try {
       cin >> option;
       // Tries to convert the user-inputted choice to an integer
       int input = stoi(option);
       if(input >= 1 && input <= 5) {
            return MenuOptions(input);
       }
       else {
            cout << "Invalid choice, please enter a valid option (1-5)";
            return INVALID;
       }

    } catch(const invalid_argument &error) {
        cout << "Invalid choice, please enter a valid option (1-5)";
        return INVALID;
        
    }
}

// Determines if the string entered is alphanumeric, returning true or false
bool isAlpha(string &str) {
    // If string is not empty...
    if(str != "") {
        // Loop through each character
        for(char c: str) {
            // If not alphabetical...
            if(!isalpha(c)) {
                cout << "Invalid choice, please re-enter your name: ";
                return false;
            }
        }
        // Returns true if every character is alphabetical
        return true;
    }
    // Else request a new name entry
    else {
        cout << "Invalid choice, please re-enter your name: ";
        return false;
    }
}

// Converts the string to a positive float, returns -1 if conversion fails
float stringToPositiveFloat(string &str) {
    try {
        // Tries to convert the string to a float
        float value = stof(str);
        // If the amount is greater than 0...
        if(value > 0) {
            return value;
        }
        // Else return -1 to indicate re-entry
        else {
            cout << "Amount cannot be negative, please re-enter: ";
            return -1;
        }
        return value;
        // String could not be converted, return -1 to indicate re-entry
    } catch(const invalid_argument &error) {
        cout << "Invalid amount, please re-enter: ";
        return -1;
    }
}

// Creates the BankAccount instance using the user-inputted name and balance, and assigns its address to the bankAccount ptr, dynamically allocated
void createAccount(BankAccount* &bankAccount, string name, float balance) {
    bankAccount = new BankAccount(name, balance);
}

// Output that displays when account is invalid
void invalidAccount() {
    cout << "\n\nBank account is invalid, please create an account first\n\n";
}

// Output that displays the balance of a valid bank account
void displayBalance(BankAccount *bankAccount) {
    if(bankAccount) {
        cout << "\n\nYour current balance is $" << fixed << setprecision(2) << bankAccount->getBalance() << "\n\n";
    }
    else {
        invalidAccount();
    }
}
