#include <igloo/igloo_alt.h>
using namespace igloo;

#include <iostream>
#include <sstream>

#include "../question.h"

Describe(question) {
  It(text) {
    std::istringstream in("3 TEXT Hello World");
    Decoder decoder(in);

    std::ostringstream out;
    Encoder encoder(out);

    Question q;
    q.decode(decoder);

    std::istringstream data("foo bar baz\n");
    q.ask(data, std::cout);

    q.encode(encoder);

    Assert::That(out.str(), Equals("3 foo bar baz\n"));
  }

  It(choice) {
    std::istringstream in("1 CHOICE 2 Hello World");
    Decoder decoder(in);

    std::ostringstream out;
    Encoder encoder(out);

    Question q;
    q.decode(decoder);

    std::istringstream data("2");
    q.ask(data, std::cout);

    q.encode(encoder);

    Assert::That(out.str(), Equals("1 2\n"));
  }
};
