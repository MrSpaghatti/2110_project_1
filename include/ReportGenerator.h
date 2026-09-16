// ReportGenerator.h — REPORTS + SORTING
//
// The spec requires reports, and it REQUIRES at least one efficient sort:
//
//   "Students must implement at least one efficient sorting algorithm:
//    Merge Sort OR Quick Sort"  (proj_1.md line 185)
//
// Reports the spec asks for ("Reporting" section):
//   - Most frequently reserved resources
//   - "Sort resources according to user-selected criteria" (line 34)
//   - Resource reports / reservation reports
//
// Class declaration goes here. Suggested shape (all static, pure functions
// that take data and print — this class holds no state):
//
//   class ReportGenerator {
//   public:
//     static void resourceReport(std::vector<Resource>& resources,
//                                bool byId, bool byName, bool byAvailability);
//     static void frequencyReport(const std::vector<Reservation>& active,
//                                 const std::vector<Resource>& resources);
//   private:
//     static void mergeSort(...);   // or quickSort(...) — YOUR choice
//   };
//
// Design questions to settle BEFORE you type:
//
// 1. WHICH sort do you implement? Merge sort is easier to get right on a
//    vector (no worst-case O(n^2) trap, stable). Quick sort is fewer lines
//    but the pivot choice matters. Pick ONE and be able to explain it —
//    the grader WILL ask ("every member must explain submitted code").
//
// 2. Sort by what criteria? The menu can offer: ID (R101 < R102), name
//    (alphabetical), availability. A comparator flag leads to either a
//    switch inside the sort or three small comparator helpers. Keep it
//    simple: one function parameter (enum) that picks the comparison, and
//    the sort itself stays generic over "is a < b".
//
// 3. Where does frequency counting live? Simplest: walk the reservation
//    list, count per resourceId in a std::map<std::string,int>, then sort
//    the (resource,count) pairs by count for the "most frequently reserved"
//    report. That report is probably the OUTPUT the milestone actually
//    checks, so get it readable.
//
// Big-O for the writeup: merge sort O(n log n) worst case; quick sort
// O(n log n) average / O(n^2) worst case (say why you picked what you did).
//
// Guard + std:: style: same as the other headers.