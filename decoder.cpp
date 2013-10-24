#include "decoder.h"

TokenType Decoder::token() { // {{{1
  input_ >> buf_;
  if(buf_ == "VERSION") { return VersionToken;    }
  if(buf_ == "ID")      { return IdentifierToken; }
  if(buf_ == "STEPS")   { return StepsToken;      }
  if(buf_ == "TEXT")    { return TextToken;       }
  if(buf_ == "CHOICE")  { return ChoiceToken;     }
  std::cerr << "Error: token `" << buf_ << "'" << std::endl;
  return ErrorToken;
}

int Decoder::number() { // {{{1
  int num;
  input_ >> num;
  return num;
}

const std::string& Decoder::word() { // {{{1
  input_ >> buf_;
  return buf_;
}

const std::string& Decoder::line() { // {{{1
  getline(input_, buf_);
  return buf_;
}

// }}}1
