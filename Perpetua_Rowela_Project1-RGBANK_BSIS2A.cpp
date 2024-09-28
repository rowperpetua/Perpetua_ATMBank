#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstdlib> // Include the <cstdlib> header for the rand() function
#include <ctime>   // Include the <ctime> header for seeding the random number generator
#include <fstream>
#include <sstream>
#include <limits>
#define MAX 5
using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void RG_Box(){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_RED);        //PURPLE BACKGROUND
int i;

// Draw the top side of the box
gotoxy(30, 6);
cout << "\xC9";
for (int i = 31; i < 90; i++) {
    cout << "\xCD";
}
cout << "\xBB";

// Draw the bottom side of the box
gotoxy(30, 25);
cout << "\xC8";
for (int i = 31; i < 90; i++) {
    cout << "\xCD";
}
cout << "\xBC";

// Draw the left and right sides of the box
for (int i = 7; i < 25; i++) {
    // Left side
    gotoxy(30, i);
    cout << "\xBA";
    // Right side
    gotoxy(90, i);
    cout << "\xBA";
}

// Draw horizontal lines inside the box
for (int i = 31; i < 90; i++) {
    // Upper horizontal line
    gotoxy(i, 6);
    cout << "\xCD";
    // Lower horizontal line
    gotoxy(i, 25);
    cout << "\xCD";
}

SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | COMMON_LVB_LEADING_BYTE | FOREGROUND_INTENSITY);   //light blue
}

struct RG_Account{
int balance;
string name, bday,pincode,accountNo, contactnum,address;
};

typedef struct ADT{
RG_Account accounts[MAX];
int last= -1;
}LIST;


class RG_Machine{
private:
    LIST A;

    int findAccount(const string  accountnum){
    for(int i=0;i<=A.last;i++){
        if(accountnum==A.accounts[i].accountNo)
            return i;   //found
    }return -1; //not found
    }

    bool isfull(){
    return(A.last==MAX-1);}

    bool isempty(){
    return(A.last==-1);}

    void cls(){system("cls");}

    bool Date(const string& birthday) {
    istringstream ss(birthday);// Check if the input has the format MM/DD/YYYY
    int month, day, year;
    char separator1, separator2;

    if (ss >> month >> separator1 >> day >> separator2 >> year &&
        separator1 == '/' && separator2 == '/' &&
        month >= 1 && month <= 12 &&
        day >= 1 && day <= 31 && // You may want to validate day ranges better
        year >= 1900 && year <= 2099) {
        return true; // Valid birthday
    }return false; // Invalid birthday
    }

