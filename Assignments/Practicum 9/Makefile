# Compiler name
CXX = g++

# C++ compiler flags
# -c : compile and assemble into object files
# -g : adds debugging information to the executable file
# -Wall : turns on most, but not all, compiler warnings
# -std=c++17 : uses c++17 standard
CXXFLAGS = -c -g -Wall -std=c++17

# The build target executable file; .exe is not required
PROGRAM = L10main.out

# List all .cpp files separated by space
CPPFILES = L10main.cpp sort.cpp  # Add sort.cpp to the list of source files

# Make all rule/default rule that will be run when we run "make"
# First, compile each file to an object file
# Then make a single binary program
all: $(PROGRAM)

$(PROGRAM): $(CPPFILES:.cpp=.o)
	$(CXX) -o $(PROGRAM) $^

# Make clean rule
# Delete object and binary files
clean:
	rm -f $(PROGRAM) *.o

# Add a rule to run the program
run: $(PROGRAM)
	./$(PROGRAM)
