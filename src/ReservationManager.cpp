#include "ReservationManager.h"
#include "FileLoader.h"
#include <algorithm>
#include <ctime>
#include <iostream>
using namespace std;

namespace {
bool isDigit(char value) {
  return value >= '0' && value <= '9';
}

bool parseTwoDigits(const string &value, size_t position, int &number) {
  if (position + 1 >= value.size() ||
      !isDigit(value[position]) || !isDigit(value[position + 1])) {
    return false;
  }
  number = (value[position] - '0') * 10 + (value[position + 1] - '0');
  return true;
}

bool isValidDate(const string &date) {
  if (date.size() != 10 || date[2] != '/' || date[5] != '/') {
    return false;
  }

  int month = 0;
  int day = 0;
  if (!parseTwoDigits(date, 0, month) || !parseTwoDigits(date, 3, day) ||
      !isDigit(date[6]) || !isDigit(date[7]) ||
      !isDigit(date[8]) || !isDigit(date[9])) {
    return false;
  }
  int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
             (date[8] - '0') * 10 + (date[9] - '0');
  if (year == 0 || month < 1 || month > 12) {
    return false;
  }

  const int daysInMonth[] = {31, 28, 31, 30, 31, 30,
                             31, 31, 30, 31, 30, 31};
  int maxDay = daysInMonth[month - 1];
  bool leapYear = year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
  if (month == 2 && leapYear) {
    maxDay = 29;
  }
  return day >= 1 && day <= maxDay;
}

bool parseTime(const string &time, int &minutes, bool allowEndOfDay) {
  if (time.size() != 5 || time[2] != ':' ||
      !isDigit(time[0]) || !isDigit(time[1]) ||
      !isDigit(time[3]) || !isDigit(time[4])) {
    return false;
  }

  int hour = (time[0] - '0') * 10 + (time[1] - '0');
  int minute = (time[3] - '0') * 10 + (time[4] - '0');
  if (allowEndOfDay && hour == 24 && minute == 0) {
    minutes = 24 * 60;
    return true;
  }
  if (hour > 23 || minute > 59) {
    return false;
  }
  minutes = hour * 60 + minute;
  return true;
}
}

// implementation of the ReservationManager class declared in ReservationManager.h

ReservationManager::ReservationManager() : nextReservationId_(0) {
  // Empty body
}

bool ReservationManager::loadData(
    const string &resourcesPath,
    const string &reservationsPath
) {
  resources_ = FileLoader::loadResources(resourcesPath);
  vector<Reservation> loaded = FileLoader::loadReservations(reservationsPath);
  for (const auto& res : loaded) {
    active_.insert(res);
    // D14: seed ids are numeric (301, 302, ...) — remember the max so new
    // ids continue the sequence (321, ...) instead of "RES" + size (which
    // collides/reuses after a cancellation shrinks the list).
    try { nextReservationId_ = max(nextReservationId_, stoi(res.getReservationId())); }
    catch (...) { /* non-numeric seed id: ignore */ }
  }
  nextReservationId_++;  // next id = one past the max we just saw
  // D12 (2026-09-19): do NOT flip Resource availability flags here. A
  // resource is "available" for a given date/time iff no ACTIVE reservation
  // conflicts with it — checked at createReservation time via
  // LinkedList::hasConflict. The file's "Unavailable" text is display
  // metadata only.
  if (resources_.empty()) {
      return false;
  }
  return true;
}

vector<Resource> ReservationManager::getResources() const {
  return resources_;
}

