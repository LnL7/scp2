#include <map>
#include <vector>

#ifndef COUNT_PRODUCTS_H
#define COUNT_PRODUCTS_H

using Buffer = std::stringstream;
using UInt   = unsigned long;


struct CountProducts
{
  map<UInt, UInt> counts;

  CountProducts(vector<Buffer*> bs)
  {
    for(auto buf : bs) {
      UInt barcode, amount;
      if (buf->peek() == '.') { break; }

      *buf >> barcode;
      *buf >> amount;
      counts.emplace(barcode, amount);
    }
  }
};

#endif
