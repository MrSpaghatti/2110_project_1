#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource {
public:
  // default constructor:
  // Builds an empty Resource so vectors and linked lists can hold one before
  // real data arrives. Availability defautls to false because an unknown
  // resource should not show up as a bookable option.
  Resource();

  // full constructor:
  // Constructs from one parsed file line.
  // The caller (reservation manager's file loader) is responsible for splitting
  // the record and converting the "Available"/"Unavailable" text into a bool
  // before calling this. Takes strings by const reference to avoid unneeded
  // copies when the record is loaded.
  Resource(
      const std::string &id,
      const std::string &name,
      const std::string &type,
      bool available
  );

  std::string getId() const;    // the unique ID: "R101" must match reservations.txt byte-for-byte
  std::string getName() const;  // human-readable display name
  std::string getType() const;  // resource category. EX: "Study Room"
  bool isAvailable() const;     // true == currently bookable

  void
  setAvailable(bool available); // flip when a reservation is created/cancelled;
                                // also used by undo to restore availability.

  void print() const;           // one formatted row for the "View Resources" menu.
                                // prints "Available"/"Unavailable" instead of 1/0 so the
                                // output reads like the input file.
private:
  std::string id_;
  std::string name_;
  std::string type_;
  bool available_;
};

#endif
