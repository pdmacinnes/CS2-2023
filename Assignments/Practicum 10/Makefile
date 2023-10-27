# Compiler name
CXX = g++

# C++ compiler flags
# -c : compile and assemble into object files
# -g : adds debugging information to the executable file
# -Wall : turns on most, but not all, compiler warnings
# -std=c++17 : uses c++17 standard
# Put all the required flags separated by space
CXXFLAGS = -c -g -Wall -std=c++17

# The build target executable file; .out is not required
PROGRAM = linkedlist.out

# List all .cpp files separated by space
CPPFILES = linkedlist.cpp

# Input data file
DATASET = dataset.txt

# Make all rule/default rule that'll be run when we run "make"
# First compile each file to an object file
# Then make a single binary program
all: $(PROGRAM)

$(PROGRAM): $(CPPFILES)
	$(CXX) $(CXXFLAGS) $(CPPFILES)
	$(CXX) -o $(PROGRAM) *.o

# Make clean rule
# Delete object and binary files
clean:
	rm -f $(PROGRAM) *.o

# Rule to run the program
run: $(PROGRAM)
	./$(PROGRAM) $(DATASET)
