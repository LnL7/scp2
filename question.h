#ifndef QUESTION_H
#define QUESTION_H

#include <sstream>
#include "decoder.h"
#include "encoder.h"

class Question {
  public:
    bool ask(std::istream& in, std::ostream& out);
    bool decode(Decoder& coder);
    bool encode(Encoder& coder);
  private:
    bool askText(std::istream&);
    bool askChoice(std::istream&);
    bool decodeText(Decoder& coder);
    bool decodeChoice(Decoder& coder);
    TokenType type_;
    int choices_;
    int line_;
    std::string answer_;
    std::string text_;
};

#endif
