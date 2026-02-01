# Run with `-j 4` flag to distribute compilation through different threads.
# `/usr/bin/time make (-j 4)` to check how long does it take to assemble the project. 

CXX = g++

CXXBASEFLAGS = --std=c++17 -MMD
CXXRELEASEFLAGS = -O2
CXXDEBUGFLAGS = -g -O0 -DDEBUG

SRC = src/main.cpp src/runner.cpp src/scanner.cpp src/token.cpp src/debug.cpp
TESTS = tests/*.cpp
OBJECTS = $(SRC:.cpp=.o)

BIN = virtel
TESTBIN = virtel_tests

# ----------------------------------------------release
$(BIN): $(OBJECTS)
	$(CXX) $(CXXBASEFLAGS) $(OBJECTS) -o $(BIN)

# ----------------------------------------------debug
debug: CXXFLAGS = $(CXXBASEFLAGS) $(CXXDEBUGFLAGS)
debug: clean $(BIN)

# ----------------------------------------------default
CXXFLAGS = $(CXXBASEFLAGS) $(CXXDEBUGFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFALGS) -c $< -o $@

# ----------------------------------------------test
test: CXXFALGS = $(CXXBASEFLAGS) $(CXXDEBUGFLAGS)
test: $(OBJECTS)
	$(CXX) $(OBJECTS) $(TESTS) -lgtest -lgtest_main -pthread -o $(TESTBIN)

# ----------------------------------------------utils
run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN) $(TESTBIN) $(OBJECTS) *.d

# include all dependencies, so make could react on any changes inside of .h/.hpp
-include *.d

