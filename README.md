# Point of Sale


## Example

- `cat input.txt | _build/run`


## Build Executable

```
clang++ -Ilib -std=c++11 -g -Wall -pedantic -c lib/run_input.cpp -o _build/lib/run_input.o -MMD -MF _build/lib/run_input.m
clang++ -Ilib -std=c++11 -g -Wall -pedantic -c run.cpp -o _build/run.o -MMD -MF _build/run.m
clang++ -o _build/run _build/run.o _build/lib/run_input.o
_build/run
```

## Build Tests

```
clang++ -Ilib -std=c++11 -g -Wall -pedantic -c lib/run_input.cpp -o _build/lib/run_input.o -MMD -MF _build/lib/run_input.m
clang++ -Ilib -std=c++11 -g -Wall -pedantic -isystem gmock-1.7.0/gtest/include -Igmock-1.7.0/gtest -isystem gmock-1.7.0/include -Igmock-1.7.0 -pthread -c gmock-1.7.0/src/gmock-all.cc -o _build/gmock-1.7.0/src/gmock-all.o
clang++ -Ilib -std=c++11 -g -Wall -pedantic -isystem gmock-1.7.0/include -Igmock-1.7.0 -isystem gmock-1.7.0/gtest/include -Igmock-1.7.0/gtest -pthread -c gmock-1.7.0/gtest/src/gtest-all.cc -o _build/gmock-1.7.0/gtest/src/gtest-all.o
ar -rv _build/gmock-1.7.0/libgmock.a _build/gmock-1.7.0/gtest/src/gtest-all.o _build/gmock-1.7.0/src/gmock-all.o
clang++ -Ilib -std=c++11 -g -Wall -pedantic -isystem gmock-1.7.0/gtest/include -isystem gmock-1.7.0/include -pthread tests/foo_test.cpp lib/run_input.cpp _build/gmock-1.7.0/libgmock.a -o _build/tests/foo_test
_build/tests/foo_test
```
