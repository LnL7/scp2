#ifndef ENCODER_H
#define ENCODER_H

#include <iostream>
#include "token.h"

class Encoder {
  public:
    Encoder(std::ostream& out) : output_(out) {}
    bool line(std::string str);
    bool number(int num);
    bool token(TokenType type);
  private:
    std::ostream& output_;
};

#endif
