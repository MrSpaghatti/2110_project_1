#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Resource.h"
#include "Reservation.h"
#include "LinkedList.h"
#include "CancellationHistory.h"
#include "WaitingList.h"

// The "hub" of the app. Owns the resource inventory, active reservations,
// the per-resource waiting queues, and the cancellation stack. Exposes the
// menu operations the main() loop calls.
//
// D12 (2026-09-19): active reservations live in a LinkedList (graded
// structure, O(n) traversal via hasConflict for the conflict gate) and
// cancellations live in a CancellationHistory stack (graded structure).
// Availability is NOT a flag the manager flips — it is derived from
// LinkedList::hasConflict(resourceId, date, start, end) against active_.
// The Resource "Available"/"Unavailable" text is display metadata only.
class ReservationManager {
public:
  ReservationManager();                 // empty system, nothing loaded

  bool loadData(
      const std::string &resourcesPath,
      const std::string &reservationsPath
  );                                     // file loading + initial reservations

  std::vector<Resource> getResources() const;

  void displayResources() const;        // "View Resources"
  void displayActiveReservations() const;

  bool createReservation(
      const std::string &studentId,
      const std::string &studentName,
      const std::string &resourceId,
      const std::string &date,
      const std::string &startTime,
      const std::string &endTime
  );                                     // if conflict -> enqueue on waiting list
  // ^ D12 (2026-09-16, professor clarification): "available" is NOT just the
  //   resource's Available flag — traverse the active list and check for
  //   resource + date + time conflicts (LinkedList::hasConflict). Call
  //   BEFORE accepting. "" = "no time constraint". Full D12 notes in
  //   DECISIONS.md.

  bool cancelReservation(const std::string &reservationId); // push onto history
  bool undoCancellation();               // pop history, restore reservation

  void addToWaitingList(
      const std::string &studentId,
      const std::string &studentName,
      const std::string &resourceId,
      const std::string &date,
      const std::string &startTime,
      const std::string &endTime
  );
  void processWaitingList(const std::string &resourceId);
  // ^ called when a resource frees up: auto-assign the next waiting request

  void displayWaitingLists() const;
  void displayCancellationHistory() const;

  // searching: find a reservation/resource by id
  bool findReservation(const std::string &id) const;
  bool findResource(const std::string &id) const;

  // searching by student: linear scan over the active list (the spec's
  // "find reservations associated with a student" example). Reuse
  // active_.filter(...) with a studentId predicate instead of writing a
  // second loop. Returns every match, empty vector if none.
  std::vector<Reservation> findReservationsByStudent(
      const std::string &studentId) const;

  // sorting: reorder resources (by name/type) before display. Body uses
  // the private quickSort below - std::sort is off the table since the
  // spec makes us implement the sort ourselves (merge or quick). The
  // criteria string just picks which comparator lambda to pass.
  void sortResources(const std::string &criteria);

private:
  // quick sort over resources_ (vector). Index-based recursion since
  // vectors have random access; comparator passed in so one sort covers
  // name/type. Called from sortResources() with the lambda the
  // criteria string picked.
  void quickSort(std::vector<Resource> &v, int lo, int hi,
                 const std::function<bool(const Resource&, const Resource&)> &before);

  // ReportGenerator reads active_ and waitingQueues_ directly, so it
  // gets friend access instead of a pile of public getters.
  friend class ReportGenerator;

  std::vector<Resource> resources_;      // inventory (vector: fast traversal)
  int nextReservationId_;                // D14: seeds are numeric (301..320);
                                         // new ids continue (321, 322, ...). Never
                                         // reuse a cancelled id. Set in loadData.
  LinkedList active_;                    // active reservations (graded LL)
  CancellationHistory history_;          // LIFO undo stack (graded stack)
  std::map<std::string, WaitingList> waitingQueues_; // one queue per resource
};

#endif