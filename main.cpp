#include <fstream>
#include "survey.h"

int main(int argc, const char *argv[]) {
  if(argc != 3) {
    std::cout << "Usage: " << argv[0] << " [INPUT] [OUTPUT]" << std::endl;
    return 1;
  }
  std::ifstream in(argv[1]);
  std::ofstream out(argv[2]);
  Decoder decoder(in);
  Encoder encoder(out);
  Survey s;

  s.run(decoder, encoder);
  return 0;
}
