#ifndef SURVEY_H
#define SURVEY_H

#include <iostream>
#include "header.h"
#include "question.h"

class Survey {
  public:
    Survey(std::istream& in=std::cin, std::ostream& out=std::cout) : in_(in), out_(out) {}
    bool run(Decoder& decoder, Encoder& encoder);
  private:
    Header header_;
    Question question_;
    std::istream& in_;
    std::ostream& out_;
};

#endif
