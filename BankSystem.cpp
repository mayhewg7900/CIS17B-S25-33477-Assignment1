#include <iostream>
#include <string>

using namespace std;

class BankAccount {
    private:
        string accountHolderName;
        int accountNumber;
        float balance;
    public:
        BankAccount(string n, float b) : accountHolderName(n), balance(b) {};
        
        void deposit(double amount) { balance += amount; }
        void withdraw(double amount) { balance -= amount; }
        float getBalance() { return balance; }
};

enum MenuOptions {CREATE, DEPOSIT, WITHDRAW, CHECK};

int getMenuOption();

int main() {
    int menu_option;
    MenuOptions menuOption;
    do {
        while(menu_option <= 1 || menu_option >= 5) {
            menu_option = getMenuOption();
        }
        menuOption = (MenuOptions)menu_option;
        switch(menuOption) {
            case CREATE:
                

        }
        
    } while(true);

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