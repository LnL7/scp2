CFLAGS=-g -Wall -Ilib -Iinclude
LDFLAGS=

SOURCES=$(filter-out main.cpp, $(wildcard *.cpp))
OBJECTS=$(SOURCES:.cpp=.o)

TEST_SOURCES=$(wildcard tests/*.cpp)
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)

build: bin/build
	@./bin/build tests/fixtures/input.txt tests/fixtures/output.txt

test: bin/test
	@./bin/test --output=color

bin/build: $(OBJECTS)
	$(CXX) $(CFLAGS) -o bin/build main.o $(OBJECTS)

bin/test: $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CFLAGS) -o bin/test $(OBJECTS) $(TEST_OBJECTS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) *.o test/*.o


.PHONY: clean
