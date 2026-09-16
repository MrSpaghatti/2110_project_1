// src/Student.cpp — implement the Student class here.
//
// This file is Hoang's half-done piece: Student.h already declares the
// contract (id, name, ctor, getters, print). Right now this file is 0 bytes
// and NOTHING defines those methods — the moment any code calls
// Student::getId() or Student::print(), the linker dies with
// "undefined reference". (It only builds today because nothing uses Student
// yet. That changes the second ReservationManager touches it.)
//
// You can finish this in under 5 minutes by copying the SHAPE of
// Resource.cpp / Reservation.cpp:
//
//   Student::Student()                     // id_ = "", name_ = ""
//   Student::Student(const string &id, const string &name)
//   string Student::getId() const          // return id_
//   string Student::getName() const        // return name_
//   void Student::print() const            // "Student ID : ..." + "Name : ..."
//                                          // (match the alignment style of
//                                          //   Reservation::print())
//
// It's trivial, but it's also the ONLY thing standing between your repo and
// every other file linking cleanly. Do it early.
//
// Note: this is Hoang's assigned piece. If you'd rather hand it back, tell
// him exactly this: "Student.cpp is empty — header declares methods, nothing
// defines them. Linker will fail as soon as anyone uses Student." But for a
// 5-minute file, the practical call is usually to just write it and mark the
// README dev log with who did what.