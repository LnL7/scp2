#include "header.h"

bool Header::ask(std::istream& in, std::ostream& out) {
  return out << "Deze enquete bestaat uit " << steps << " vragen" << std::endl;
}

bool Header::decode(Decoder& coder) { // {{{1
  if(coder.token() != VersionToken) {
    return false;
  }
  version_ = coder.number();
  coder.line();
  if(coder.token() != IdentifierToken) {
    return false;
  }
  id_ = coder.word();
  coder.line();
  if(coder.token() != StepsToken) {
    return false;
  }
  steps = coder.number();
  return true;
}

bool Header::encode(Encoder& coder) { // {{{1
  coder.token(IdentifierToken);
  coder.line(id_);
  return true;
}

// }}}1
