#ifndef DECODER_H
#define DECODER_H

#include <iostream>
#include "token.h"

class Decoder {
  public:
    Decoder(std::istream& in) : input_(in) {}
    TokenType token();
    int number();
    const std::string& word();
    const std::string& line();
  private:
    std::string buf_;
    std::istream& input_;
};

#endif
