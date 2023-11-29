#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Dice {
public:
    int roll() {
        return rand() % 6 + 1;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    Dice dice;

    while (true) {
        cout << "Press enter to roll the dice: ";
        cin.ignore();

        int result = dice.roll();


        cout << "|  " << result << " |" << endl;


        cout << "Result: " << result << endl;
    }

    return 0;
}
