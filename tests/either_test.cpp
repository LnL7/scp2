#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE either
#include <boost/test/unit_test.hpp>
#include "either.h"

using std::function;
using std::string;

using A = Either<string,int>;
using B = Either<string,bool>;

BOOST_AUTO_TEST_CASE (monad)
{
  function<B(int)> f = [](int i) { return B(i == 40); };

  const A rightA = A::Return(40).e;
  BOOST_CHECK_EQUAL
    ( A::FromRight(42, rightA).b
    , 40 );

  const B rightB = A::Bind<bool>(f, rightA).e;
  BOOST_CHECK_EQUAL
    ( B::FromRight(false, rightB).b
    , true );

  const A leftA("foo");
  const B leftB = A::Bind<bool>(f, leftA).e;
  BOOST_CHECK_EQUAL
    ( B::FromLeft("bar", leftB).a
    , "foo" );
}

BOOST_AUTO_TEST_CASE (functor)
{
  function<bool(int)> f = [](int i) { return i == 40; };

  const A rightA(40);
  const B rightB = A::Fmap<bool>(f, rightA).e;
  BOOST_CHECK_EQUAL
    ( B::FromRight(false, rightB).b
    , true );

  const A leftA("foo");
  const B leftB = A::Fmap<bool>(f, leftA).e;
  BOOST_CHECK_EQUAL
    ( B::FromLeft("bar", leftB).a
    , "foo" );
}
