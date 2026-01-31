# Run with `-j 4` flag to distribute compilation through different threads.
# `/usr/bin/time make (-j 4)` to check how long does it take to assemble the project. 

CXX = g++
CXXFLAGS = --std=c++17 -MMD --optimize=2

SRC = src/main.cpp
OBJECTS = $(SRC:.cpp=.o)
BIN = virtel

virtel: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BIN)

run: build
	./$(BIN)

%.o: $(SRC)
	$(CXX) $(CXXFALGS) -c $< -o $@

clean:
	rm -f virtel *.o *.d

# include all dependencies, so make could react on any changes inside of .h/.hpp
-include *.d

