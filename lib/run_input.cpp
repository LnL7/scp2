#include "run_input.h"

void RunInput::run(Output& out) {
  double total(0);

  for(auto c : _counts) {
    auto p = _products[c.first];
    if (p == NULL) {
      out << "ERROR: Invalid Product\n";
      exit(1);
    }
    double price = p->price * c.second;
    total += price;
    out << c.second << "\t" << p->name << "\t" << price << std::endl;
  }
  out << "Total\t" << total << std::endl;
  }
