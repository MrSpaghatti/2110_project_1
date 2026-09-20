#include "ReservationManager.h"
#include "FileLoader.h"
#include <algorithm>
#include <ctime>
#include <iostream>
using namespace std;
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

void ReservationManager::displayResources() const {
  cout << "===== Resources =====" << endl;
  // "right now" once, so every row answers the same question
  time_t t = time(nullptr);
  struct tm tmv;
  localtime_r(&t, &tmv);
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
    // 1. Resource must exist.
    bool found = false;
    for (const auto& r : resources_) {
        if (r.getId() == resourceId) {
            found = true;
            break;
        }
    }
    if (!found) {
        return false;
    }

    // 2. D12 gate: accept only when no ACTIVE reservation conflicts on
    //    resource + date + time. Availability is derived, not a flag.
    if (active_.hasConflict(resourceId, date, startTime, endTime)) {
        // resource is busy for that slot — add to waiting list
        addToWaitingList(studentId, studentName, resourceId);
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

  if (waitingQueues_[resourceId].isEmpty()) {
      // nobody waiting — slot simply opens up (availability is derived
      // from active_ now, so there is no flag to flip)
  } else {
      processWaitingList(resourceId);
  }
  return true;
}


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

void ReservationManager::addToWaitingList(
    const string &studentId,
    const string &studentName,
    const string &resourceId) {
    WaitingEntry entry{studentId, studentName, resourceId};
    waitingQueues_[resourceId].enqueue(entry);
    }

void ReservationManager::processWaitingList(const string &resourceId) {
  WaitingList &q = waitingQueues_[resourceId];
  if (q.isEmpty()) return;
  WaitingEntry e = q.dequeue();
  string resId = to_string(nextReservationId_++);
  active_.insert(Reservation(resId, e.studentId, e.studentName,
                             resourceId, "", "", ""));
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

void ReservationManager::sortResources(const string &criteria) {
  if (criteria == "name") {
    sort(resources_.begin(), resources_.end(),
          [](const Resource &a, const Resource &b) {
            return a.getName() < b.getName();
          });
  } else if (criteria == "type") {
    sort(resources_.begin(), resources_.end(),
          [](const Resource &a, const Resource &b) {
            return a.getType() < b.getType();
          });
  } else if (criteria == "availability") {
    sort(resources_.begin(), resources_.end(),
          [](const Resource &a, const Resource &b) {
            return a.isAvailable() && !b.isAvailable();
          });
  } else {
    cout << "Invalid sorting criteria: " << criteria << endl;
  }
}