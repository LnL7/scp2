#include <igloo/igloo_alt.h>
using namespace igloo;

#include <iostream>

#include <fstream>
#include <sstream>
#include <string>

class Survey {
  public:
    Survey(std::istream& in, std::ostringstream& out, std::istream& data=std::cin) : output_(out), data_(data), input_(in) {}
    bool run();
    int buildHeader();
    void answerText(int line, std::string& answer);
    void answerChoise(int line, int answers, int& answer);
  private:
    std::string buf_;
    std::ostream& output_;
    std::istream& data_;
    std::istream& input_;
};

bool Survey::run() {
  int steps(buildHeader());

  while(steps > 0) {
    int line(0);
    std::string text;

    input_ >> line;
    input_ >> buf_;
    if(buf_ == "TEXT") {
      getline(input_, text);
      std::cout << text << std::endl;

      std::string answer;
      std::cout << "> ";
      answerText(line, answer);
      output_ << line << " " << answer << std::endl;

    } else if(buf_ == "CHOICE") {
      int answers;
      std::stringstream stream;
      input_ >> answers;
      getline(input_, text);
      for(int i=1; i<=answers; i++) {
        getline(input_, buf_);
        stream << i << ") " << buf_ << std::endl;
      }

      std::cout << text << std::endl;
      std::cout << stream.rdbuf();

      int answer;
      std::cout << "> ";
      answerChoise(line, answers, answer);
      output_ << line << " " << answer << std::endl;

    } else {
      std::cerr << "Error: question" << std::endl;
      return false;
    }
    steps--;
  }
  return true;
}

int Survey::buildHeader() {
  int version(0);
  int steps(0);
  std::string id("");

  input_ >> buf_;
  if(buf_ != "VERSION") {
    std::cerr << "Error: version" << std::endl;
    return false;
  }
  input_ >> version;
  getline(input_, buf_);

  input_ >> buf_;
  if(buf_ != "ID") {
    std::cerr << "Error: id" << std::endl;
    return false;
  }
  input_ >> id;
  getline(input_, buf_);

  input_ >> buf_;
  if(buf_ != "STEPS") {
    std::cerr << "Error: steps" << std::endl;
    return false;
  }
  input_ >> steps;
  getline(input_, buf_);

  return steps;
}

void Survey::answerText(int line, std::string& answer) {
  getline(data_, answer);
}

void Survey::answerChoise(int line, int answers, int& answer) {
  data_ >> answer;
  getline(data_, buf_);
}

Describe(survey) {
  It(works) {
    std::ostringstream out;
    std::istringstream data("Dries Harnie\n1\nSpelletjes Programmeren\n2\n");
    std::ifstream file("tests/fixtures/input.txt");
    Survey s(file, out, data);
    Assert::That(s.run(), Equals(true));
    std::cout << std::endl << std::endl << out.str();
  }
};
