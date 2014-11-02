#include <sstream>

#include "product.h"

#ifndef READ_PRODUCT_H
#define READ_PRODUCT_H

using Buffer = std::stringstream;

struct ReadProduct
{
  Product* product;

  ReadProduct(Buffer& is) {
    Buffer barcode, name, price;
    product = new Product;

    is.get(*barcode.rdbuf(), '\t');
    is.get();
    is.get(*name.rdbuf(), '\t');
    is.get();
    is.get(*price.rdbuf(), '\t');

    product->name = name.str();
    barcode >> product->barcode;
    price   >> product->price;
  }
};

#endif
