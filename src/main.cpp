#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "FileLoader.h"
#include "ReservationManager.h"
#include "ReportGenerator.h"
using namespace std;

enum class InputStatus {
    Ok,
    Invalid,
    End
};

bool readLine(const string &prompt, string &value) {
    cout << prompt;
    if (!getline(cin, value)) {
        cout << endl << "Input ended. Exiting." << endl;
        return false;
    }
    return true;
}

InputStatus readChoice(const string &prompt, int &choice) {
    string line;
    if (!readLine(prompt, line)) {
        return InputStatus::End;
    }

    istringstream input(line);
    if (!(input >> choice)) {
        return InputStatus::Invalid;
    }
    input >> ws;
    return input.eof() ? InputStatus::Ok : InputStatus::Invalid;
}

int main() {
    // Load the catalog ONCE, before the loop. Every menu option that needs
    // the resource list reads from the manager.
    ReservationManager manager;
    manager.loadData("data/resources.txt", "data/reservations.txt");

    // One ReportGenerator, built once. It reads the manager's data for reports.
    ReportGenerator gen(manager);

    while (true) {
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

        int choice = 0;
        InputStatus status = readChoice("Choice: ", choice);
        if (status == InputStatus::End) {
            break;
        }
        if (status == InputStatus::Invalid) {
            cout << "Invalid choice. Enter a number from 1 to 11." << endl;
            continue;
        }

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

                if (!readLine("Enter student ID: ", studentId) ||
                    !readLine("Enter student name: ", studentName) ||
                    !readLine("Enter resource ID: ", resourceId) ||
                    !readLine("Enter date (MM/DD/YYYY, 0 for none): ", date) ||
                    !readLine("Enter start time (HH:MM, 0 for none): ", startTime) ||
                    !readLine("Enter end time (HH:MM, 0 for none): ", endTime)) {
                    return 0;
                }

                // "0" means no time constraint.
                if (date == "0") date = "";
                if (startTime == "0") startTime = "";
                if (endTime == "0") endTime = "";

                string slotError = manager.validateReservationSlot(date, startTime, endTime);
                if (!slotError.empty()) {
                    cout << "Invalid reservation slot: " << slotError << endl;
                } else if (!manager.findResource(resourceId)) {
                    cout << "Resource not found." << endl;
                } else if (manager.createReservation(studentId, studentName, resourceId,
                                                     date, startTime, endTime)) {
                    cout << "Reservation created." << endl;
                } else {
                    cout << "Unavailable - request added to waiting list." << endl;
                }
                break;
            }

            case 3: {
                string reservationId;
                if (!readLine("Enter reservation ID: ", reservationId)) {
                    return 0;
                }

                if (manager.cancelReservation(reservationId)) {
                    cout << "Reservation cancelled." << endl;
                } else {
                    cout << "Reservation not found." << endl;
                }
                break;
            }

            case 4: {
                if (manager.undoCancellation()) {
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
                int searchChoice = 0;
                cout << endl << "--- Search ---" << endl;
                cout << "1. By resource ID" << endl;
                cout << "2. By reservation ID" << endl;
                cout << "3. By student ID" << endl;
                status = readChoice("Choice: ", searchChoice);
                if (status == InputStatus::End) return 0;
                if (status == InputStatus::Invalid ||
                    searchChoice < 1 || searchChoice > 3) {
                    cout << "Invalid choice. Enter 1, 2, or 3." << endl;
                    break;
                }

                string id;
                if (searchChoice == 1) {
                    if (!readLine("Enter resource ID: ", id)) return 0;
                    cout << (manager.findResource(id) ? "Resource found." :
                                                        "Resource not found.") << endl;
                } else if (searchChoice == 2) {
                    if (!readLine("Enter reservation ID: ", id)) return 0;
                    cout << (manager.findReservation(id) ? "Reservation found." :
                                                           "Reservation not found.") << endl;
                } else {
                    if (!readLine("Enter student ID: ", id)) return 0;
                    vector<Reservation> matches = manager.findReservationsByStudent(id);
                    if (matches.empty()) {
                        cout << "No reservations found for that student." << endl;
                    } else {
                        for (const Reservation &reservation : matches) {
                            reservation.print();
                        }
                    }
                }
                break;
            }

            case 9: {
                int sortChoice = 0;
                cout << endl << "--- Sort Resources ---" << endl;
                cout << "1. By name" << endl;
                cout << "2. By type" << endl;
                cout << "3. By availability" << endl;
                status = readChoice("Choice: ", sortChoice);
                if (status == InputStatus::End) return 0;
                if (status == InputStatus::Invalid ||
                    sortChoice < 1 || sortChoice > 3) {
                    cout << "Invalid choice. Enter 1, 2, or 3." << endl;
                    break;
                }

                if (sortChoice == 1) {
                    manager.sortResources("name");
                } else if (sortChoice == 2) {
                    manager.sortResources("type");
                } else {
                    manager.sortResources("availability");
                }
                manager.displayResources();
                break;
            }

            case 10: {
                int reportChoice = 0;
                cout << endl << "--- Reports ---" << endl;
                cout << "1. Active reservations" << endl;
                cout << "2. Resource utilization" << endl;
                cout << "3. Most requested resources" << endl;
                cout << "4. Waiting list statistics" << endl;
                status = readChoice("Choice: ", reportChoice);
                if (status == InputStatus::End) return 0;
                if (status == InputStatus::Invalid ||
                    reportChoice < 1 || reportChoice > 4) {
                    cout << "Invalid choice. Enter a number from 1 to 4." << endl;
                    break;
                }

                if (reportChoice == 1) {
                    gen.activeReservationsReport();
                } else if (reportChoice == 2) {
                    gen.utilizationReport();
                } else if (reportChoice == 3) {
                    gen.mostRequestedReport();
                } else {
                    gen.waitingStatsReport();
                }
                break;
            }

            case 11: {
                cout << "Goodbye." << endl;
                return 0;
            }

            default: {
                cout << "Invalid choice. Enter a number from 1 to 11." << endl;
                break;
            }
        }
    }

    return 0;
}
