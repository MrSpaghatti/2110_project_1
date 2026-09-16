#include <iostream>
#include "FileLoader.h"
// NEXT STEPS (see the comment skeletons in include/ and src/):
//   1. Implement LinkedList, CancellationHistory, then ReservationManager.
//   2. Create ONE ReservationManager here (after the resource load) and
//      replace every `case N:` body below with a manager method call:
//         case 1: manager.displayAllResources();      break;
//         case 2: manager.createReservation(...);     break;   // ask for id/name/resource/date
//         case 3: manager.cancelReservation(id);      break;
//         case 4: manager.undoLastCancellation();     break;
//         case 5: manager.displayWaitingLists();      break;
//         case 6: manager.displayCancellationHistory(); break;
//   3. Delete the menu labels "(waiting on teammate's PR)" — they are now
//      stale: the WaitingList/Reservation PRs merged.
//   Keep main.cpp THIN: prompts + reads + manager calls. No business logic.
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
                // Bad input guard: a LETTER in the choice box makes
                // `cin >> choice` fail and leaves garbage in the stream,
                // which can spin this loop forever. clear() resets the
                // failure flag, ignore() drains up to 10000 chars or the
                // newline, whichever comes first, so the next read starts
                // fresh. (Verified 2026-09-08: exit 0 on letter input.)
                cout << "Invalid choice. Pick 1-7.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                break;
        }
    } while (choice != 7);

    return 0;
}
