#include "encoder.h"

bool Encoder::line(std::string str) { // {{{1
  return output_ << str << std::endl;
}

bool Encoder::number(int num) { // {{{1
  return output_ << num << " ";
}

bool Encoder::token(TokenType type) { // {{{1
  switch(type) {
    case VersionToken:    return output_ << "VERSION ";
    case IdentifierToken: return output_ << "ID ";
    case StepsToken:      return output_ << "STEPS ";
    case TextToken:       return output_ << "TEXT ";
    case ChoiceToken:     return output_ << "Choice ";
    default:
      std::cerr << "Error: token `" << type << "'" << std::endl;
      return false;
  }
}

// }}}1