string ReservationManager::validateReservationSlot(
    const string &date,
    const string &startTime,
    const string &endTime
) const {
  if (!date.empty() && !isValidDate(date)) {
    return "Date must be a real date in MM/DD/YYYY format, or 0 for none.";
  }

  if (startTime.empty() && endTime.empty()) {
    return "";
  }
  if (startTime.empty() || endTime.empty()) {
    return "Enter both start and end times, or enter 0 for both.";
  }

  int startMinutes = 0;
  int endMinutes = 0;
  if (!parseTime(startTime, startMinutes, false) ||
      !parseTime(endTime, endMinutes, true)) {
    return "Times must use 24-hour HH:MM format; only an end time may be 24:00.";
  }
  if (endMinutes <= startMinutes) {
    return "End time must be later than start time; overnight reservations are not supported.";
  }
  return "";
}

void ReservationManager::displayResources() const {
  cout << "===== Resources =====" << endl;
  // "right now" once, so every row answers the same question
  time_t t = time(nullptr);
  struct tm tmv;
#ifdef _WIN32
  if (localtime_s(&tmv, &t) != 0) {
    cerr << "Unable to determine the current local time." << endl;
    return;
  }
#else
  if (localtime_r(&t, &tmv) == nullptr) {
    cerr << "Unable to determine the current local time." << endl;
    return;
  }
#endif
  char dateBuf[16], timeBuf[8];
  strftime(dateBuf, sizeof(dateBuf), "%m/%d/%Y", &tmv); // "09/19/2026"
  strftime(timeBuf, sizeof(timeBuf), "%H:%M", &tmv);    // "23:48"
  string today(dateBuf), now(timeBuf);

  for (const auto& res : resources_) {
    bool busyNow = active_.hasConflict(res.getId(), today, now, now);
    res.print(active_.countFor(res.getId()), busyNow);
  }
}

void ReservationManager::displayActiveReservations() const {
  active_.display();
}

bool ReservationManager::createReservation(
    const string &studentId,
    const string &studentName,
    const string &resourceId,
    const string &date,
    const string &startTime,
    const string &endTime
) {
    if (!validateReservationSlot(date, startTime, endTime).empty()) {
        return false;
    }

    // 1. Resource must exist.
    bool found = false;
    bool available = false;
    for (const auto& r : resources_) {
        if (r.getId() == resourceId) {
            found = true;
            available = r.isAvailable();
            break;
        }
    }
    if (!found) {
        return false;
    }

    if (!available) {
        addToWaitingList(studentId, studentName, resourceId, date, startTime, endTime);
        return false;
    }

    // 2. D12 gate: accept only when no ACTIVE reservation conflicts on
    //    resource + date + time. Availability is derived, not a flag.
    if (active_.hasConflict(resourceId, date, startTime, endTime)) {
        // resource is busy for that slot — add to waiting list
        addToWaitingList(studentId, studentName, resourceId, date, startTime, endTime);
        return false;
    }

    // 3. Free slot: create a new reservation and append to the LinkedList.
    string resId = to_string(nextReservationId_++);
    active_.insert(Reservation(resId, studentId, studentName,
                               resourceId, date, startTime, endTime));
    return true;
}

bool ReservationManager::cancelReservation(const string &reservationId) {
  Reservation* match = active_.find(reservationId);
  if (match == nullptr) {
      return false;
  }
  string resourceId = match->getResourceId();
  history_.push(*match);          // remember for undo (graded stack)
  active_.remove(reservationId);  // take it out of the active list

  // nobody waiting -> the slot just opens (availability derives from
  // active_, no flag to flip); someone waiting -> promote them now.
  if (waitingQueues_[resourceId].isEmpty()) {
  } else {
      processWaitingList(resourceId);
  }
  return true;
}


// LIFO restore: newest cancel first. If a student is already waiting on
// that resource, the slot goes to them instead of back to the original.
bool ReservationManager::undoCancellation() {
  if (history_.isEmpty()) {
    cout << "No cancellations to undo." << endl;
    return false;
  }
  Reservation* last = history_.top();
  Reservation lastCopy = *last;
  history_.pop();
  if (!waitingQueues_[lastCopy.getResourceId()].isEmpty()) {
    processWaitingList(lastCopy.getResourceId());
  } else {
    active_.insert(lastCopy);
  }
  return true;
}

