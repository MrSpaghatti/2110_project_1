#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include <string>
#include <vector>
#include <map>
#include "Resource.h"
#include "WaitingList.h"

// A reservation stored directly inside the manager (no separate
// Reservation class, no LinkedList). One per row in reservations.txt.
struct ReservationData {
  std::string reservationId;
  std::string studentId;
  std::string studentName;
  std::string resourceId;
  std::string date;
};

// The "hub" of the app. Owns the resource inventory, active reservations,
// the per-resource waiting queues, and the cancellation stack. Exposes the
// menu operations the main() loop calls.
class ReservationManager {
public:
  ReservationManager();                 // empty system, nothing loaded

  bool loadData(
      const std::string &resourcesPath,
      const std::string &reservationsPath
  );                                     // file loading + initial reservations

  std::vector<Resource> getResources() const;
  std::vector<ReservationData> getActiveReservations() const;

  void displayResources() const;        // "View Resources"
  void displayActiveReservations() const;

  bool createReservation(
      const std::string &studentId,
      const std::string &studentName,
      const std::string &resourceId
  );                                     // if busy -> enqueue on waiting list

  bool cancelReservation(const std::string &reservationId); // push onto history
  bool undoCancellation();               // pop history, restore reservation

  void addToWaitingList(
      const std::string &studentId,
      const std::string &studentName,
      const std::string &resourceId
  );
  void processWaitingList(const std::string &resourceId);
  // ^ called when a resource frees up: auto-assign the next waiting request

  void displayWaitingLists() const;
  void displayCancellationHistory() const;

  // searching: find a reservation/resource by id
  bool findReservation(const std::string &id) const;
  bool findResource(const std::string &id) const;

  // sorting: reorder resources (by name/type/availability) before display
  void sortResources(const std::string &criteria);

private:
  std::vector<Resource> resources_;      // inventory (vector: fast traversal)
  std::vector<ReservationData> active_;  // active reservations
  std::vector<ReservationData> history_; // LIFO undo stack (pop from back)
  std::map<std::string, WaitingList> waitingQueues_; // one queue per resource
};

#endif