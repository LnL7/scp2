#include <igloo/igloo_alt.h>
using namespace igloo;

#include <iostream>
#include <sstream>

#include "../header.h"

Describe(header) {
  It(id) {
    std::istringstream in("VERSION 1\nID foo-bar-baz\nSTEPS 0");
    Decoder decoder(in);

    std::ostringstream out;
    Encoder encoder(out);

    Header h;
    h.decode(decoder);
    h.encode(encoder);

    Assert::That(out.str(), Equals("ID foo-bar-baz\n"));
  }
};
