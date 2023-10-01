CXX = clang++

CXXFLAGS = -std=c++11

all: Bank

Bank: main.o
	$(CXX) $(CXXFLAGS) -o Bank main.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o Bank
