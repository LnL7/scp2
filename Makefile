CFLAGS=-g -Wall -Iinclude
LDFLAGS=

SOURCES=$(filter-out asker.cpp, $(wildcard *.cpp))
OBJECTS=$(SOURCES:.cpp=.o)

TEST_SOURCES=$(wildcard tests/*.cpp)
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)

asker: bin/asker
	@./bin/asker tests/fixtures/input.txt tests/fixtures/output.txt

test: bin/test
	@./bin/test --output=color

bin/asker: asker.o $(OBJECTS)
	$(CXX) $(CFLAGS) -o bin/asker asker.o $(OBJECTS)

bin/test: $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CFLAGS) -o bin/test $(OBJECTS) $(TEST_OBJECTS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) *.o test/*.o


.PHONY: clean
