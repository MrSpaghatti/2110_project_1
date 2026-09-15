#include "ReportGenerator.h"
// src/ReportGenerator.cpp — implement REPORTS + SORTING here.
//
// This file has one real algorithm in it (the sort) and the rest is
// printing. The sort is the graded piece — give it its own section with a
// comment above it explaining the algorithm in 3 lines, so the person
// grading can find it fast.
//
// Suggested order:
//
// 1. Implement the sort FIRST, on a plain std::vector<Resource>, before any
//    report code exists. Test it standalone in main() with a tiny hardcoded
//    vector (or via a temporary test in the menu) — sort must be visibly
//    correct before reports use it. Quick sanity: 5 resources in scrambled
//    order -> sorted output.
//
// 2. mergeSort(lo, hi) or quickSort(lo, hi): the recursive shape. Remember
//    vector bounds — the #1 bug in student sorts is an off-by-one on the
//    midpoint or pivot. Trace your partition on paper first (3 elements,
//    then 5), then type.
//
// 3. resourceReport(): print the table header, sort a COPY of resources_
//    (don't mutate the manager's real data — pass by value or copy inside),
//    print rows. A neat aligned table reads like a real report.
//
// 4. frequencyReport(): count reservations per resourceId with a
//    std::map<std::string,int>, then sort (count desc, tie-break by
//    resourceId asc) and print the top few. This is the "most frequently
//    reserved resources" deliverable.
//
// 5. Wire it to the manager: add a `report` action to the menu (or to
//    ReservationManager as a displayReports() method). Menu flow is your
//    call, just keep main.cpp thin.
//
// Compile after every step. The sort deserves its OWN `make check` before
// you build anything on top of it — a report that uses a broken sort looks
// like wrong output, and wrong output is hard to debug at the report layer.