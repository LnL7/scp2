#ifndef HEADER_H
#define HEADER_H

#include <string>
#include "decoder.h"
#include "encoder.h"

class Header {
  public:
    bool ask(std::istream& in, std::ostream& out);
    bool decode(Decoder& coder);
    bool encode(Encoder& coder);
    int steps;
  private:
    int version_;
    std::string id_;
};

#endif
