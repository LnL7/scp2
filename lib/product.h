#ifndef PRODUCT_H
#define PRODUCT_H

using String = std::string;
using UInt   = unsigned long;


struct Product
{
  String name;
  UInt barcode;
  double price;
};

#endif
