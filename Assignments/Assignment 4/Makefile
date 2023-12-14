CXX = clang++
CXXFLAGS = -std=c++11 -I./include

SRCDIR = src

# List source files
SRC = $(SRCDIR)/main.cpp \
      $(SRCDIR)/bSearchTreeType.cpp \
      $(SRCDIR)/binaryTreeType.cpp

# List object files
OBJ = $(SRC:.cpp=.o)

# Main target
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I./include

clean:
	rm -f $(OBJ) $(TARGET)
