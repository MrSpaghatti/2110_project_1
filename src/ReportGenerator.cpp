#include "ReportGenerator.h"
using namespace std;

// ReportGenerator::ReportGenerator(const ReservationManager &manager)
//   - just sets the reference member. Nothing else to initialize.
//
// The four report bodies follow the contracts in ReportGenerator.h:
//
// activeReservationsReport(): easiest correct version is to call
//   manager_.displayActiveReservations(); otherwise walk active_ and
//   print each reservation yourself.
//
// utilizationReport(): loop manager_.getResources(); for each, print
//   id/name + active_.countFor(id) + the Available/Unavailable text.
//
// mostRequestedReport(): tally counts per resourceId into a
//   vector<pair<string,int>>, quickSort descending by count, print.
//
// waitingStatsReport(): loop the resource list; for each id look up
//   the queue size in waitingQueues_ (use find(), not at() - at()
//   throws when a resource has no queue) and sum a total at the end.
//
// quickSort(v, lo, hi): recursive quick sort comparing the second
//   element of each pair (the count) so it sorts descending. Follow
//   the same structure as the LinkedList quickSort.