#include <iostream>
#include "FileLoader.h"
#include "ReservationManager.h"
using namespace std;

int main() {
    // Load the catalog ONCE, before the loop. Every menu option that needs
    // the resource list reads from the manager — do NOT re-read the file
    // inside each option, and do NOT keep a second local vector (the
    // availability text shown must agree with what createReservation checks).
    ReservationManager manager;
    manager.loadData("data/resources.txt", "data/reservations.txt");

    // The menu loop: show options, read a choice, do something, repeat,
    // until the user picks quit. do/while so the menu always shows at
    // least once.
    int choice = 0;
    do {
        cout << endl << "===== Campus Resource Reservation System =====" << endl;
        cout << "1. Display all resources" << endl;
        cout << "2. Create a reservation" << endl;
        cout << "3. Cancel a reservation" << endl;
        cout << "4. Undo last cancellation" << endl;
        cout << "5. Display waiting lists" << endl;
        cout << "6. Display cancellation history" << endl;
        cout << "7. Quit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.displayResources();
                break;

            case 2: {
                string studentId;
                string studentName;
                string resourceId;
                string date;
                string startTime;
                string endTime;

                cout << "Enter student ID: ";
                cin >> studentId;
                cout << "Enter student name: ";
                cin >> studentName;
                cout << "Enter resource ID: ";
                cin >> resourceId;
                cout << "Enter date (MM/DD/YYYY, 0 for none): ";
                cin >> date;
                cout << "Enter start time (HH:MM, 0 for none): ";
                cin >> startTime;
                cout << "Enter end time (HH:MM, 0 for none): ";
                cin >> endTime;

                if (date == "0") date = "";
                if (startTime == "0") startTime = "";
                if (endTime == "0") endTime = "";

                if (manager.createReservation(studentId, studentName, resourceId,
                                              date, startTime, endTime)){
                    cout << "Reservation created." << endl;
                } else {
                    cout << "Unavailable - added to waiting list." << endl;
                }
                break;
            }

            case 3: {
                string reservationId;
                cout << "Enter reservation ID: ";
                cin >> reservationId;

                if (manager.cancelReservation(reservationId)){
                    cout << "Reservation cancelled." << endl;
                } else {
                    cout << "Reservation not found." << endl;
                }
                break;
            }

            case 4: {
                if (manager.undoCancellation()){
                    cout << "Most recent cancellation undone." << endl;
                } else {
                    cout << "Nothing to undo." << endl;
                }
                break;
            }

            case 5: {
                manager.displayWaitingLists();
                break;
            }

            case 6: {
                manager.displayCancellationHistory();
                break;
            }

            case 7:
                cout << "Goodbye." << endl;
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
