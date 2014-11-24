# Point of Sale


## Example

- `bin/cli [file]`


## Build Executable

```
clang++ -Isrc -std=c++11 -g -Wall -pedantic -c src/entry.cpp -o _build/src/entry.o
clang++ -Isrc -std=c++11 -g -Wall -pedantic -c src/catalogue.cpp -o _build/src/catalogue.o
clang++ -Isrc -std=c++11 -g -Wall -pedantic -o bin/cli _build/src/catalogue.o _build/src/entry.o cli.cpp
bin/cli
```

## Build Tests

```
clang++ -Isrc -std=c++11 -g -Wall -pedantic -c src/entry.cpp -o _build/src/entry.o
clang++ -Isrc -std=c++11 -g -Wall -pedantic -c src/catalogue.cpp -o _build/src/catalogue.o
clang++ -Isrc -std=c++11 -g -Wall -pedantic -o bin/either_test _build/src/catalogue.o _build/src/entry.o -lboost_unit_test_framework tests/either_test.cpp
clang++ -Isrc -std=c++11 -g -Wall -pedantic -o bin/maybe_test _build/src/catalogue.o _build/src/entry.o -lboost_unit_test_framework tests/maybe_test.cpp
clang++ -Isrc -std=c++11 -g -Wall -pedantic -o bin/foo_test _build/src/catalogue.o _build/src/entry.o -lboost_unit_test_framework tests/foo_test.cpp
bin/either_test
bin/maybe_test
bin/foo_test
```
