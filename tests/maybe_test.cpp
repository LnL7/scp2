#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE maybe
#include <boost/test/unit_test.hpp>
#include "maybe.h"

using A = Maybe<int>;
using B = Maybe<bool>;

BOOST_AUTO_TEST_CASE (from_maybe)
{
  const A justA(40);
  BOOST_CHECK_EQUAL
    ( A::FromJust(42, justA).a
    , 40 );

  const A nothingA;
  BOOST_CHECK_EQUAL
    ( A::FromJust(42, nothingA).a
    , 42 );
}

BOOST_AUTO_TEST_CASE (monad)
{
  function<B(int)> f = [](int i) { return B(i == 40); };

  const A justA = A::Return(40).m;
  BOOST_CHECK_EQUAL
    ( A::FromJust(42, justA).a
    , 40 );

  const B justB = A::Bind<bool>(f, justA).m;
  BOOST_CHECK_EQUAL
    ( B::FromJust(false, justB).a
    , true );

  const A nothingA;
  const B nothingB = A::Bind<bool>(f, nothingA).m;
  BOOST_CHECK_EQUAL
    ( B::FromJust(false, nothingB).a
    , false );
}

BOOST_AUTO_TEST_CASE (functor)
{
  function<bool(int)> f = [](int i) { return i == 40; };

  const A justA(40);
  BOOST_CHECK_EQUAL
    ( A::FromJust(42, justA).a
    , 40 );

  const B justB = A::Fmap<bool>(f, justA).m;
  BOOST_CHECK_EQUAL
    ( B::FromJust(false, justB).a
    , true );

  const A nothingA;
  const B nothingB = A::Fmap<bool>(f, nothingA).m;
  BOOST_CHECK_EQUAL
    ( B::FromJust(false, nothingB).a
    , false );
}
