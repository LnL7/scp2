#include "types.h"

#ifndef SHOW_H
#define SHOW_H

namespace Show {
  template< class A
          , class Show = typename A::Show >
  String show(const A& a) { return Show(a).s; }

  OString buf() {
    OString os;

    os.setf(std::ios::fixed);
    os.precision(2);
    return os;
  }
};

#endif