// operator[] creates the queue on first use, then enqueue appends to the
// back so the longest-waiting student is served first.
void ReservationManager::addToWaitingList(
    const string &studentId,
    const string &studentName,
    const string &resourceId,
    const string &date,
    const string &startTime,
    const string &endTime) {
    WaitingEntry entry{studentId, studentName, resourceId, date, startTime, endTime};
    waitingQueues_[resourceId].enqueue(entry);
    }

// promote the longest-waiting student; the slot stays booked, so the
// resource itself never flips back to "available" here.
void ReservationManager::processWaitingList(const string &resourceId) {
  WaitingList &q = waitingQueues_[resourceId];
  if (q.isEmpty()) return;
  const WaitingEntry next = q.front();
  if (active_.hasConflict(resourceId, next.date, next.startTime, next.endTime)) {
    return;
  }
  WaitingEntry e = q.dequeue();
  string resId = to_string(nextReservationId_++);
  active_.insert(Reservation(resId, e.studentId, e.studentName,
                             resourceId, e.date, e.startTime, e.endTime));
}

void ReservationManager::displayWaitingLists() const {
  for (const auto& pair : waitingQueues_) {
     if (!pair.second.isEmpty()) {
          cout << "Resource ID: " << pair.first << endl;
          pair.second.display();
     }
  }
}

void ReservationManager::displayCancellationHistory() const {
  history_.display();
}

bool ReservationManager::findReservation(const string &id) const {
  Reservation* r = const_cast<LinkedList&>(active_).find(id);
  return r != nullptr;
}

bool ReservationManager::findResource(const string &id) const {
  for (const auto& r : resources_) {
    if (r.getId() == id) {
      return true;
    }
  }
  return false;
}

// search by student id: hand the active list a lambda that keeps
// reservations whose studentId matches. filter() does the walking, so
// this stays one line. Lambda captures studentId by value so the copy
// lives in the closure for the whole call.
vector<Reservation> ReservationManager::findReservationsByStudent(const string &studentId) const {
    return active_.filter([studentId](const Reservation& r) {
        return r.getStudentId() == studentId;
    });
}

// reorder resources_ by the chosen criteria. The lambda picks the
// "comes before" test; quickSort does the actual work. No std::sort -
// the spec wants us to implement the sort (D-spec note in header).
void ReservationManager::sortResources(const string &criteria) {
  if (criteria == "name") {
      quickSort(resources_, 0, resources_.size() - 1, [](const Resource &a, const Resource &b) {
          return a.getName() < b.getName();
      });
  } else if (criteria == "type") {
      quickSort(resources_, 0, resources_.size() - 1, [](const Resource &a, const Resource &b) {
          return a.getType() < b.getType();
      });
  } else if (criteria == "availability") {
      quickSort(resources_, 0, resources_.size() - 1, [](const Resource &a, const Resource &b) {
          return a.isAvailable() && !b.isAvailable();
      });
  } else {
      cout << "Invalid sorting criteria: " << criteria << endl;
  }
}

// hand-written quick sort over a vector<Resource> (spec requirement).
// Same Lomuto partition as ReportGenerator::quickSort, but the order
// test comes in as a lambda ("before(x,y) == should x come first").
// Average O(n log n), worst O(n^2) on already-sorted input.
void ReservationManager::quickSort(vector<Resource> &v, int lo, int hi, const function<bool(const Resource&, const Resource&)> &before) {
    if (lo >= hi) return;

    Resource pivot = v[hi];
    int smaller = lo;

    for (int j = lo; j < hi; j++){
        if (before(v[j], pivot)) {
            swap(v[smaller], v[j]);
            smaller++;
        }
    }
    swap(v[smaller], v[hi]);

    quickSort(v, lo, smaller - 1, before);
    quickSort(v, smaller + 1, hi, before);

}
