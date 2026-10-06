#include "ReportGenerator.h"
#include <iostream>
using namespace std;

// ReportGenerator::ReportGenerator(const ReservationManager &manager)
//   - just sets the reference member. Nothing else to initialize.
ReportGenerator::ReportGenerator(const ReservationManager &manager)
    : manager_(manager) {}

// activeReservationsReport(): print the active reservation list (same
// shape as displayActiveReservations).
void ReportGenerator::activeReservationsReport() const {
    manager_.displayActiveReservations();
}

// utilizationReport(): one line per resource: id/name + how many active
// reservations it has (active_.countFor(id)) + Available/Unavailable text.
void ReportGenerator::utilizationReport() const {
    cout << "===== Resource Utilization =====" << endl;

    const auto& resources = manager_.resources_;

    for (const auto& res: resources){
        int count = manager_.active_.countFor(res.getId());
        res.print(count, false);
    }
}

// mostRequestedReport(): tally counts per resourceId into a
//   vector<pair<string,int>>, quickSort descending by count, print.
void ReportGenerator::mostRequestedReport() const {
    vector<pair<string,int>> tallies;
    for (const auto& res: manager_.resources_){
        int count = manager_.active_.countFor(res.getId());
        tallies.push_back(make_pair(res.getId(), count));
    }

    quickSort(tallies, 0, tallies.size() - 1);

    for (size_t i = 0; i < tallies.size(); i++) {
        cout << tallies[i].first << " - " << tallies[i].second << (tallies[i].second == 1 ? " reservation" : " reservations") << endl;
    }
}

// waitingStatsReport(): loop the resource list; for each id look up
//   the queue size in waitingQueues_ (use find(), not at() - at()
//   throws when a resource has no queue) and sum a total at the end.
void ReportGenerator::waitingStatsReport() const {
    cout << "===== Waiting List Statistics =====" << endl;

    int total = 0;

    for (const auto& res: manager_.resources_) {
        map<string, WaitingList>::const_iterator it = manager_.waitingQueues_.find(res.getId());

        if (it != manager_.waitingQueues_.end()) {
            int n = it->second.size();
            total += n;
            cout << res.getId() << " - " << n << " waiting" << endl;
        }
    }

    cout << "Total: " << total << " students waiting" << endl;
}

// quickSort(v, lo, hi): recursive quick sort comparing the second
//   element of each pair (the count) so it sorts descending. Follow
//   the same structure as the LinkedList quickSort.
void ReportGenerator::quickSort(std::vector<std::pair<std::string, int> > &v, int lo, int hi) const {
    if (lo >= hi) return;

    pair<string,int> pivot = v[hi];
    int smaller = lo;
    for (int j = lo; j < hi; j++) {
        if (v[j].second >= pivot.second) {
            swap(v[smaller], v[j]);
            smaller++;
        }
    }
    swap(v[smaller], v[hi]);

    quickSort(v, lo, smaller - 1);
    quickSort(v, smaller + 1, hi);
}
