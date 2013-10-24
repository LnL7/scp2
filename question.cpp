#include "question.h"

bool Question::ask(std::istream& in, std::ostream& out) { // {{{1
  out << text_ << std::endl;
  switch(type_) {
    case TextToken:   return askText(in);
    case ChoiceToken: return askChoice(in);
    default:
      std::cerr << "Error: question type `" << type_ << "'" << std::endl;
      return false;
  }
}

bool Question::decode(Decoder& coder) { // {{{1
  line_ = coder.number();
  type_ = coder.token();
  switch(type_) {
    case TextToken:   return decodeText(coder);
    case ChoiceToken: return decodeChoice(coder);
    default:          return false;
  }
}

bool Question::encode(Encoder& coder) { // {{{1
  coder.number(line_);
  coder.line(answer_);
  return true;
}

bool Question::askText(std::istream& in) { // {{{1
  getline(in, answer_);
  return !answer_.empty();
}

bool Question::askChoice(std::istream& in) { // {{{1
  int choice;
  getline(in, answer_);
  choice = atoi(answer_.c_str());
  if(choice > choices_ || choice < 1) {
    return false;
  }
  return true;
}

bool Question::decodeText(Decoder& coder) { // {{{1
  text_ = coder.line();
  return !text_.empty();
}

bool Question::decodeChoice(Decoder& coder) { // {{{1
  choices_ = coder.number();

  std::stringstream buf;
  buf << coder.line() << std::endl;
  for(int i=1; i<=choices_; i++) {
    buf << i << ") " << coder.line() << std::endl;
  }
  text_ = buf.str();
  return choices_;
}

// }}}1
