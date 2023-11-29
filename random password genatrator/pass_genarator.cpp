#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

class PasswordGenerator {
public:
    string generatePassword(int length) {
        const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+";
        string password;

        for (int i = 0; i < length; ++i) {
            int index = rand() % charset.length();
            password += charset[index];
        }

        return password;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    PasswordGenerator passwordGenerator;

    int length;
    cout << "Enter the length of the password: ";
    cin >> length;

    if (length <= 0) {
        cout << "Invalid password length. Please enter a positive integer." << endl;
        return 1;
    }

    string generatedPassword = passwordGenerator.generatePassword(length);

    cout << "Generated Password: " << generatedPassword << endl;

    return 0;
}