    bool isAllDigits(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false; // If any character is not a digit, return false
        }
    }
    return true; // All characters are digits
    }

    string encrypt(const string& digits,int shift) {
    string encryptedDigits = "";
    for (char digit : digits) {
        if (isdigit(digit)) {
            encryptedDigits += static_cast<char>('0' + (digit - '0' + shift) % 10);
        } else {
            encryptedDigits += digit; // Keep non-digit characters as-is
            }
        }return encryptedDigits;
    }

    string decrypt(const string& encryptedDigits,int shift) {
    return encrypt(encryptedDigits, 10 - shift); // Decrypt by shifting in the opposite direction
    }

    int generate5digit() {
    srand(static_cast<unsigned int>(time(nullptr)));    // Seed the random number generator with the current time
    int randomNum = 10000 + (rand() % (99999 - 10000+ 1)); // Generate a random 5-digit number
    return randomNum;
    }

    string hideInput( ) {
    string input;
    char ch;
    int inputLength = 0;
    while (true) {
        ch = _getch();
        if (ch == 13 || inputLength == 6) { // Accept input on Enter key or after max length
            break;
        }
        if (isdigit(ch) && inputLength < 6) {
            input.push_back(ch);
            cout << '*'; // Display '*' to hide the input
            inputLength++;
        } else if (ch == 8 && !input.empty()) { // Check for backspace to erase
            input.pop_back();
            cout << "\b \b"; // Erase the last character from the console
            inputLength--;
            }
        }
    return input;
    }
	bool detectRemovableDrives() {
    DWORD drives = GetLogicalDrives();

    for (char drive = 'A'; drive <= 'Z'; ++drive) {
        if ((drives & 1) == 1) {
            std::string drivePath = "";
            drivePath += drive;
            drivePath += ":\\";	
            UINT driveType = GetDriveTypeA(drivePath.c_str()); // Use GetDriveTypeA for ANSI version
            if (driveType == DRIVE_REMOVABLE || driveType == DRIVE_CDROM) {
                return true;
            }
        }
        drives >>= 1;
    }

    return false; // No removable drives were found
}
public:
    string registerBank() {
    cls();
    RG_Box();
    RG_Account newAccount;
    gotoxy(52,7);
    cout<<"ACCOUNT REGISTER";
    gotoxy(35,9);
    cout << "ENTER YOUR NAME: ";
    getline(cin >> ws, newAccount.name);
    while (true) {
        gotoxy(35,10);
        cout << "INPUT YOUR BIRTHDAY (MM/DD/YYYY): ";
        getline(cin >> ws, newAccount.bday);
        if (!Date(newAccount.bday)) {
            gotoxy(35,11);
            cout << "INVALID DATE (MM/DD/YYYY). Please try again.";
            Sleep(1500);
            gotoxy(35,11);
            cout << "                                              ";
        }else{
        gotoxy(35,11);
        cout << "INPUT YOUR ADDRESS: ";
        getline(cin >> ws, newAccount.address);
        while(true){
        gotoxy(35,12);
        cout << "INPUT YOUR CONTACT NO: ";
        getline(cin >> ws, newAccount.contactnum);
            if (newAccount.contactnum.length() != 10 || !isAllDigits(newAccount.contactnum)) {
                gotoxy(35,13);
                cout << "Invalid contact number. It should be exactly 10 digits. Please try again.";
                Sleep(1500);
                gotoxy(35,13);
                cout << "                                                        $                 ";
            }else{
                break;}
            }
        string newPin;
        while (true) {
            gotoxy(35,13);
            cout << "INPUT YOUR PIN (6 digits): ";
            newPin = hideInput();
            gotoxy(35,14);
            cout << "CONFIRM PIN: ";
            newAccount.pincode = hideInput();
            if (newPin == newAccount.pincode && newPin.length() >= 4 && newPin.length() <=6) {
                gotoxy(35,15);
                cout << "PIN MATCHED. You may proceed.";
                Sleep(1500);
                gotoxy(35,15);
                cout<<"                                 ";
                break;
            } else {
                gotoxy(35,15);
                cout <<"PIN MISMATCH or PIN is less than 4 digits. Please try again.";
                Sleep(1500);
                gotoxy(35,15);
                cout<<"                                                       $           ";
                }
            }
            while(true){
                gotoxy(35,15);
                cout << "INPUT INITIAL DEPOSIT: ";
                cin >> newAccount.balance;
                if (newAccount.balance < 5000) {
                    gotoxy(35,16);
                    cout<<"Initial deposit should be 5000 or greater. Please try again.";
                    Sleep(1500);
                    gotoxy(35,16);
                    cout<<"                                                        $   ";
                } else {
                    newAccount.accountNo = to_string(generate5digit());
                    A.last++;
                    A.accounts[A.last] = newAccount; // Add the account to the list
                    gotoxy(35,18);
                    cout << "YOUR ACCOUNT NUMBER: " << newAccount.accountNo;
                    gotoxy(51,20);
                    cout<<"A C C O U N T  R E G I S T E R E D !";
                    Sleep(3000);
                    return A.accounts[A.last].accountNo;
                    break;
                    }
                }
            }
        }
    }

    void logIn(const string accnumber) {
    cls();
    RG_Box();
    string pin;
    int accountIndex = findAccount(accnumber);
    if (accountIndex < 0) {
        gotoxy(49,15);
        cout << "PLEASE REGISTER FIRST...";
        Sleep(1000);
        gotoxy(49,15);
        cout<<"                             ";
        gotoxy(49,15);
        cout << "REGISTRATION SERVICE...";
        Sleep(1000);
        gotoxy(49,15);
        cout<<"                          ";
        string account = registerBank();
        logIn(account);
    }
    while (true) {
        gotoxy(45,7);
        cout << "WELCOME! LOG IN YOUR ACCOUNT.";
        gotoxy(35,9);
        cout << "PLEASE INPUT YOUR PINCODE (6 digits): ";
        pin=hideInput();
        if (pin == A.accounts[accountIndex].pincode && pin.length()<=6 && pin.length()>=4) {
            gotoxy(45,11);
            cout << "SUCCESSFULLY LOGGED IN!!!";
            Sleep(1500);
            break;
        } else {
            gotoxy(35,11);
            cout << "PIN MISMATCH. Please try again.";
            Sleep(1500);
            gotoxy(35,11);
            cout << "                                         ";
        }
    }while (true) {
        cls();
        RG_Box();
        int action;
        gotoxy(46,7);
        cout << "PLEASE SELECT TRANSACTION";
        gotoxy(35,9);
        cout << "1. BALANCE";
        gotoxy(35,11);
        cout << "2. DEPOSIT";
        gotoxy(35,13);
        cout << "3. WITHDRAW";
        gotoxy(35,15);
        cout << "4. FUND TRANSFER";
        gotoxy(35,17);
        cout << "5. CHANGE PIN";
        gotoxy(35,19);
        cout << "6. LOG OUT";
        gotoxy(35,21);
        cout << "PLEASE ENTER AN ACTION(1-6): ";
        cin >> action;
        switch (action) {
            case 1:
                cls();
                RG_Box();
                checkBalance(accountIndex);
                Sleep(3000);
                break;
            case 2:
                cls();
                RG_Box();
                cashDeposit(accountIndex);
                break;
            case 3:
                cls();
                RG_Box();
                cashWithdrawal(accountIndex);
                break;
            case 4:
                cls();
                RG_Box();
                fundTransfer(accountIndex);
                break;
            case 5:
                cls();
                RG_Box();
                changePIN(accountIndex);
                break;
            case 6:
                cls();
                RG_Box();
                save(accnumber);
                exit(0);
                break;
            default:
                gotoxy(35,22);
                cout << "ERROR: 1 TO 6 ONLY";
                break;
            }
        }
    }

    void checkBalance(int accountIndex) {
    gotoxy(54,7);
    cout << "CHECK BALANCE";
    gotoxy(45,9);
    cout << "YOUR ACCOUNT NUMBER: " << A.accounts[accountIndex].accountNo;
    gotoxy(45,11);
    cout << "AVAILABLE BALANCE: " << A.accounts[accountIndex].balance;
    }

    void cashDeposit(int accountIndex) {
    int deposit;
    gotoxy(54,7);
    cout << "CASH DEPOSIT";
    gotoxy(35,9);
    cout << "ENTER AMOUNT: ";
    cin >> deposit;
    if (deposit < 100) {
        gotoxy(35,11);
        cout << "ERROR AMOUNT.";
        Sleep(1500);
        gotoxy(35,11);
        cout<<"                         ";
        return;
    } else {
        int balance = A.accounts[accountIndex].balance;
        A.accounts[accountIndex].balance += deposit;
        gotoxy(35,12);
        cout << "YOUR ACCOUNT NUMBER: " << A.accounts[accountIndex].accountNo;
        gotoxy(35,13);
        cout << "AVAILABLE BALANCE: " << balance;
        gotoxy(35,14);
        cout << "AMOUNT DEPOSIT: " << deposit;
        gotoxy(35,15);
        cout << "YOUR NEW BALANCE: " << A.accounts[accountIndex].balance;
        Sleep(3000);
        }
    }

    void cashWithdrawal(int accountIndex) {
    int withdraw;
    gotoxy(51,7);
    cout << "CASH WITHDRAWAL";
    gotoxy(35,9);
    cout << "ENTER AMOUNT: ";
    cin >> withdraw;
    if (withdraw < 100) {
        gotoxy(35,11);
        cout << "ERROR AMOUNT.";
        Sleep(1500);
        gotoxy(35,11);
        cout<<"                   ";
    } else {
        int balance = A.accounts[accountIndex].balance;
        if (balance < withdraw) {
            gotoxy(35,11);
            cout << "INSUFFICIENT FUNDS.";
            Sleep(1500);
            gotoxy(35,11);
            cout<<"                        ";
        } else {
            A.accounts[accountIndex].balance -= withdraw;
            gotoxy(35,11);
            cout << "YOUR ACCOUNT NUMBER: " << A.accounts[accountIndex].accountNo;
            gotoxy(35,13);
            cout << "AVAILABLE BALANCE: " << balance;
            gotoxy(35,15);
            cout << "AMOUNT WITHDRAW: " << withdraw;
            gotoxy(35,17);
            cout << "YOUR NEW BALANCE: " << A.accounts[accountIndex].balance;
            Sleep(3000);
            }
        }
    }

    void fundTransfer(int senderIndex) {
    int transfer;
    string receiverAccount;
    gotoxy(54,7);
    cout << "FUND TRANSFER";
    gotoxy(35,9);
    cout << "ENTER RECEIVER ACCOUNT: ";
    cin >> receiverAccount;
    int receiverIndex = findAccount(receiverAccount);
    if (receiverIndex < 0) {
        gotoxy(35,11);
        cout << "RECIPIENT ACCOUNT NOT FOUND.";
        Sleep(1500);
        gotoxy(35,11);
        cout<<"                                                                ";
    } else {
        gotoxy(35,11);
        cout << "ENTER AMOUNT: ";
        cin >> transfer;
        if (transfer < 100 || transfer > A.accounts[senderIndex].balance) {
            gotoxy(35,13);
            cout << "ERROR: Invalid amount. Min. 100PHP or insufficient funds.";
            Sleep(1500);
            gotoxy(35,13);
            cout<<"                                                                ";
        } else {
            int senderBalance = A.accounts[senderIndex].balance;
            int receiverBalance = A.accounts[receiverIndex].balance;
            A.accounts[senderIndex].balance -= transfer;
            A.accounts[receiverIndex].balance += transfer;
            gotoxy(35,15);
            cout << "YOUR ACCOUNT NUMBER: " << A.accounts[senderIndex].accountNo;
            gotoxy(35,16);
            cout << "AVAILABLE BALANCE: " << senderBalance;
            gotoxy(35,17);
            cout << "AMOUNT TRANSFER: " << transfer;
            gotoxy(35,18);
            cout << "YOUR NEW BALANCE: " << A.accounts[senderIndex].balance;
            gotoxy(35,19);
            cout << "RECIPIENT ACCOUNT NUMBER: " << A.accounts[receiverIndex].accountNo;
            gotoxy(35,21);
            cout << "RECIPIENT BALANCE: " << A.accounts[receiverIndex].balance;
            Sleep(3000);
            }
        }
    }

    bool changePIN(int accountIndex) {
    string oldPin, newPin, confirmPin;
    bool pinMatched = false;
    while (true) {
        gotoxy(52,7);
        cout << "CHANGE PINCODE";
        gotoxy(35,9);
        cout << "ENTER YOUR OLD PIN: ";
        oldPin = hideInput();
        if (oldPin == A.accounts[accountIndex].pincode && oldPin.length() <= 6 && oldPin.length() >= 4) {
            gotoxy(35,11);
            cout << "PIN MATCHED. You may proceed.";
            pinMatched = true;
            break;
        }
        gotoxy(35,11);
        cout << "PIN MISMATCH or does not have the required length (6 digits). Please try again.";
        Sleep(1500);
        gotoxy(35,11);
        cout<<"                                                                                       ";
    }if (pinMatched) {
        while (true) {
            gotoxy(35,13);
            cout << "ENTER YOUR NEW PIN (6 digits): ";
            newPin = hideInput();
            gotoxy(35,15);
            cout << "CONFIRM NEW PIN: ";
            confirmPin = hideInput();
            if (newPin == confirmPin && newPin.length() <= 6 && newPin.length() >= 4 && confirmPin.length() <= 6 && confirmPin.length() >= 4) {
                gotoxy(35,17);
                cout << "PIN MATCHED. PIN set successfully!";
                Sleep(3000);
                A.accounts[accountIndex].pincode = newPin;
                return true;
            }
            gotoxy(35,17);
            cout << "PIN MISMATCH or does not have the required length (6 digits). Please try again.";
            Sleep(1500);
            gotoxy(35,16);
            cout<<"                                                                                       ";
            }
        }return false;
    }

    void save(string account) {
    int p;
    // Open "data.txt" for writing
    ofstream dataFile("E://data.txt");      //to save all accounts
    if (!dataFile.is_open()) {
        gotoxy(42, 14);
        cout << "Error: Unable to create data file";
        return;
    }
    // Saving valid account data to "data.txt"
    for (int i = 0; i <= A.last; i++) {
        if (!A.accounts[i].name.empty() &&
            !A.accounts[i].bday.empty() &&
            !A.accounts[i].contactnum.empty() &&
            !A.accounts[i].address.empty() &&
            !A.accounts[i].accountNo.empty() && // Add other relevant checks for validity
             A.accounts[i].balance >= 0 &&
            !A.accounts[i].pincode.empty()) {

            dataFile << A.accounts[i].name << endl;
            dataFile << A.accounts[i].bday << endl;
            dataFile << A.accounts[i].contactnum << endl;
            dataFile << A.accounts[i].address << endl;
            dataFile << A.accounts[i].accountNo << endl;
            dataFile << A.accounts[i].balance << endl;
            dataFile << A.accounts[i].pincode << endl;
        }
    }
    dataFile.close();
    // Saving account to flash drive
    p = findAccount(account);
    if (p < 0) {
        gotoxy(46, 13);
        cout << "ERROR: Account not found";
        return;
    }
    // Open the flash drive file for writing
    ofstream flashDriveFile("E://pincode.txt");
    if (!flashDriveFile.is_open()) {
        gotoxy(46, 13);
        cout << "ERROR: No flash drive found.";
        return;
    }
    // Writing valid account data to the flash drive
    if (!A.accounts[p].name.empty() &&
        !A.accounts[p].bday.empty() &&
        !A.accounts[p].contactnum.empty() &&
        !A.accounts[p].address.empty() &&
        !A.accounts[p].accountNo.empty() && // Add other relevant checks for validity
         A.accounts[p].balance >= 0 &&
        !A.accounts[p].pincode.empty()) {
        string eAccount=encrypt(A.accounts[p].accountNo,3);
        string eBal=encrypt(to_string(A.accounts[p].balance),3);
        string ePin=encrypt(A.accounts[p].pincode,3);
        flashDriveFile <<eAccount<< endl;
        flashDriveFile <<eBal<< endl;
        flashDriveFile <<ePin<< endl;
    }
    flashDriveFile.close();
    gotoxy(48, 13);
    cout << "DATA SAVED SUCCESSFULLY.";
    }


    void load() {
    string loadacc, loadpin, loadbalance;
    if (!detectRemovableDrives()) {
        gotoxy(51,13);
        cout << "PLEASE INSERT CARD";
        Sleep(1500);
        exit(0);
    }
        // Load account information from "data.txt"
    ifstream dataFile("E://data.txt");
    if (!dataFile.is_open()) {
        gotoxy(55,13);
        cout << "FILE ERROR!";
        Sleep(1000);
        gotoxy(55,13);
        cout<<"                            ";
        gotoxy(51,13);
        cout<<"CREATING A FILE...";
        Sleep(1000);
        gotoxy(51,13);
        cout<<"                            ";
        gotoxy(53,13);
        cout<<"PLEASE WAIT...";
        Sleep(1000);
        gotoxy(53,13);
        cout<<"                            ";
        gotoxy(47,13);
        cout<<"FILE CREATED SUCCESSFULLY";
        Sleep(1500);
        gotoxy(47,13);
        cout<<"                            ";
        gotoxy(47,13);
        return;
        }
        A.last = -1; // Initialize last to -1 to indicate an empty array
   		while (dataFile) {
       	if (!isfull()) {
            A.last++;
            dataFile >> A.accounts[A.last].name;
            dataFile.ignore();
            getline(dataFile, A.accounts[A.last].bday);
            getline(dataFile, A.accounts[A.last].contactnum);
            getline(dataFile, A.accounts[A.last].address);
            dataFile >> A.accounts[A.last].accountNo;
            dataFile >> A.accounts[A.last].balance;
            dataFile >> A.accounts[A.last].pincode;
            dataFile.ignore();
            } else {
                gotoxy(42,13);
                cout << "Record is full! Data may be lost.";
                Sleep(1000);
                break;
            }
        }
        dataFile.close();
        // Load account information from "pincode.txt"
        string tempacc, temppin, tempbal;
   	 	ifstream pincodeFile("E://pincode.txt");
    	if (pincodeFile.is_open()) {
            while (pincodeFile >> tempacc >> tempbal >> temppin) {
            string dAccount = decrypt(tempacc, 3);
            int p = findAccount(dAccount);
            if (p >= 0) {
                logIn(A.accounts[p].accountNo);
                gotoxy(44, 13);
                cout << "ACCOUNT DATA LOAD SUCCESSFULLY.";

            }
        }
        }else {
        gotoxy(55, 13);
        cout << "FILE ERROR!";
        Sleep(1000);
        gotoxy(55, 13);
        cout << "                            ";
        gotoxy(51, 13);
        cout << "CREATING A FILE...";
        Sleep(1000);
        gotoxy(51, 13);
        cout << "                            ";
        gotoxy(53, 13);
        cout << "PLEASE WAIT...";
        Sleep(1000);
        gotoxy(53, 13);
        cout << "                            ";
        gotoxy(47, 13);
        cout << "FILE CREATED SUCCESSFULLY";
        Sleep(1500);
        gotoxy(47, 13);
        cout << "                            ";
        gotoxy(47, 13);
        cout << "W E L C O M E !";
        Sleep(1500);
            }
        }
};

int main(){
system("Color 5");
cout << "\n\n\n\t\t\t\t\t\tPLEASE TAKE NOTE OF YOUR FLASHDRIVE!";
Sleep(1000);
system("cls");
RG_Machine Bank;
RG_Box();
Bank.load();
int act;
string account;
while(true){
    RG_Box();
    gotoxy(58,7);
    cout<<"MENU";
    gotoxy(48,10);
    cout<<"1. ENROLL AN ACCOUNT";
    gotoxy(48,13);
    cout<<"2. EXIT";
    gotoxy(48,16);
    cout<<"ENTER AN ACTION(1-2): ";
    cin>>act;
    switch(act){
        case 1:
            account=Bank.registerBank();
            Bank.logIn(account);
            break;
        case 2:
			exit(0);
        default:
            gotoxy(48,17);
            cout<<"ERROR: 1 to 2 ONLY!!!";
            Sleep(1000);
            gotoxy(48,17);
            cout<<"                         ";
        }
    }
}
