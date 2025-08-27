#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <functional> // for std::hash

using namespace std;

// Hash the password using std::hash
string hashPassword(const string& password) {
    hash<string> hasher;
    return to_string(hasher(password));
}

// Load users into a map from file
unordered_map<string, string> loadUsers(const string& filename) {
    unordered_map<string, string> users;
    ifstream file(filename);
    string line, username, password;

    while (getline(file, line)) {
        istringstream iss(line);
        if (iss >> username >> password) {
            users[username] = password;
        }
    }

    return users;
}

// Register a new user
void registerUser(const string& filename) {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;

    unordered_map<string, string> users = loadUsers(filename);

    if (users.find(username) != users.end()) {
        cout << "? Username already exists. Try another.\n";
        return;
    }

    cout << "Enter a password: ";
    cin >> password;

    ofstream file(filename, ios::app);
    file << username << " " << hashPassword(password) << "\n";
    cout << "? Registration successful!\n";
}

// Login a user
void loginUser(const string& filename) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    unordered_map<string, string> users = loadUsers(filename);
    string hashed = hashPassword(password);

    if (users.find(username) != users.end() && users[username] == hashed) {
        cout << "? Login successful!\n";
    } else {
        cout << "? Invalid username or password.\n";
    }
}

// Main menu
int main() {
    string filename = "users.txt";
    int choice;

    do {
        cout << "\n--- Login & Registration System ---\n";
        cout << "1. Register\n2. Login\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser(filename);
                break;
            case 2:
                loginUser(filename);
                break;
            case 3:
                cout << "?? Exiting...\n";
                break;
            default:
                cout << "? Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}

