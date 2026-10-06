#include <iostream>
#include "FileLoader.h"
#include "ReservationManager.h"
#include "ReportGenerator.h"
using namespace std;

int main() {
    // Load the catalog ONCE, before the loop. Every menu option that needs
    // the resource list reads from the manager — do NOT re-read the file
    // inside each option, and do NOT keep a second local vector (the
    // availability text shown must agree with what createReservation checks).
    ReservationManager manager;
    manager.loadData("data/resources.txt", "data/reservations.txt");

    // One ReportGenerator, built once. It holds a reference to the manager
    // and just reads its data for the four reports.
    ReportGenerator gen(manager);

    int choice = 0;
    do {
        cout << endl << "===== Campus Resource Reservation System =====" << endl;
        cout << "1. Display all resources" << endl;
        cout << "2. Create a reservation" << endl;
        cout << "3. Cancel a reservation" << endl;
        cout << "4. Undo last cancellation" << endl;
        cout << "5. Display waiting lists" << endl;
        cout << "6. Display cancellation history" << endl;
        cout << "7. Display active reservations" << endl;
        cout << "8. Search" << endl;
        cout << "9. Sort resources" << endl;
        cout << "10. Reports" << endl;
        cout << "11. Quit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                manager.displayResources();
                break;
            }

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
                cin.ignore();
                getline(cin, studentName);
                cout << "Enter resource ID: ";
                cin >> resourceId;
                cout << "Enter date (MM/DD/YYYY, 0 for none): ";
                cin >> date;
                cout << "Enter start time (HH:MM, 0 for none): ";
                cin >> startTime;
                cout << "Enter end time (HH:MM, 0 for none): ";
                cin >> endTime;

                // "0" typed = no constraint; store as "" because hasConflict
                // treats empty as "skip this check" (D12 convention).
                if (date == "0") date = "";
                if (startTime == "0") startTime = "";

                if (endTime == "0") endTime = "";
                if (manager.createReservation(studentId, studentName, resourceId, date, startTime, endTime)){
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

            case 7: {
                manager.displayActiveReservations();
                break;
            }

            case 8: {
                // Search: pick which collection to look in, read the id,
                // call the matching find function.
                int searchChoice = 0;
                cout << endl << "--- Search ---" << endl;
                cout << "1. By resource ID" << endl;
                cout << "2. By reservation ID" << endl;
                cout << "3. By student ID" << endl;
                cout << "Choice: ";
                cin >> searchChoice;

                if (searchChoice == 1) {
                    string id;
                    cout << "Enter resource ID: ";
                    cin >> id;
                    if (manager.findResource(id)) {
                        cout << "Resource found." << endl;
                    } else {
                        cout << "Resource not found." << endl;
                    }
                } else if (searchChoice == 2) {
                    string id;
                    cout << "Enter reservation ID: ";
                    cin >> id;
                    if (manager.findReservation(id)) {
                        cout << "Reservation found." << endl;
                    } else {
                        cout << "Reservation not found." << endl;
                    }
                } else if (searchChoice == 3) {
                    string studentId;
                    cout << "Enter student ID: ";
                    cin >> studentId;
                    vector<Reservation> matches = manager.findReservationsByStudent(studentId);
                    if (matches.empty()) {
                        cout << "No reservations found for that student." << endl;
                    } else {
                        for (const Reservation &r : matches) {
                            r.print();
                        }
                    }
                } else {
                    cout << "Invalid choice." << endl;
                }
                break;
            }

            case 9: {
                // Sort: pick the criteria, reorder, then show the new order
                // so the sort is visible. sortResources() takes the criteria
                // string and does the quick sort.
                int sortChoice = 0;
                cout << endl << "--- Sort Resources ---" << endl;
                cout << "1. By name" << endl;
                cout << "2. By type" << endl;
                cout << "3. By availability" << endl;
                cout << "Choice: ";
                cin >> sortChoice;

                if (sortChoice == 1) {
                    manager.sortResources("name");
                } else if (sortChoice == 2) {
                    manager.sortResources("type");
                } else if (sortChoice == 3) {
                    manager.sortResources("availability");
                } else {
                    cout << "Invalid choice." << endl;
                }
                manager.displayResources();
                break;
            }

            case 10: {
                // Reports: four read-only summaries from ReportGenerator.
                int reportChoice = 0;
                cout << endl << "--- Reports ---" << endl;
                cout << "1. Active reservations" << endl;
                cout << "2. Resource utilization" << endl;
                cout << "3. Most requested resources" << endl;
                cout << "4. Waiting list statistics" << endl;
                cout << "Choice: ";
                cin >> reportChoice;

                if (reportChoice == 1) {
                    gen.activeReservationsReport();
                } else if (reportChoice == 2) {
                    gen.utilizationReport();
                } else if (reportChoice == 3) {
                    gen.mostRequestedReport();
                } else if (reportChoice == 4) {
                    gen.waitingStatsReport();
                } else {
                    cout << "Invalid choice." << endl;
                }
                break;
            }

            case 11: {
                cout << "Goodbye." << endl;
                break;
            }

            default: {
                // Bad input guard: a LETTER in the choice box makes
                // `cin >> choice` fail and leaves garbage in the stream.
                // clear() resets the failure flag, ignore() drains it.
                cout << "Invalid choice. Pick 1-11.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
        }                            // end switch
    } while (choice != 11);          // closes the do-loop
    return 0;
}
