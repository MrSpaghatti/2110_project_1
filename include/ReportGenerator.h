#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <string>
#include <vector>
#include <functional>
#include <utility>
#include "ReservationManager.h"

// The four reports the final submission asks for:
//   1. active reservations
//   2. resource utilization
//   3. most requested resources
//   4. waiting-list statistics
//
// Just a reader - holds a const ref to the manager and doesn't change
// anything. Friend of ReservationManager so it can see active_ and the
// waiting queues. Reports print to cout like the rest of the menu.
class ReportGenerator {
public:
  // Has to be given the manager it reports on; the reference member
  // means there's no default constructor.
  explicit ReportGenerator(const ReservationManager &manager);

  // 1: print the active reservation list (same shape as
  //    displayActiveReservations).
  void activeReservationsReport() const;

  // 2: one line per resource: how many active reservations it has
  //    (active_.countFor(id)) plus its Available/Unavailable status.
  void utilizationReport() const;

  // 3: count reservations per resourceId, sort the (resourceId, count)
  //    pairs descending with the private quickSort, print top first.
  void mostRequestedReport() const;

  // 4: per resource, how many students are waiting (queue size at
  //    waitingQueues_[id]) plus a total across all resources.
  void waitingStatsReport() const;

private:
  // sort the (resourceId, count) pairs by count descending. Same
  // comparator idea as the LinkedList sort, but on a vector of pairs.
  // Used by mostRequestedReport.
  void quickSort(std::vector<std::pair<std::string, int>> &v, int lo, int hi);

  const ReservationManager &manager_;   // the system these reports read
};

#endif