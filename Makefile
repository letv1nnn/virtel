# Run with `-j 4` flag to distribute compilation through different threads.
# `/usr/bin/time make (-j 4)` to check how long does it take to assemble the project. 

CXX = g++
CXXFLAGS = --std=c++17 -O2 -MMD

SRC = src/main.cpp src/runner.cpp
OBJECTS = $(SRC:.cpp=.o)
BIN = virtel

$(BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BIN)

debug: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -D DEBUG -o $(BIN)

run: $(BIN)
	./$(BIN)

%.o: %.cpp
	$(CXX) $(CXXFALGS) -c $< -o $@

clean:
	rm -f $(BIN) $(OBJECTS) *.d

# include all dependencies, so make could react on any changes inside of .h/.hpp
-include *.d

