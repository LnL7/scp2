#include "survey.h"

bool Survey::run(Decoder& decoder, Encoder& encoder) { // {{{1
  header_.decode(decoder);
  header_.ask(in_, out_);
  header_.encode(encoder);
  for(int i=0; i<header_.steps; i++) {
    question_.decode(decoder);
    while(!question_.ask(in_, out_));
    out_ << "OK" << std::endl;
    question_.encode(encoder);
  }
  return true;
}

// }}}1
