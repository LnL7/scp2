#include <igloo/igloo_alt.h>
using namespace igloo;

#include <iostream>
#include <fstream>
#include <sstream>

#include "../survey.h"

Describe(survey) {
  It(works) {
    std::istringstream data("Dries Harnie\n1\nSpelletjes Programmeren\n2\n");
    Survey s(data);

    std::ifstream in("tests/fixtures/input.txt");
    Decoder decoder(in);

    std::ostringstream out;
    Encoder encoder(out);

    s.run(decoder, encoder);
    Assert::That(out.str(), Equals("ID bb8c7729-c57c-4acb-bb35-35ecfa89e778\n1 Dries Harnie\n2 1\n3 Spelletjes Programmeren\n4 2\n"));
  }
};
