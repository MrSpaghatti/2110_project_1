#include "Resource.h"
#include <iostream>
using namespace std;
// implementation of the Resource class declared in Resource.h

// this is a placeholder so that vectors and lists can hold a Resource type before real data loads in.
// available set to false because we dont want an empty listing showing up for reservation.
Resource::Resource() {
    available_ = false;
}

// strings by const & to avoid copies when loading a full file
Resource::Resource(const string &id, const string &name, const string &type, bool available){
    id_ = id;
    name_ = name;
    type_ = type;
    available_ = available;
}

// const because the getters only read data. 
string Resource::getId() const {
    return id_;
}
string Resource::getName() const {
    return name_;
}
string Resource::getType() const {
    return type_;
}

// checks whether a listing is open for reservation
bool Resource::isAvailable() const {
    return available_;
}

// flips the flag between available and unavailable when a reservation, cancel, or undo happens.
void Resource::setAvailable(bool available){
    available_ = available;
}

// menu must read like input file, cant just print 1/0
void Resource::print(int activeCount, bool busyNow) const {
    // D14: the word is live. File "Unavailable" wins (equipment out of
    // service); otherwise the resource is "Unavailable (in use now)" when a
    // reservation conflicts with the current date/time, else "Available".
    cout << id_ << " - " << name_ << " - " << type_ << " - ";
    if (!available_) {
        cout << "Unavailable";
    } else if (busyNow) {
        cout << "Unavailable (in use right now)";
    } else {
        cout << "Available";
    }
    if (activeCount > 0) {
        cout << " (" << activeCount << " active reservation" << (activeCount == 1 ? "" : "s") << ")";
    }
    cout << endl;
}
