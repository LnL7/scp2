#include <sstream>

#ifndef READ_LINES_H
#define READ_LINES_H
#define EOL '\n'

using std::vector;
using Input  = std::istream;
using Buffer = std::stringstream;

struct ReadLines
{
  vector<Buffer*> lines;

  ReadLines(Input& is) {
    Buffer* buf;
    do {
      buf = new Buffer;
      is.get(*buf->rdbuf(), EOL);
      lines.push_back(buf);
    } while (is.get() == EOL);
  }

  ~ReadLines() {
    for(auto l : lines) { delete l; }
  }
};

#endif
