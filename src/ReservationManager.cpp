#include "ReservationManager.h"
#include "FileLoader.h"
#include <algorithm>
#include <iostream>
using namespace std;
// implementation of the ReservationManager class declared in ReservationManager.h

ReservationManager::ReservationManager() {
  // Empty body
}

bool ReservationManager::loadData(
    const string &resourcesPath,
    const string &reservationsPath
) {
  resources_ = FileLoader::loadResources(resourcesPath);
  active_ = FileLoader::loadReservations(reservationsPath);
  for ( const auto& res : active_) {
    for (auto &resource : resources_) {
      if (resource.getId() == res.resourceId) {
        resource.setAvailable(false);
      }
    }
  }
  if (resources_.empty()) {
      return false;
  }
  return true;
}
  // then parse reservations.txt into active_ and mark matched resources
  // unavailable. Return false on a failed load.


vector<Resource> ReservationManager::getResources() const {
  return resources_;
}

vector<ReservationData> ReservationManager::getActiveReservations() const {
  return active_;
}

void ReservationManager::displayResources() const {
  cout << "===== Resources =====" << endl;
  for (const auto& r : resources_) {
    r.print();
  }
}

void ReservationManager::displayActiveReservations() const {
  for (const auto& res : active_){
      cout << res.reservationId << " | " << res.studentId << " | " << res.studentName << " | " << res.resourceId << endl;
    
  }
}

bool ReservationManager::createReservation(
    const string &studentId,
    const string &studentName,
    const string &resourceId
) {
    for (auto& r : resources_) {
        if (r.getId() == resourceId) {
            if (r.isAvailable()) {
                // create a new reservation and add to active_
                string resId = "RES" + to_string(active_.size() + 1);
                active_.push_back({resId, studentId, studentName, resourceId});
                r.setAvailable(false);
                return true;
            } else {
                // resource is busy, add to waiting list
                addToWaitingList(studentId, studentName, resourceId);
                return false;
            }
        }
    }
    return false;
}

bool ReservationManager::cancelReservation(const string &reservationId) {
  auto it = active_.end();
  for (auto i = active_.begin(); i != active_.end(); ++i) {
    if (i->reservationId == reservationId) {
      it = i;
      break;
    }
  }
  if (it == active_.end()) {
      return false;
  }
  string resourceId = it->resourceId;
  history_.push_back(*it);
  active_.erase(it);

  
  if (waitingQueues_[resourceId].isEmpty()) {
      for (auto& r : resources_) {
          if (r.getId() == resourceId) {
              r.setAvailable(true);
              break;
          }
      }
  } else {
      processWaitingList(resourceId);
  }
  return true;
}


bool ReservationManager::undoCancellation() {
  if (history_.empty()) {
    cout << "No cancellations to undo." << endl;
    return false;
  }
  ReservationData last = history_.back();
  history_.pop_back();
  if (!waitingQueues_[last.resourceId].isEmpty()) {
    processWaitingList(last.resourceId);
  } else {
    active_.push_back(last);
    for (auto& r : resources_) {
      if (r.getId() == last.resourceId) {
          r.setAvailable(false);
          break;
      }
    }
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
  string resId = "RES" + to_string(active_.size() + 1);
  active_.push_back({resId, e.studentId, e.studentName, resourceId});
  for (auto& r : resources_) {
      if ( r.getId() == resourceId) {
            r.setAvailable(false);
            break;
      }
  }
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
  for (const auto& res : history_) {
    cout << res.reservationId << " | " << res.studentId << " | " << res.studentName << " | " << res.resourceId << endl;
  }
}

bool ReservationManager::findReservation(const string &id) const {
  for (const auto& res : active_) {
    if (res.reservationId == id) {
      return true;
    }
  }
  return false;
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