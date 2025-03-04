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

enum MenuOptions {CREATE, DEPOSIT, WITHDRAW, CHECK, EXIT};

void displayMenu();
int getMenuOption();
bool isAlpha(string &str);
float stringToFloat(string &str);
void createAccount(BankAccount* &bankAccount, string name, float balance);


int main() {

    int menu_option;
    MenuOptions menuOption;
    BankAccount* bankAccount;
    bool accountCreated = false;
    
    do {
        displayMenu();
        menu_option = getMenuOption();
        while(menu_option < 1 || menu_option > 5) {
            menu_option = getMenuOption();
        }
        menuOption = (MenuOptions)(menu_option-1);
        string name = "";
        string amount = "";
        float num = -1.0f;
        switch(menuOption) {
            case CREATE:
                if(!accountCreated) {
                    cout << "Enter your account name: ";
                    cin >> name;

                    while(!isAlpha(name)) {
                        cin >> name;
                    }
                    cout << "Please enter your initial deposit: ";
                    cin >> amount;

                    num = stringToFloat(amount);
                    while(num == -1) {
                        cin >> amount;
                        num = stringToFloat(amount);
                    }

                    createAccount(bankAccount, name, num);
                    cout << "\n\nAccount created successfully!\n\n";
                    accountCreated = true;
                }
                else {
                    cout << "\nAccount already created, please choose another option(1-5)\n\n";
                }
                break;

            case DEPOSIT:
                if(bankAccount) {
                    cout << "\n\nPlease enter the deposit amount: ";
                    cin >> amount;

                    num = stringToFloat(amount);
                    while(num == -1) {
                        cin >> amount;
                        num = stringToFloat(amount);
                    }

                    bankAccount->deposit(num);

                    cout << "\n\nYour new balance is $" <<  fixed << setprecision(2) << bankAccount->getBalance() << "\n\n";

                }
                else {
                    cout << "\n\nBank account is invalid\n\n";
                }
                break;
            case WITHDRAW:
                if(bankAccount) {
                    cout << "Please enter the deposit amount: ";
                    cin >> amount;

                    num = stringToFloat(amount);
                    while(num == -1) {
                        cin >> amount;
                        num = stringToFloat(amount);
                    }

                    bankAccount->withdraw(num);

                    cout << "\n\nYour current balance is $" << fixed << setprecision(2) << bankAccount->getBalance() << "\n\n";
                }
                else {
                    cout << "\n\nBank account is invalid\n\n";
                }
                break;
            case CHECK:
                if(bankAccount) {
                    cout << "\n\nYour current balance is $" << fixed << setprecision(2) << bankAccount->getBalance() << "\n\n";
                }
                break;
            case EXIT:
                cout << "\n\nExiting banking program...";
                break;
        }
    } while(menu_option != 5);

    delete bankAccount;

    return 0;

}

void displayMenu() {
    cout << "Welcome to the Simple Bank System" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Exit" << endl;
}

int getMenuOption() {
    string option;
    cout << "\n\n Enter your choice: ";
    try {
       cin >> option;
       int input = stoi(option);
       return input;

    } catch(const invalid_argument &e) {
        cout << "Invalid choice, please enter a valid option (1-5)";
        return 0;
    }
}

bool isAlpha(string &str) {
    if(str != "") {
        for(char c: str) {
            if(!isalpha(c)) {
                cout << "Invalid choice, please re-enter your name: ";
                return false;
            }
        }
        return true;
    }
    else {
        cout << "Invalid choice, please re-enter your name: ";
        return false;
    }
}

float stringToFloat(string &str) {
    try {
        float value = stof(str);
        return value;
    } catch(const invalid_argument &e) {
        cout << "Invalid amount, please re-enter: ";
        return -1;
    }
}

void createAccount(BankAccount* &bankAccount, string name, float balance) {
    bankAccount = new BankAccount(name, balance);
}
