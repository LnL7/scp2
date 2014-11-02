#include <iostream>
#include <fstream>

#include "run_input.h"

using File = std::ifstream;


int main(int argc, char* argv[]) {
  File pricelist("prijslijst.txt");
  RunInput(std::cin, pricelist).run(std::cout);
  return 0;
}
