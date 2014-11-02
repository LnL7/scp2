#include <map>
#include <vector>

#include "product.h"
#include "read_product.h"

#ifndef COLLECT_PRODUCTS_H
#define COLLECT_PRODUCTS_H

using std::map;
using std::vector;
using Buffer = std::stringstream;
using UInt   = unsigned long;


struct CollectProducts
{
  map<UInt, Product*> products;

  CollectProducts(vector<Buffer*> bs) {
    for(auto buf : bs) {
      auto p = ReadProduct(*buf).product;
      products.emplace(p->barcode, p);
    }
  };
};

#endif
