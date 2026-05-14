
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>

using namespace std;

// ==========================================
//            USER STRUCTURE
// ==========================================
struct User {
    string username;
    string password;
};

// ==========================================
//         PASSWORD STRENGTH CHECKER
// ==========================================
bool strongPassword(string pass) {

    bool upper = false, lower = false, digit = false;

    if (pass.length() < 6)
        return false;

    for(char ch : pass) {

        if(isupper(ch))
            upper = true;

        else if(islower(ch))
            lower = true;

        else if(isdigit(ch))
            digit = true;
    }

    return upper && lower && digit;
}

// ==========================================
//          CHECK USER EXISTS
// ==========================================
bool userExists(string username) {

    ifstream file("database.txt");

    string u, p;

    while(file >> u >> p) {

        if(u == username)
            return true;
    }

    return false;
}

// ==========================================
//            SAVE LOGIN HISTORY
// ==========================================
void saveHistory(string username) {

    ofstream history("history.txt", ios::app);

    time_t now = time(0);

    history << "User : " << username
            << " | Login Time : "
            << ctime(&now);

    history.close();
}

// ==========================================
//          REGISTRATION FUNCTION
// ==========================================
void registerUser() {

    string username, password;

    cout << "\n============================================\n";
    cout << "           USER REGISTRATION\n";
    cout << "============================================\n";

    cout << "Enter Username : ";
    cin >> username;

    if(userExists(username)) {

        cout << "\n❌ Username Already Exists!\n";
        return;
    }

    cout << "Enter Password : ";
    cin >> password;

    if(!strongPassword(password)) {

        cout << "\n⚠ Weak Password!\n";
        cout << "Password must contain:\n";
        cout << "✔ Uppercase Letter\n";
        cout << "✔ Lowercase Letter\n";
        cout << "✔ Number\n";
        cout << "✔ Minimum 6 Characters\n";

        return;
    }

    ofstream file("database.txt", ios::app);

    file << username << " " << password << endl;

    file.close();

    cout << "\n🎉 Registration Successful!\n";
}

// ==========================================
//             LOGIN FUNCTION
// ==========================================
void loginUser() {

    string username, password;
    string storedUser, storedPass;

    int attempts = 0;

    while(attempts < 3) {

        cout << "\n============================================\n";
        cout << "                USER LOGIN\n";
        cout << "============================================\n";

        cout << "Enter Username : ";
        cin >> username;

        cout << "Enter Password : ";
        cin >> password;

        ifstream file("database.txt");

        bool found = false;

        while(file >> storedUser >> storedPass) {

            if(username == storedUser &&
               password == storedPass) {

                found = true;
                break;
            }
        }

        file.close();

        if(found) {

            cout << "\n🎯 LOGIN SUCCESSFUL!\n";
            cout << "🔥 Welcome Back, " << username << endl;

            saveHistory(username);

            return;
        }
        else {

            attempts++;

            cout << "\n❌ Invalid Credentials!";
            cout << "\nAttempts Left : "
                 << 3 - attempts << endl;
        }
    }

    cout << "\n🚫 ACCOUNT LOCKED!";
}

// ==========================================
//          FORGOT PASSWORD
// ==========================================
void forgotPassword() {

    string username;
    string u, p;

    cout << "\n============================================\n";
    cout << "             FORGOT PASSWORD\n";
    cout << "============================================\n";

    cout << "Enter Username : ";
    cin >> username;

    ifstream file("database.txt");

    bool found = false;

    while(file >> u >> p) {

        if(u == username) {

            found = true;

            cout << "\n🔑 Your Password is : " << p << endl;
            break;
        }
    }

    file.close();

    if(!found) {

        cout << "\n❌ Username Not Found!\n";
    }
}

// ==========================================
//          VIEW LOGIN HISTORY
// ==========================================
void viewHistory() {

    ifstream file("history.txt");

    string line;

    cout << "\n============================================\n";
    cout << "              LOGIN HISTORY\n";
    cout << "============================================\n";

    while(getline(file, line)) {

        cout << line << endl;
    }

    file.close();
}

// ==========================================
//            USER STATISTICS
// ==========================================
void userStats() {

    ifstream file("database.txt");

    string u, p;

    int totalUsers = 0;

    while(file >> u >> p) {

        totalUsers++;
    }

    file.close();

    cout << "\n============================================\n";
    cout << "              SYSTEM ANALYTICS\n";
    cout << "============================================\n";

    cout << "👥 Total Registered Users : "
         << totalUsers << endl;
}

// ==========================================
//                 MAIN
// ==========================================
int main() {

    int choice;

    do {

        cout << "\n\n";
        cout << "==================================================\n";
        cout << "        🔐 SMART AUTHENTICATION SYSTEM\n";
        cout << "==================================================\n";

        cout << "1. Register New User\n";
        cout << "2. Login\n";
        cout << "3. Forgot Password\n";
        cout << "4. View Login History\n";
        cout << "5. System Statistics\n";
        cout << "6. Exit\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch(choice) {

            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                forgotPassword();
                break;

            case 4:
                viewHistory();
                break;

            case 5:
                userStats();
                break;

            case 6:
                cout << "\n🚀 Exiting Secure System...\n";
                break;

            default:
                cout << "\n⚠ Invalid Choice!\n";
        }

    } while(choice != 6);

    return 0;
}