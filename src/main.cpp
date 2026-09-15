#include <iostream>
#include "FileLoader.h"
using namespace std;

int main() {
    // Load the catalog ONCE, before the loop. Every menu option that needs
    // the resource list reads from this vector — do NOT re-read the file
    // inside each option.
    vector<Resource> resources = FileLoader::loadResources("data/resources.txt");

    // The menu loop: show options, read a choice, do something, repeat,
    // until the user picks quit. do/while so the menu always shows at
    // least once.
    int choice = 0;
    do {
        cout << "\n===== Campus Resource Reservation System =====\n";
        cout << "1. Display all resources\n";
        cout << "2. Create a reservation     (waiting on teammate's PR)\n";
        cout << "3. Cancel a reservation     (waiting on teammate's PR)\n";
        cout << "4. Undo last cancellation   (waiting on teammate's PR)\n";
        cout << "5. Display waiting lists    (waiting on teammate's PR)\n";
        cout << "6. Display cancellation history (waiting on teammate's PR)\n";
        cout << "7. Quit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                for (size_t i = 0; i < resources.size(); ++i){
                    resources[i].print();
                }
                break;

            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                // Teammate's lane. Keep the app compiling even before
                // their PR merges: print a standby message and go back
                // to the menu instead of breaking the build.
                cout << "Reservations features: waiting on teammate's PR.\n";
                break;

            case 7:
                cout << "Goodbye.\n";
                break;

            default:
                // what happens if the user types a LETTER instead
                // of a number? cin >> choice fails, and the failed input
                // stays in the stream — the loop can spin forever. Look up
                // `cin.clear()` and `cin.ignore()` and decide how to handle it
                cout << "Invalid choice. Pick 1-7.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                break;
        }
    } while (choice != 7);

    return 0;
}
