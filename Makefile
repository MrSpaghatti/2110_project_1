# Campus Resource Reservation System — Makefile
# Usage:
#   make          build the whole project -> reservation_system
#   make check    syntax-check every .cpp file (no build, no main needed)
#   make run      build and run the program
#   make clean    delete build artifacts

CXX      = g++
CXXFLAGS = -std=c++11 -Wall -I include
SRCS     = $(wildcard src/*.cpp)
TARGET   = reservation_system

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

check:
	$(CXX) $(CXXFLAGS) -fsyntax-only $(SRCS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) src/*.o

.PHONY: all check run clean