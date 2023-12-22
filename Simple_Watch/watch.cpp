#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

class Watch {
public:
    Watch() {
        isStopwatchRunning = false;
        alarmHour = 0;
        alarmMinute = 0;
        alarmSet = false;
    }

    void displayTime() {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        cout << "Time: " << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec;

        // Display day of the week
        cout << "  Day: " << getDayOfWeek(localTime->tm_wday);

        cout << endl;
    }

    void displayDate() {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        cout << "Date: " << localTime->tm_year + 1900 << "-" << localTime->tm_mon + 1 << "-" << localTime->tm_mday << endl;
    }

    void displayDay() {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        cout << "Day: " << getDayOfWeek(localTime->tm_wday) << endl;
    }

    string getDayOfWeek(int day) {
        string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        return days[day];
    }

    void startStopwatch() {
        isStopwatchRunning = true;
        stopwatchStartTime = chrono::steady_clock::now();
    }

    void stopStopwatch() {
        isStopwatchRunning = false;
        auto endTime = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(endTime - stopwatchStartTime).count();
        cout << "Stopwatch: " << elapsed << " seconds" << endl;
    }

    void setAlarm(int hour, int minute) {
        alarmHour = hour;
        alarmMinute = minute;
        alarmSet = true;
        cout << "Alarm set for " << hour << ":" << minute << endl;
    }

    void checkAlarm() {
        time_t now = time(0);
        tm* localTime = localtime(&now);

        if (alarmSet && localTime->tm_hour == alarmHour && localTime->tm_min == alarmMinute) {
            cout << "\nAlarm! Wake up!\n" << endl;
            alarmSet = false;
        }
    }

    void displayMenu() {
        cout << "\n1. Display Time" << endl;
        cout << "2. Display Date" << endl;
        cout << "3. Display Day" << endl;
        cout << "4. Start Stopwatch" << endl;
        cout << "5. Stop Stopwatch" << endl;
        cout << "6. Set Alarm" << endl;
        cout << "7. Exit\n" << endl;
    }

    void operate() {
        int choice;
        do {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    displayTime();
                    break;
                case 2:
                    displayDate();
                    break;
                case 3:
                    displayDay();
                    break;
                case 4:
                    startStopwatch();
                    break;
                case 5:
                    stopStopwatch();
                    break;
                case 6:
                    int alarmHour, alarmMinute;
                    cout << "Enter alarm hour: ";
                    cin >> alarmHour;
                    cout << "Enter alarm minute: ";
                    cin >> alarmMinute;
                    setAlarm(alarmHour, alarmMinute);
                    break;
                case 7:
                    cout << "Exiting the watch.\n" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n" << endl;
                    break;
            }

            if (choice != 7) {
                checkAlarm();
                this_thread::sleep_for(chrono::seconds(1));
                system("clear");  // For Linux/Mac. Use "cls" for Windows.
            }
        } while (choice != 7);
    }

private:
    bool isStopwatchRunning;
    chrono::steady_clock::time_point stopwatchStartTime;
    int alarmHour;
    int alarmMinute;
    bool alarmSet;
};

int main() {
    Watch watch;
    watch.operate();

    return 0;
}
