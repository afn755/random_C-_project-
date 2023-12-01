#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <conio.h>

using namespace std;

class Contact {
public:
    string name;
    string phoneNumber;
};

class ButtonPhone {
private:
    vector<Contact> contacts;
    string currentTime;
    bool gameOver;
    const int width = 20;
    const int height = 10;
    int x, y, fruitX, fruitY, score;
    int tailX[100], tailY[100];

public:
    ButtonPhone() : gameOver(false), x(width / 2), y(height / 2), fruitX(rand() % width), fruitY(rand() % height), score(0) {}

    void addContact(const string& name, const string& phoneNumber) {
        Contact contact;
        contact.name = name;
        contact.phoneNumber = phoneNumber;
        contacts.push_back(contact);
        cout << "Contact added successfully.\n";
    }

    void viewContacts() {
        if (contacts.empty()) {
            cout << "No contacts available.\n";
        } else {
            cout << "Contacts:\n";
            for (const auto& contact : contacts) {
                cout << contact.name << ": " << contact.phoneNumber << "\n";
            }
        }
    }

    void makeCall(const string& phoneNumber) {
        cout << "Calling " << phoneNumber << "...\n";
    }

    void sendText(const string& phoneNumber, const string& message) {
        cout << "Sending text to " << phoneNumber << ": " << message << "\n";
    }

    void viewTime() {
        auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        cout << "Current Local Time: " << ctime(&now);
    }

    void viewCalendar() {
        auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        cout << "Current Local Calendar Date: " << ctime(&now);
    }

    void setup() {
        gameOver = false;
        x = width / 2;
        y = height / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        score = 0;
    }

    void draw() {
        system("cls");
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    cout << "#";
                if (i == y && j == x)
                    cout << "O";
                else if (i == fruitY && j == fruitX)
                    cout << "•";
                else {
                    bool print = false;
                    for (int k = 0; k < score; k++) {
                        if (tailX[k] == j && tailY[k] == i) {
                            cout << "o";
                            print = true;
                        }
                    }
                    if (!print)
                        cout << " ";
                }
                if (j == width - 1)
                    cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;
        cout << "Score:" << score << endl;
    }

    void input() {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a':
                    x--;
                    break;
                case 'd':
                    x++;
                    break;
                case 'w':
                    y--;
                    break;
                case 's':
                    y++;
                    break;
                case 'x':
                    gameOver = true;
                    break;
            }
        }
    }

    void algorithm() {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;
        for (int i = 1; i < score; i++) {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
        switch (_getch()) {
            case 'a':
                x--;
                break;
            case 'd':
                x++;
                break;
            case 'w':
                y--;
                break;
            case 's':
                y++;
                break;
            case 'x':
                gameOver = true;
                break;
        }
        if (x >= width) x = 0;
        else if (x < 0) x = width - 1;
        if (y >= height) y = 0;
        else if (y < 0) y = height - 1;

        for (int i = 0; i < score; i++)
            if (tailX[i] == x && tailY[i] == y)
                gameOver = true;

        if (x == fruitX && y == fruitY) {
            score += 10;
            fruitX = rand() % width;
            fruitY = rand() % height;
        }
    }

    void snakeGame() {
        while (!gameOver) {
            draw();
            input();
            algorithm();
        }
    }

    void startSnakeGame() {
        setup();
        snakeGame();
    }
};

int main() {
    ButtonPhone phone;
    int choice;
    string phoneNumber, name, message;

    do {
        cout << "\nMenu:\n";
        cout << "1. View Contacts\n";
        cout << "2. Add Contact\n";
        cout << "3. Make a Call\n";
        cout << "4. Send a Text\n";
        cout << "5. View Time\n";
        cout << "6. View Calendar\n";
        cout << "7. Play Snake Game\n";
        cout << "0. Exit\n";
        cout << "\nEnter your choice: \n";
        cin >> choice;

        switch (choice) {
            case 1:
                phone.viewContacts();
                break;
            case 2:
                cout << "Enter contact name: ";
                cin >> name;
                cout << "Enter phone number: ";
                cin >> phoneNumber;
                phone.addContact(name, phoneNumber);
                break;
            case 3:
                cout << "Enter phone number to make a call: ";
                cin >> phoneNumber;
                phone.makeCall(phoneNumber);
                break;
            case 4:
                cout << "Enter phone number to send a text: ";
                cin >> phoneNumber;
                cout << "Enter message: ";
                cin.ignore();
                getline(cin, message);
                phone.sendText(phoneNumber, message);
                break;
            case 5:
                phone.viewTime();
                break;
            case 6:
                phone.viewCalendar();
                break;
            case 7:
                phone.startSnakeGame();
                break;
            case 0:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != 0);

    return 0;
}
