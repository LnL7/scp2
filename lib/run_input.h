#include <map>
#include <sstream>

#include "collect_products.h"
#include "count_products.h"
#include "product.h"
#include "read_lines.h"
#include "read_product.h"

#ifndef RUN_INPUT_H
#define RUN_INPUT_H

using std::map;
using Buffer = std::stringstream;
using Input  = std::istream;
using Output = std::ostream;
using UInt   = unsigned long;


class RunInput
{
  map<UInt, UInt> _counts;
  map<UInt, Product*> _products;

  public:
    RunInput(Input& in, Input& file)
      : _counts(CountProducts(ReadLines(in).lines).counts)
      , _products(CollectProducts(ReadLines(file).lines).products)
    {}

    ~RunInput() {
      for(auto p : _products) { delete p.second; }
    }

    void run(Output& out);
};

#endif
