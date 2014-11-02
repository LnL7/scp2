#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../lib/run_input.h"


TEST(Product, ReadingProducts)
{
  Buffer s("5449000000996\tCoca-Cola 33cl blik\t1.00\n4333465106205\tZakdoekjes\t0.30\n9780321563842\tThe C++ Programming Language, 4th Edition\t17.90");

  ReadLines l(s);
  ReadProduct fst(*l.lines[0])
            , snd(*l.lines[1])
            , trd(*l.lines[2]);
  EXPECT_EQ("Coca-Cola 33cl blik", fst.product->name);
  EXPECT_EQ(4333465106205, snd.product->barcode);
  EXPECT_EQ(17.90, trd.product->price);
}

TEST(Product, CollectingProducts)
{
  Buffer s("5449000000996\tCoca-Cola 33cl blik\t1.00\n4333465106205\tZakdoekjes\t0.30\n9780321563842\tThe C++ Programming Language, 4th Edition\t17.90");
  auto p = CollectProducts(ReadLines(s).lines).products;

  EXPECT_EQ(5449000000996, p[5449000000996]->barcode);
  EXPECT_EQ(4333465106205, p[4333465106205]->barcode);
  EXPECT_EQ(9780321563842, p[9780321563842]->barcode);
}

TEST(Product, UserInput)
{
  Buffer i("5449000000996\t4\n9780321563842\t1\n.\n");
  Buffer s("5449000000996\tCoca-Cola 33cl blik\t1.00\n4333465106205\tZakdoekjes\t0.30\n9780321563842\tThe C++ Programming Language, 4th Edition\t17.90");
  RunInput main(i, s);

  Buffer o;
  main.run(o);
  EXPECT_EQ("4\tCoca-Cola 33cl blik\t4\n1\tThe C++ Programming Language, 4th Edition\t17.9\nTotal\t21.9\n", o.str());
};

GTEST_API_ int main(int argc, char** argv) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
